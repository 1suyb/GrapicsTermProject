#pragma once
#include"Box.h"

void Box::DrawCube(float size) {
    is_spawned = true;
    glBegin(GL_QUADS);

    //앞면;
    glTexCoord2f(0, 0); glVertex3f(-1 * size, -1 * size, 1 * size);
    glTexCoord2f(1, 0); glVertex3f(1 * size, -1 * size, 1 * size);
    glTexCoord2f(1, 1); glVertex3f(1 * size, 1 * size, 1 * size);
    glTexCoord2f(0, 1); glVertex3f(-1 * size, 1 * size, 1 * size);

    //뒷면
    glTexCoord2f(1, 0); glVertex3f(-1 * size, -1 * size, -1 * size);
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
    printf("Boom");
    is_spawned = false;
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].position[0] = this->position.x;
        particles[i].position[1] = this->position.y;
        particles[i].position[2] = this->position.z;

        particles[i].color[0] = 1.0;
        particles[i].color[1] = 1.0;
        particles[i].color[2] = 0.5;

        newSpeed(particles[i].speed);
    }

    for (int i = 0; i < NUM_DEBRIS; i++) {
        debris[i].position[0] = this->position.x;
        debris[i].position[1] = this->position.y;
        debris[i].position[2] = this->position.z;

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

    fuel = 500;
}

//파티클 및 파편 업데이트
void Box::ParticleUpdate(void) {
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
        if (fuel == 0) {
            is_spawned = false;
        }
    }

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

void Box::ShowParticles() {
    if (fuel > 0) {
        glPushMatrix();
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glBegin(GL_POINTS);
        for (int i = 0; i < NUM_PARTICLES; i++) {
            glColor3fv(particles[i].color);
            glVertex3fv(particles[i].position);
        }
        glEnd();
        glPopMatrix();

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_DEPTH_TEST);


        for (int i = 0; i < NUM_DEBRIS; i++) {
            glColor3fv(debris[i].color);

            glPushMatrix();
            glTranslatef(debris[i].position[0],
                debris[i].position[1],
                debris[i].position[2]);

            glRotatef(debris[i].orientation[0], 1.0, 0.0, 0.0);
            glRotatef(debris[i].orientation[1], 0.0, 1.0, 0.0);
            glRotatef(debris[i].orientation[2], 0.0, 0.0, 1.0);

            glScalef(debris[i].scale[0], debris[i].scale[1], debris[i].scale[2]);

            glBegin(GL_TRIANGLES);
            glNormal3f(0.0, 0.0, 1.0);
            glVertex3f(0.0, 0.5, 0.0);
            glVertex3f(-0.25, 0.0, 0.0);
            glVertex3f(0.25, 0.0, 0.0);
            glEnd();
            glPopMatrix();
        }
    }
}