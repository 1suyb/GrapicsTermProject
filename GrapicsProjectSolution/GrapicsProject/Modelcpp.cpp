#include "Model.h"
#include "glaux.h"


GLuint g_textureID[4];
std::vector<Box> boxes;

void addBox(glm::vec3 leftBottom, glm::vec3 rightTop)
{
    int random = 0;
    int randRange = 100;
    Box newBox;

    std::vector<Box> boxes;

    glm::vec3 _pos(0, 0, 0);
    glm::vec3 _vel(0, 0, 0);
    float m = 1;

    for (int i = 0; i < 3; i++)
    {
        float value = (float)(rand() % randRange) / (float)randRange;
        _pos[i] = leftBottom[i] + (rightTop[i] - leftBottom[i]) * value;
        _vel[i] = value * 2.f - 1.f;

        m = 1 + value;
    }
    
    newBox.p = _pos;
    newBox.v = _vel;

    newBox.force = glm::vec3(0, 0, 0);
    newBox.m = m;
    newBox.r = m / 2.f;

    boxes.push_back(newBox);
}

// �ڽ� ��ġ�� �о��
void Contact(float stiff) {
    std::vector<Box> boxes;
    for (int i = 0; i < boxes.size(); i++)
    {
        for (int j = i + 1; j < boxes.size(); j++) {
            glm::vec3 dis = boxes[i].p - boxes[j].p;

            float L = length(dis);
            dis = normalize(dis);

            if (L < boxes[i].r + boxes[j].r) {
                glm::vec3 force = stiff * ((boxes[i].r + boxes[j].r) - L) * dis;
                boxes[i].force += force;
                boxes[j].force -= force;
            }
        }
    }
}

void texturedCube(float size) {
    //glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    //glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    //glEnable(GL_TEXTURE_GEN_S);
    //glEnable(GL_TEXTURE_GEN_T);
    //glutSolidCube(1);

    glBegin(GL_QUADS);

    //�ո�;
    glTexCoord2f(0, 0); glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 0); glVertex3f(1, -1, 1);
    glTexCoord2f(1, 1); glVertex3f(1, 1, 1);
    glTexCoord2f(0, 1); glVertex3f(-1, 1, 1);

    //�޸�
    glTexCoord2f(1, 0); glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 1); glVertex3f(-1, 1, -1);
    glTexCoord2f(0, 1); glVertex3f(1, 1, -1);
    glTexCoord2f(0, 0); glVertex3f(1, -1, -1);

    //����
    glTexCoord2f(0, 1); glVertex3f(-1, 1, -1);
    glTexCoord2f(0, 0); glVertex3f(-1, 1, 1);
    glTexCoord2f(1, 0); glVertex3f(1, 1, 1);
    glTexCoord2f(1, 1); glVertex3f(1, 1, -1);

    //������ ����
    glTexCoord2f(1, 1); glVertex3f(-1, -1, -1);
    glTexCoord2f(0, 1); glVertex3f(1, -1, -1);
    glTexCoord2f(0, 0); glVertex3f(1, -1, 1);
    glTexCoord2f(1, 0); glVertex3f(-1, -1, 1);

    //
    glTexCoord2f(1, 0); glVertex3f(1, -1, -1);
    glTexCoord2f(1, 1); glVertex3f(1, 1, -1);
    glTexCoord2f(0, 1); glVertex3f(1, 1, 1);
    glTexCoord2f(0, 0); glVertex3f(1, -1, 1);

    //
    glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 0); glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 1); glVertex3f(-1, 1, 1);
    glTexCoord2f(0, 1); glVertex3f(-1, 1, -1);

    glEnd();

}

void loadTexture() {
    //��η� ���� �̹��� ���� �ҷ�����
    AUX_RGBImageRec* pBoxImage = auxDIBImageLoad("Data/woodBox.bmp");
    AUX_RGBImageRec* pBoosterImage = auxDIBImageLoad("Data/booster.bmp");
    AUX_RGBImageRec* pCarImage = auxDIBImageLoad("Data/Porsche/skin00/0000.bmp");

    if (pBoxImage != NULL && pBoosterImage != NULL && pCarImage != NULL) {
        //�ڽ� ��ֹ�
        //�ؽ��� ���� (�ؽ��ļ�, �ؽ��� ID �迭 �ּ�)
        glGenTextures(3, &g_textureID[0]);

        //�ؽ��� �Ķ���� ������ ���� �κ� (0�� �ؽ��� ID ����)
        glBindTexture(GL_TEXTURE_2D, g_textureID[0]);

        //�ؽ��� �Ķ���� ����: �ؽ��� Ȯ�� ��ҽ� ���� ó�� ��� ����
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //�ҷ��� �̹��� ������ ���� ������ �ؽ���ID�� ����
        glTexImage2D(GL_TEXTURE_2D, 0, 3, pBoxImage->sizeX, pBoxImage->sizeY, 0,
            GL_RGB, GL_UNSIGNED_BYTE, pBoxImage->data);

        //�ν��� ������
        //�ؽ��� �Ķ���� ������ ���� �κ� (1�� �ؽ��� ID ����)
        glBindTexture(GL_TEXTURE_2D, g_textureID[1]);

        //�ؽ��� �Ķ���� ����: �ؽ��� Ȯ�� ��ҽ� ���� ó�� ��� ����
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //�ҷ��� �̹��� ������ ���� ������ �ؽ���ID�� ����
        glTexImage2D(GL_TEXTURE_2D, 0, 3, pBoosterImage->sizeX, pBoosterImage->sizeY, 0,
            GL_RGB, GL_UNSIGNED_BYTE, pBoosterImage->data);

        // ��
        //�ؽ��� �Ķ���� ������ ���� �κ� (1�� �ؽ��� ID ����)
        glBindTexture(GL_TEXTURE_2D, g_textureID[2]);

        //�ؽ��� �Ķ���� ����: �ؽ��� Ȯ�� ��ҽ� ���� ó�� ��� ����
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);

        //�ҷ��� �̹��� ������ ���� ������ �ؽ���ID�� ����
        glTexImage2D(GL_TEXTURE_2D, 0, 3, pCarImage->sizeX, pCarImage->sizeY, 0,
            GL_RGB, GL_UNSIGNED_BYTE, pCarImage->data);

        //�ҷ��� �ؽ��� ���� ������ ����
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


Model::Model() {
    position = glm::vec3(0, 0, 0);
    angle = 0;
    axis = glm::vec3(0, 1, 0);
    front = glm::vec3(1, 0, 0);
}

bool Model::LoadObj(const char* path,
	std::vector < glm::vec3 >& out_vertices,
	std::vector < glm::ivec3 >& out_faces,
	std::vector < glm::vec2 >& out_uvs,
    std::vector < glm::ivec3 >& uvindices,
	std::vector < glm::vec3 >& out_normals,
    std::vector < glm::ivec3 >& normalindices)
{
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
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            out_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "&f, &f\n", &uv.x, &uv.y);
            out_uvs.push_back(uv);
        }
        // %d/%d/%d %d/%d/%d %d/%d/%d�� ����, &uvIndex[] �߰�
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
            out_faces.push_back(glm::ivec3(normalIndex[0] - 1, normalIndex[1] - 1, normalIndex[2] - 1));
        }
    }
}

