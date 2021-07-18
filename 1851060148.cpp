#include "Definition.h"

#define STB_IMAGE_IMPLEMENTATION
#include "GL/stb_image.h"

extern void toMau(GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat shininess, GLfloat lowAmbient[]);
extern void DrawCircle(float cx, float cy, float r, int num_segments, float cphx, float cphy, float cphz);
extern void cubefill(float h, float w, float size);
extern void fulldauxe(int isShadow, unsigned int texVant, unsigned int texDenxe, GLfloat spinb);
extern void fullThanXe(int isShadow, unsigned int texLogo, GLfloat spinb);
extern void drawShowroom(GLint poster1[], GLint texTuong);
extern void robot(GLfloat nachphai, GLfloat tayphai, GLfloat khuyphai, GLfloat nachtrai, GLfloat taytrai, GLfloat khuytrai);
extern void draw_ground(GLint texSan);
// Biến di chuyển
#define PI 3.14159
#define BIKE_LENGTH 3.5f  //<------
#define HANDLE_LIMIT 30.0f
#define INC_STEERING 3.0f
#define INC_SPEED 0.05f
GLfloat xpos, zpos, direction;
static GLfloat spin = 0.0;
static GLfloat nachphai = 110.0;
static GLfloat nachtrai = 100.0;
static GLfloat khuyphai = 55.0;
static GLfloat khuytrai = 55.0;
static GLfloat tayphai = 50.0;
static GLfloat taytrai = 75.0;
GLfloat speed, steering;
int amthanh = 0;
// các hàm chuyển đổi độ
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
// cập nhật giá trị  khi xe di chuyển
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
    // cập nhât giá trị quay của bánh xe
    spin = spin + 1.0 + speed * 10 * 2;
    if (spin > 360.0)
        spin = spin - 360.0;
}
// texture
//unsigned int texName;
unsigned int matVanTocTex;
unsigned int denXeTex;
unsigned int logoTex;
GLint grass;
GLint san;
GLint tuong;
GLint poster[3];
GLint cubemap[6];
// giá trị báo để tắt nền và trục tọa độ
int Flag1 = 0, Flag2 = 0, FlagShadow = 0;
// hàm loadtexture sử dụng thư viện stbi
void LoadTexture(const char* filename, unsigned int& texName) {
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

// hàm loadtexture thủ công
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
GLfloat camx = 10.0, camy = 0.0, camz = 15.0;

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


//
void reset(void);
// hàm init các giá trị texture côt để tối ưu hiệu năng
void init(void) {
    reset();
    grass = loadimage("grass_1.bmp");
    san = loadimage("san.bmp");
    tuong = loadimage("tuong.bmp");
    poster[0] = loadimage("poster1.bmp");
    poster[1] = loadimage("poster2.bmp");
    poster[2] = loadimage("poster3.bmp");
    LoadTexture("denxe.bmp", denXeTex);
    LoadTexture("matDoVantoc24.bmp", matVanTocTex);
    LoadTexture("logo.bmp", logoTex);
}

GLfloat lightPosition[4] = { 10,10,10,0 };
// hàm thiết lập độ sáng và màu của nguồn sáng (light0)
void lighting() // FUNCTION FOR LIGHTING
{
    glClearColor(0.2, 0.2, 0.2, 1.0);
    // printf("%s\n", "YESS ");
    GLfloat light_directional[] = { 1.0,1.0,1.0,1.0 };
    GLfloat light_diffuse[] = { 0.8,0.8,0.8,1.0 };
    GLfloat light_ambient[] = { 0.2,0.2,0.2,1.0 };

    GLfloat light_positional[] = { 10.0,10.0,10.0,1.0 };

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_positional);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}
// hàm vẽ trục tọa độ
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
// viet chu len man hinh ở trong rendersence2
void writeText(float x, float y, float z, char* string)
{

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);
    //glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos3f(x, y, z);
    while (*string)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
    glEnable(GL_LIGHTING);
}
// cung la ham viet chu nhung cho man hinh bat dau và màn hinh operation
void bitmap_output(float x, float y, float z, const char* string1)
{
    glRasterPos3f(x, y, z);
    while (*string1)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string1++);
}
//
void suongmu() {
    //Color of the fog : grey fog
    float fogColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glFogfv(GL_FOG_COLOR, fogColor);
    /*
     * Select the fog mode
     *     GL_EXP, GL_EXP2 or GL_LINEAR
     */
    glFogi(GL_FOG_MODE, GL_EXP);
    /*
     * Density of the fog
     *     ONLY used by the modes : GL_EXP, GL_EXP2
     * GL_EXP  fog equation : exp(-GL_FOG_DENSITY * z)
     * GL_EXP2 fog equation : exp(-(GL_FOG_DENSITY * z)2)
     */
    glFogf(GL_FOG_DENSITY, 0.006f);
    //    /*
    //     * Start of the fog (object begin to mix with the fog) and end of the fog (objects disappear)
    //     * The value
    //     *     ONLY used by the mode : GL_LINEAR
    //     * Fog equation : (GL_FOG_END-z)/(GL_FOG_END-GL_FOG_START)
    //     */
    //glFogf(GL_FOG_START, 4.0f);
    //glFogf(GL_FOG_END, 10.0f);
        /*
         * Precision of the fog calculation (per pixel or per vertex)
         *     GL_DONT_CARE, GL_NICEST (per pixel calculation) or GL_FASTEST (per vertex calculation)
         */
    glHint(GL_FOG_HINT, GL_DONT_CARE);

    //enable the fog mode
    glEnable(GL_FOG);

    //Clearing color equal to the fog color
    glClearColor(fogColor[0], fogColor[1], fogColor[2], 0.0f);
}

