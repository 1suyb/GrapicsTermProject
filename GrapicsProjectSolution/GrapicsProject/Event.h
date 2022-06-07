#pragma once

#ifndef __EVENT_INCLUDED__
#define __EVENT_INCLUDED__

#include "Scene.h"

extern int ClickMouseButton ;
extern float Speed;
extern float Acceleration;
extern float Speed;
extern bool InCarView;

void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Reshape(int w, int h);
void Timer(int value);
void Idel();

void CarMoveEvent();
void Motion(int x, int y);



#endif // !__EVENET_INCLUDED__
