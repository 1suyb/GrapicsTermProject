#pragma once

#ifndef __EVENT_INCLUDED__
#define __EVENT_INCLUDED__

#include "Scene.h"

extern int ClickMouseButton ;
extern float Speed;

void EventCall();

void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Reshape(int w, int h);
void Timer(int value);



#endif // !__EVENET_INCLUDED__
