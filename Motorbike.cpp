#include "Definition.h"

extern void toMau(GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat shininess, GLfloat lowAmbient[]);
extern void DrawCircle(float cx, float cy, float r, int num_segments, float cphx, float cphy, float cphz);
extern void cubefill(float h, float w, float size);

// denxe
// rev là gía trị đệ quy báo hiệu lấy đối xứng qua trục x
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
// dán texture vào mặt đèn xe
void denXePlus(int isShadow, unsigned int texDenxe) {
    if (isShadow == 0) {
        glEnable(GL_TEXTURE_2D);
        //
        //LoadTexture("denxe.bmp");
        glBindTexture(GL_TEXTURE_2D, texDenxe);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    }
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // ket hop voi lighting
    //glColor3f(1,1,0);
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.00 + 0.11, 0.0 - 0.02); glVertex3f(3.5, 1, 1.5);
    glTexCoord2f(0.00 + 0.11, 1.0 - 0.02); glVertex3f(4, -2, 1.5);
    glTexCoord2f(0.75 + 0.11, 1.0 - 0.02); glVertex3f(4, -2, -1.5);
    glTexCoord2f(0.75 + 0.11, 0.0 - 0.02); glVertex3f(3.5, 1, -1.5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
// dau xe 
void dauxe(int isShadow, unsigned int texVant, unsigned int texDenxe) {
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
    // dán texture cho mặt đo vận tốc
    glPushMatrix();
    if (isShadow == 0) {
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glBindTexture(GL_TEXTURE_2D, texVant);
    }
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.00 + 0.01, 0.0 + 0.18);glVertex3f(0, 2, -2);
    glTexCoord2f(0.00 + 0.01, 0.5 + 0.18);glVertex3f(2, 2, -2);
    glTexCoord2f(0.25 + 0.01, 0.75 + 0.18);glVertex3f(3, 2.5, -1);
    glTexCoord2f(0.75 + 0.01, 0.75 + 0.18); glVertex3f(3, 2.5, 1.0);
    glTexCoord2f(1.0 + 0.01, 0.5 + 0.18); glVertex3f(2.0, 2, 2.0);
    glTexCoord2f(1.0 + 0.01, 0.0 + 0.18); glVertex3f(0.0, 2, 2.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
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
    glTranslatef(0, 1.15, 0);
    glRotatef(-10, 0.0, 0.0, 1.0);
    denXePlus(isShadow, texDenxe);
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
    //glColor3f(1.0, 0, 0);
    glVertex3f(2.2, 1, 5);
    glVertex3f(2.2, 1.2, 5);
    glVertex3f(2, 1.2, 5);
    glVertex3f(2, 1, 5);
    glEnd();

    glTranslatef(2.1, 1.1, 5);
    //glColor3f(0.1, 0.5, 0);
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
    //glColor3f(0.75, 0.75, 0.75);
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
void fulldauxe(int isShadow, unsigned int texVant, unsigned int texDenxe, GLfloat spinb) {
    // dau xe + tay ga
    glPushMatrix();
    toMau(qaRed, qaRed, qaWhite, 128.0, qaLowAmbient);
    //dauxe(FlagShadow,matVanTocTex,denXeTex);
    dauxe(isShadow, texVant, texDenxe);
    glTranslatef(0, 0, 2);
    glTranslatef(1.0, 1.0, 0.0);
    //maugoc();
    // tay ga
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    tayga();
    glTranslatef(0, 0, -4);
    glRotatef(-180, 1.0, 0.0, 0.0);
    tayga();
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    glPopMatrix();
    //maugoc();

    // phanh phải
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    phanh();
    glPopMatrix();
    //maugoc();
    // phanh trai
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glScalef(1.0, 1.0, -1.0);
    phanh();
    glPopMatrix();
    //maugoc();
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
    glRotatef(-spinb, 0, 0, 1);
    glTranslatef(-3.0, 8.0, 0);
    DrawRims();
    glPopMatrix();

    // chan bun
    //maugoc();
    glPushMatrix();
    toMau(qaRed, qaRed, qaWhite, 128.0, qaLowAmbient);
    // update
    chanBunTruoc(1);
    glPopMatrix();
    //maugoc();

    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    TrucChinhDauXe();
    glPopMatrix();
}
//////////////////
/// than xe
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
// hàm vẽ phần nối giữa thân xe và bánh sau
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
void fixBinhXang(float loi, int rev, int isShadow, unsigned int texLogo) {
    glBegin(GL_POLYGON);
    glVertex3f(3.5, -0.5, loi);
    glVertex3f(3.85, -1.75, loi);
    glVertex3f(3.0, -2.25, loi);
    glVertex3f(-0.5, -1.5, loi);
    glVertex3f(-0.85, -0.25, loi);
    glVertex3f(0.25, 0.25, loi);
    glEnd();
    //
    glPushMatrix();
    if (isShadow == 0) {
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glBindTexture(GL_TEXTURE_2D, texLogo);
    }
    glTranslatef(1.5, -1, 3);
    glRotatef(180, 0, 0, 1.0);
    glTranslatef(-1.5, 1, -3);
    glBegin(GL_QUADS);
    glNormal3f(1.0, -0.15, 0.0);
    glTexCoord2f(0.00, 0.0);glVertex3f(1, -0.75, loi + 0.001);
    glTexCoord2f(0.00, 1.0); glVertex3f(1, -1.75, loi + 0.001);
    glTexCoord2f(1.0, 1.0);glVertex3f(2, -1.75, loi + 0.001);
    glTexCoord2f(1, 0.0); glVertex3f(2, -0.75, loi + 0.001);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glBegin(GL_QUADS);
    // ben tren nguoc chieu
    //glNormal3f(1.0, 0, 0);
    glVertex3f(4, 0, 2.0);
    glVertex3f(4.75, -2, 2.0);
    glVertex3f(3.85, -1.75, loi);
    glVertex3f(3.5, -0.5, loi);

    glNormal3f(0.0, 1.0, 0);
    glVertex3f(4, 0, 2.0);
    glVertex3f(0.0, 1.0, 2.0);
    glVertex3f(0.25, 0.25, loi);
    glVertex3f(3.5, -0.5, loi);

    //glNormal3f(0.0, 1.25, 0);
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

    //glNormal3f(0.0, 1.25, 0);
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
        fixBinhXang(loi, 0, isShadow, texLogo);
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
void fullThanXe(int isShadow, unsigned int texLogo, GLfloat spinb) {
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    trucChinhThanXe();
    glPopMatrix();
    //maugoc();

    //khớp nối chứa ngông xich
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(0, 1.75, 0);
    khopNoiBanhsau();
    glPopMatrix();
    //maugoc();

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
    //maugoc();

    // vẫn là động cơ
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(-2, -6.5, 0);
    bauDongCo2(0, 1.50, 2.5, 1, -3, 1.75, 0);
    bauDongCo2(0, 1.0, 2.75, 1, -3, 1.75, 0);
    glRotatef(10, 0, 0, 1.0);
    bauDongCo2(7, 1.50, 2.25, 1, -4.5, 2.25, 0);
    glPopMatrix();
    //maugoc();

    // giam soc sau
    glPushMatrix();
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(0, 1.5, 0);
    glTranslatef(-12.2, -0.2, 0);
    giamsoctruoc(-20);
    glPopMatrix();
    //maugoc();

    // giam soc sau
    glPushMatrix();
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(0, 1.5, 0);
    glTranslatef(-12.2, -0.2, 0);
    glScalef(1.0, 1.0, -1.0);
    giamsoctruoc(-20);
    glPopMatrix();
    //maugoc();

    //banh xe
    // to lai mau cho banh xe
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    glPushMatrix();
    glTranslatef(-17, 1.5, 0);
    glTranslatef(3.0, -8.0, 0);
    glRotatef(-spinb, 0, 0, 1);
    glTranslatef(-3.0, 8.0, 0);
    DrawRims();
    glPopMatrix();
    //maugoc();

    // fix binh xang remake
    glPushMatrix();
    toMau(qaRed, qaRed, qaWhite, 128.0, qaLowAmbient);
    fixBinhXang(3, 1, isShadow, texLogo);
    napBinhXang();
    glPopMatrix();
    //maugoc();

    // yen xe
    glPushMatrix();
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(-6.25, 0.0, 0);
    yenXe();
    glPopMatrix();
    //maugoc();

    // dong co phan 1
    glPushMatrix();
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(-1.0, -6.0, 0);
    dongCo();
    bauDongCo2(10, 1.0, 2.25, 1, -2.25, 1.25, 0);
    glPopMatrix();
    //maugoc();

    // dong co phan 2
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(-5.5, -4.0, 0);
    /*glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, denXeTex);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);*/
    //glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    //glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
   /* glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);*/
    dongco2();
    /*glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_2D);*/
    glPopMatrix();
    //maugoc();

    // bô xe
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);

    boXe(1);

    glPopMatrix();
    //maugoc();

    // đuôi xe
    glPushMatrix();
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    duoiXe(1);
    glPopMatrix();
    //maugoc();
}
