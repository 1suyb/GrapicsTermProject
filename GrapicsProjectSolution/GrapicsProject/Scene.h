#pragma once
/*
*	Main에서 실행할 씬 초기화 및 씬 렌더링 함수 정의부분 입니다.
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

void init();					// 초기화
void render();			// Scene Render
void nightLight();
void afternoonLight();
void modelinit();
void LoadGLTextures();
void MyIdle(void);
void PerspectiveSetting();
void CameraSetting();

#endif // !SCENEINCLUDED
