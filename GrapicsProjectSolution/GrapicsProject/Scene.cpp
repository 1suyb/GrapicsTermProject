#include "Scene.h"

GLfloat light_amb[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_specular[] = { 1, 1, 1, 1.0 };

GLfloat Car_mat_amb[] = { 0.2, 0 , 0, 1.0 }; // /주변 반사
GLfloat Car_mat_diffuse[] = { 1, 0.5, 0.5, 1.0 }; // 확산 반사 
GLfloat Car_mat_specular[] = { 0, 0, 0, 1 }; // 경면 반사

// 카메라

camera Cam;
#pragma region 모델선언부
Model Car;
Model Bunny;
#pragma endregion


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

    loadTexture();
    srand(time(NULL));

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);    //구로 셰이딩
    glEnable(GL_DEPTH_TEST); // 깊이버퍼
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_FRONT);
    //InitLight();
    modelinit();
    caminit();

    addBox(glm::vec3(-10, -10, -5), glm::vec3(10, 10, 20));

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
    Car.LoadObj("Data/Porsche/Porsche_911_GT2.obj", Car.vertices, Car.faces, Car.uvs, Car.uvindices, Car.normals, Car.normalindices);
    Car.Scale(glm::vec3(0.5, 0.5, 0.5));

    printf("모델");
    Bunny = Model();
    Bunny.LoadObj("Data/Porsche/Porsche_911_GT2.obj", Bunny.vertices, Bunny.faces, Bunny.uvs, Bunny.uvindices, Bunny.normals, Bunny.normalindices);
    Bunny.Scale(glm::vec3(0.1, 0.1, 0.1));
    
}

void caminit() {
    Cam.Start(glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(0, 1, 0));
    Cam.InCar(Car.position);
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
    glMaterialfv(GL_FRONT, GL_AMBIENT, Car_mat_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Car_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Car_mat_specular);
    //glColor3f(0.0, 0.0, 0.0);
    Car.DrawSurface();
    
    glPopMatrix();
    glPushMatrix();
    Bunny.SetPosition(glm::vec3(0, 0, 0));
    Bunny.Translate();
    
    Bunny.DrawSurface();
    
    glPopMatrix();

    for (int i = 0; i < boxes.size(); i++)
    {
        glPushMatrix();
        glTranslatef(boxes[i].p[0], boxes[i].p[1], boxes[i].p[2]);
        glBindTexture(GL_TEXTURE_2D, g_textureID[0]);
        texturedCube(boxes[i].r);
        glPopMatrix();
    }


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

