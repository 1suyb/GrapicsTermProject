#pragma once
/*
*	Main���� ������ �� �ʱ�ȭ �� �� ������ �Լ� ���Ǻκ� �Դϴ�.
*/
#ifndef __SCENE_INCLUDED__
#define __SCENE_INCLUDED__

#include "Includes.h"
#include "Model.h"
#include "Camera.h"
#include "Event.h"
#include "Skybox.h"
#include"Box.h"

#define BOX_SIZE 10


extern Camera Cam;
extern Model Car;
extern Box* Boxes;

void init();					// �ʱ�ȭ
void render();			// Scene Render
void nightLight();
void afternoonLight();
void modelinit();
void LoadGLTextures();
void MyIdle(void);
void PerspectiveSetting();
void CameraSetting();

#endif // !SCENEINCLUDED
