#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "GL/stb_image.h"
#include<iostream>
using namespace std;

//
static GLfloat testxoayxe = 0.0;
#define PI 3.14159
#define BIKE_LENGTH 3.3f  //<------
#define HANDLE_LIMIT 30.0f
#define INC_STEERING 2.0f
#define INC_SPEED 0.05f
GLfloat xpos, zpos, direction;
static GLfloat spin = 0.0;

GLfloat speed, steering;
GLfloat degrees(GLfloat a)
{
    return a * 180.0f / PI;
}

GLfloat radians(GLfloat a)
{
    return a * PI / 180.0f;
}

GLfloat angleSum(GLfloat a, GLfloat b)
{
    a += b;
    if (a < 0) return a + 2 * PI;
    else if (a > 2 * PI) return a - 2 * PI;
    else return a;
}
void updateScene()
{
    GLfloat xDelta, zDelta;
    GLfloat rotation;
    GLfloat sin_steering, cos_steering;
    if (-INC_SPEED < speed && speed < INC_SPEED)
        return;
    if (speed < 0.0f)
        speed = 0.0f;

    xDelta = speed * cos(radians(direction + steering));
    zDelta = speed * sin(radians(direction + steering));
    xpos += xDelta;
    zpos -= zDelta;
    //pedalAngle = degrees(angleSum(radians(pedalAngle), speed / RADIUS_WHEEL));
    sin_steering = sin(radians(steering));
    cos_steering = cos(radians(steering));

    rotation = atan2(speed * sin_steering, BIKE_LENGTH + speed * cos_steering);
    direction = degrees(angleSum(radians(direction), rotation));
    //
    spin = spin + 1.0 + speed *10*2; 
    if (spin > 360.0)
        spin = spin - 360.0;
}
// gia tri cac mau
int light_value = 0;
GLfloat qaBlack[] = { 0,0,0,1.0 };
GLfloat qaGreen[] = { 0,1.0,0,1.0 };
GLfloat qaRed[] = { 1.0,0,0,1.0 };
GLfloat qaBlue[] = { 0,0,1.0,1.0 };
GLfloat qaWhite[] = { 1.0,1.0,1.0,1.0 };
GLfloat qaYellow[] = { 1.0,1.0,0,1.0 };
GLfloat qaGrey[] = { 0.5,0.5,0.5,0.5 };
GLfloat qaLowAmbient[] = { 0.2,0.2,0.2,1.0 };
GLfloat qaFullAmbient[] = { 1.0,1.0,1.0,1.0 };
// texture
unsigned int texName;
unsigned int texName1;
GLint grass;
int Flag1 = 0;
unsigned int ID;
void LoadTexture(const char* filename) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //const char* file = "matDoVantoc24.bmp";
    int width = 50, height = 50, channels = 0;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
        stbi_set_flip_vertically_on_load(true);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
}
GLuint loadimage(const char* fileName)
{
    FILE* file;
    unsigned char header[54], * data;
    unsigned int dataPos, size, width, height;
    #pragma warning(disable:4996)
    file = fopen(fileName, "rb");
    fread(header, 1, 54, file);
    dataPos = *(int*)&(header[0x0A]);
    size = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);
    if (size == NULL)
        size = width * height * 3;
    if (dataPos == NULL)
        dataPos = 54;
    data = new unsigned char[size];
    fread(data, 1, size, file);
    fclose(file);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
    return texture;
}

// test cam
GLfloat camx = 10.0, camy= 0.0, camz=15.0;

//int x,y,z;
// camera attributes
float viewerPosition[3] = { 0.0, 0.0, -20.0 };
float viewerDirection[3] = { 0.0, 0.0, 0.0 };
float viewerUp[3] = { 0.0, 1.0, 0.0 };

// rotation values for the navigation
float navigationRotation[3] = { 0.0, 0.0, 0.0 };
int mousePressedX = 0, mousePressedY = 0;
float lastXOffset = 0.0, lastYOffset = 0.0, lastZOffset = 0.0;
// mouse button states
int leftMouseButtonActive = 0, middleMouseButtonActive = 0, rightMouseButtonActive = 0;
// modifier state
int shiftActive = 0, altActive = 0, ctrlActive = 0;


//
void init(void) {
    //glClearColor(0.2, 0.2, 0.2, 1.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    //GLfloat qaAmbientLight[] = { 0.2,0.2,0.2,1.0 };
    //GLfloat qaDiffuseLight[] = { 0.8,0.8,0.8,1.0 };
    //GLfloat qaSpeculartLight[] = { 1.0,1.0,1.0,1.0 };

    //glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpeculartLight);

    //// diem chieu sang
    //GLfloat qaLightPos[] = { 4.0, 4.0, 10.0, 0.0 };
    //glLightfv(GL_LIGHT0, GL_POSITION, qaLightPos);
}
void lighting() // FUNCTION FOR LIGHTING
{
    glClearColor(0.2, 0.2, 0.2, 1.0);
    // printf("%s\n", "YESS ");
    GLfloat light_directional[] = { 1.0,1.0,1.0,1.0 };
    GLfloat light_positional[] = { 1.0,1.0,1.0,1.0 };
    GLfloat light_diffuse[] = { 0.8,0.8,0.8,1.0 };
    GLfloat light_ambient[] = { 0.2,0.2,0.2,1.0 };

    if (light_value == 0) {
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_POSITION, light_positional);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    }
    else if (light_value == 1) {
        glLightfv(GL_LIGHT0, GL_POSITION, light_positional);
    }
    else if (light_value == 2) {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    }
    else if (light_value == 3) {
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
        // only ambient
    }
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}
void maugoc() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGreen);
    glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
    glMaterialfv(GL_LIGHT0, GL_AMBIENT, qaLowAmbient);
}

// to mau
void toMau(GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat shininess, GLfloat lowAmbient[]) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_LIGHT0, GL_AMBIENT, lowAmbient);
}

void DrawCoordinate()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); // red x
    glVertex3f(-20.0, 0.0, 0.0);
    glVertex3f(20.0, 0.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0); // green y
    glVertex3f(0.0, -20.0, 0.0);
    glVertex3f(0.0, 20.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0); // blue z
    glVertex3f(0.0, 0.0, -20.0);
    glVertex3f(0.0, 0.0, 20.0);
    glEnd();

    glEnable(GL_LIGHTING);
}

