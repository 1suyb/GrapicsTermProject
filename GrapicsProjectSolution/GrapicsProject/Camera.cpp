#include "Camera.h"

void Camera::Init(glm::vec3 offset) {
	this->offset = offset;
	this->is_CarView = true;
}

void Camera::Move(glm::vec3 move) {
	this->eye += move;
	this->at += move;
	std::printf("cameye : %f,%f,%f\n", (float)this->eye.x, (float)this->eye.y, (float)this->eye.z);
	std::printf("camat : %f,%f,%f\n", (float)this->at.x, (float)this->at.y, (float)this->at.z);

}
void Camera::Rotate(float angle, glm::vec3 axis) {
	glm::mat4 rot = glm::rotate(glm::mat4(1), glm::radians(angle), axis);
	glm::vec3 atdir = this->at - this->eye;
	atdir = rot * glm::normalize(glm::vec4(atdir, 0));
	this->at = atdir+this->eye;
	up = glm::normalize(rot * glm::vec4(up,0));
}

void Camera::OutCar(glm::vec3 carpositon) {
	this->eye = carpositon + glm::vec3(-distance, distance, 0);
	this->at = carpositon;
	glm::mat4 rot = glm::rotate(glm::mat4(1), glm::radians(-45.f), glm::vec3(0, 1, 0));
	this->up = glm::normalize(rot * glm::vec4(up, 0));
}
void Camera::InCar(glm::vec3 carpostion, glm::vec3 at) {
	this->eye = carpostion + offset;
	this->at = at+offset;
	this->up = glm::vec3(0, 1, 0);
}


