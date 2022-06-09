#include "Model.h"
#include<math.h>


GLuint g_textureID[4];
//std::vector<Box> boxes;

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

//void Model::DrawSurface(std::vector < glm::vec3 >& vertices,
//    std::vector < glm::vec3 >& normals,
//    std::vector < glm::vec2 >& uvs,
//    std::vector < glm::ivec3 >& uvindicies,
//    std::vector < glm::ivec3 >& normalindices,
//    std::vector < glm::ivec3 >& faces)
//{
//    glBegin(GL_TRIANGLES);
//    for (int i = 0; i < faces.size(); i++) {
//        for (int j = 0; j < 2; j++) {
//            glm::vec2 vt = uvs[uvindices[i][j]];
//            glTexCoord2f(vt[0], vt[1]);
//        }
//        for (int j = 0; j < 3; j++) {
//
//            glm::vec3 n = normals[normalindices[i][j]];
//            glNormal3f(n[0], n[1], n[2]);
//        }
//        for (int j = 0; j < 3; j++) {
//            glm::vec3 p = vertices[faces[i][j]];
//            /*p.x = vertices[faces[i][j]].x;
//            p.y = vertices[faces[i][j]].y;
//            p.z = vertices[faces[i][j]].z;*/
//            glVertex3f(p[0], p[1], p[2]);
//        }
//    }
//
//    glEnd();
//}

// ���� Ʈ������ ����� �����մϴ�.
void Model::Translate() {
    glTranslatef(this->position.x, this->position.y, this->position.z);
}
// ���� ȸ�� ����� �����մϴ�.
void Model::RotateAngle() {
    printf("Car Angle : %f\n", this->angle);
    glRotatef(this->angle, this->axis.x, this->axis.y, this->axis.z);
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
    printf("Car position : %f %f %f\n", this->position.x, this->position.y, this->position.z);
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
void Model::SetFront(glm::vec3 dir) {
    this->front = dir;
}
void Model::Scale(glm::vec3 scale) {
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].x *= scale.x;
        vertices[i].y *= scale.y;
        vertices[i].z *= scale.z;
        /*uvs[i].x *= scale.x;
        uvs[i].y *= scale.y;
        normals[i].x *= scale.x;
        normals[i].y *= scale.y;
        normals[i].z *= scale.z;*/
    }
    SetCollider();
}
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

void Box::texturedCube(float size) {
    //glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    //glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    //glEnable(GL_TEXTURE_GEN_S);
    //glEnable(GL_TEXTURE_GEN_T);
    //glutSolidCube(1);

    glBegin(GL_QUADS);

    //앞면;
    glTexCoord2f(0, 0); glVertex3f(-1 * size, -1 * size, 1 * size);
    glTexCoord2f(1, 0); glVertex3f(1 * size, -1 * size, 1 * size);
    glTexCoord2f(1, 1); glVertex3f(1 * size, 1 * size, 1 * size);
    glTexCoord2f(0, 1); glVertex3f(-1 * size, 1 * size, 1 * size);

    //뒷면
    glTexCoord2f(1, 0); glVertex3f(-1 * size, -1 * size, -1* size);
    glTexCoord2f(1, 1); glVertex3f(-1 * size, 1 * size, -1 * size);
    glTexCoord2f(0, 1); glVertex3f(1 * size, 1 * size, -1 * size);
    glTexCoord2f(0, 0); glVertex3f(1 * size, -1 * size, -1 * size);

    //윗면
    glTexCoord2f(0, 1); glVertex3f(-1 * size, 1 * size, -1 * size);
    glTexCoord2f(0, 0); glVertex3f(-1 * size, 1 * size, 1 * size);
    glTexCoord2f(1, 0); glVertex3f(1 * size, 1 * size, 1 * size);
    glTexCoord2f(1, 1); glVertex3f(1 * size, 1 * size, -1 * size);

    //오른쪽 옆면
    glTexCoord2f(1, 1); glVertex3f(-1 * size, -1 * size, -1 * size);
    glTexCoord2f(0, 1); glVertex3f(1 * size, -1 * size, -1 * size);
    glTexCoord2f(0, 0); glVertex3f(1 * size, -1 * size, 1 * size);
    glTexCoord2f(1, 0); glVertex3f(-1, -1, 1);

    //
    glTexCoord2f(1, 0); glVertex3f(1 * size, -1 * size, -1 * size);
    glTexCoord2f(1, 1); glVertex3f(1 * size, 1 * size, -1 * size);
    glTexCoord2f(0, 1); glVertex3f(1 * size, 1 * size, 1 * size);
    glTexCoord2f(0, 0); glVertex3f(1 * size, -1 * size, 1 * size);

    //
    glTexCoord2f(0, 0); glVertex3f(-1 * size, -1 * size, -1 * size);
    glTexCoord2f(1, 0); glVertex3f(-1 * size, -1 * size, 1 * size);
    glTexCoord2f(1, 1); glVertex3f(-1 * size, 1 * size, 1 * size);
    glTexCoord2f(0, 1); glVertex3f(-1 * size, 1 * size, -1 * size);

    glEnd();

}