// ham tai su dung
// ham ve duong tron fill mau
void DrawCircle(float cx, float cy, float r, int num_segments, float cphx, float cphy, float cphz) {
    glBegin(GL_POLYGON);
    glNormal3f(cphx, cphy, cphz);
    for (int ii = 0; ii < num_segments; ii++) {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 
        glVertex2f(x + cx, y + cy);//output vertex 
    }
    glEnd();
}
// denxe
void denxe(int rev) {
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0, 0);
    glVertex3f(3, 2, 1);
    glVertex3f(3, 2.5, 1);
    glVertex3f(3, 2.5, 0);
    glVertex3f(3, 2, 0);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-0.05, 1.0, 0);
    glVertex3f(2, 2, 2);
    glVertex3f(3, 2.5, 1);
    glVertex3f(3, 2.5, 0);
    glVertex3f(2, 2, 0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(0.5, 0.0, 0.75);
    glVertex3f(3, 2, 1);
    glVertex3f(2, 2, 2);
    glVertex3f(3, 2.5, 1);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(0.5, 0.0, 0.75);
    glVertex3f(3, 1.5, 1);
    glVertex3f(3.5, 1, 1.5);
    glVertex3f(2, 0, 2);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0, 0.0, 1.0);
    glVertex3f(3.5, 1, 1.5);
    glVertex3f(2, 0, 2);
    glVertex3f(3.5, -2.25, 1.5);
    glVertex3f(4, -2, 1.5);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-0.05, 0.0, 1.0);
    glVertex3f(3.5, -2.25, 1.5);
    glVertex3f(2, -2, 2);
    glVertex3f(1, 0, 2);
    glVertex3f(2.0, 0, 2.0);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1, 0.0, 0.0);
    glVertex3f(2, -2, 2);
    glVertex3f(1, 0, 2);
    glVertex3f(1, 0, 0);
    glVertex3f(2, -2, 0);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0, -1.0, 0.0);
    glVertex3f(3.5, -2.25, 1.5);
    glVertex3f(2, -2, 2);
    glVertex3f(2, -2, 0);
    glVertex3f(3.5, -2.25, 0);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0, -1.0, 0.0);
    glVertex3f(4, -2, 1.5);
    glVertex3f(3.5, -2.25, 1.5);
    glVertex3f(3.5, -2.25, 0);
    glVertex3f(4, -2, 0);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0.5, 1.0, 0.0);
    glVertex3f(3, 1.5, 1);
    glVertex3f(3.5, 1, 1.5);
    glVertex3f(3.5, 1, 0);
    glVertex3f(3, 1.5, 0);
    glEnd();
    
    if (rev == 1) {
        glScalef(1.0, 1.0, -1.0);
        denxe(0);
    }
}
void denXePlus() {
    glEnable(GL_TEXTURE_2D);

    LoadTexture("denxe.bmp");
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    //glColor3f(1,1,0);
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.00  + 0.11, 0.0 - 0.02); glVertex3f(3.5, 1, 1.5);
    glTexCoord2f(0.00  + 0.11, 1.0 - 0.02); glVertex3f(4, -2, 1.5);
    glTexCoord2f(0.75  + 0.11, 1.0 - 0.02); glVertex3f(4, -2, -1.5);
    glTexCoord2f(0.75  + 0.11, 0.0 - 0.02); glVertex3f(3.5, 1, -1.5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
// dau xe 
void dauxe() {
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0, 1.0);
    glVertex3f(0, 0, 2.0);
    glVertex3f(2, 0, 2);
    glVertex3f(2, 2, 2);
    glVertex3f(0, 2, 2);

    glNormal3f(0.15, 0.0, 1.0);
    glVertex3f(2.0, 0, 2.0);
    glVertex3f(3, 0, 1.0);
    glVertex3f(3, 2, 1);
    glVertex3f(2, 2, 2);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(3.0, 0, 1.0);
    glVertex3f(3, 0, -1.0);
    glVertex3f(3, 2, -1);
    glVertex3f(3, 2, 1);

    glNormal3f(0.15, 0, -1.0);
    glVertex3f(3.0, 0, -1.0);
    glVertex3f(2, 0, -2.0);
    glVertex3f(2, 2, -2);
    glVertex3f(3, 2, -1);

    glNormal3f(0.0, 0, 1.0);
    glVertex3f(0.0, 0, -2.0);
    glVertex3f(2, 0, -2.0);
    glVertex3f(2, 2, -2);
    glVertex3f(0, 2, -2);

    glNormal3f(-1.0, 0.0, 0);
    glVertex3f(0.0, 0, -2.0);
    glVertex3f(0, 2, -2.0);
    glVertex3f(0, 2, 2);
    glVertex3f(0, 0, 2);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    LoadTexture("matDoVantoc24.bmp");
    glBindTexture(GL_TEXTURE_2D, texName);
    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.00 + 0.01, 0.0 + 0.18);glVertex3f(0, 2, -2);
    glTexCoord2f(0.00 + 0.01, 0.5 + 0.18);glVertex3f(2, 2, -2);
    glTexCoord2f(0.25 + 0.01, 0.75 + 0.18);glVertex3f(3, 2.5, -1);
    glTexCoord2f(0.75 + 0.01, 0.75 + 0.18); glVertex3f(3, 2.5, 1.0);
    glTexCoord2f(1.0 + 0.01, 0.5 + 0.18); glVertex3f(2.0, 2, 2.0);
    glTexCoord2f(1.0 + 0.01, 0.0 + 0.18); glVertex3f(0.0, 2, 2.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, 0, 2.0);
    glVertex3f(2.0, 0, 2.0);
    glVertex3f(3, 0, 1.0);
    glVertex3f(3, 0, -1);
    glVertex3f(2, 0, -2);
    glVertex3f(0, 0, -2);
    glEnd();

    glPushMatrix();
    denxe(1);
    glRotatef(10, 0.0, 0.0, 1.0);
    glTranslatef(0, -1.15, 0);
    glRotatef(180,1.0,0,0);
    glTranslatef(0,1.15,0);
    glRotatef(-10, 0.0, 0.0, 1.0);
    denXePlus();
    glPopMatrix();
    
}


// tay ga
void tayga() {
    glPushMatrix();
    GLUquadricObj* quadratic_obj;
    quadratic_obj = gluNewQuadric();
    //glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(quadratic_obj, 0.5, 0.5, 4, 32, 32);

    glutSolidTorus(0.2, 0.35, 32, 32);

    glTranslatef(0, 0, 3.9);
    glutSolidTorus(0.2, 0.35, 32, 32);
    glTranslatef(0, 0, 0.15);
    DrawCircle(0, 0, 0.4, 32, 0, 0, 1.0);
    glPopMatrix();
}
// phanh
void phanh() {
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1.0);
    glVertex3f(2, 1, 5);
    glVertex3f(2.2, 1, 5);
    glVertex3f(2, 1, 2);
    glVertex3f(1.8, 1, 2);

    glNormal3f(0, 1.0, 0.0);
    glVertex3f(2.2, 1, 5);
    glVertex3f(2, 1, 2);
    glVertex3f(2, 1.2, 2);
    glVertex3f(2.2, 1.2, 5);

    glNormal3f(0, 0, 1.0);
    glVertex3f(2.2, 1.2, 5);
    glVertex3f(2, 1.2, 2);
    glVertex3f(1.8, 1.2, 2);
    glVertex3f(2, 1.2, 5);

    glNormal3f(1.0, 0, 0.0);
    glVertex3f(2, 1.2, 5);
    glVertex3f(1.8, 1.2, 2);
    glVertex3f(1.8, 1, 2);
    glVertex3f(2, 1, 5);

    glNormal3f(1.0, 0, 0.0);
    glColor3f(1.0, 0, 0);
    glVertex3f(2.2, 1, 5);
    glVertex3f(2.2, 1.2, 5);
    glVertex3f(2, 1.2, 5);
    glVertex3f(2, 1, 5);
    glEnd();

    glTranslatef(2.1, 1.1, 5);
    glColor3f(0.1, 0.5, 0);
    glutSolidSphere(0.2, 20, 20);
}

//dua banh xe
void duabanhxe() {
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1.0);
    glVertex3f(0.05, -3, 0.05);
    glVertex3f(0.05, -3, -0.05);
    glVertex3f(-0.05, -3, -0.05);
    glVertex3f(-0.05, -3, 0.05);

    glNormal3f(0, 1.0, 0.0);
    glVertex3f(0.05, -3, 0.05);
    glVertex3f(0.05, -3, -0.05);
    glVertex3f(0.05, 3, -0.05);
    glVertex3f(0.05, 3, 0.05);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(0.05, -3, -0.05);
    glVertex3f(-0.05, -3, -0.05);
    glVertex3f(-0.05, 3, -0.05);
    glVertex3f(0.05, 3, -0.05);

    glNormal3f(0, 1.0, 0.0);
    glVertex3f(-0.05, -3, -0.05);
    glVertex3f(-0.05, -3, 0.05);
    glVertex3f(-0.05, 3, 0.05);
    glVertex3f(-0.05, 3, -0.05);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(-0.05, -3, 0.05);
    glVertex3f(0.05, -3, 0.05);
    glVertex3f(0.05, 3, 0.05);
    glVertex3f(-0.05, 3, 0.05);

    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.05, 3, 0.05);
    glVertex3f(0.05, 3, -0.05);
    glVertex3f(-0.05, 3, -0.05);
    glVertex3f(-0.05, 3, 0.05);
    glEnd();
}
// bien the tu dua banh xe
void TanNhietDongCoXe(float h) {
    glBegin(GL_QUADS);
    glNormal3f(0, 1.0, 0.0);
    glVertex3f(0.05, 0, 0.05);
    glVertex3f(0.05, 0, -0.05);
    glVertex3f(-0.05, 0, -0.05);
    glVertex3f(-0.05, 0, 0.05);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(0.05, 0, 0.05);
    glVertex3f(0.05, 0, -0.05);
    glVertex3f(0.05, h, -0.05);
    glVertex3f(0.05, h, 0.05);

    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.05, 0, -0.05);
    glVertex3f(-0.05, 0, -0.05);
    glVertex3f(-0.05, h, -0.05);
    glVertex3f(0.05, h, -0.05);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(-0.05, 0, -0.05);
    glVertex3f(-0.05, 0, 0.05);
    glVertex3f(-0.05, h, 0.05);
    glVertex3f(-0.05, h, -0.05);

    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-0.05, 0, 0.05);
    glVertex3f(0.05, 0, 0.05);
    glVertex3f(0.05, h, 0.05);
    glVertex3f(-0.05, h, 0.05);

    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.05, h, 0.05);
    glVertex3f(0.05, h, -0.05);
    glVertex3f(-0.05, h, -0.05);
    glVertex3f(-0.05, h, 0.05);
    glEnd();
}
//truc banh xe
void trucbanhxe() {
    GLUquadricObj* quadratic_obj;
    quadratic_obj = gluNewQuadric();

    //glTranslatef(0.0, 0.0, 8.0);
    //glTranslatef(0.0,0.0,2.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(quadratic_obj, 0.5, 0.5, 2, 32, 32);
}
// banhxe 
void DrawRims()
{
    glColor3f(0.75, 0.75, 0.75);
    glTranslatef(3.0, -8.0, 0);
    glutSolidTorus(1, 3, 16, 64);

    for (int i = 0;i < 10;i++) {
        glRotatef(20, 0, 0, 1.0);
        duabanhxe();
    }
}
// giam soc truoc
void giamsoctruoc(int gocxoay) {
    GLUquadricObj* quadratic_obj;
    quadratic_obj = gluNewQuadric();

    glTranslatef(1.0, 0.0, 1.5);
    glRotatef(gocxoay, 0.0, 0.0, 1.0);
    glRotatef(90, 1.0, 0.0, 0.0);

    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    gluCylinder(quadratic_obj, 0.5, 0.5, 5, 32, 32);
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    gluCylinder(quadratic_obj, 0.3, 0.3, 8, 32, 32);
    //
    glTranslatef(0.0, 0.0, 8.0);
    glutSolidSphere(0.5, 20, 20);
    //
    trucbanhxe();
}

