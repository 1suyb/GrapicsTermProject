#pragma once
/*
	모델을 불러오고 드로잉하는 클래스를 정의하는 헤더파일입니다.
*/
#ifndef __MODEL_INCLUDED__
#define __MODEL_INCLUDED__

#include "Includes.h"


class Model {
public:
	std::vector < glm::vec3 > vertices;
	std::vector < glm::ivec3 > faces;
	std::vector < glm::vec2 > uvs;
	std::vector < glm::vec3 > normals;

	glm::vec3 position;
	GLfloat angle;
	glm::vec3 axis;

public:
//	Model();
	static bool LoadObj(const char* path,
		std::vector < glm::vec3 >& out_vertices,
		std::vector < glm::ivec3 >& out_faces,
		std::vector < glm::vec2 >& out_uvs,
		std::vector < glm::vec3 >& out_normals);	// obj파일 import

	static bool LoadPly(const char* path,
		std::vector < glm::vec3 >& out_vertices,
		std::vector < glm::ivec3 >& out_faces,
		std::vector < glm::vec3 >& out_normals);	// ply파일 import

	void DrawSurface();		// 표면 그리기

	void Texturing();			/** 텍스쳐올리는게 여기에 있어야할지 따로있어야할지 잘모르겠어요 **/

	void Translate(glm::vec3 translate);
	void RotateAngle(GLfloat angle, glm::vec3 axis);

	void Move(bool front);
	void Rotate(GLfloat angle, glm::vec3 axis);
};



#endif // !MODELINCLUDED

