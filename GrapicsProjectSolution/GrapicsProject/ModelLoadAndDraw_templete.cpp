#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <iostream>


#include <vector>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>


float g_fDistance = -4.5f;
float g_fSpinX = 0.0f;
float g_fSpinY = 0.0f;


static POINT ptLastMousePosit;
static POINT ptCurrentMousePosit;
static bool bMousing;

std::vector < glm::vec3 > vertices;
std::vector < glm::ivec3 > faces;
std::vector < glm::vec2 > uvs;
std::vector < glm::vec3 > normals;
std::vector < glm::vec3> uvs2;
std::vector < glm::ivec4 > faces2;

// 조명
GLfloat light_amb[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_specular[] = { 1, 1, 1, 1.0 };



bool LoadObj(const char* path,
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



bool LoadPly(const char* path,
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
		//뒤에 인덱스만 포문으로

    }

    for (int i = 0; i < nbFaces; i++)
    {

    }

}
void MyMouse(int button, int state, int x, int y) {
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            ptLastMousePosit.x = ptCurrentMousePosit.x = x;
            ptLastMousePosit.y = ptCurrentMousePosit.y = y;
            bMousing = true;
        }
        else
            bMousing = false;
        break;
    case GLUT_MIDDLE_BUTTON:
    case GLUT_RIGHT_BUTTON:
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void MyMotion(int x, int y) {
    ptCurrentMousePosit.x = x;
    ptCurrentMousePosit.y = y;

    if (bMousing)
    {
        g_fSpinX -= (ptCurrentMousePosit.x - ptLastMousePosit.x);
        g_fSpinY -= (ptCurrentMousePosit.y - ptLastMousePosit.y);
    }

    ptLastMousePosit.x = ptCurrentMousePosit.x;
    ptLastMousePosit.y = ptCurrentMousePosit.y;

    glutPostRedisplay();
}

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

void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_SMOOTH);    //구로 셰이딩
    glEnable(GL_DEPTH_TEST); // 깊이버퍼
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
    InitLight();
}


void DrawS(std::vector < glm::vec3 >& vectices,
    std::vector < glm::vec3 >& normals,
    std::vector < glm::ivec4 >& faces)
{
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

void DrawSurface(std::vector < glm::vec3 >& vectices, 
    std::vector < glm::vec3 >& normals, 
    std::vector < glm::ivec3 >& faces)
{
    glBegin(GL_TRIANGLES);
	for (int i = 0; i < faces.size(); i++) {



		for (int j = 0; j < 3; j++) 
		{
			glm::vec3 p = vertices[faces[i][j]];
			
			if (normals.size() == vertices.size())
			{
				glm::vec3 n = normals[faces[i][j]];
				glNormal3f(n[0], n[1], n[2]);
			}
			glVertex3f(p[0], p[1], p[2]);
		}
	}
    glEnd();
}

void DrawW(std::vector < glm::vec3 >& vectices,
    std::vector < glm::vec3 >& normals, std::vector < glm::ivec4 >& faces)
{
    glBegin(GL_LINES);
    for (int i = 0; i < faces.size(); i++) {
        for (int j = 0; j < 3; j++)
        {
            glm::vec3 p = vertices[faces[i][j]];

            if (normals.size() == vertices.size())
            {
                glm::vec3 n = normals[faces[i][j]];
                glNormal3f(n[0], n[1], n[2]);
            }
            glVertex3f(p[0], p[1], p[2]);
        }
    }
    glEnd();
}

void DrawWireSurface(std::vector < glm::vec3 >& vectices,
 std::vector < glm::vec3 > &normals,   std::vector < glm::ivec3 >& faces)
{
	glBegin(GL_LINES);
	for (int i = 0; i < faces.size(); i++) {
		for (int j = 0; j < 3; j++)
		{
			glm::vec3 p = vertices[faces[i][j]];

			if (normals.size() == vertices.size())
			{
				glm::vec3 n = normals[faces[i][j]];
				glNormal3f(n[0], n[1], n[2]);
			}
			glVertex3f(p[0], p[1], p[2]);
		}
	}
	glEnd();
}



void render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glTranslatef(0.0f, 0.0f, g_fDistance);
    glRotatef(-g_fSpinY, 1.0f, 0.0f, 0.0f);
    glRotatef(-g_fSpinX, 0.0f, 1.0f, 0.0f);

    //Draw here
    glTranslatef(0.0f, 0.0f,-75.0f);
   // glRotatef(45, 0.0f, 0.0f, 1.0f);
    DrawS(vertices, normals, faces2);
    //DrawSurface(vertices, normals, faces);
	//DrawWireSurface(vertices, normals, faces);
    glutSwapBuffers();
}



void MyReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("151927 정용진");
    init();

    LoadObj("Data/race-track/race-track.obj", vertices, faces2, uvs2, normals);
    LoadPly("C://users//jyj75//source//repos//컴퓨터그래픽스//컴그//Data//bunny//bun_zipper_res4.obj", vertices, faces, normals);

    glutDisplayFunc(render);
    glutReshapeFunc(MyReshape);
    glutMouseFunc(MyMouse);
    glutMotionFunc(MyMotion);

    glutMainLoop();
}