void Box::newSpeed(float dest[3]) {
    float x, y, z, len;

    x = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;
    y = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;
    z = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;

    if (wantNormalize) {
        len = sqrt(x * x + y * y + z * z);

        if (len) {
            x = x / len;
            y = y / len;
            z = z / len;
        }
    }

    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
}

//폭발시 파티클 및 파편 생성
void Box::newExplosion(void) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].position[0] = 0.0;
        particles[i].position[1] = 0.0;
        particles[i].position[2] = 0.0;

        particles[i].color[0] = 1.0;
        particles[i].color[1] = 1.0;
        particles[i].color[2] = 0.5;

        newSpeed(particles[i].speed);
    }

    for (int i = 0; i < NUM_DEBRIS; i++) {
        debris[i].position[0] = 0.0;
        debris[i].position[1] = 0.0;
        debris[i].position[2] = 0.0;

        debris[i].orientation[0] = 0.0;
        debris[i].orientation[1] = 0.0;
        debris[i].orientation[2] = 0.0;

        debris[i].color[0] = 0.2;
        debris[i].color[1] = 0.2;
        debris[i].color[2] = 0.7;

        debris[i].scale[0] = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;
        debris[i].scale[1] = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;
        debris[i].scale[2] = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;

        newSpeed(debris[i].speed);
        newSpeed(debris[i].orientationSpeed);
    }

    fuel = 1000;
}

//파티클 및 파편 업데이트
void Box::MyIdle(void) {
    if (fuel > 0) {
        for (int i = 0; i < NUM_PARTICLES; i++) {
            particles[i].position[0] += particles[i].speed[0] * 0.2;
            particles[i].position[1] += particles[i].speed[1] * 0.2;
            particles[i].position[2] += particles[i].speed[2] * 0.2;

            particles[i].color[0] -= 1.0 / 500.0;
            if (particles[i].color[0] < 0.0) {
                particles[i].color[0] = 0.0;
            }

            particles[i].color[1] -= 1.0 / 100.0;
            if (particles[i].color[1] < 0.0) {
                particles[i].color[1] = 0.0;
            }

            particles[i].color[2] -= 1.0 / 50.0;
            if (particles[i].color[2] < 0.0) {
                particles[i].color[2] = 0.0;
            }
        }

        for (int i = 0; i < NUM_DEBRIS; i++) {
            debris[i].position[0] += debris[i].speed[0] * 0.1;
            debris[i].position[1] += debris[i].speed[1] * 0.1;
            debris[i].position[2] += debris[i].speed[2] * 0.1;

            debris[i].orientation[0] += debris[i].orientationSpeed[0] * 10;
            debris[i].orientation[1] += debris[i].orientationSpeed[1] * 10;
            debris[i].orientation[2] += debris[i].orientationSpeed[2] * 10;
        }

        --fuel;
    }

    glutPostRedisplay();
}

void Box::InitGL(void) {
    GLfloat  light0Amb[4] = { 1.0, 0.6, 0.2, 1.0 };
    GLfloat  light0Dif[4] = { 1.0, 0.6, 0.2, 1.0 };
    GLfloat  light0Spec[4] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat  light0Pos[4] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat  light1Amb[4] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat  light1Dif[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat  light1Spec[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat  light1Pos[4] = { 0.0, 5.0, 5.0, 0.0 };

    GLfloat  materialAmb[4] = { 0.25, 0.22, 0.26, 1.0 };
    GLfloat  materialDif[4] = { 0.63, 0.57, 0.60, 1.0 };
    GLfloat  materialSpec[4] = { 0.99, 0.91, 0.81, 1.0 };
    GLfloat  materialShininess = 27.8;

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Spec);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1Amb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Dif);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Spec);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);
    glEnable(GL_NORMALIZE);

    srand(time(NULL));
}