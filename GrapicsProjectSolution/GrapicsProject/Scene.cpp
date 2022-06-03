#include "Scene.h"



float g_fDistance = -4.5f;
float g_fSpinX = 0.0f;
float g_fSpinY = 0.0f;


static POINT ptLastMousePosit;
static POINT ptCurrentMousePosit;
static bool bMousing;

GLfloat light_amb[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_specular[] = { 1, 1, 1, 1.0 };

Model Car;
camera Cam;
Model Bunny;
void InitLight()
{
    GLfloat LightPosition[] = { 0.0, 2.0, 0.0, 1.0 };
    glEnable(GL_LIGHTING);      //조명 활성화
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb); //주변광 설정
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); //확산광 설정
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); //반사광 설정
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_SMOOTH);    //구로 셰이딩
    glEnable(GL_DEPTH_TEST); // 깊이버퍼
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_FRONT);
    InitLight();

    Car = Model();
    Car.Translate(glm::vec3(0, 0, 0));
    Car.LoadObj("Data/bunny/bunny.obj", Car.vertices, Car.faces, Car.uvs, Car.normals);
    Car.Scale(glm::vec3(0.5,0.5,0.5));
    printf("모델");
    Bunny = Model();
    Bunny.LoadObj("Data/bunny/bunny.obj", Bunny.vertices, Bunny.faces, Bunny.uvs, Bunny.normals);
    Bunny.Scale(glm::vec3(0.1, 0.1, 0.1));
    Cam.Start(glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    Speed = 1;
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    CameraSetting();

    glPushMatrix();
    Car.Translate();
    Car.RotateAngle();
    Car.DrawSurface();
    glPopMatrix();
    glPushMatrix();
    Bunny.Translate(glm::vec3(0, 0, 0));
    Bunny.DrawSurface();
    glPopMatrix();
    glutSwapBuffers();
}

void PerspectiveSetting() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 640.0f / 480.0f, 0.1f, 1000.0f);
}
void CameraSetting() {
    
    gluLookAt(Cam.eye.x, Cam.eye.y, Cam.eye.z, Cam.at.x, Cam.at.y, Cam.at.z, Cam.up.x, Cam.up.y, Cam.up.z);
}