bool Model::LoadPly(const char* path,
    std::vector < glm::vec3 >& out_vertices,
    std::vector < glm::ivec3 >& out_faces,
    std::vector < glm::vec3 >& out_normals) 
{
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file !\n");
        return false;
    }

    //init variables
    out_vertices.clear();
    out_faces.clear();
    out_normals.clear();

    int nbVertices = 0;
    int nbFaces = 0;

    while (1) {
        char lineHeader1[128];
        char lineHeader2[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader1);
        if (res == -1)
            break;
        if (strcmp(lineHeader1, "element") == 0) {
            fscanf(file, "%s", lineHeader2);
            if (strcmp(lineHeader2, "vertex") == 0) {
                fscanf(file, "%d\n", &nbVertices);
            }
            else if (strcmp(lineHeader2, "face") == 0) {
                fscanf(file, "%d\n", &nbFaces);
            }
        }
        else if (strcmp(lineHeader1, "end_header") == 0) {
            break;
        }
    }

    for (int i = 0; i < nbVertices; i++)
    {
        glm::vec3 vertex;
        float confidence, intensity;
        fscanf(file, "%f %f %f %f %f\n", &vertex.x, &vertex.y, &vertex.z, &confidence, &intensity);
        out_vertices.push_back(vertex);
    }

    for (int i = 0; i < nbFaces; i++)
    {
        unsigned int count, vertexIndex[3];
        fscanf(file, "%d %d %d %d\n", &count, &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
        out_faces.push_back(glm::ivec3(vertexIndex[0], vertexIndex[1], vertexIndex[2]));
    }
    return true;
}

//�ﰢ���� �׸��Ƕ� �� �ﰢ�� ���������� ����� vt ��ǥ�� ����� ����ϴµ�, vt ����Ʈ �߿� �����ؾ��� vt �� index�� ��Ÿ���°� unindex �Դϴ�.
void Model::DrawSurface() {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < faces.size(); i++) {
        for (int j = 0; j < 3; j++) {
            glm::vec3 p;
            p.x = vertices[faces[i][j]].x;
            p.y = vertices[faces[i][j]].y;
            p.z = vertices[faces[i][j]].z;
            glVertex3f(p[0], p[1], p[2]);
        }
    }
    for (int i = 0; i < uvindices.size(); i++) {
        for (int j = 0; j < 2; j++) {
            glm::vec2 vt = uvs[uvindices[i][j]];
            glTexCoord2f(vt[0], vt[1]);
        }
    }
    for (int i = 0; i < normalindices.size(); i++) {
        for (int j = 0; j < 3; j++) {
            glm::vec3 n = normals[normalindices[i][j]];
            glNormal3f(n[0], n[1], n[2]);
        }
    }
    glEnd();
}

// ���� Ʈ������ ����� �����մϴ�.
void Model::Translate() {
    glTranslatef(this->position.x,this->position.y,this->position.z);
}
// ���� ȸ�� ����� �����մϴ�.
void Model::RotateAngle() {
    glRotatef(this->angle,this->axis.x,this->axis.y,this->axis.z);
}
// ���� Ʈ������ ����� �����մϴ�.
void Model::SetPosition(glm::vec3 translate) {
    this->position = translate;
}
// ���� ȸ�� ����� �����մϴ�.
void Model::SetRotation(GLfloat angle, glm::vec3 axis) {
    this->angle = angle;
    this->axis = axis;
}
// ���� �̵�
void Model::Move(glm::vec3 move) {
    this->position += move;
}
// ���� ȸ��
void Model::Rotate(GLfloat angle, glm::vec3 axis) {
    this->angle += angle;
    this->axis = axis;
}
// ���� ������ �����մϴ�.
void Model::SetFront(glm::vec3 dir) {
    this->front = dir;
}
// ���� ũ�⸦ �����մϴ�.
void Model::Scale(glm::vec3 scale) {
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].x *= scale.x;
        vertices[i].y *= scale.y;
        vertices[i].z *= scale.z;
    }
}