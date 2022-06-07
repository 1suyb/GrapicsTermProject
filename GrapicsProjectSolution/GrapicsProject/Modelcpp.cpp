#include "Model.h"
#include<math.h>

Model::Model() {
    position = glm::vec3(0, 0, 0);
    angle = 0;
    axis = glm::vec3(0, 1, 0);
    front = glm::vec3(1, 0, 0);

    hasCollision = false;
    colliderX = 0;
    colliderY = 0;
    colliderZ = 0;
}
Model::Model(bool collision) {
    position = glm::vec3(0, 0, 0);
    angle = 0;
    axis = glm::vec3(0, 1, 0);
    front = glm::vec3(1, 0, 0);

    hasCollision = true;
    colliderX = 0;
    colliderY = 0;
    colliderZ = 0;
}
bool Model::LoadObj(const char* path,
	std::vector < glm::vec3 >& out_vertices,
	std::vector < glm::ivec3 >& out_faces,
	std::vector < glm::vec2 >& out_uvs,
	std::vector < glm::vec3 >& out_normals) 
{
	out_vertices.clear();
	out_faces.clear();
	out_uvs.clear();
	out_normals.clear();

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
        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            out_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d//%d %d//%d %d//%d\n",
                &vertexIndex[0], &normalIndex[0],
                &vertexIndex[1], &normalIndex[1],
                &vertexIndex[2], &normalIndex[2]);
            out_faces.push_back(glm::ivec3(vertexIndex[0] - 1, vertexIndex[1] - 1, vertexIndex[2] - 1));
        }
    }
}

bool Model::TrackObj(const char* path,
    std::vector < glm::vec3 >& out_vertices,
    std::vector < glm::ivec4 >& out_faces2,
    std::vector < glm::vec3 >& out_uvs2,
    std::vector < glm::vec3 >& out_normals)
{
    out_vertices.clear();
    out_faces2.clear();
    out_uvs2.clear();
    out_normals.clear();

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
            glm::vec3 uv2;
            fscanf(file, "&f &f &f\n", &uv2.x, &uv2.y, &uv2.z);
            out_uvs2.push_back(uv2);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            out_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
                &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                &vertexIndex[2], &uvIndex[2], &normalIndex[2],
                &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
            out_faces2.push_back(glm::ivec4(vertexIndex[0] - 1, vertexIndex[1] - 1, vertexIndex[2] - 1, vertexIndex[3] - 1));
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

void Model::DrawSurface(std::vector < glm::vec3 >& vectices,
    std::vector < glm::vec3 >& normals,
    std::vector < glm::ivec3 >& faces) {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < faces.size(); i++) {
        for (int j = 0; j < 3; j++) {
            glm::vec3 p;
            p.x = vertices[faces[i][j]].x;
            p.y = vertices[faces[i][j]].y;
            p.z = vertices[faces[i][j]].z;
            if (normals.size() == vertices.size()) {
                glm::vec3 n = normals[faces[i][j]];
                glNormal3f(n[0], n[1], n[2]);
            }
            glVertex3f(p[0], p[1], p[2]);
        }
    }
    glEnd();
}

