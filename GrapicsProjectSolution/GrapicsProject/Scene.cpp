#include "Scene.h"
#include <windows.h>

GLfloat light_amb[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_specular[] = { 1, 1, 1, 1.0 };

// 카메라
camera Cam;
#pragma region 모델선언부
Model Car;
Model Bunny;
#pragma endregion

GLuint tex[7];   // Texture Mapping을 하기 위한 Texture 이미지의 개수를 위한 배열 변수

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
// 각종 초기화 함수들의 모임
void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_SMOOTH);    //구로 셰이딩
    glEnable(GL_DEPTH_TEST); // 깊이버퍼
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_FRONT);
    Acceleration = 0;
    Speed = 0;
    InitLight();
    modelinit();
    caminit();
}
// 모델들 초기화하는 함수
void modelinit() {
    /* 모델 선언시 */
    // 모델 전역변수로 선언
    // 모델에 모델 클래스 할당
    // 모델 모델 초기 포지션 할당
    // 모델 로드
    // 모델 크기 조정

    Car = Model();
    Car.SetPosition(glm::vec3(0, 0, 0));
    Car.LoadObj("Data/bunny/bunny.obj", Car.vertices, Car.faces, Car.uvs, Car.normals);
    Car.Scale(glm::vec3(0.1, 0.1, 0.1));
    Car.SetRotation(180.f, glm::vec3(0, 1, 0));
    Car.SetCollider();

    Bunny = Model();
    Bunny.LoadObj("Data/bunny/bunny.obj", Bunny.vertices, Bunny.faces, Bunny.uvs, Bunny.normals);
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
    Car.DrawSurface();
    glPopMatrix();

    glPushMatrix();
    Bunny.SetPosition(glm::vec3(0, 0, 0));
    Bunny.Translate();
    Bunny.DrawSurface();
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