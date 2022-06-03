#pragma once
/*
	���� �ҷ����� ������ϴ� Ŭ������ �����ϴ� ��������Դϴ�.
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
	glm::vec3 front;

public:
	Model() {
		position = glm::vec3(0, 0, 0);
		angle = 0;
		axis = glm::vec3(0, 1, 0);
		front = glm::vec3(1, 0, 0);
	}
	static bool LoadObj(const char* path,
		std::vector < glm::vec3 >& out_vertices,
		std::vector < glm::ivec3 >& out_faces,
		std::vector < glm::vec2 >& out_uvs,
		std::vector < glm::vec3 >& out_normals);	// obj���� import

	static bool LoadPly(const char* path,
		std::vector < glm::vec3 >& out_vertices,
		std::vector < glm::ivec3 >& out_faces,
		std::vector < glm::vec3 >& out_normals);	// ply���� import

	void DrawSurface();		// ǥ�� �׸���

	void Texturing();			/** �ؽ��Ŀø��°� ���⿡ �־������ �����־������ �߸𸣰ھ�� **/

	void Translate();
	void RotateAngle();
	void Translate(glm::vec3 translate);
	void RotateAngle(GLfloat angle, glm::vec3 axis);
	
	void Move(glm::vec3 move);
	void Rotate(GLfloat angle, glm::vec3 axis);

	void SetFront(glm::vec3 dir);

	void Scale(glm::vec3 scale);

};



#endif // !MODELINCLUDED

