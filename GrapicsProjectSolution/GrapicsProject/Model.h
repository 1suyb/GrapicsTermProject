#pragma once
/*
	모델을 불러오고 드로잉하는 클래스를 정의하는 헤더파일입니다.
*/
#ifndef __MODEL_INCLUDED__
#define __MODEL_INCLUDED__

#include "Includes.h"
#include <time.h>



class Model {
public:
	std::vector < glm::vec3 > vertices;
	std::vector < glm::ivec3 > faces;
	std::vector < glm::vec2 > uvs;
	std::vector < glm::ivec3 > uvindices;
	std::vector < glm::vec3 > normals;
	std::vector < glm::ivec3 > normalindices;

	glm::vec3 position;
	GLfloat angle;
	glm::vec3 axis;
	glm::vec3 front;

public:
	Model();
	static bool LoadObj(const char* path,
		std::vector < glm::vec3 >& out_vertices,
		std::vector < glm::ivec3 >& out_faces,
		std::vector < glm::vec2 >& out_uvs,
		std::vector < glm::ivec3 >& uvindices,
		std::vector < glm::vec3 >& out_normals,
		std::vector < glm::ivec3 >& normalindices);	// obj파일 import


	static bool LoadPly(const char* path,
		std::vector < glm::vec3 >& out_vertices,
		std::vector < glm::ivec3 >& out_faces,
		std::vector < glm::vec3 >& out_normals);	// ply파일 import

	void DrawSurface(std::vector < glm::vec3 >& vectices,
		std::vector < glm::vec3 >& normals,
		std::vector < glm::vec2 >& uvs,
		std::vector < glm::ivec3 >& uvindicies,
		std::vector < glm::ivec3 >& normalindices,
		std::vector < glm::ivec3 >& faces);		// 표면 그리기

	//void Texturing();			/** 텍스쳐올리는게 여기에 있어야할지 따로있어야할지 잘모르겠어요 **/

	void Translate();
	void RotateAngle();
	void SetPosition(glm::vec3 translate);
	void SetRotation(GLfloat angle, glm::vec3 axis);
	
	void Move(glm::vec3 move);
	void Rotate(GLfloat angle, glm::vec3 axis);

	void SetFront(glm::vec3 dir);

	void Scale(glm::vec3 scale);

};

struct Box {
    glm::vec3 p; //position
    glm::vec3 v; //velocity
    glm::vec3 force; //force
    float r; //radius
    float m; //mass

};

void addBox(glm::vec3 leftBottom, glm::vec3 rightTop);
void Contact(float stiff);
void texturedCube(float size);
void loadTexture();

extern GLuint g_textureID[4];
extern std::vector<Box> boxes;


#endif // !MODELINCLUDED

