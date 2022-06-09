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
	std::vector < glm::ivec3 > uvindices;
	std::vector < glm::vec3 > normals;
	std::vector < glm::ivec3 > normalindices; 
	std::vector < glm::vec3> uvs2;
	std::vector < glm::ivec4 > faces2;

	glm::vec3 position;
	GLfloat angle;
	glm::vec3 axis;
	glm::vec3 front;

	bool hasCollision;
	float colliderX;
	float colliderY;
	float colliderZ;

	Model();
	Model(bool collision);

	static bool LoadObj(const char* path,
		std::vector < glm::vec3 >& out_vertices,
		std::vector < glm::ivec3 >& out_faces,
		std::vector < glm::vec2 >& out_uvs,
		std::vector < glm::ivec3 >& uvindices,
		std::vector < glm::vec3 >& out_normals,
		std::vector < glm::ivec3 >& normalindices);	

	static bool LoadPly(const char* path,
		std::vector < glm::vec3 >& out_vertices,
		std::vector < glm::ivec3 >& out_faces,
		std::vector < glm::vec3 >& out_normals);	// ply���� import

	void Model::DrawSurface();
	
	void Texturing();

	void Translate();
	// ���� ȸ�� ����� �����մϴ�.
	void RotateAngle();
	// ���� Ʈ������ ����� �����մϴ�.
	void SetPosition(glm::vec3 translate);
	// ���� ȸ�� ����� �����մϴ�.
	void SetRotation(GLfloat angle, glm::vec3 axis);
	// ���� �̵�
	void Move(glm::vec3 move);
	// ���� ȸ��
	void Rotate(GLfloat angle, glm::vec3 axis);
	// ���� ������ �����մϴ�.
	void SetFront(glm::vec3 dir);
	// ���� ũ�⸦ �����մϴ�. �浹������ �Բ� �缳�� �մϴ�.
	void Scale(glm::vec3 scale);
	// �浹 ���� ����
	void SetCollider();
	// �浹���� ũ�� ����
	void SetColliderSize(glm::vec3 colscale);
	// �浹�� �൹
	void OnEnterCollider();

};

class Car : Model {
public :
	Car() :Model() {};
	Car(bool collider) :Model( collider) {};
	void OnEnterCollider();
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

