#include "Camera.h"
//class Camera {
//public:
//	glm::vec3 eye;
//	glm::vec3 at;
//	glm::vec3 up;
//
//	void Start(glm::vec3 _eye, glm::vec3 _at, glm::vec3 _up);
//	void Update();
//	void Move(glm::vec3 move);
//	void Rotate(float angle, glm::vec3 axis);
//
//};

void camera::Start(glm::vec3 _eye, glm::vec3 _at, glm::vec3 _up) {
	this->eye = _eye;
	this->at = _at;
	this->up = normalize(_up);
}
void camera::Move(glm::vec3 move) {
	this->eye += move;
	this->at += move;
	std::printf("cameye : %f,%f,%f\n", (float)this->eye.x, (float)this->eye.y, (float)this->eye.z);
	std::printf("camat : %f,%f,%f\n", (float)this->at.x, (float)this->at.y, (float)this->at.z);

}
void camera::Rotate(float angle, glm::vec3 axis) {
	glm::mat4 rot = glm::rotate(glm::mat4(1), glm::radians(angle), axis);
	glm::vec3 atdir = this->at - this->eye;
	atdir = rot * glm::vec4(atdir, 0);
	this->at = atdir;
	up = glm::normalize(rot * glm::vec4(up,0));
}

void camera::OutCar(glm::vec3 carpositon) {
	this->eye = carpositon + glm::vec3(distance, distance, 0);
	this->at = carpositon;
	glm::mat4 rot = glm::rotate(glm::mat4(1), glm::radians(-45.f), glm::vec3(0, 1, 0));
	this->up = glm::normalize(rot * glm::vec4(up, 0));
}
void camera::InCar(glm::vec3 carpostion) {
	this->eye = carpostion;
	this->at = glm::vec3(distance, 0, 0);
	this->up = glm::vec3(0, 1, 0);
}