enum {
    X, Y, Z, W
};
enum {
    A, B, C, D
};
/* Create a matrix that will project the desired shadow. */
void
shadowMatrix(GLfloat shadowMat[4][4],
    GLfloat groundplane[4],
    GLfloat lightpos[4])
{
    GLfloat dot;

    /* Find dot product between light position vector and ground plane normal. */
    dot = groundplane[X] * lightpos[X] +
        groundplane[Y] * lightpos[Y] +
        groundplane[Z] * lightpos[Z] +
        groundplane[W] * lightpos[W];

    shadowMat[0][0] = dot - lightpos[X] * groundplane[X];
    shadowMat[1][0] = 0.f - lightpos[X] * groundplane[Y];
    shadowMat[2][0] = 0.f - lightpos[X] * groundplane[Z];
    shadowMat[3][0] = 0.f - lightpos[X] * groundplane[W];

    shadowMat[X][1] = 0.f - lightpos[Y] * groundplane[X];
    shadowMat[1][1] = dot - lightpos[Y] * groundplane[Y];
    shadowMat[2][1] = 0.f - lightpos[Y] * groundplane[Z];
    shadowMat[3][1] = 0.f - lightpos[Y] * groundplane[W];

    shadowMat[X][2] = 0.f - lightpos[Z] * groundplane[X];
    shadowMat[1][2] = 0.f - lightpos[Z] * groundplane[Y];
    shadowMat[2][2] = dot - lightpos[Z] * groundplane[Z];
    shadowMat[3][2] = 0.f - lightpos[Z] * groundplane[W];

    shadowMat[X][3] = 0.f - lightpos[W] * groundplane[X];
    shadowMat[1][3] = 0.f - lightpos[W] * groundplane[Y];
    shadowMat[2][3] = 0.f - lightpos[W] * groundplane[Z];
    shadowMat[3][3] = dot - lightpos[W] * groundplane[W];

}
/* Find the plane equation given 3 points. */
void
findPlane(GLfloat plane[4],
    GLfloat v0[3], GLfloat v1[3], GLfloat v2[3])
{
    GLfloat vec0[3], vec1[3];

    /* Need 2 vectors to find cross product. */
    vec0[X] = v1[X] - v0[X];
    vec0[Y] = v1[Y] - v0[Y];
    vec0[Z] = v1[Z] - v0[Z];

    vec1[X] = v2[X] - v0[X];
    vec1[Y] = v2[Y] - v0[Y];
    vec1[Z] = v2[Z] - v0[Z];

    /* find cross product to get A, B, and C of plane equation */
    plane[A] = vec0[Y] * vec1[Z] - vec0[Z] * vec1[Y];
    plane[B] = -(vec0[X] * vec1[Z] - vec0[Z] * vec1[X]);
    plane[C] = vec0[X] * vec1[Y] - vec0[Y] * vec1[X];

    plane[D] = -(plane[A] * v0[X] + plane[B] * v0[Y] + plane[C] * v0[Z]);

}
static GLfloat floorVertices[4][3] = {
  { -180.0, 0.0, 180.0 },
  { 180.0, 0.0, 180.0 },
  { 180.0, 0.0, -180.0 },
  { -180.0, 0.0, -180.0 },
};

static GLfloat floorPlane[4];
static GLfloat floorShadow[4][4];


