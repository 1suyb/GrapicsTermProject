#include "Scene.h"
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
Model Bunny;
Model Track;
#pragma endregion

bool TestLoadObj(const char* path,
    std::vector < glm::vec3 >& out_vertices,
    std::vector < glm::ivec3 >& out_faces,
    std::vector < glm::vec2 >& out_uvs,
    std::vector < glm::ivec3 >& uvindices,
    std::vector < glm::vec3 >& out_normals,
    std::vector < glm::ivec3 >& normalindices)
{
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

    //init variables
    out_vertices.clear();
    out_faces.clear();
    out_uvs.clear();
    out_normals.clear();
    uvindices.clear();
    normalindices.clear();

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file !\n");
        return false;
    }

    while (1) {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == -1)
            break;

        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, " %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            out_vertices.push_back(vertex);

        }

        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            out_uvs.push_back(uv);
        }

        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            out_normals.push_back(normal);
        }

        else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

            out_faces.push_back(glm::ivec3(vertexIndex[0] - 1, vertexIndex[1] - 1, vertexIndex[2] - 1));
            uvindices.push_back(glm::ivec3(uvIndex[0] - 1, uvIndex[1] - 1, uvIndex[2] - 1));
            normalindices.push_back(glm::ivec3(normalIndex[0] - 1, normalIndex[1] - 1, normalIndex[2] - 1));
        }

    }
}

void TestDrawSurface(
    std::vector < glm::vec3 >& vertices,
    std::vector < glm::vec3 >& normals,
    std::vector < glm::vec2 >& uvs,
    std::vector < glm::ivec3 >& uvindices,
    std::vector < glm::ivec3 >& normalindices,
    std::vector < glm::ivec3 >& faces)
{
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < faces.size(); i++) {
        for (int j = 0; j < 2; j++) {
            glm::vec2 vt = uvs[uvindices[i][j]];
            glTexCoord2f(vt[0], vt[1]);
        }
        for (int j = 0; j < 3; j++) {
            glm::vec3 vn = normals[normalindices[i][j]];
            glNormal3f(vn[0], vn[1], vn[2]);
        }

        for (int j = 0; j < 3; j++) {
            glm::vec3 p = vertices[faces[i][j]];
            glVertex3f(p[0], p[1], p[2]);
        }
    }
    glEnd();
}

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
   // TestLoadObj("Data/Porsche/Porsche_911_GT2.obj", Car.vertices, Car.faces, Car.uvs, Car.uvindices, Car.normals, Car.normalindices);
    Car.Scale(glm::vec3(0.1, 0.1, 0.1)); 
    Car.SetRotation(180.f, glm::vec3(0, 1, 0));
    Car.Scale(glm::vec3(0.1, 0.1, 0.1));
    Car.SetCollider();

    Track = Model();
    Track.LoadObj("Data/Track/")
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, g_textureID[2]);  
    Car.DrawSurface();
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