// truc giua chinh dau xe
void TrucChinhDauXe() {
    GLUquadricObj* quadratic_obj;
    quadratic_obj = gluNewQuadric();

    glTranslatef(1.0, 0.0, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(quadratic_obj, 0.4, 0.4, 3, 32, 32);

    glTranslatef(0.0, 0, 1.0);
    gluCylinder(quadratic_obj, 0.5, 0.5, 1, 32, 32);

    glutSolidSphere(0.5, 20, 20);
    glTranslatef(0.0, 0, 1.05);
    glutSolidSphere(0.5, 20, 20);
    glTranslatef(0.0, 0, 1.05);
    glutSolidSphere(0.4, 20, 20);
}

//chắn bùn ở bánh xe trước
void chanBunTruoc(int rev) {
    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.05, 0.0);
    glVertex3f(-1, -6, 1.25);
    glVertex3f(0, -4.75, 1.25);
    glVertex3f(0, -4.75, 0);
    glVertex3f(-1, -6, 0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.05, 0.0);
    glVertex3f(0, -4.75, 1.25);
    glVertex3f(2, -3.5, 1.25);
    glVertex3f(2, -3.5, 0);
    glVertex3f(0, -4.75, 0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.05, 0.0);
    glVertex3f(2, -3.5, 1.25);
    glVertex3f(5, -4, 1.25);
    glVertex3f(5.75, -4, 0);
    glVertex3f(2, -3.5, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0, 1.0);
    glVertex3f(5, -4, 1.25);
    glVertex3f(2, -3.5, 1.25);
    glVertex3f(0, -4.75, 1.25);
    glVertex3f(-1, -6, 1.25);
    //
    glVertex3f(2.5, -5.75, 1.25);
    //
    glVertex3f(3, -8, 1.25);
    glEnd();

    if (rev == 1) {
        glScalef(1.0, 1.0, -1.0);
        chanBunTruoc(0);
    }
}
// final dau xe
void fulldauxe() {
    // dau xe + tay ga
    glPushMatrix();
    toMau(qaRed, qaRed, qaWhite, 128.0, qaLowAmbient);
    dauxe();
    glTranslatef(0, 0, 2);
    glTranslatef(1.0, 1.0, 0.0);
    maugoc();
    // tay ga
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    tayga();
    glTranslatef(0, 0, -4);
    glRotatef(-180, 1.0, 0.0, 0.0);
    tayga();
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    glPopMatrix();
    maugoc();

    // phanh phải
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    phanh();
    glPopMatrix();
    maugoc();
    // phanh trai
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glScalef(1.0, 1.0, -1.0);
    phanh();
    glPopMatrix();
    maugoc();
    //giam soc truoc
    // ben phai
    glPushMatrix();
    giamsoctruoc(15);
    glPopMatrix();
    // ben trai
    glPushMatrix();
    glScalef(1.0, 1.0, -1.0);
    giamsoctruoc(15);
    glPopMatrix();

    //banh xe
    // to lai mau cho banh xe
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    glPushMatrix();
    glTranslatef(3.0, -8.0, 0);
    glRotatef(-spin, 0, 0, 1); 
    glTranslatef(-3.0, 8.0, 0);
    DrawRims();
    glPopMatrix();

    // chan bun
    maugoc();
    glPushMatrix();
    toMau(qaRed, qaRed, qaWhite, 128.0, qaLowAmbient);
    // update
    chanBunTruoc(1);
    glPopMatrix();
    maugoc();

    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    TrucChinhDauXe();
    glPopMatrix();
}
//////////////////
/// than xe
////////////////
// ham tai su dung
// vẽ hình chữ nhật 
// h: độ rộng theo trục x
// w: chiều cao y
// size : tăng nhanh kích thước trục x
void cubefill(float h, float w, float size) {
    glBegin(GL_QUADS);
    // x
    glNormal3f(0, 0, 1.0);
    glVertex3f(-1.0 * h * size, 0.0, 1.0 * h);
    glVertex3f(1.0 * h * size, 0.0, 1.0 * h);
    glVertex3f(1.0 * h * size, 1.0 * w, 1.0 * h);
    glVertex3f(-1.0 * h * size, 1.0 * w, 1.0 * h);
    // duoi
    glNormal3f(0, 0, -1.0);
    glVertex3f(-1.0 * h * size, 0.0, -1.0 * h);
    glVertex3f(1.0 * h * size, 0.0, -1.0 * h);
    glVertex3f(1.0 * h * size, 1.0 * w, -1.0 * h);
    glVertex3f(-1.0 * h * size, 1.0 * w, -1.0 * h);
    // y
    glNormal3f(-1.0, 0.0, 0);
    glVertex3f(-1.0 * h * size, 0.0, -1.0 * h);
    glVertex3f(-1.0 * h * size, 1.0 * w, -1.0 * h);
    glVertex3f(-1.0 * h * size, 1.0 * w, 1.0 * h);
    glVertex3f(-1.0 * h * size, 0.0, 1.0 * h);
    //mat phai yz
    glNormal3f(1.0, 0.0, 0);
    glVertex3f(1.0 * h * size, 0.0, 1.0 * h);
    glVertex3f(1.0 * h * size, 0.0, -1.0 * h);
    glVertex3f(1.0 * h * size, 1.0 * w, -1.0 * h);
    glVertex3f(1.0 * h * size, 1.0 * w, 1.0 * h);
    // z
    glNormal3f(0, -1.0, 0.0);
    glVertex3f(1.0 * h * size, 0.0, 1.0 * h);
    glVertex3f(1.0 * h * size, 0.0, -1.0 * h);
    glVertex3f(-1.0 * h * size, 0.0, -1.0 * h);
    glVertex3f(-1.0 * h * size, 0.0, 1.0 * h);
    // mat tren zx
    glNormal3f(0, 1.0, 0.0);
    glVertex3f(1.0 * h * size, 1.0 * w, 1.0 * h);
    glVertex3f(1.0 * h * size, 1.0 * w, -1.0 * h);
    glVertex3f(-1.0 * h * size, 1.0 * w, -1.0 * h);
    glVertex3f(-1.0 * h * size, 1.0 * w, 1.0 * h);
    glEnd();
}
// truc chinh than xe
void trucChinhThanXe() {
    GLUquadricObj* quadratic_obj;
    quadratic_obj = gluNewQuadric();

    glTranslatef(5.0, 0.0, 0);
    glRotatef(-90, 0.0, 1.0, 0.0);
    gluCylinder(quadratic_obj, 0.4, 0.4, 18, 32, 32);

    glRotatef(30, 1.0, 0.0, 0.0);
    gluCylinder(quadratic_obj, 0.4, 0.4, 15, 32, 32);

    glTranslatef(0, 0, 10.0);
    glRotatef(-75, 1.0, 0, 0);
    glRotatef(-30, 1.0, 0.0, 0.0);
    gluCylinder(quadratic_obj, 0.4, 0.4, 5, 32, 32);


    glTranslatef(0, -5.0, 0);
    glTranslatef(0, 0, -1);
    glutSolidSphere(0.7, 20, 20);
    gluCylinder(quadratic_obj, 0.4, 0.4, 8, 32, 32);
    glTranslatef(-2.0, 0.0, 0.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    gluCylinder(quadratic_obj, 0.4, 0.4, 4, 32, 32);
}
// khop noi ban sau voi than xe
void updateKhopNoiBanhSau(int rev) {
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-12, -2, 1.5);
    glVertex3f(-13, -5, 1.5);
    glVertex3f(-7.5, -5, 2);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-12, -2, 1.5);
    glVertex3f(-13, -3, 1.5);
    glVertex3f(-15, -2, 1.5);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.05, 1.0, 0.0);
    glVertex3f(-7.5, -5, 2);
    glVertex3f(-12, -2, 1.5);
    glVertex3f(-12, -2, 0);
    glVertex3f(-7.5, -5, 0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-12, -2, 1.5);
    glVertex3f(-15, -2, 1.5);
    glVertex3f(-15, -2, 0);
    glVertex3f(-12, -2, 0);
    glEnd();

    if (rev == 1) {
        glScalef(1.0, 1.0, -1.0);
        updateKhopNoiBanhSau(0);
    }
}
void khopNoiBanhsau() {

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-8, -6.3, 2.0);
    glVertex3f(-7, -8.3, 2.0);
    glVertex3f(-14, -8.3, 2.0);
    glVertex3f(-15, -6.3, 2.0);

    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-8, -6.3, 1.5);
    glVertex3f(-7, -8.3, 1.5);
    glVertex3f(-14, -8.3, 1.5);
    glVertex3f(-15, -6.3, 1.5);

    glNormal3f(1.0, 0.0, 0);
    glVertex3f(-8, -6.3, 2);
    glVertex3f(-8, -6.3, 1.5);
    glVertex3f(-7, -8.3, 1.5);
    glVertex3f(-7, -8.3, 2);

    glNormal3f(-1.0, 0.0, 0);
    glVertex3f(-15, -6.3, 2);
    glVertex3f(-15, -6.3, 1.5);
    glVertex3f(-14, -8.3, 1.5);
    glVertex3f(-14, -8.3, 2);

    glNormal3f(0, 1.0, 0.0);
    glVertex3f(-8, -6.3, 2);
    glVertex3f(-8, -6.3, 1.5);
    glVertex3f(-15, -6.3, 1.5);
    glVertex3f(-15, -6.3, 2);

    glNormal3f(0, -1.0, 0.0);
    glVertex3f(-7, -8.3, 2);
    glVertex3f(-7, -8.3, 1.5);
    glVertex3f(-14, -8.3, 1.5);
    glVertex3f(-14, -8.3, 2);
    glEnd();
}

