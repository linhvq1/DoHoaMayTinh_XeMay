#include "Definition.h"

// hàm tô màu cho chất liệu của vật thể
void toMau(GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat shininess, GLfloat lowAmbient[]) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_LIGHT0, GL_AMBIENT, lowAmbient);
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

void drawShowroom(GLint poster1[], GLint texTuong) {
    // to mau tam
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    // sau
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-180.0f, 0, 180.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(-180.0f, 0, -180.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(-180.0f, 170.0f, -180.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(-180.0f, 170.0f, 180.0f);
    glEnd();
    // poster phai
    glBindTexture(GL_TEXTURE_2D, poster1[2]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-179.0f, 20, 100.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-179.0f, 20, -100.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-179.0f, 150.0f, -100.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-179.0f, 150.0f, 100.0f);
    glEnd();
    // sau 2
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(-182.0f, 0, 182.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(-182.0f, 0, -182.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(-182.0f, 170.0f, -182.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(-182.0f, 170.0f, 182.0f);
    glEnd();
    // trai
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(-180.0f, 0, -180.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(180.0f, 0, -180.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(180.0f, 170.0f, -180.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(-180.0f, 170.0f, -180.0f);
    glEnd();
    //poster trai
    glBindTexture(GL_TEXTURE_2D, poster1[0]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(-100.0f, 20, -179.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(100.0f, 20, -179.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(100.0f, 150.0f, -179.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-100.0f, 150.0f, -179.0f);
    glEnd();
    // trai2
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(-182.0f, 0, -182.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(182.0f, 0, -182.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(182.0f, 170.0f, -182.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(-182.0f, 170.0f, -182.0f);
    glEnd();
    //phai
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(180.0f, 0, 180.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(-180.0f, 0, 180.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(-180.0f, 170.0f, 180.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(180.0f, 170.0f, 180.0f);
    glEnd();
    // poster phai
    glBindTexture(GL_TEXTURE_2D, poster1[1]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(100.0f, 20, 179.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-100.0f, 20, 179.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-100.0f, 150.0f, 179.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(100.0f, 150.0f, 179.0f);
    glEnd();
    // phai 2
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(182.0f, 0, 182.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(-182.0f, 0, 182.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(-182.0f, 170.0f, 182.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(182.0f, 170.0f, 182.0f);
    glEnd();
    //truoc
    // ben trai cua
    toMau(qaYellow, qaYellow, qaWhite, 128.0, qaLowAmbient);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1, 1, 1, 0.7f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(181.0f, 0, -180.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(181.0f, 0, -50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(181.0f, 170.0f, -50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(181.0f, 170.0f, -180.0f);
    glEnd();
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    // mep duoi ben trai
    //toMau(qaYellow,qaYellow,qaWhite,128.0,qaLowAmbient);
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(180.0f, 0, -180.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(180.0f, 0, -50.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(180.0f, 20.0f, -50.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(180.0f, 20.0f, -180.0f);
    glEnd();

    //mep duoi ben trai 2
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(182.0f, 0, -180.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(182.0f, 0, -50.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(182.0f, 20.0f, -50.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(182.0f, 20.0f, -180.0f);
    glEnd();
    // canh trai tuong
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(180.0f, 0, -180.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(180.0f, 0, -160.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(180.0f, 170.0f, -160.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(180.0f, 170.0f, -180.0f);
    glEnd();
    // canh trai tuong2
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(182.0f, 0, -182.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(182.0f, 0, -160.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(182.0f, 170.0f, -160.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(182.0f, 170.0f, -182.0f);
    glEnd();
    // cach trai cua
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(180.0f, 0, -70.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(180.0f, 0, -50.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(180.0f, 80.0f, -50.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(180.0f, 80.0f, -70.0f);
    glEnd();
    // cach trai cua 2
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(182.0f, 0, -70.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(182.0f, 0, -50.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(182.0f, 80.0f, -50.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(182.0f, 80.0f, -70.0f);
    glEnd();
    toMau(qaYellow, qaYellow, qaWhite, 128.0, qaLowAmbient);
    // ben phai cua
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1, 1, 1, 0.7f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(181.0f, 0, 50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(181.0f, 0, 180.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(181.0f, 170.0f, 180.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(181.0f, 170.0f, 50.0f);
    glEnd();
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    // mep duoi ben phai
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //toMau(qaYellow, qaYellow, qaWhite, 128.0, qaLowAmbient);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(180.0f, 0, 180.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(180.0f, 0, 50.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(180.0f, 20.0f, 50.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(180.0f, 20.0f, 180.0f);
    glEnd();
    // mep duoi ben phai 2
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(182.0f, 0, 180.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(182.0f, 0, 50.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(182.0f, 20.0f, 50.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(182.0f, 20.0f, 180.0f);
    glEnd();
    // canh phai tuong
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(180.0f, 0, 180.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(180.0f, 0, 160.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(180.0f, 170.0f, 160.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(180.0f, 170.0f, 180.0f);
    glEnd();
    // canh phai tuong2
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(182.0f, 0, 182.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(182.0f, 0, 160.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(182.0f, 170.0f, 160.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(182.0f, 170.0f, 182.0f);
    glEnd();
    // cach phai cua
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(180.0f, 0, 70.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(180.0f, 0, 50.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(180.0f, 80.0f, 50.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(180.0f, 80.0f, 70.0f);
    glEnd();
    // cach phai cua 2
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(182.0f, 0, 70.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(182.0f, 0, 50.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(182.0f, 80.0f, 50.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(182.0f, 80.0f, 70.0f);
    glEnd();
    toMau(qaYellow, qaYellow, qaWhite, 128.0, qaLowAmbient);
    //ben tren cua
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1, 1, 1, 0.7f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(181.0f, 80, -50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(181.0f, 80, 50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(181.0f, 170.0f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(181.0f, 170.0f, -50.0f);
    glEnd();
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    // canh tren cua
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(180.0f, 80, -70.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(180.0f, 80, 70.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(180.0f, 100.0f, 70.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(180.0f, 100.0f, -70.0f);
    glEnd();
    // canh tren cua 2
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(182.0f, 80, -70.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(182.0f, 80, 70.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(182.0f, 100.0f, 70.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(182.0f, 100.0f, -70.0f);
    glEnd();
    // canh tren tuong
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(180.0f, 170, -180.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(180.0f, 150, -180.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(180.0f, 150.0f, 180.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(180.0f, 170.0f, 180.0f);
    glEnd();
    // canh tren tuong
    glBindTexture(GL_TEXTURE_2D, texTuong);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(182.0f, 170, -180.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3f(182.0f, 150, -180.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3f(182.0f, 150.0f, 180.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3f(182.0f, 170.0f, 180.0f);
    glEnd();
    //toMau(qaGreen, qaGreen, qaWhite, 128.0, qaLowAmbient);
    glDisable(GL_TEXTURE_2D);
    glLineWidth(5.0);
}

////ro bot
static GLfloat time2 = 0.0;
void daurobot()
{
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0, 0.4, 0);
    glScalef(0.7, 0.9, 1.1);
    glutSolidCube(3);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.0, 0.5, -1);
    //mat
    glRotatef(90, 0, 1, 0);
    GLUquadricObj* quadratic_obj;
    quadratic_obj = gluNewQuadric();
    gluCylinder(quadratic_obj, 0.4, 0.4, 0.2, 64, 64);

    glTranslatef(0, 0, 0.2);

    toMau(qaWhite, qaWhite, qaWhite, 128.0, qaLowAmbient);
    DrawCircle(0, 0, 0.4, 32, 0, 0, 1.0);
    glTranslatef(0, 0, 0.01);
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    DrawCircle(0, 0, 0.3, 32, 0, 0, 1.0);
    //tai
    toMau(qaGrey, qaGrey, qaGrey, 128.0, qaLowAmbient);
    glTranslatef(-2, 0, -0.2);
    gluCylinder(quadratic_obj, 0.4, 0.4, 0.2, 64, 64);
    glTranslatef(0, 0, 0.2);
    toMau(qaWhite, qaWhite, qaWhite, 128.0, qaLowAmbient);
    DrawCircle(0, 0, 0.4, 32, 0, 0, 1.0);
    glTranslatef(0, 0, 0.01);
    toMau(qaBlack, qaBlack, qaWhite, 128.0, qaLowAmbient);
    DrawCircle(0, 0, 0.3, 32, 0, 0, 1.0);
    toMau(qaGrey, qaGrey, qaGrey, 128.0, qaLowAmbient);
    glTranslatef(-1, 0, -1);
    glRotatef(90, 0, 1, 0);
    gluCylinder(quadratic_obj, 0.4, 0.4, 4, 64, 64);
    toMau(qaRed, qaRed, qaWhite, 128.0, qaLowAmbient);

    glRotatef(180, 1, 0, 0);
    DrawCircle(0, 0, 0.4, 32, 0, 0, 1.0);
    glTranslatef(0, 0, -4);
    glRotatef(180, 1, 0, 0);
    DrawCircle(0, 0, 0.4, 32, 0, 0, 1.0);
    glTranslatef(0, 0, -2);
    glRotatef(-90, 1, 0, 0);

    //cot song tin hieu
    gluCylinder(quadratic_obj, 0.4, 0.1, 2.5, 64, 64);
    glTranslatef(0, 0, 2.5);
    if (time2 > 10)
    {
        toMau(qaYellow, qaYellow, qaWhite, 128.0, qaLowAmbient);
    }
    if (time2 < 10)
    {
        toMau(qaWhite, qaWhite, qaWhite, 128.0, qaLowAmbient);
    }
    glutSolidSphere(0.4, 64, 64);
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    //mieng
    glTranslatef(-0.8, 0, -3.5);
    glutSolidSphere(0.4, 64, 64);
    glPopMatrix();
    glPopMatrix();
    //co
    glPushMatrix();
    glRotated(-90, 1, 0, 0);
    glTranslatef(0, 0, -1);
    glScalef(1, 1.5, 0.4);
    glutSolidCube(1);
    glTranslatef(0, 0, -1);
    glScalef(1, 1.2, 1);
    glutSolidCube(1);
    glPopMatrix();
    time2 = time2 + 1;
    if (time2 > 20)
    {
        time2 = 0;
    }
}
void thanrobot(GLfloat nachphai, GLfloat tayphai, GLfloat khuyphai, GLfloat nachtrai, GLfloat taytrai, GLfloat khuytrai)
{
    //than 
    GLUquadricObj* quadratic_obj;
    quadratic_obj = gluNewQuadric();
    toMau(qaRed, qaRed, qaWhite, 128.0, qaLowAmbient);
    glRotatef(90, -1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0, 0, -1.6);
    glPopMatrix();
    glTranslatef(0, 0, -7.5);
    glPushMatrix();
    glTranslatef(0, 0, 2.5);
    glScalef(0.8, 1.2, 1.75);
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glutSolidCube(4);
    glPopMatrix();
    glPushMatrix();
    if (time2 < 10)
    {
        toMau(qaYellow, qaYellow, qaWhite, 128.0, qaLowAmbient);
    }
    if (time2 > 20)
    {
        toMau(qaWhite, qaWhite, qaWhite, 128.0, qaLowAmbient);
    }
    //toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(1.6, 1.6, 1.2);
    glutSolidSphere(0.4, 64, 64);
    glTranslatef(0, -3.2, 0);
    glutSolidSphere(0.4, 64, 64);

    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glTranslatef(-0.05, 1.6, 0.2);
    glScalef(0.2, 2, 0.2);
    glutSolidCube(1);
    glTranslatef(0, 0, -2.6);
    glutSolidCube(1);
    toMau(qaGrey, qaGrey, qaWhite, 128.0, qaLowAmbient);
    glPopMatrix();
    //canh tay phai
    glPushMatrix();
    glTranslatef(0.5, 3, 4.5);
    //đẩy cánh tay về trước sau 
    glRotatef(-nachphai, -1.0, -1.0, -1.0);
    glRotatef(-nachphai, -1.0, 0.0, -1.0);
    glutSolidSphere(1, 64, 64);


    gluCylinder(quadratic_obj, 1, 0.8, 4, 64, 64);
    glTranslatef(0, 0, 4);
    glutSolidSphere(0.8, 64, 64);
    //nâng tay cao thấp 
    glRotatef(tayphai, -1.0, 0.0, 1.0);
    //di chuyển bản tay sang phải trái 
    glRotatef(khuyphai, 0.0, 1.0, 0.0);

    gluCylinder(quadratic_obj, 0.8, 0.6, 5, 64, 64);
    glTranslatef(0, -0.2, 5.3);
    glutSolidSphere(0.8, 64, 64);
    glTranslatef(0, -3.5, -6.8);

    glPopMatrix();
    //canh tay trai
    glPushMatrix();
    glTranslatef(0.5, -3, 4.5);
    //đẩy cánh tay về trước sau 
    glRotatef(-nachtrai, -1.0, 1.0, -0.2);
    //canh tay cao thap
    glRotatef(-nachtrai, -1.5, -1.2, 1.4);
    glutSolidSphere(1, 64, 64);

    gluCylinder(quadratic_obj, 1, 0.8, 4, 64, 64);
    glTranslatef(0, 0, 4);
    glutSolidSphere(0.8, 64, 64);
    //di chuyển bản tay sang phải trái 
    glRotatef(taytrai, 1.0, 1.0, 0.0);

    //nâng tay cao thấp 
    glRotatef(-khuytrai, 1.0, 0.0, 1.0);

    gluCylinder(quadratic_obj, 0.8, 0.6, 5, 64, 64);
    glTranslatef(0, -0.2, 5.2);
    glutSolidSphere(0.8, 64, 64);
    glTranslatef(0, -3.5, -6.8);

    glPopMatrix();

    //chan tu cho nay
    glPushMatrix();
    glScalef(0.9, 1, 0.8);

    //chan phai
    glPushMatrix();
    glTranslatef(0.5, 3, 0);
    glutSolidSphere(1.3, 64, 64);
    glRotatef(120, 0.0, 1.0, 0.2);
    gluCylinder(quadratic_obj, 1.3, 1.1, 4, 64, 64);
    glTranslatef(0, 0, 4);
    glutSolidSphere(1.1, 64, 64);
    glRotatef(90, 0.3, 1.0, -0.2);
    gluCylinder(quadratic_obj, 1.1, 0.8, 5, 64, 64);
    glTranslatef(-0.5, 0, 5);
    glScalef(1.5, 1, 0.5);
    glutSolidSphere(1.1, 64, 64);
    glPopMatrix();
    //chan trai
    glPushMatrix();
    glTranslatef(0.5, -3, 0);
    glutSolidSphere(1.3, 64, 64);
    glRotatef(120, 0.0, 1.0, -0.2);
    gluCylinder(quadratic_obj, 1.3, 1.1, 4, 64, 64);
    glTranslatef(0, 0, 4);
    glutSolidSphere(1.1, 64, 64);
    glRotatef(90, -0.3, 1.0, 0.2);
    gluCylinder(quadratic_obj, 1.1, 0.8, 5, 64, 64);
    glTranslatef(-0.5, 0, 5);
    glScalef(1.5, 1, 0.5);
    glutSolidSphere(1.1, 64, 64);
    glPopMatrix();
    //thanh de chan
    glRotatef(90, 1, 0, 0);
    glPushMatrix();
    glTranslatef(3, -7.3, -4.5);
    gluCylinder(quadratic_obj, 0.35, 0.35, 9, 64, 64);
    glTranslatef(0, 0, 9);
    DrawCircle(0, 0, 0.35, 64, 0, 0, 1.0);
    glutSolidTorus(0.2, 0.35, 32, 32);
    glTranslatef(0, 0, -9);
    DrawCircle(0, 0, 0.35, 64, 0, 0, 1.0);
    glutSolidTorus(0.2, 0.35, 32, 32);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

}
void robot(GLfloat nachphai, GLfloat tayphai, GLfloat khuyphai, GLfloat nachtrai, GLfloat taytrai, GLfloat khuytrai)
{
    glPushMatrix();
    daurobot();
    glPopMatrix();

    glPushMatrix();
    thanrobot(nachphai, tayphai, khuyphai, nachtrai, taytrai, khuytrai);
    glPopMatrix();
}

////
// hàm vẽ mặt cỏ
void draw_ground(GLint texSan)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texSan);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    // mapping ảnh lên không gian 2 chiều
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-180.0f, 0.01f, 180.0f);
    glTexCoord2f(100.0f, 0.0f); glVertex3f(-180.0f, 0.01f, -180.0f);
    glTexCoord2f(100.0f, 100.0f); glVertex3f(180.0f, 0.01f, -180.0f);
    glTexCoord2f(0.0f, 100.0f); glVertex3f(180.0f, 0.01f, 180.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glTranslatef(0.0, -2, 0.0);
    glTranslatef(0.0, 2, 0.0);
}