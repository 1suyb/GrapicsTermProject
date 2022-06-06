#pragma once
/*
*	Main에서 실행할 씬 초기화 및 씬 렌더링 함수 정의부분 입니다.
*/
#ifndef __SCENE_INCLUDED__
#define __SCENE_INCLUDED__

#include "Includes.h"
#include "Model.h"
#include "Event.h"
#include "Camera.h"

static float g_fDistance = -2.5f;
static float g_fSpinX = 0.0f;
static float g_fSpinY = 0.0f;
void init();					// 초기화
void render();			// Scene Render
void InitLight();			/** Test를 위한 조명입니다. 따로 조명 헤더파일 파서 만들어주시면 될 것 같아요 **/
// 모델 초기화 함수
void modelinit();
// 카메라 초기화 함수
void caminit();
void LoadGLTextures();

void PerspectiveSetting();
void CameraSetting();

extern Model Car;
extern camera Cam;

#endif // !SCENEINCLUDED