// yen xe 
// ham ve do nhap nho cua yen
void yenNhapNho() {
    glPushMatrix();
    GLUquadricObj* quadratic_obj;
    quadratic_obj = gluNewQuadric();
    glTranslatef(-1.5, 0.0, 0);
    glTranslatef(0, 1.5, 0);
    gluCylinder(quadratic_obj, 1, 1, 2, 32, 32);
    glTranslatef(0, 0.0, 2);
    DrawCircle(0, 0, 1, 100, 0, 0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, 0.0, 0);
    glTranslatef(0, 1.0, 0);
    gluCylinder(quadratic_obj, 1, 1, 2, 32, 32);
    glTranslatef(0, 0.0, 2);
    DrawCircle(0, 0, 1, 100, 0, 0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, 0.0, 0);
    glTranslatef(0, 1.0, 0);
    gluCylinder(quadratic_obj, 0.5, 0.5, 2, 32, 32);
    glTranslatef(0, 0.0, 2);
    DrawCircle(0, 0, 0.5, 100, 0, 0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2, 0.0, 0);
    glTranslatef(0, 0.7, 0);
    gluCylinder(quadratic_obj, 0.5, 0.5, 2.0, 32, 32);
    glTranslatef(0, 0.0, 2);
    DrawCircle(0, 0, 0.5, 100, 0, 0, 1.0);
    glPopMatrix();
}
// yen xe full
void yenXe() {
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1.0);
    glVertex3f(-5, 2.25, 2.0);
    glVertex3f(-2.5, 2.5, 2.0);
    glVertex3f(-1.5, 2.5, 2.0);
    glVertex3f(0.0, 1, 2.0);
    glVertex3f(0, 0, 2.0);
    glVertex3f(-5, 0, 2.0);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1.0);
    glVertex3f(-5, 0, -2.0);
    glVertex3f(0, 0, -2.0);
    glVertex3f(0.0, 1, -2.0);
    glVertex3f(-1.5, 2.5, -2.0);
    glVertex3f(-2.5, 2.5, -2.0);
    glVertex3f(-5, 2.25, -2.0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0, 0.0);
    glVertex3f(-5, 2.25, 2.0);
    glVertex3f(-5, 2.25, -2.0);
    glVertex3f(-5, 0, -2.0);
    glVertex3f(-5, 0, 2.0);

    glNormal3f(-0.02, 1.0, 0.0);
    glVertex3f(-5, 2.25, 2.0);
    glVertex3f(-5, 2.25, -2.0);
    glVertex3f(-2.5, 2.5, -2.0);
    glVertex3f(-2.5, 2.5, 2.0);

    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-2.5, 2.5, -2.0);
    glVertex3f(-2.5, 2.5, 2.0);
    glVertex3f(-1.5, 2.5, 2.0);
    glVertex3f(-1.5, 2.5, -2.0);

    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-5, 0, 2.0);
    glVertex3f(0, 0, 2.0);
    glVertex3f(0, 0, -2.0);
    glVertex3f(-5, 0, -2.0);

    glNormal3f(0.5, 0.0, 0.0);
    glVertex3f(-1.5, 2.5, 2.0);
    glVertex3f(0, 1, 2.0);
    glVertex3f(0, 1, -2.0);
    glVertex3f(-1.5, 2.5, -2.0);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(0, 1, 2.0);
    glVertex3f(0, 0, 2.0);
    glVertex3f(0, 0, -2.0);
    glVertex3f(0, 1, -2.0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0);
    glVertex3f(0, 0, 2.0);
    glVertex3f(2, 0, 2);
    glVertex3f(2, 0, -2);
    glVertex3f(0, 0, -2.0);

    glNormal3f(0.0, 1.0, 0);
    glVertex3f(0, 1, 2.0);
    glVertex3f(2, 1, 2);
    glVertex3f(2, 1, -2);
    glVertex3f(0, 1, -2.0);

    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0, 0, -2.0);
    glVertex3f(2, 0, -2);
    glVertex3f(2, 1, -2);
    glVertex3f(0, 1, -2.0);

    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 2.0);
    glVertex3f(2, 0, 2);
    glVertex3f(2, 1, 2);
    glVertex3f(0, 1, 2.0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0);
    glVertex3f(2, 0, 2.0);
    glVertex3f(3, 0, 1.5);
    glVertex3f(3, 0, -1.5);
    glVertex3f(2, 0, -2.0);

    glNormal3f(0.0, 1.0, 0);
    glVertex3f(2, 1, 2.0);
    glVertex3f(3, 1, 1.5);
    glVertex3f(3, 1, -1.5);
    glVertex3f(2, 1, -2.0);

    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(2, 0, -2.0);
    glVertex3f(3, 0, -1.5);
    glVertex3f(3, 1, -1.5);
    glVertex3f(2, 1, -2.0);

    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(2, 0, 2.0);
    glVertex3f(3, 0, 1.5);
    glVertex3f(3, 1, 1.5);
    glVertex3f(2, 1, 2.0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0);
    glVertex3f(3, 0, 1.5);
    glVertex3f(4.5, 0, 1.0);
    glVertex3f(4.5, 0, -1.0);
    glVertex3f(3, 0, -1.5);

    glNormal3f(0.0, 1.0, 0);
    glVertex3f(3, 1, 1.5);
    glVertex3f(4.5, 1, 1.0);
    glVertex3f(4.5, 1, -1.0);
    glVertex3f(3, 1, -1.5);

    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(3, 0, -1.5);
    glVertex3f(4.5, 0, -1.0);
    glVertex3f(4.5, 1, -1.0);
    glVertex3f(3, 1, -1.5);

    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(3, 0, 1.5);
    glVertex3f(4.5, 0, 1.0);
    glVertex3f(4.5, 1, 1.0);
    glVertex3f(3, 1, 1.5);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(4.5, 0, 1.0);
    glVertex3f(4.5, 0, -1.0);
    glVertex3f(4.5, 1, -1.0);
    glVertex3f(4.5, 1, 1.0);
    glEnd();

    yenNhapNho();

    glPushMatrix();
    glScalef(1.0, 1.0, -1.0);
    yenNhapNho();
    glPopMatrix();
}
// Dong co phan 1
void dongCo() {
    glPushMatrix();
    cubefill(2, 2.5, 1);
    glTranslatef(1.5, 0.25, 0);
    cubefill(1, 2, 1);

    //tannhiet
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(1.0, 1, -0.75);
    glRotatef(90, 1.0, 0, 0);
    TanNhietDongCoXe(1.5);
    glTranslatef(0.0, 0.0, 0.5);
    TanNhietDongCoXe(1.5);
    glTranslatef(0.0, 0.0, -1.0);
    TanNhietDongCoXe(1.5);
    glPopMatrix();
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);

    glPushMatrix();
    glTranslatef(0, 1, 0);
    glutSolidSphere(2, 20, 64);
    glPopMatrix();

    glPushMatrix();
    GLUquadricObj* quadratic_obj;
    quadratic_obj = gluNewQuadric();
    glRotatef(-90, 0, 1.0, 0);
    gluCylinder(quadratic_obj, 1, 1, 5, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1, 0);
    glutSolidSphere(2, 20, 64);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 0.75);
    glRotatef(-90, 1.0, 0.0, 0);
    gluCylinder(quadratic_obj, 0.5, 0.5, 4, 32, 32);
    glTranslatef(0, 0, 4.0);
    glutSolidSphere(0.5, 20, 64);
    glRotatef(-90, 0.0, 1.0, 0);
    gluCylinder(quadratic_obj, 0.5, 0.5, 2, 32, 32);
    glTranslatef(-1.5, 0.0, 0.0);
    glRotatef(90, 0.0, 1.0, 0);
    glutSolidTorus(0.3, 0.7, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0, 1.0, -1.0);
    glTranslatef(0, 0, 0.75);
    glRotatef(-90, 1.0, 0.0, 0);
    gluCylinder(quadratic_obj, 0.5, 0.5, 4, 32, 32);
    glTranslatef(0, 0, 4.0);
    glutSolidSphere(0.5, 20, 64);
    glRotatef(-90, 0.0, 1.0, 0);
    gluCylinder(quadratic_obj, 0.5, 0.5, 2, 32, 32);
    glTranslatef(-1.5, 0.0, 0.0);
    glRotatef(90, 0.0, 1.0, 0);
    glutSolidTorus(0.3, 0.7, 20, 20);
    glPopMatrix();
}
// Hàm vẽ hình oval cho phần bầu ra của động cơ
//w: độ dài của hình oval
//h: bán kinh của tâm mỗi đường tròn
//lengz: chiều dài trục z (ống dài)
//rev: phản chiếu qua trục ox (1 or 0)
// pos xyz tọa độ ban đầu của vật thể
void bauDongCo2(float w, float h, float lengz, int rev, float posx, float posy, float posz) {
    glPushMatrix();
    GLUquadricObj* quadratic_obj;
    quadratic_obj = gluNewQuadric();

    glTranslatef(posx, posy, posz);
    gluCylinder(quadratic_obj, h, h, lengz, 32, 32);

    for (int i = 0; i < w; i++) {
        glTranslatef(0.3, 0, 0);
        gluCylinder(quadratic_obj, h, h, lengz, 32, 32);
        DrawCircle(0, 0, h, 100, 0, 0, 1.0);
    }

    glTranslatef(0, 0, lengz);
    DrawCircle(0, 0, h, 100, 0, 0, 1.0);
    for (int i = 0; i < w; i++) {
        glTranslatef(-0.3, 0, 0);
        DrawCircle(0, 0, h, 100, 0, 0, 1.0);
    }
    glPopMatrix();

    if (rev == 1) {
        glPushMatrix();
        glScalef(1.0, 1.0, -1.0);
        bauDongCo2(w, h, lengz, 0, posx, posy, posz);
        glPopMatrix();
    }
}
// dong co phan 2
void dongco2() {
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0);
    glVertex3f(0, 0, 2.0);
    glVertex3f(2, 0, 1.5);
    glVertex3f(2, 0, -1.5);
    glVertex3f(0, 0, -2.0);

    glNormal3f(0.0, 1.0, 0);
    glVertex3f(0, 3, 2.0);
    glVertex3f(2, 3, 1.5);
    glVertex3f(2, 3, -1.5);
    glVertex3f(0, 3, -2.0);

    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0, 0, -2.0);
    glVertex3f(2, 0, -1.5);
    glVertex3f(2, 3, -1.5);
    glVertex3f(0, 3, -2.0);

    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 2.0);
    glVertex3f(2, 0, 1.5);
    glVertex3f(2, 3, 1.5);
    glVertex3f(0, 3, 2.0);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(2, 0, 1.5);
    glVertex3f(2, 0, -1.5);
    glVertex3f(2, 3, -1.5);
    glVertex3f(2, 3, 1.5);

    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0, 0, 2.0);
    glVertex3f(0, 0, -2.0);
    glVertex3f(0, 3, -2.0);
    glVertex3f(0, 3, 2.0);
    glEnd();

    glPushMatrix();
    glTranslatef(2.0, 0, 0);
    cubefill(2, 1, 1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2.0, 0.15, 0);
    cubefill(2.15, 3.80, 1);
    glPopMatrix();
    // phan bau ra cua dong co
    glPushMatrix();
    bauDongCo2(2, 1.50, 2.15, 1, -3, 1.75, 0);
    glPopMatrix();
}
// vẽ phần đuôi xe
void duoiXe(int rev) {
    glBegin(GL_QUADS);
    glNormal3f(0, 0.15, 1.0);
    glVertex3f(-5.25, -2.0, 2.15);
    glVertex3f(-6.0, -3.25, 2.5);
    glVertex3f(-7.5, -3.5, 2.5);
    glVertex3f(-8.0, -2.5, 2.15);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0.0, -0.25, 1.0);
    glVertex3f(-8.0, -2.5, 2.15);
    glVertex3f(-5.25, -2.0, 2.15);
    glVertex3f(-8.0, -1.5, 2.5);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(-.25, 0.0, 1.0);
    glVertex3f(-8.0, -2.5, 2.15);
    glVertex3f(-8.0, -1.5, 2.5);
    glVertex3f(-16.0, 2.5, 2.15);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0.05, 0, 1.0);
    glVertex3f(-8.0, -1.5, 2.5);
    glVertex3f(-11.5, 2.5, 2.15);
    glVertex3f(-5.25, -2.0, 2.15);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(-.15, 0.0, 1.0);
    glVertex3f(-8.0, -1.5, 2.5);
    glVertex3f(-16.0, 2.5, 2.15);
    glVertex3f(-11.5, 2.5, 2.15);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-16.0, 2.5, 2.15);
    glVertex3f(-11.5, 2.5, 2.15);
    glVertex3f(-11.5, 2.5, 0);
    glVertex3f(-16.0, 2.5, 0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(-1.0, -0.25, 0.0);
    glVertex3f(-16.0, 2.5, 2.15);
    glVertex3f(-8.0, -2.5, 2.15);
    glVertex3f(-8.0, -2.5, 0);
    glVertex3f(-16.0, 2.5, 0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.05, 0.0);
    glVertex3f(-11.5, 2.5, 2.15);
    glVertex3f(-5.25, -2.0, 2.15);
    glVertex3f(-5.25, -2.0, 0);
    glVertex3f(-11.5, 2.5, 0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-6.0, -3.25, 2.5);
    glVertex3f(-7.5, -3.5, 2.5);
    glVertex3f(-7.5, -3.5, 0);
    glVertex3f(-6.0, -3.25, 0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.05, -1.0, 0.0);
    glVertex3f(-5.25, -2.0, 2.15);
    glVertex3f(-6.0, -3.25, 2.5);
    glVertex3f(-6.0, -3.25, 0);
    glVertex3f(-5.25, -2.0, 0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(-0.05, -1.0, 0.0);
    glVertex3f(-7.5, -3.5, 2.5);
    glVertex3f(-8.0, -2.5, 2.15);
    glVertex3f(-8.0, -2.5, 0);
    glVertex3f(-7.5, -3.5, 0);
    glEnd();
    // duoi chan bun sau
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-17.5, 1.0, 2.15);
    glVertex3f(-13.0, 1.0, 2.15);
    glVertex3f(-13.0, 0.75, 2.15);
    glVertex3f(-17, 0.75, 2.15);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(-.15, 0.0, 1.0);
    glVertex3f(-17, 0.75, 2.15);
    glVertex3f(-18.0, -2, 2.15);
    glVertex3f(-16.25, 0.75, 2.15);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-17.5, 1.0, 2.15);
    glVertex3f(-13.0, 1.0, 2.15);
    glVertex3f(-13.0, 1.0, 0);
    glVertex3f(-17.5, 1.0, 0);

    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-13.0, 0.75, 2.15);
    glVertex3f(-17, 0.75, 2.15);
    glVertex3f(-17, 0.75, 0);
    glVertex3f(-13.0, 0.75, 0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(-1.0, -0.25, 0.0);
    glVertex3f(-17.5, 1.0, 2.15);
    glVertex3f(-17, 0.75, 2.15);
    glVertex3f(-17, 0.75, 0);
    glVertex3f(-17.5, 1.0, 0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.05, 0.0);
    glVertex3f(-17, 0.75, 2.15);
    glVertex3f(-18.0, -2, 2.15);
    glVertex3f(-18.0, -2, 0);
    glVertex3f(-17, 0.75, 0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0, -0.15, 0.0);
    glVertex3f(-18.0, -2, 2.15);
    glVertex3f(-16.25, 0.75, 2.15);
    glVertex3f(-16.25, 0.75, 0);
    glVertex3f(-18.0, -2, 0);
    glEnd();

    //baudongco
    toMau(qaRed, qaRed, qaWhite, 128.0, qaLowAmbient);
    bauDongCo2(0, 0.6, 2.15, 0, -13, 0, 0);
    toMau(qaRed, qaYellow, qaWhite, 128.0, qaLowAmbient);
    bauDongCo2(0, 0.5, 2.25, 0, -13, 0, 0);
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);

    if (rev == 1) {
        glScalef(1.0, 1.0, -1.0);
        duoiXe(0);
    }
}

