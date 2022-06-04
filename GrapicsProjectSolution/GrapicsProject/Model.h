#pragma once
/*
	모델을 불러오고 드로잉하는 클래스를 정의하는 헤더파일입니다.
*/
#ifndef __MODEL_INCLUDED__
#define __MODEL_INCLUDED__

#include "Includes.h"


class Model {
public:
	/* obj파일의 정보 */
	std::vector < glm::vec3 > vertices;
	std::vector < glm::ivec3 > faces;
	std::vector < glm::vec2 > uvs;
	std::vector < glm::vec3 > normals;

	/* Scene에서의 위치 정보 */
	glm::vec3 position;
	GLfloat angle;
	glm::vec3 axis;
	glm::vec3 front;	// 모델의 정면 방향 벡터.
	/* 
	 * 기본적으로 모델이 1,0,0의 방향을 바라보고 있다고 가정합니다. 그렇지 않은 모델만 SetFront함수로 한번만 변경해주면됩니다. 
	 * ex) obj로드해서 불러왔더니 -1,0,0 이 정면인 모델 -> setFront(glm::vec3(-1,0,0))
	 */

	/* 물리처리에 대한 정보 */
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
		std::vector < glm::vec3 >& out_normals);	// obj파일 import

	static bool LoadPly(const char* path,
		std::vector < glm::vec3 >& out_vertices,
		std::vector < glm::ivec3 >& out_faces,
		std::vector < glm::vec3 >& out_normals);	// ply파일 import

	void DrawSurface();		// 표면 그리기

	void Texturing();			/** 텍스쳐올리는게 여기에 있어야할지 따로있어야할지 잘모르겠어요 **/

	// 모델의 트랜스폼 행렬을 적용합니다.

	void Translate();
	// 모델의 회전 행렬을 적용합니다.
	void RotateAngle();
	// 모델의 트렌스폼 행렬을 변경합니다.
	void SetPosition(glm::vec3 translate);
	// 모델의 회전 행렬을 변경합니다.
	void SetRotation(GLfloat angle, glm::vec3 axis);
	// 모델의 이동
	void Move(glm::vec3 move);
	// 모델의 회전
	void Rotate(GLfloat angle, glm::vec3 axis);
	// 모델의 정면을 정의합니다.
	void SetFront(glm::vec3 dir);
	// 모델의 크기를 변경합니다. 충돌범위도 함께 재설정 합니다.
	void Scale(glm::vec3 scale);
	// 충돌 범위 설정
	void SetCollider();
	// 충돌범위 크기 설정
	void SetColliderSize(glm::vec3 colscale);
	// 충돌시 행돌
	void OnEnterCollider();

};

class Car : Model {
public :
	Car() :Model() {};
	Car(bool collider) :Model( collider) {};
	void OnEnterCollider();
};

#endif // !MODELINCLUDED

