#pragma once

#ifndef __CAMERA_INCLUDED__
#define __CAMERA_INCLUDED__
#include "Includes.h"

class camera {
private:
	const float distance = 1;

public:
	glm::vec3 eye;
	glm::vec3 at;
	glm::vec3 up;
	glm::vec3 offset;

	void Start(glm::vec3 _eye, glm::vec3 _at, glm::vec3 _up, glm::vec3 _offset);
	void Move(glm::vec3 move);
	void Rotate(float angle, glm::vec3 axis);
	void OutCar(glm::vec3 carpositon);
	void InCar(glm::vec3 carpostion, glm::vec3 at);
	

};

#endif // 
