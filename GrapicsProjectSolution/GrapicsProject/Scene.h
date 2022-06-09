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

extern Camera Cam;
extern Model Car;
extern Box box;


void init();					// 초기화
void render();			// Scene Render
void InitLight();			/** Test를 위한 조명입니다. 따로 조명 헤더파일 파서 만들어주시면 될 것 같아요 **/
void modelinit();
void LoadGLTextures();
void MyIdle(void);
void PerspectiveSetting();
void CameraSetting();

#endif // !SCENEINCLUDED
