#include "Scene.h"
#include "Skybox.h"
#include <glaux.h>
#include <windows.h>

GLfloat light_amb[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_specular[] = { 1, 1, 1, 1.0 };

GLfloat Car_mat_amb[] = { 0.2, 0 , 0, 1.0 }; // /주변 반사
GLfloat Car_mat_diffuse[] = { 1, 0.5, 0.5, 1.0 }; // 확산 반사 
GLfloat Car_mat_specular[] = { 0, 0, 0, 1 }; // 경면 반사

Camera Cam;
#pragma region �𵨼����
Model Car;
Model Track;
#pragma endregion

float r = 1000.0f;


void init() {
    loadTexture();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glShadeModel(GL_SMOOTH);    //���� ���̵�
    glEnable(GL_DEPTH_TEST); // ���̹���
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_FRONT);
    Speed = 0;
    modelinit();
    Cam.Init(glm::vec3(0.5, 1.5, 0));
    addBox(glm::vec3(-10, -10, -5), glm::vec3(10, 10, 20));

}
void modelinit() {
    Car = Model();
    Car.SetPosition(glm::vec3(0, 0, 0));
    Car.LoadObj("Data/Porsche/Porsche_911_GT2.obj", Car.vertices, Car.faces, Car.uvs, Car.uvindices, Car.normals, Car.normalindices);
    Car.Scale(glm::vec3(0.1, 0.1, 0.1)); 
    Car.SetRotation(180.f, glm::vec3(0, 1, 0));
    Car.SetCollider();

    Track = Model();
    Track.LoadObj("Data/Track/Track.obj", Track.vertices, Track.faces, Track.uvs, Track.uvindices, Track.normals, Track.normalindices);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PerspectiveSetting();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    CameraSetting();
    gluLookAt(0, 50, 100, 0.0, 50.0, 0.0, 0.0, 1.0, 0.0);  // 카메라의 위치를 제어한다.
    // Car
    glPushMatrix();
    Car.Translate();
    Car.RotateAngle();
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
    Track.DrawSurface();
    glPopMatrix();

    //Skybox
    // Skybox의 앞면을 Rendering 한다.
    //glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-r, -r / 2, -r);
    glTexCoord2f(1, 0); glVertex3f(r, -r / 2, -r);
    glTexCoord2f(1, 1); glVertex3f(r, r, -r);
    glTexCoord2f(0, 1); glVertex3f(-r, r, -r);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();

    // Skybox의 뒷면을 Rendering 한다.
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(r, -r / 2, r);
    glTexCoord2f(1, 0); glVertex3f(-r, -r / 2, r);
    glTexCoord2f(1, 1); glVertex3f(-r, r, r);
    glTexCoord2f(0, 1); glVertex3f(r, r, r);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();

    // Skybox의 오른쪽 면을 Rendering 한다.
    glBindTexture(GL_TEXTURE_2D, tex[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(r, -r / 2, -r);
    glTexCoord2f(1, 0); glVertex3f(r, -r / 2, r);
    glTexCoord2f(1, 1); glVertex3f(r, r, r);
    glTexCoord2f(0, 1); glVertex3f(r, r, -r);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();

    // Skybox의 왼쪽 면을 Rendering 한다.
    glBindTexture(GL_TEXTURE_2D, tex[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-r, -r / 2, r);
    glTexCoord2f(1, 0); glVertex3f(-r, -r / 2, -r);
    glTexCoord2f(1, 1); glVertex3f(-r, r, -r);
    glTexCoord2f(0, 1); glVertex3f(-r, r, r);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();

    // Skybox의 윗면을 Rendering 한다.
    glBindTexture(GL_TEXTURE_2D, tex[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-r, r, -r);
    glTexCoord2f(1, 0); glVertex3f(r, r, -r);
    glTexCoord2f(1, 1); glVertex3f(r, r, r);
    glTexCoord2f(0, 1); glVertex3f(-r, r, r);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();

    // Skybox의 아랫면을 Rendering 한다.
    glBindTexture(GL_TEXTURE_2D, tex[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-r, -r / 2, r);
    glTexCoord2f(1, 0); glVertex3f(r, -r / 2, r);
    glTexCoord2f(1, 1); glVertex3f(r, -r / 2, -r);
    glTexCoord2f(0, 1); glVertex3f(-r, -r / 2, -r);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();

    // Skybox의 지표면을 Rendering 한다.
    glBindTexture(GL_TEXTURE_2D, tex[6]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-r, 0.1f, r);
    glTexCoord2f(1, 0); glVertex3f(r, 0.1f, r);
    glTexCoord2f(1, 1); glVertex3f(r, 0.1f, -r);
    glTexCoord2f(0, 1); glVertex3f(-r, 0.1f, -r);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    //glPopMatrix();

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

AUX_RGBImageRec* LoadBMP(char* Filename) {  // Bitmap 이미지를 호출한다.
    FILE* File = NULL;

    if (!Filename) return NULL;
    File = fopen(Filename, "r");
    if (File) {
        fclose(File);
        return auxDIBImageLoad(Filename);
    }

    return NULL;
}

void LoadGLTextures() {  // Bitmap 이미지 7개를 호출하여 Texture 이미지로 변환한다.
    AUX_RGBImageRec* texRec[7];
    memset(texRec, 0, sizeof(void*) * 7);

    if ((texRec[0] = LoadBMP("Data/skybox1_posz.bmp")) &&
        (texRec[1] = LoadBMP("Data/skybox1_negz.bmp")) &&
        (texRec[2] = LoadBMP("Data/skybox1_posx.bmp")) &&
        (texRec[3] = LoadBMP("Data/skybox1_negx.bmp")) &&
        (texRec[4] = LoadBMP("Data/skybox1_posy.bmp")) &&
        (texRec[5] = LoadBMP("Data/skybox1_negy.bmp")) &&
        (texRec[6] = LoadBMP("Data/Lawn2.bmp"))) {

        for (int i = 0; i < 7; i++) {
            glGenTextures(1, &tex[i]);
            glBindTexture(GL_TEXTURE_2D, tex[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, 3, texRec[i]->sizeX, texRec[i]->sizeY, 0,
                GL_RGB, GL_UNSIGNED_BYTE, texRec[i]->data);
        }
    }

    for (int i = 0; i < 7; i++) {
        if (texRec[i]) {
            if (texRec[i]->data) free(texRec[i]->data);
            free(texRec[i]);
        }
    }

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}