void draw_moto(int flagShadow) {
    FlagShadow = flagShadow;
    glTranslatef(0, 10.5, 0);
    glPushMatrix();
    glTranslatef(xpos, 0.0f, zpos);// <-------
    glRotatef(direction, 0.0f, 1.0f, 0.0f);// <-------  
    // di chuyen len truc y 1,5 => toa do dau xe la 2 + 1,5 = 3,5(mep cao nhat)
    // 1,5 la mep thap nhat
    glTranslatef(4.0, 1.5, 0);// <-------
    //
    glRotatef((GLfloat)steering, 0.0, 1.0, 0.0);
    fulldauxe(FlagShadow, matVanTocTex, denXeTex,spin);
    glPopMatrix();
    //
    glPushMatrix();

    glTranslatef(xpos, 0.0f, zpos);// <-------
    glRotatef(direction, 0.0f, 1.0f, 0.0f);// <-------
    //
    fullThanXe(FlagShadow,logoTex,spin);
    glPopMatrix();
    glPushMatrix();
    //glTranslatef(-3, 8.5, 0);
    glTranslatef(xpos, 0.0f, zpos);// <-------
    glRotatef(direction, 0.0f, 1.0f, 0.0f);// <-------
    //robot();
    //glPopMatrix();
    glPushMatrix();
    //biensoxe();
    glTranslatef(-3, 8.5, 0);
    //toMau(qaRed, qaRed, qaWhite, 128.0, qaLowAmbient);
    robot(nachphai, tayphai, khuyphai, nachtrai, taytrai, khuytrai);
    //tanso();
    glPopMatrix();

    glPopMatrix();
}
void DrawShadow() {
    shadowMatrix(floorShadow, floorPlane, lightPosition);

    //glEnable(GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_LIGHTING);  /* Force the 50% black. */
    glColor4f(0.0, 0.0, 0.0, 0.5);

    glPushMatrix();
    /* Project the shadow. */
    glMultMatrixf((GLfloat*)floorShadow);
    glPushMatrix();
    draw_moto(1);
    glPopMatrix();

    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
    //glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}
void DrawFlection() {
    // test 
    //glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer
    glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen
    glDisable(GL_DEPTH_TEST); //Disable depth testing
    glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass
    //Make pixels in the stencil buffer be set to 1 when the stencil test passes
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    //Set all of the pixels covered by the floor to be 1 in the stencil buffer
    draw_ground(san);
    glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
    glEnable(GL_DEPTH_TEST); //Enable depth testing
    //Make the stencil test pass only when the pixel is 1 in the stencil buffer
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change

    glPushMatrix();
    glScalef(1, -1, 1);
    draw_moto(0);
    glPopMatrix();

    glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer

    //Blend the floor onto the screen
    glEnable(GL_BLEND);
    glColor4f(1, 1, 1, 0.7f);
    draw_ground(san);
    glDisable(GL_BLEND);
    // test
}
// hàm hiển thị xe máy
void rendenScene2() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    char speedString[100], speedString1[100], speedString2[100];

    sprintf(speedString, "speed: %f", speed);
    writeText(20, 8, 1, speedString);

    sprintf(speedString1, "steering: %f", steering);
    writeText(20, 7, 1, speedString1);

    sprintf(speedString2, "direction: %f", direction);
    writeText(20, 6, 1, speedString2);
    for (int i = 0; i < 2;i++) {
        if (i == 0) {
            glShadeModel(GL_FLAT);
        }
        else {
            glShadeModel(GL_SMOOTH);
        }
    }
    lighting();
    glEnable(GL_DEPTH_TEST);
    //suongmu();
    // camera hover
    glTranslatef(viewerPosition[0], viewerPosition[1], viewerPosition[2]);
    glRotatef(navigationRotation[0], 1.0f, 0.0f, 0.0f);
    glRotatef(navigationRotation[1], 0.0f, 1.0f, 0.0f);

    // ve xe
    glPushMatrix();
    draw_moto(0);
    glPopMatrix();
    // ve bong
    DrawShadow();
    // phan chieu
    DrawFlection();
    // ve truc toa do va ve showroom
    if (Flag1 == 0) {
        glPushMatrix();
        drawShowroom(poster,tuong);
        glPopMatrix();
        if (Flag2 == 1) {
            DrawCoordinate();
        }
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camx, camy, camz, camx, 1.0, 0.0, 0.0, 1.0, 1.0);
    glutSwapBuffers();
}

