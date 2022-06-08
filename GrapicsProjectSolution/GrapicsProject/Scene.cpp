#include "Scene.h"
#include <windows.h>

GLfloat light_amb[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_specular[] = { 1, 1, 1, 1.0 };

Camera Cam;
#pragma region Models
Model Car;
Model Track;
#pragma endregion

void InitLight()
{
    GLfloat LightPosition[] = { 0.0, 2.0, 0.0, 1.0 };
    glEnable(GL_LIGHTING);      //���� Ȱ��ȭ
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb); //�ֺ��� ����
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); //Ȯ�걤 ����
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); //�ݻ籤 ����
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
}
void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_SMOOTH);    //���� ���̵�
    glEnable(GL_DEPTH_TEST); // ���̹���
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_FRONT);
    Speed = 0;
    InitLight();
    modelinit();
    Cam.Init(glm::vec3(0, 1, 0));
}
void modelinit() {

    Car = Model();
    Car.SetPosition(glm::vec3(-20, 0, 0));
    Car.SetRotation(90, glm::vec3(0, 1, 0));
    Car.SetRotation(180.f, glm::vec3(0, 1, 0));
    Car.LoadObj("Data/Car/Car.obj", Car.vertices, Car.faces, Car.uvs, Car.normals);
    Car.Scale(glm::vec3(0.1, 0.1, 0.1));
    Car.SetCollider();

    Track = Model();
    Track.LoadObj("Data/Track/Track.obj", Track.vertices, Track.faces, Track.uvs, Track.normals);
    Track.SetPosition(glm::vec3(0, -2, 0));
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PerspectiveSetting();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    CameraSetting();

    // Car
    glPushMatrix();
    Car.Translate();
    Car.RotateAngle();
    Car.DrawSurface();
    glPopMatrix();

    //Track
    glPushMatrix();
    Track.Translate();
    Track.DrawSurface();
    glPopMatrix();


    system("cls");
    glutSwapBuffers();
}


void PerspectiveSetting() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1000.0f / 600.0f, 0.1f, 100.0f);
}

void CameraSetting() {
    if (Cam.is_CarView) {
        Cam.InCar(Car.position, Car.front);
    }
    else {
        Cam.OutCar(Car.position);
    }
    gluLookAt(Cam.eye.x, Cam.eye.y, Cam.eye.z,
        Cam.at.x, Cam.at.y, Cam.at.z,
        Cam.up.x, Cam.up.y, Cam.up.z);
}