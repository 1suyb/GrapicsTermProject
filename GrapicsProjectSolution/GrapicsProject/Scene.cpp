#include "Scene.h"
#include <windows.h>


void nightLight() {
    GLfloat light_amb[] = { 0, 0, 0, 1.0 };
    GLfloat light_diffuse[] = { 1, 1, 1, 1.0 };
    GLfloat light_specular[] = { 1, 1, 1, 1.0 };

    glEnable(GL_LIGHTING); //조명 활성화
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT,light_amb); //주변광 설정
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); //확산광 설정
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); //정반사광 설정
}

void afternoonLight()
{
    GLfloat light_amb[] = { 1, 1, 1, 1.0 };
    GLfloat light_diffuse[] = { 1, 1, 1, 1.0 };
    GLfloat light_specular[] = { 1, 1, 1, 1.0 };

    glEnable(GL_LIGHTING); //조명 활성화
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb); //주변광 설정
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); //확산광 설정
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); //정반사광 설정
}

GLuint g_textureID[4];

Camera Cam;
#pragma region �𵨼����
Model Car;
Model Track;
Box* Boxes;
#pragma endregion





void init() {
    loadTexture();
    LoadGLTextures();
    afternoonLight();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glShadeModel(GL_SMOOTH);    //���� ���̵�
    glEnable(GL_DEPTH_TEST); // ���̹���
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_FRONT);
    Speed = 0;
    modelinit();
    Cam.Init(glm::vec3(0.5, 1.5, 0));

}
void modelinit() {
    Car = Model();
    Car.SetPosition(glm::vec3(0, 0, 0));
    Car.LoadObj("Data/Porsche/Porsche_911_GT2.obj", Car.vertices, Car.faces, Car.uvs, Car.uvindices, Car.normals, Car.normalindices);
    Car.Scale(glm::vec3(0.1, 0.1, 0.1)); 
    Car.SetRotation(-90.f, glm::vec3(0, 1, 0));
    Car.SetCollider();

    Track = Model();
    Track.LoadObj("Data/Track/Track.obj", Track.vertices, Track.faces, Track.uvs, Track.uvindices, Track.normals, Track.normalindices);
    Track.SetPosition(glm::vec3(0, -2.f, 0));

    Boxes = new Box[10];
}

void render() {

    GLfloat Car_mat_amb[] = { 1, 1 , 1, 1.0 };
    GLfloat Car_mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat Car_mat_specular[] = { 0, 0, 0, 1 };
    GLfloat LightPosition[] = { 0.0, 0.0, 0.0, 1.0 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PerspectiveSetting();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    CameraSetting();

    // Car
    glPushMatrix();
    Car.Translate();
    Car.RotateAngle();
    glLightfv(GL_LIGHT0, GL_POSITION,
        LightPosition);
    glDisable(GL_LIGHTING);
    glEnable(GL_LIGHTING);

    glMaterialfv(GL_FRONT, GL_AMBIENT,
        Car_mat_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,
        Car_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,
        Car_mat_specular);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, g_textureID[2]);  
    Car.DrawSurface();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    //Track
    glPushMatrix();
    glColor3f(0.f, 0.f, 0.f);
    Track.Translate();
    Track.DrawSurface();
    glColor3f(1,1,1);
    glPopMatrix();

    DrawSkyBox();
    
    glBindTexture(GL_TEXTURE_2D, g_textureID[0]);
    Boxes[0].DrawCube(1);
    glBindTexture(GL_TEXTURE_2D, 0);
    system("cls");
    glutSwapBuffers();
}


void PerspectiveSetting() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1000.0f / 600.0f, 1.0f, 2000.0f);
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

void loadTexture() {
    //경로로 부터 이미지 파일 불러오기
    AUX_RGBImageRec* pBoxImage = auxDIBImageLoad("Data/woodBox.bmp");
    AUX_RGBImageRec* pBoosterImage = auxDIBImageLoad("Data/booster.bmp");
    AUX_RGBImageRec* pCarImage = auxDIBImageLoad("Data/Porsche/skin00/0000.bmp");

    if (pBoxImage != NULL && pBoosterImage != NULL && pCarImage != NULL) {
        //박스 장애물
        //텍스쳐 생성 (텍스쳐수, 텍스쳐 ID 배열 주소)
        glGenTextures(3, &g_textureID[0]);

        //텍스쳐 파라미터 설정을 위한 부분 (0번 텍스쳐 ID 설정)
        glBindTexture(GL_TEXTURE_2D, g_textureID[0]);

        //텍스쳐 파라미터 설정: 텍스쳐 확대 축소시 필터 처리 방법 설정
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //불러온 이미지 파일을 위에 생성한 텍스쳐ID에 결합
        glTexImage2D(GL_TEXTURE_2D, 0, 3, pBoxImage->sizeX, pBoxImage->sizeY, 0,
            GL_RGB, GL_UNSIGNED_BYTE, pBoxImage->data);

        //부스터 아이템
        //텍스쳐 파라미터 설정을 위한 부분 (1번 텍스쳐 ID 설정)
        glBindTexture(GL_TEXTURE_2D, g_textureID[1]);

        //텍스쳐 파라미터 설정: 텍스쳐 확대 축소시 필터 처리 방법 설정
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //불러온 이미지 파일을 위에 생성한 텍스쳐ID에 결합
        glTexImage2D(GL_TEXTURE_2D, 0, 3, pBoosterImage->sizeX, pBoosterImage->sizeY, 0,
            GL_RGB, GL_UNSIGNED_BYTE, pBoosterImage->data);

        // 차
        //텍스쳐 파라미터 설정을 위한 부분 (1번 텍스쳐 ID 설정)
        glBindTexture(GL_TEXTURE_2D, g_textureID[2]);

        //텍스쳐 파라미터 설정: 텍스쳐 확대 축소시 필터 처리 방법 설정
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

        //glEnable(GL_TEXTURE_GEN_S);
        //glEnable(GL_TEXTURE_GEN_T);

        //불러온 이미지 파일을 위에 생성한 텍스쳐ID에 결합
        glTexImage2D(GL_TEXTURE_2D, 0, 3, pCarImage->sizeX, pCarImage->sizeY, 0,
            GL_RGB, GL_UNSIGNED_BYTE, pCarImage->data);

        //불러온 텍스쳐 파일 데이터 삭제
        if (pBoxImage->data)
            free(pBoxImage->data);

        if (pBoosterImage->data)
            free(pBoosterImage->data);
        if (pCarImage->data)
            free(pCarImage->data);

        free(pBoxImage);
        free(pBoosterImage);
        free(pCarImage);
    }
}