void Model::DrawTrack(std::vector < glm::vec4 >& vectices,
    std::vector < glm::vec4 >& normals,
    std::vector < glm::ivec4 >& faces) {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < faces.size(); i++) {
        glm::ivec4 tempFace = faces[i];

        int idx = 0;
        idx = tempFace[0];
        glm::vec3 p1 = vertices[idx];
        if (normals.size() == vertices.size())
        {
            glm::vec3 n = normals[idx];
            glNormal3f(n[0], n[1], n[2]);
        }
        glVertex3f(p1[0], p1[1], p1[2]);

        int idx1 = 0;
        idx1 = tempFace[1];
        glm::vec3 p2 = vertices[idx1];
        if (normals.size() == vertices.size())
        {
            glm::vec3 n = normals[idx1];
            glNormal3f(n[0], n[1], n[2]);
        }
        glVertex3f(p2[0], p2[1], p2[2]);

        int idx2 = 0;
        idx2 = tempFace[2];
        glm::vec3 p3 = vertices[idx2];
        if (normals.size() == vertices.size())
        {
            glm::vec3 n = normals[idx2];
            glNormal3f(n[0], n[1], n[2]);
        }
        glVertex3f(p3[0], p3[1], p3[2]);

        if (normals.size() == vertices.size())
        {
            glm::vec3 n = normals[idx];
            glNormal3f(n[0], n[1], n[2]);
        }
        glVertex3f(p1[0], p1[1], p1[2]);

        if (normals.size() == vertices.size())
        {
            glm::vec3 n = normals[idx2];
            glNormal3f(n[0], n[1], n[2]);
        }
        glVertex3f(p3[0], p3[1], p3[2]);

        int idx3 = 0;
        idx3 = tempFace[3];
        glm::vec3 p4 = vertices[idx3];
        if (normals.size() == vertices.size())
        {
            glm::vec3 n = normals[idx3];
            glNormal3f(n[0], n[1], n[2]);
        }
        glVertex3f(p4[0], p4[1], p4[2]);
    }
    glEnd();
}

// ���� Ʈ������ ����� �����մϴ�.
void Model::Translate() {
    glTranslatef(this->position.x,this->position.y,this->position.z);
}
// ���� ȸ�� ����� �����մϴ�.
void Model::RotateAngle() {
    printf("Car Angle : %f\n", this->angle);
    glRotatef(this->angle,this->axis.x,this->axis.y,this->axis.z);
}
// ���� Ʈ������ ����� �����մϴ�.
void Model::SetPosition(glm::vec3 translate) {
    this->position = translate;
    glm::mat4 rot = glm::rotate(glm::mat4(1), glm::radians(angle), axis);
    glm::vec3 atdir = this->front - this->position;
    atdir = rot * glm::normalize(glm::vec4(atdir, 0));
    this->front = atdir + this->position;
}
// ���� ȸ�� ����� �����մϴ�.
void Model::SetRotation(GLfloat angle, glm::vec3 axis) {
    this->angle = angle;
    this->axis = axis;
}
// ���� �̵�
void Model::Move(glm::vec3 move) {
    this->position += move;
    this->front += move;
    printf("Car position : %f %f %f\n",this->position.x, this->position.y, this->position.z);
    printf("Car at : %f %f %f \n", this->front.x, this->front.y, this->front.z);
}
void Model::Rotate(GLfloat angle, glm::vec3 axis) {
    this->angle += angle;
    this->axis = axis;
    glm::mat4 rot = glm::rotate(glm::mat4(1), glm::radians(angle), axis);
    glm::vec3 atdir = this->front - this->position;
    atdir = rot * glm::normalize(glm::vec4(atdir, 0));
    this->front = atdir + this->position;
}
// ���� ������ �����մϴ�.
void Model::SetFront(glm::vec3 dir) {
    this->front = dir;
}
// ���� ũ�⸦ �����մϴ�. �浹������ �Բ� �缳�� �մϴ�.
void Model::Scale(glm::vec3 scale) {
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].x *= scale.x;
        vertices[i].y *= scale.y;
        vertices[i].z *= scale.z;
    }
    SetCollider();
}
// �浹 ���� ����
void Model::SetCollider() {
    for (int i = 0; i < this->vertices.size(); i++) {
        if (std::abs(vertices[i].x) > colliderX) {
            colliderX = std::abs(vertices[i].x);
        }
        if (std::abs(vertices[i].y) > colliderY) {
            colliderY = std::abs(vertices[i].y);
        }
        if (std::abs(vertices[i].z) > colliderZ) {
            colliderZ = std::abs(vertices[i].z);
        }
    }
}
// �浹���� ũ�� ����
void Model::SetColliderSize(glm::vec3 colscale) {
    if (colscale.x > 0) {
        colliderX *= colscale.x;
    }
    if (colscale.y > 0) {
        colliderY *= colscale.y;
    }
    if (colscale.z > 0) {
        colliderZ *= colscale.z;
    }
}
void Model::OnEnterCollider() {

}


void Car::OnEnterCollider(){
}