// ve lai binh xang va ve them vo xe
void fixBinhXang(float loi, int rev) {
    glBegin(GL_POLYGON);
    glVertex3f(3.5, -0.5, loi);
    glVertex3f(3.85, -1.75, loi);
    glVertex3f(3.0, -2.25, loi);
    glVertex3f(-0.5, -1.5, loi);
    glVertex3f(-0.85, -0.25, loi);
    glVertex3f(0.25, 0.25, loi);
    glEnd();
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    LoadTexture("logo.bmp");
    glBindTexture(GL_TEXTURE_2D, texName);
    glTranslatef(1.5, -1, 3);
    glRotatef(180,0,0,1.0);
    glTranslatef(-1.5,1,-3);
    glBegin(GL_QUADS);
    glNormal3f(1.0, -0.15, 0.0);
    glTexCoord2f(0.00 , 0.0);glVertex3f(1, -0.75, loi);
    glTexCoord2f(0.00 , 1.0 ); glVertex3f(1, -1.75, loi);
    glTexCoord2f(1.0 , 1.0 );glVertex3f(2, -1.75, loi);
    glTexCoord2f(1 , 0.0 ); glVertex3f(2, -0.75, loi);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glBegin(GL_QUADS);
    // ben tren nguoc chieu
    glNormal3f(1.0, 0, 0);
    glVertex3f(4, 0, 2.0);
    glVertex3f(4.75, -2, 2.0);
    glVertex3f(3.85, -1.75, loi);
    glVertex3f(3.5, -0.5, loi);

    glNormal3f(0.0, 1.0, 0);
    glVertex3f(4, 0, 2.0);
    glVertex3f(0.0, 1.0, 2.0);
    glVertex3f(0.25, 0.25, loi);
    glVertex3f(3.5, -0.5, loi);

    glNormal3f(0.0, 1.25, 0);
    glVertex3f(0.0, 1.0, 2.0);
    glVertex3f(-3.5, -0.5, 2.0);
    glVertex3f(-0.85, -0.25, loi);
    glVertex3f(0.25, 0.25, loi);
    // ben duoi
    glNormal3f(0.0, -1.0, 0);
    glVertex3f(4.75, -2, 2.0);
    glVertex3f(3.0, -3, 2.0);
    glVertex3f(3.0, -2.25, loi);
    glVertex3f(3.85, -1.75, loi);

    glVertex3f(3.0, -3, 2.0);
    glVertex3f(-1.0, -2, 2.0);
    glVertex3f(-0.5, -1.5, loi);
    glVertex3f(3.0, -2.25, loi);

    glVertex3f(-3.5, -0.5, 2.0);
    glVertex3f(-1.0, -2, 2.0);
    glVertex3f(-0.5, -1.5, loi);
    glVertex3f(-0.85, -0.25, loi);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0, 0, 0.0);
    glVertex3f(4, 0, 2.0);
    glVertex3f(4.75, -2, 2.0);
    glVertex3f(4.75, -2, 0.0);
    glVertex3f(4, 0, 0.0);

    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(4, 0, 2.0);
    glVertex3f(0.0, 1.0, 2.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(4, 0, 0.0);

    glNormal3f(0.0, 1.25, 0);
    glVertex3f(0.0, 1.0, 2.0);
    glVertex3f(-3.5, -0.5, 2.0);
    glVertex3f(-3.5, -0.5, 0.0);
    glVertex3f(0.0, 1.0, 0.0);

    glNormal3f(0.0, -1.0, 0);
    glVertex3f(4.75, -2, 2.0);
    glVertex3f(3.0, -3, 2.0);
    glVertex3f(3.0, -3, 0.0);
    glVertex3f(4.75, -2, 0.0);

    glVertex3f(3.0, -3, 2.0);
    glVertex3f(-1.0, -2, 2.0);
    glVertex3f(-1.0, -2, 0.0);
    glVertex3f(3.0, -3, 0.0);

    glVertex3f(-3.5, -0.5, 2.0);
    glVertex3f(-4.0, 0.0, 2.0);
    glVertex3f(-4.0, 0.0, 0.0);
    glVertex3f(-3.5, -0.5, 0.0);

    glVertex3f(-8.0, 0, 2.0);
    glVertex3f(-4.0, -3.5, 2.0);
    glVertex3f(-4.0, -3.5, 0.0);
    glVertex3f(-8.0, 0, 0.0);

    glVertex3f(-4.0, -3.5, 2.0);
    glVertex3f(-1.0, -2, 2.0);
    glVertex3f(-1.0, -2, 0.0);
    glVertex3f(-4.0, -3.5, 0.0);
    glEnd();
    // ve phan sau
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, 1.0);
    glVertex3f(-3.5, -0.5, 2.0);
    glVertex3f(-1.0, -2, 2.0);
    glVertex3f(-4.0, -3, loi);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0, -1.0, 0.0);
    glVertex3f(-4.0, -3, loi);
    glVertex3f(-4.0, -3.5, 2.0);
    glVertex3f(-1.0, -2, 2.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(-4.0, -3, loi);
    glVertex3f(-3.5, -0.5, 2.0);
    glVertex3f(-4.0, 0.0, 2.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-8.0, 0, 2.0);
    glVertex3f(-4.0, -3, loi);
    glVertex3f(-4.0, 0.0, 2.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-8.0, 0, 2.0);
    glVertex3f(-4.0, -3.5, 2.0);
    glVertex3f(-4.0, -3, loi);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.05, 0.0, 1.0);
    glVertex3f(-8.0, 0, 2.0);
    glVertex3f(-4.0, 0.0, 2.0);
    glVertex3f(-4.0, -3, loi);
    glVertex3f(-4.0, -3.5, 2.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(4.0, 0.0, 2.0);
    glVertex3f(2, 2.0, 1.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.0, 1.0, 2.0);
    glVertex3f(0, 2.25, 1.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-3.5, -0.5, 2.0);
    glVertex3f(0, 2.25, 1.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0.0, 0, 0.75);
    glVertex3f(-3.5, -0.5, 2.0);
    glVertex3f(0, 2.25, 1.0);
    glVertex3f(0.0, 1.0, 2.0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0, 1.0);
    glVertex3f(0.0, 1.0, 2.0);
    glVertex3f(0, 2.25, 1.0);
    glVertex3f(2, 2.0, 1.0);
    glVertex3f(4.0, 0.0, 2.0);

    glNormal3f(1.0, 0, 0.0);
    glVertex3f(4.0, 0.0, 2.0);
    glVertex3f(2, 2.0, 1.0);
    glVertex3f(2, 2.0, 0);
    glVertex3f(4.0, 0.0, 0);

    glVertex3f(2, 2.0, 1.0);
    glVertex3f(0, 2.25, 1.0);
    glVertex3f(0, 2.25, 0.0);
    glVertex3f(2, 2.0, 0.0);

    glVertex3f(-3.5, -0.5, 2.0);
    glVertex3f(0, 2.25, 1.0);
    glVertex3f(0, 2.25, 0.0);
    glVertex3f(-3.5, -0.5, 0.0);
    glEnd();

    // lay doi xung qua truc x
    if (rev == 1) {
        glScalef(1.0, 1.0, -1.0);
        fixBinhXang(loi, 0);
    }
}
// nắp bình xăng
// có thể viết thêm tham số để tái sử dụng
void napBinhXang() {
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(0.85, 0, 0);
    glRotatef(-5, 0.0, 0, 1.0);
    glRotatef(-90, 1.0, 0, 0);
    bauDongCo2(0, 0.7, 2.20, 0, 0, 0, 0);
    bauDongCo2(0, 0.5, 2.22, 0, 0, 0, 0);
}
// bô xe máy
void boXe(int rev) {
    glPushMatrix();
    glTranslatef(-8.25, -7.25, 2);
    glutSolidSphere(0.4, 32, 32);

    GLUquadricObj* quadratic_obj;
    quadratic_obj = gluNewQuadric();
    glRotatef(10, 0.0, 0.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(quadratic_obj, 0.4, 0.4, 1.5, 32, 32);
    glTranslatef(0, 0, 1.5);
    glutSolidSphere(0.4, 32, 32);
    glRotatef(-80, 0.0, 1.0, 0.0);
    gluCylinder(quadratic_obj, 0.4, 0.6, 6.5, 32, 32);
    gluCylinder(quadratic_obj, 0.3, 0.375, 6.75, 32, 32);

    glTranslatef(0, 0, 6.5);
    DrawCircle(0, 0, 0.6, 32, -1.0, 0, 0);
    glPopMatrix();

    if (rev == 1) {
        glScalef(1.0, 1.0, -1.0);
        boXe(0);
    }
}

// final than xe
void fullThanXe() {
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    trucChinhThanXe();
    glPopMatrix();
    maugoc();

    //khớp nối chứa ngông xich
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(0, 1.75, 0);
    khopNoiBanhsau();
    glPopMatrix();
    maugoc();

    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(0, 1.75, 0);
    glScalef(1.0, 1.0, -1.0);
    khopNoiBanhsau();
    glPopMatrix();

    //chan bun sau
    glPushMatrix();
    toMau(qaRed, qaRed, qaWhite, 128.0, qaLowAmbient);
    updateKhopNoiBanhSau(1);
    glPopMatrix();
    maugoc();

    // vẫn là động cơ
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(-2, -6.5, 0);
    bauDongCo2(0, 1.50, 2.5, 1, -3, 1.75, 0);
    bauDongCo2(0, 1.0, 2.75, 1, -3, 1.75, 0);
    glRotatef(10, 0, 0, 1.0);
    bauDongCo2(7, 1.50, 2.25, 1, -4.5, 2.25, 0);
    glPopMatrix();
    maugoc();

    // giam soc sau
    glPushMatrix();
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(0, 1.5, 0);
    glTranslatef(-12.2, -0.2, 0);
    giamsoctruoc(-20);
    glPopMatrix();
    maugoc();

    // giam soc sau
    glPushMatrix();
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(0, 1.5, 0);
    glTranslatef(-12.2, -0.2, 0);
    glScalef(1.0, 1.0, -1.0);
    giamsoctruoc(-20);
    glPopMatrix();
    maugoc();

    //banh xe
    // to lai mau cho banh xe
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    glPushMatrix();
    glTranslatef(-17, 1.5, 0);
    glTranslatef(3.0, -8.0, 0);
    glRotatef(-spin, 0, 0, 1); 
    glTranslatef(-3.0, 8.0, 0);
    DrawRims();
    glPopMatrix();
    maugoc();

    // fix binh xang remake
    glPushMatrix();
    toMau(qaRed, qaRed, qaWhite, 128.0, qaLowAmbient);
    fixBinhXang(3, 1);
    napBinhXang();
    glPopMatrix();
    maugoc();

    // yen xe
    glPushMatrix();
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(-6.25, 0.0, 0);
    yenXe();
    glPopMatrix();
    maugoc();

    // dong co phan 1
    glPushMatrix();
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(-1.0, -6.0, 0);
    dongCo();
    bauDongCo2(10, 1.0, 2.25, 1, -2.25, 1.25, 0);
    glPopMatrix();
    maugoc();

    // dong co phan 2
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(-5.5, -4.0, 0);
    dongco2();
    glPopMatrix();
    maugoc();

    // bô xe
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    boXe(1);
    glPopMatrix();
    maugoc();

    // đuôi xe
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    duoiXe(1);
    glPopMatrix();
    maugoc();
}
// add
void draw_ground()
{
    grass = loadimage("grass_1.bmp");
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, grass);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-150.0f, -1.5f, 150.0f);;
    glTexCoord2f(100.0f, 0.0f); glVertex3f(-150.0f, -1.5f, -150.0f);;
    glTexCoord2f(100.0f, 100.0f); glVertex3f(150.0f, -1.5f, -150.0f);
    glTexCoord2f(0.0f, 100.0f); glVertex3f(150.0f, -1.5f, 150.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glLineWidth(5.0);
    glTranslatef(0.0, -2, 0.0);
    glTranslatef(0.0, 2, 0.0);
}
// viet chu len man hinh
void writeText(float x, float y, float z, char* string)
{

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);
    //glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos3f(x, y, z);
    for (int i = 0; i < (int)strlen(string); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}
