#pragma once
/*
	���� �ҷ����� ������ϴ� Ŭ������ �����ϴ� ��������Դϴ�.
*/
#ifndef __MODEL_INCLUDED__
#define __MODEL_INCLUDED__

#include "Includes.h"


class Model {
public:
	/* obj������ ���� */
	std::vector < glm::vec3 > vertices;
	std::vector < glm::ivec3 > faces;
	std::vector < glm::vec2 > uvs;
	std::vector < glm::vec3 > normals;

	/* Scene������ ��ġ ���� */
	glm::vec3 position;
	GLfloat angle;
	glm::vec3 axis;
	glm::vec3 front;	// ���� ���� ���� ����.
	/* 
	 * �⺻������ ���� 1,0,0�� ������ �ٶ󺸰� �ִٰ� �����մϴ�. �׷��� ���� �𵨸� SetFront�Լ��� �ѹ��� �������ָ�˴ϴ�. 
	 * ex) obj�ε��ؼ� �ҷ��Դ��� -1,0,0 �� ������ �� -> setFront(glm::vec3(-1,0,0))
	 */

	/* ����ó���� ���� ���� */
	bool hasCollision;
	float colliderX;
	float colliderY;
	float colliderZ;

public:
	Model();
	Model(bool collision);
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

	// ���� Ʈ������ ����� �����մϴ�.

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

#endif // !MODELINCLUDED

