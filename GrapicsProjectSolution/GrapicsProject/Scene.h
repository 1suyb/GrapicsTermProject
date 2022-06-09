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

extern Camera Cam;
extern Model Car;
extern Box box;


void init();					// �ʱ�ȭ
void render();			// Scene Render
void InitLight();			/** Test�� ���� �����Դϴ�. ���� ���� ������� �ļ� ������ֽø� �� �� ���ƿ� **/
void modelinit();
void LoadGLTextures();
void MyIdle(void);
void PerspectiveSetting();
void CameraSetting();

#endif // !SCENEINCLUDED