// cung la ham viet chu nhung cho man hinh bat dau
void bitmap_output(float x, float y, float z, const char* string1)
{
    int len, i;
    glRasterPos3f(x, y, z);
    len = (int)strlen(string1);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string1[i]);
    }
}
void rendenScene2() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_NORMALIZE);
    
    char speedString[100], speedString1[100], speedString2[100];
    
    sprintf(speedString, "speed: %f", speed);
    writeText(22, 8, 1, speedString);
   
    sprintf(speedString1, "steering: %f", steering);
    writeText(22, 7, 1, speedString1);

    sprintf(speedString2, "direction: %f", direction);
    writeText(22, 6, 1, speedString2);
    
    lighting();
    //shading();
    // camera hover
    glTranslatef(viewerPosition[0], viewerPosition[1], viewerPosition[2]);
    glRotatef(navigationRotation[0], 1.0f, 0.0f, 0.0f);
    glRotatef(navigationRotation[1], 0.0f, 1.0f, 0.0f);

   
    for (int i = 0; i < 2;i++) {
        if (i == 0) {
            glShadeModel(GL_FLAT);
        }
        else {
            glShadeModel(GL_SMOOTH);
        }
    }
    if (Flag1 == 0) {
        glPushMatrix();
        glColor3f(1, 1, 0);
        glTranslatef(0, -10.5, -5);
        draw_ground();
        glPopMatrix();
        DrawCoordinate();
    }

    //set ambient diffuse specular
    glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGreen);
    glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
    glMaterialfv(GL_LIGHT0, GL_AMBIENT, qaLowAmbient);


    glPushMatrix();
    glTranslatef(xpos, 0.0f, zpos);// <-------
    glRotatef(direction, 0.0f, 1.0f, 0.0f);// <-------  
    // di chuyen len truc y 1,5 => toa do dau xe la 2 + 1,5 = 3,5(mep cao nhat)
    // 1,5 la mep thap nhat
    glTranslatef(4.0, 1.5, 0);// <-------
    //
    glRotatef((GLfloat)steering, 0.0, 1.0, 0.0);
    fulldauxe();
    glPopMatrix();
    //
    glTranslatef(xpos, 0.0f, zpos);// <-------
    glRotatef(direction, 0.0f, 1.0f, 0.0f);// <-------
    fullThanXe();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camx, camy, camz, camx, 1.0, 0.0, 0.0, 1.0, 1.0);
    glutSwapBuffers();
    //glFlush();
    
}


