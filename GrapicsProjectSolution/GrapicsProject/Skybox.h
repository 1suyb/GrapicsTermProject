#pragma once

#ifndef __SKYBOX_INCLUDED__
#define __SKYBOX_INCLUDED__

#include "Includes.h"
#include <glaux.h>
static GLuint tex[7];   // Skybox Texture Mapping을 하기 위한 Texture 이미지의 개수를 위한 배열 변수
AUX_RGBImageRec* LoadBMP(char* Filename);
void LoadGLTextures();

void DrawSkyBox();

#endif // !SKYBOXINCLUDED
