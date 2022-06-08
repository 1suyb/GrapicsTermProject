#include "Scene.h"
#include <windows.h>

GLfloat light_amb[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_specular[] = { 1, 1, 1, 1.0 };

GLfloat Car_mat_amb[] = { 0.2, 0 , 0, 1.0 }; // /주변 반사
GLfloat Car_mat_diffuse[] = { 1, 0.5, 0.5, 1.0 }; // 확산 반사 
GLfloat Car_mat_specular[] = { 0, 0, 0, 1 }; // 경면 반사

// ī�޶�
camera Cam;
#pragma region �𵨼����
Model Car;
Model Bunny;
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
// ���� �ʱ�ȭ �Լ����� ����
void init() {
    //loadTexture(); // 이거하면 전체적으로 어두워져요

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_SMOOTH);    //���� ���̵�
    glEnable(GL_DEPTH_TEST); // ���̹���
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_FRONT);
    Acceleration = 0;
    Speed = 0;
    InitLight();
    modelinit();
    caminit();

    addBox(glm::vec3(-10, -10, -5), glm::vec3(10, 10, 20));

}
// �𵨵� �ʱ�ȭ�ϴ� �Լ�
void modelinit() {
    /* �� ����� */
    // �� ���������� ����
    // �𵨿� �� Ŭ���� �Ҵ�
    // �� �� �ʱ� ������ �Ҵ�
    // �� �ε�
    // �� ũ�� ����

    Car = Model();
    Car.SetPosition(glm::vec3(0, 0, 0));
    Car.LoadObj("Data/Porsche/Porsche_911_GT2.obj", Car.vertices, Car.faces, Car.uvs, Car.uvindices, Car.normals, Car.normalindices);
    Car.Scale(glm::vec3(0.1, 0.1, 0.1));
    Car.SetRotation(180.f, glm::vec3(0, 1, 0));
    Car.SetCollider();

    Bunny = Model();
    Bunny.LoadObj("Data/Porsche/Porsche_911_GT2.obj", Bunny.vertices, Bunny.faces, Bunny.uvs, Bunny.uvindices, Bunny.normals, Bunny.normalindices);
    Bunny.Scale(glm::vec3(0.01, 0.01, 0.01));

}

void caminit() {
    Cam.Start(glm::vec3(0, 1, 0), glm::vec3(1, -1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0.05, 0));
    InCarView = true;
    //Cam.InCar(Car.position,glm::vec3(0,0.05,0),Car.front);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PerspectiveSetting();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    CameraSetting();

    glPushMatrix();
    Car.Translate();
    Car.RotateAngle();

    //glEnable(GL_TEXTURE_2D);
    ///*glMaterialfv(GL_FRONT, GL_AMBIENT, Car_mat_amb);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, Car_mat_diffuse);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, Car_mat_specular);*/
    //
    //glBindTexture(GL_TEXTURE_2D, g_textureID[2]);
    
    Car.DrawSurface(Car.vertices, Car.normals, Car.uvs, Car.uvindices, Car.normalindices, Car.faces);
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    Bunny.SetPosition(glm::vec3(0, 0, 0));
    Bunny.Translate();
    /*glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, g_textureID[2]);*/
    Bunny.DrawSurface(Bunny.vertices, Bunny.normals, Bunny.uvs,Bunny.uvindices,Bunny.normalindices, Bunny.faces);
    /*glDisable(GL_TEXTURE_2D);*/
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 0, -75);
    Track.DrawTrack(Track.vertices2, Track.normals2, Track.faces2);
    glPopMatrix();
    for (int i = 0; i < boxes.size(); i++)
    {
        glPushMatrix();
        glTranslatef(boxes[i].p[0], boxes[i].p[1], boxes[i].p[2]);        
        //glBindTexture(GL_TEXTURE_2D, g_textureID[0]);
        texturedCube(boxes[i].r);
        glPopMatrix();
    }
    system("cls");


    glutSwapBuffers();
}


void PerspectiveSetting() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1000.0f / 600.0f, 0.1f, 100.0f);
}
void CameraSetting() {
    if (InCarView) {
        Cam.InCar(Car.position, Car.front);
    }
    else {
        Cam.OutCar(Car.position);
    }
    gluLookAt(Cam.eye.x, Cam.eye.y, Cam.eye.z,
        Cam.at.x, Cam.at.y, Cam.at.z,
        Cam.up.x, Cam.up.y, Cam.up.z);
}