// hàm hoạt động khi kích thước màn hình thay đổi
void reShape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 800.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camx, camy, camz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// xu li motion chuot
void mouseMotionFunc(int x, int y) {

    float xOffset = 0.0, yOffset = 0.0, zOffset = 0.0;
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

}
// hàm hoạt động khi không có hoạt động nào xảy ra
void idleFunc(void) {
    updateScene();
    glutPostRedisplay();
}
// hàm sử dụng các phím mũi tên để di chuyển cam
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
// hàm reset xe về điểm ban đầu
void reset() {
    speed = steering = 0.0f;
    camx = 10.0, camy = 0.0, camz = 15.0;
    xpos = zpos = 0.0f;
    direction = 0.0f;
    PlaySound(NULL, 0, 0);
    amthanh = 0;
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
    bitmap_output(-7.5, 6, 0.50, "CAC CHUC NANG DUNG DE DIEU KHIEN XE");
    bitmap_output(-7.5, 4, 0.50, "1. RESET THE CAMERA - USE 'R' OR 'r'");
    bitmap_output(-7.5, 3, 0.50, "2. TANG TOC DO CUA XE 'W' USE 'w'");
    bitmap_output(-7.5, 2, 0.50, "3. GIAM TOC DO CUA XE 'S' USE 's'");
    bitmap_output(-7.5, 1, 0.50, "4. RE PHAI 'D' USE 'd'");
    bitmap_output(-7.5, 0, 0.50, "5. RE TRAI 'A' USE 'a'");
    bitmap_output(-7.5, -1, 0.50, "6. ZOOM VAO - USE 'UPWARD ARROW'");
    bitmap_output(-7.5, -2, 0.50, "7. ZOOM RA - USE 'DOWNWARD ARROW'");
    bitmap_output(-7.5, -3, 0.50, "8. CHUYEN CAM SANG TRAI - DUNG 'LEFT ARROW'");
    bitmap_output(-7.5, -4, 0.50, "9. CHUYEN CAM SANG PHAI - DUNG 'RIGHT ARROW'");
    bitmap_output(-7.5, -5, 0.50, "10. SU DUNG CHUOT TRAI DE THAY DOI TOA DO CUA KHUNG NHIN");
    bitmap_output(-7.5, -6, 0.50, "10. SU DUNG CHUOT PHAI DE ZOOM RA/VAO KHUNG NHIN");
    bitmap_output(-7.5, -7, 0.50, "PLEASE PRESS C TO CONTINUE");
    glutSwapBuffers();
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
    case 'V':
    case 'v':
        if (Flag2 == 0) Flag2 = 1;
        else Flag2 = 0;
        break;
    case 'R':
    case 'r':
        reset();
        break;
    case 'W':
    case 'w':
        //key up
        speed += INC_SPEED;
        /*if (amthanh == 0)
        {
            amthanh = 1;
            PlaySound(L"motorcycle-ride-01.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        }*/
        break;
    case 'S':
    case 's':
        // key down
        speed -= INC_SPEED;
        /*if (amthanh == 1)
        {
            amthanh = 0;
            PlaySound(L"motorcycle-idle-01.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        }*/
        break;
    case 'A':
    case 'a':
        if (steering < HANDLE_LIMIT)
            steering += INC_STEERING;
        nachphai += 2;
        if (nachphai >= 130)
            nachphai = 130;
        tayphai += 2;
        if (tayphai >= 70)
            tayphai = 70;
        khuyphai += 3;
        if (khuyphai >= 85)
            khuyphai = 85;

        nachtrai += 2;
        if (nachtrai >= 120)
            nachtrai = 120;
        taytrai -= 3;
        if (taytrai <= 45)
            taytrai = 45;
        khuytrai += 1;
        if (khuytrai >= 60)
            khuytrai = 60;

        break;
    case 'D':
    case 'd':
        if (steering > -HANDLE_LIMIT)
            steering -= INC_STEERING;

        nachphai -= 2;
        if (nachphai <= 90)
            nachphai = 90;
        khuyphai -= 3;
        if (khuyphai <= 25)
            khuyphai = 25;
        tayphai -= 2;
        if (tayphai <= 30)
            tayphai = 30;

        nachtrai -= 2;
        if (nachtrai <= 80)
            nachtrai = 80;
        taytrai += 3;
        if (taytrai >= 105)
            taytrai = 105;
        khuytrai -= 1;
        if (khuytrai <= 40)
            khuytrai = 40;
        break;
    case 'M':
    case 'm':
        glutDisplayFunc(operations_window);
        break;
    case 'C':
    case 'c':
        glutDisplayFunc(rendenScene2);
        break;
    case 'x':
        PlaySound(NULL, 0, 0);
        break;
    }
}
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1366, 768);
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
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);

    /* Setup floor plane for projected shadow calculations. */
    findPlane(floorPlane, floorVertices[1], floorVertices[2], floorVertices[3]);
    glutMainLoop();
    return 0;
}