void reShape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 300.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camx, camy, camz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// xu li motion chuot
void mouseMotionFunc(int x, int y) {

    float xOffset = 0.0, yOffset = 0.0, zOffset = 0.0;

    // navigation
    // if (altActive) {

    // rotatation
    if (leftMouseButtonActive) {

        navigationRotation[0] -= ((mousePressedY - y) * 180.0f) / 200.0f;
        navigationRotation[1] -= ((mousePressedX - x) * 180.0f) / 200.0f;

        mousePressedY = y;
        mousePressedX = x;

    }
    // panning
    else if (middleMouseButtonActive) {

        xOffset = (mousePressedX + x);
        if (!lastXOffset == 0.0) {
            viewerPosition[0] -= (xOffset - lastXOffset) / 8.0;
            viewerDirection[0] -= (xOffset - lastXOffset) / 8.0;
        }
        lastXOffset = xOffset;

        yOffset = (mousePressedY + y);
        if (!lastYOffset == 0.0) {
            viewerPosition[1] += (yOffset - lastYOffset) / 8.0;
            viewerDirection[1] += (yOffset - lastYOffset) / 8.0;
        }
        lastYOffset = yOffset;

    }
    // depth movement
    else if (rightMouseButtonActive) {
        zOffset = (mousePressedX + x);
        if (!lastZOffset == 0.0) {
            viewerPosition[2] -= (zOffset - lastZOffset) / 5.0;
            viewerDirection[2] -= (zOffset - lastZOffset) / 5.0;
        }
        lastZOffset = zOffset;
    }
    // }
}

