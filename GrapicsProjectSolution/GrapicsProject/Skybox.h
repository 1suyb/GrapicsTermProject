#pragma once

#ifndef __SKYBOX_INCLUDED__
#define __SKYBOX_INCLUDED__

#include "Includes.h"
#include <glaux.h>
static GLuint tex[7];   // Skybox Texture Mapping�� �ϱ� ���� Texture �̹����� ������ ���� �迭 ����
AUX_RGBImageRec* LoadBMP(char* Filename);
void LoadGLTextures();

void DrawSkyBox();

#endif // !SKYBOXINCLUDED
