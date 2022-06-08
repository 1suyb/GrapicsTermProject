#pragma once

#ifndef __EVENT_INCLUDED__
#define __EVENT_INCLUDED__

#include "Scene.h"

extern int ClickMouseButton ;
extern float Acceleration;
extern float Speed;
extern bool InCarView;

void Keyboard(unsigned char key, int x, int y);
void Reshape(int w, int h);
void Timer(int value);
void UpKeyboard(unsigned char key, int x, int y);

void CollisionDetection();
void CarMoveEvent();



#endif // !__EVENET_INCLUDED__
