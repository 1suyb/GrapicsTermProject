#include"Box.h"

using namespace std;
using namespace glm;

int windowHeight, windowWidth;
GLuint g_textureID = -1;

camera myCamera;

vector<Box> boxes;


void addBox(vec3 leftBottom, vec3 rightTop)
{
    int random = 0;
    int randRange = 100;
    Box newBox;

    vec3 _pos(0, 0, 0);
    vec3 _vel(0, 0, 0);
    float m = 1;

    for (int i = 0; i < 3; i++)
    {
        float value = (float)(rand() % randRange) / (float)randRange;
        _pos[i] = leftBottom[i] + (rightTop[i] - leftBottom[i]) * value;
        _vel[i] = value * 2.f - 1.f;

        m = 1 + value;
    }
    /*_pos[2] = -10;*/
    newBox.p = _pos;
    newBox.v = _vel;

    newBox.force = vec3(0, 0, 0);
    newBox.m = m;
    newBox.r = m / 2.f;

    boxes.push_back(newBox);
}

// 박스 겹치면 밀어내게
void Contact(float stiff) {
    for (int i = 0; i < boxes.size(); i++)
    {
        for (int j = i + 1; j < boxes.size(); j++) {
            vec3 dis = boxes[i].p - boxes[j].p;

            float L = length(dis);
            dis = normalize(dis);

            if (L < boxes[i].r + boxes[j].r) {
                vec3 force = stiff * ((boxes[i].r + boxes[j].r) - L) * dis;
                boxes[i].force += force;
                boxes[j].force -= force;
            }
        }
    }
}

void loadTexture(void) {
    // 박스 장애물
    AUX_RGBImageRec* pTextureImage = auxDIBImageLoad("Data/woodBox.bmp");
    // 부스터 아이템
    /*AUX_RGBImageRec* pTextureImage = auxDIBImageLoad("Data/booster.bmp");*/


    if (pTextureImage != NULL) {
        glGenTextures(1, &g_textureID);

        glBindTexture(GL_TEXTURE_2D, g_textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage->sizeX, pTextureImage->sizeY, 0,
            GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data);
    }

    if (pTextureImage) {
        if (pTextureImage->data)
            free(pTextureImage->data);

        free(pTextureImage);
    }
}


void texturedCube(float size) {
    //glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    //glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    //glEnable(GL_TEXTURE_GEN_S);
    //glEnable(GL_TEXTURE_GEN_T);
    //glutSolidCube(1);

    glBegin(GL_QUADS);

    //앞면;
    glTexCoord2f(0, 0); glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 0); glVertex3f(1, -1, 1);
    glTexCoord2f(1, 1); glVertex3f(1, 1, 1);
    glTexCoord2f(0, 1); glVertex3f(-1, 1, 1);

    //뒷면
    glTexCoord2f(1, 0); glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 1); glVertex3f(-1, 1, -1);
    glTexCoord2f(0, 1); glVertex3f(1, 1, -1);
    glTexCoord2f(0, 0); glVertex3f(1, -1, -1);

    //윗면
    glTexCoord2f(0, 1); glVertex3f(-1, 1, -1);
    glTexCoord2f(0, 0); glVertex3f(-1, 1, 1);
    glTexCoord2f(1, 0); glVertex3f(1, 1, 1);
    glTexCoord2f(1, 1); glVertex3f(1, 1, -1);

    //오른쪽 옆면
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

void init2() {
    loadTexture();

    srand(time(NULL));

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800 / 600, -0.1f, 100.0f);

    //get window size
    windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    //Init camera
    vec3 center(0, 40, -5);
    vec3 at(0, 0, -5);
    vec3 up = vec3(0, 0, 1);
    myCamera.InitCamera(center, at, up);

    //Init variables
    addBox(vec3(-10, -10, -5), vec3(10, 10, 20));
    
}



void Render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //get camera variables from camera class
    vec3 eye = myCamera.eye;
    vec3 at = myCamera.at;
    vec3 up = myCamera.up;

    //set view transform matrix
    gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);

    for (int i = 0; i < boxes.size(); i++)
    {
        glPushMatrix();
        glTranslatef(boxes[i].p[0], boxes[i].p[1], boxes[i].p[2]);
        glBindTexture(GL_TEXTURE_2D, g_textureID);
        texturedCube(boxes[i].r);
        glPopMatrix();
    }

    //Swap buffers
    glutSwapBuffers();
}

void MyReshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
}

void MyTimer(int Value) {

    float dt = 0.1;

    for (int i = 0; i < boxes.size(); i++) {

        //add gradient force
        vec3 gravity(0, 0, -9.8);
        boxes[i].force += gravity * boxes[i].m;

        //update velocity
        boxes[i].v += boxes[i].force / boxes[i].m * dt;

        //update position
        boxes[i].p += boxes[i].v * dt;

        //바닥에서 안 튀어오르게
        //modify position and velocity according to constraints
        if (boxes[i].p[2] - boxes[i].r < -10) {
            boxes[i].p[2] = -10; // + boxes[i].r;
            /*boxes[i].v *= 0.9;
            boxes[i].v[2] *= -1;*/
        }

        Contact(10.0);

        //clear force
        boxes[i].force = vec3(0, 0, 0);

    }
    addBox(vec3(-10, -10, -5), vec3(10, 10, 20));

    glutPostRedisplay();
    glutTimerFunc(500, MyTimer, 1);
}

//void main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Bouncing ball");
//    init();
//    //InitLight();
//    glutDisplayFunc(Render);
//    glutReshapeFunc(MyReshape);
//    //glutMouseFunc(MyMouse);
//    //glutMotionFunc(MyMouseMove);
//    //glutKeyboardFunc(MyKeyboard);
//    glutTimerFunc(500, MyTimer, 1);
//
//    glutMainLoop();
//}