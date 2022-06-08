#pragma once

#ifndef __CAMERA_INCLUDED__
#define __CAMERA_INCLUDED__
#include "Includes.h"

class Camera {
private:
	const float distance = 1;

public:
	glm::vec3 eye;
	glm::vec3 at;
	glm::vec3 up;
	glm::vec3 offset;

	bool is_CarView;


	void Init(glm::vec3 offset);
	void Move(glm::vec3 move);
	void Rotate(float angle, glm::vec3 axis);
	void OutCar(glm::vec3 carpositon);
	void InCar(glm::vec3 carpostion, glm::vec3 at);
};

#endif // 