/* các thao tác xử lý chuột */
void mouse(int button, int state, int x, int y)
{
    // get the mouse buttons
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN) {
            leftMouseButtonActive += 1;
        }
        else
            leftMouseButtonActive -= 1;
    else if (button == GLUT_MIDDLE_BUTTON)
        if (state == GLUT_DOWN) {
            middleMouseButtonActive += 1;
            lastXOffset = 0.0;
            lastYOffset = 0.0;
        }
        else
            middleMouseButtonActive -= 1;
    else if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN) {
            rightMouseButtonActive += 1;
            lastZOffset = 0.0;
        }
        else
            rightMouseButtonActive -= 1;
    // if (altActive) {
    mousePressedX = x;
    mousePressedY = y;
    // }


    // get the modifiers
    switch (glutGetModifiers()) {
    case GLUT_ACTIVE_SHIFT:
        shiftActive = 1;
        break;
    case GLUT_ACTIVE_ALT:
        altActive = 1;
        break;
    case GLUT_ACTIVE_CTRL:
        ctrlActive = 1;
        break;
    default:
        shiftActive = 0;
        altActive = 0;
        ctrlActive = 0;
        break;
    }
}

void idleFunc(void) {
    updateScene();
    glutPostRedisplay();
}

void special(int key, int x, int y) // FUNCTION FOR CAM ZOOMING
{
    switch (key)
    {
    case GLUT_KEY_UP:
        camz -= 0.1f;
        break;
    case GLUT_KEY_DOWN:
        camz += 0.1f;
        break;
    case GLUT_KEY_LEFT:
        camx -= 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        camx += 0.1f;
        break;
    }
    glutPostRedisplay();
}
void reset() {
    speed = steering = 0.0f;
    camx = 10.0, camy = 0.0, camz = 15.0;
    xpos = zpos = 0.0f;
    direction = 0.0f;
}
// man hinh bat dau
void welcome_window() // WELCOME WINDOW
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glColor3f(1.0, 1.0, 1.0);
    bitmap_output(-3.75, 2, 0.50, "Bai Tap Lon Do Hoa May Tinh");
    bitmap_output(-3.3, 1.2, 0.50, "De Tai: Mo Phong Xe May");

    bitmap_output(-3.75, -1.5, 0.50, "PLEASE PRESS M TO START");
    glutSwapBuffers();
    glFlush();
}
// man hinh gioi thieu cac mode su dung
void operations_window() // OPERATION WINDOW FOR DESCRIPTION OF OPERATIONS TO PERFORM
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glColor3f(0.0, 1.0, 1.0);
    //bitmap_output(-1.25, 1.7, 0.50, "lol");
    bitmap_output(-5.5, 6, 0.50, "CAC CHUC NANG DUNG DE DIEU KHIEN XE");
    bitmap_output(-5.5, 4, 0.50, "1. RESET THE CAMERA - USE 'R' OR 'r'");
    bitmap_output(-5.5, 3, 0.50, "2. TANG TOC DO CUA XE 'W' USE 'w'");
    bitmap_output(-5.5, 2, 0.50, "3. GIAM TOC DO CUA XE 'S' USE 's'");
    bitmap_output(-5.5, 1, 0.50, "4. RE PHAI 'D' USE 'd'");
    bitmap_output(-5.5, 0, 0.50, "5. RE TRAI 'A' USE 'a'");
    bitmap_output(-5.5, -1, 0.50, "6. ZOOM VAO - USE 'UPWARD ARROW'");
    bitmap_output(-5.5, -2, 0.50, "7. ZOOM RA - USE 'DOWNWARD ARROW'");
    bitmap_output(-5.5, -3, 0.50, "8. CHUYEN CAM SANG TRAI - DUNG 'LEFT ARROW'");
    bitmap_output(-5.5, -4, 0.50, "9. CHUYEN CAM SANG PHAI - DUNG 'RIGHT ARROW'");
    bitmap_output(-5.5, -5, 0.50, "10. SU DUNG CHUOT TRAI DE THAY DOI TOA DO CUA KHUNG NHIN");
    bitmap_output(-5.5, -6, 0.50, "10. SU DUNG CHUOT PHAI DE ZOOM RA/VAO KHUNG NHIN");
    bitmap_output(-5.5, -7, 0.50, "PLEASE PRESS C TO CONTINUE");
    glutSwapBuffers();
    glFlush();
}
// key event
void key(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'G':
    case 'g':
        if (Flag1 == 0) Flag1 = 1;
        else Flag1 = 0;
        break;
    case 'R':
    case 'r':
        reset();
        break;
    case 'W':
    case 'w':
        //key up
        speed += INC_SPEED;
        break;
    case 'S':
    case 's':
        // key down
        speed -= INC_SPEED;
        break;
    case 'A':
    case 'a':
        if (steering < HANDLE_LIMIT)
            steering += INC_STEERING;
        break;
    case 'D':
    case 'd':
        if (steering > -HANDLE_LIMIT)
            steering -= INC_STEERING;
        break;
    case 'P':
    case 'p':
        light_value = 0;
        lighting();
        break;
    case 'O':
    case 'o':
        light_value = 1;
        lighting();
        break;
    case 'I':
    case 'i':
        light_value = 2;
        lighting();
        break;
    case 'U':
    case 'u':
        light_value = 3;
        lighting();
        break;
    case 'M':
    case 'm':
        glutDisplayFunc(operations_window);
        break;
    case 'C':
    case 'c':
        glutDisplayFunc(rendenScene2);
        break;
    }
    
}
void passive(int x, int y) // PASSIVE FUNCTION WHEN NO MOUSE KEYS ARE PRESSED
{

}
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Opengl Study");
    init();
    glutReshapeFunc(reShape);
    glutDisplayFunc(welcome_window);
    glutSpecialFunc(special);
    glutMouseFunc(mouse); /* đăng ký hàm mouse cho sự kiện về chuột */
    glutMotionFunc(mouseMotionFunc);
    glutIdleFunc(idleFunc);
    glutKeyboardFunc(key);
    glutPassiveMotionFunc(passive);
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    glutMainLoop();
    return 0;
}
