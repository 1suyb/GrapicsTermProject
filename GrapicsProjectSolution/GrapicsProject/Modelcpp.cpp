#include "Model.h"
#include<math.h>
#include <stdlib.h>

Model::Model() {
    position = glm::vec3(0, 0, 0);
    angle = 0;
    axis = glm::vec3(0, 1, 0);
    front = glm::vec3(1, 0, 0);
    coliider = glm::vec3(0, 0, 0);
}

#pragma region Model_Import
bool Model::LoadObj(const char* path,
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
#pragma endregion

#pragma region Model_Move
void Model::Translate() {
    glTranslatef(this->position.x, this->position.y, this->position.z);
}
void Model::RotateAngle() {
    printf("Car Angle : %f\n", this->angle);
    glRotatef(this->angle, this->axis.x, this->axis.y, this->axis.z);
}
void Model::SetPosition(glm::vec3 translate) {
    this->position = translate;
    glm::mat4 rot = glm::rotate(glm::mat4(1), glm::radians(angle), axis);
    glm::vec3 atdir = this->front - this->position;
    atdir = rot * glm::normalize(glm::vec4(atdir, 0));
    this->front = atdir + this->position;
}
void Model::SetRotation(GLfloat angle, glm::vec3 axis) {
    this->angle = angle;
    this->axis = axis;
}
void Model::Move(glm::vec3 move) {
    this->position += move;
    this->front += move;
    printf("Car position : %f %f %f\n", this->position.x, this->position.y, this->position.z);
    printf("Car at : %f %f %f \n", this->front.x, this->front.y, this->front.z);
}
void Model::Rotate(GLfloat angle, glm::vec3 axis) {
    this->angle = (GLfloat)((int)(this->angle + angle) % 360);
    this->axis = axis;
    glm::mat4 rot = glm::rotate(glm::mat4(1), glm::radians(angle), axis);
    glm::vec3 atdir = this->front - this->position;
    atdir = rot * glm::normalize(glm::vec4(atdir, 0));
    this->front = atdir + this->position;
}
#pragma endregion


void Model::DrawSurface() {
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
void Model::SetFront(glm::vec3 dir) {
    this->front = dir+this->position;
}
void Model::Scale(glm::vec3 scale) {
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].x *= scale.x;
        vertices[i].y *= scale.y;
        vertices[i].z *= scale.z;
    }
    SetCollider();
}
void Model::SetCollider() {
    for (int i = 0; i < this->vertices.size(); i++) {
        if (std::abs(vertices[i].x) > coliider.x) {
            coliider.x = std::abs(vertices[i].x);
        }
        if (std::abs(vertices[i].y) > coliider.y) {
            coliider.y = std::abs(vertices[i].y);
        }
        if (std::abs(vertices[i].z) > coliider.z) {
            coliider.z = std::abs(vertices[i].z);
        }
    }
}

void Model::OnEnterCollider() {
}

void Car::OnEnterCollider() {
}

//void Box::addBox(glm::vec3 leftBottom, glm::vec3 rightTop)
//{
//    int random = 0;
//    int randRange = 100;
//    Box newBox;
//
//    glm::vec3 _pos(0, 0, 0);
//    glm::vec3 _vel(0, 0, 0);
//    float m = 1;
//
//    for (int i = 0; i < 3; i++)
//    {
//        float value = (float)(rand() % randRange) / (float)randRange;
//        _pos[i] = leftBottom[i] + (rightTop[i] - leftBottom[i]) * value;
//        _vel[i] = value * 2.f - 1.f;
//
//        m = 1 + value;
//    }
//
//    newBox.p = _pos;
//    newBox.v = _vel;
//
//    newBox.force = glm::vec3(0, 0, 0);
//    newBox.m = m;
//    newBox.r = m / 2.f;
//
//    boxes.push_back(newBox);
//}

// 박스 겹치면 밀어내게
//void Box::Contact(float stiff) {
//    std::vector<Box> boxes;
//    for (int i = 0; i < boxes.size(); i++)
//    {
//        for (int j = i + 1; j < boxes.size(); j++) {
//            glm::vec3 dis = boxes[i].p - boxes[j].p;
//
//            float L = length(dis);
//            dis = normalize(dis);
//
//            if (L < boxes[i].r + boxes[j].r) {
//                glm::vec3 force = stiff * ((boxes[i].r + boxes[j].r) - L) * dis;
//                boxes[i].force += force;
//                boxes[j].force -= force;
//            }
//        }
//    }
//}

