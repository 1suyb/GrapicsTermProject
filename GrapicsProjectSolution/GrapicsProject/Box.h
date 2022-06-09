#pragma once
#include "Includes.h"
#include <time.h>
#include "Camera.h"
#include "glaux.h"


struct Box {
    vec3 p; //position
    vec3 v; //velocity
    //vec3 color; //color
    vec3 force; //force
    float r; //radius
    float m; //mass
};

void addBox(vec3 leftBottom, vec3 rightTop);
void Contact(float stiff);
void loadTexture();
void texturedCube(float size);
void init2();
void Render();
void MyReshape(int w, int h);
void MyTimer(int Value);