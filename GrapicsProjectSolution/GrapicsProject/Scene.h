#pragma once
/*
*	Main���� ������ �� �ʱ�ȭ �� �� ������ �Լ� ���Ǻκ� �Դϴ�.
*/
#ifndef __SCENE_INCLUDED__
#define __SCENE_INCLUDED__

#include "Includes.h"
#include "Model.h"
#include "Event.h"
#include "Camera.h"

void init();					// �ʱ�ȭ
void render();			// Scene Render
void InitLight();			/** Test�� ���� �����Դϴ�. ���� ���� ������� �ļ� ������ֽø� �� �� ���ƿ� **/

void PerspectiveSetting();
void CameraSetting();

extern Model Car;
extern camera Cam;

#endif // !SCENEINCLUDED
