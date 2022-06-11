#include "Event.h"
#include "Includes.h"
#include "Model.h"
#include "Scene.h"
#include <stdlib.h>

float Acceleration;
float Speed;
bool InCarView;
static bool Accelerate = false;
static bool Decelerate = false;

void Keyboard(unsigned char key, int x, int y) {

	GLfloat angle = 10.f;
	glm::vec3 r(0, 1, 0);
	
	switch(key)
	{
	case 'e':
	case 'E':
		////newExplosion();
		Boxes[0].newExplosion();
		break;
	case 'a':
	case 'A' :
		Car.Rotate(angle, r);

		break;
	case 'd':
	case 'D' :
		Car.Rotate(-angle, r);
		break;
	case 'f' :
	case'F' :
		Cam.is_CarView = !Cam.is_CarView;
		break;
	case 'l' :
	case 'L' :
		nightLight();
		break;
	case ';' :
		afternoonLight();
		break;
	default:
		
		break;
	}
	if (key == 'w' || key == 'W') {
		Accelerate = true;
	}
	if (key == 's' || key == 'S') {
		Decelerate = true;
	}
	glutPostRedisplay();
}
void Reshape(int w, int h) {

}
void Timer(int value) {
	if (Car.position.x > 30||Car.position.x <-30 || Car.position.z >60||Car.position.z<-60) {
		Speed = -1*Speed;
	}
	
	CarMoveEvent();
	CollisionDetection();
	for (int i = 0; i < BOX_SIZE; i++) {
		Boxes[i].ParticleUpdate();
	}
	glutPostRedisplay();
	glutTimerFunc(50, Timer, 1);
	// x +- 20 , z+- 60
}
void UpKeyboard(unsigned char key, int x, int y) {
	if (key == 'w' || key == 'W') {
		Accelerate = false;
	}
	if (key == 's' || key == 'S') {
		Decelerate = false;
	}
}


void CarMoveEvent() {
	glm::vec3 front = glm::normalize(Car.front-Car.position);

	if (Accelerate) {
		Acceleration = 0.05f;
		if (Speed < 2.f) {
			Speed += Acceleration;
		}
	}
	else if (Decelerate) {
		Acceleration = -0.05f;
		if (Speed > -2.f) {
			Speed += Acceleration;
		}
	}
	else {
		Acceleration = 0;
		Speed *= 0.7f;
	}
	Car.Move(front * Speed);


	printf("%f\n", Acceleration);
	printf("%f\n", Speed);
}
void CollisionDetection() {
	for (int i = 0; i < BOX_SIZE; i++) {
		glm::vec3 vec = Car.position - Boxes[i].position;
		float mag = glm::length(vec);
		if (mag < Car.coliider.x || mag<Car.coliider.z) {
			glm::mat4 rot = glm::rotate(glm::mat4(1), glm::radians(Car.angle), Car.axis);
			glm::vec3 vecx = glm::normalize(rot * glm::vec4(1, 0, 0, 0));
			glm::vec3 vecz = glm::normalize(rot * glm::vec4(0, 0, 1, 0));
			float x = glm::dot(vec, vecx);
			float z = glm::dot(vec, vecz);
			if (x < Car.coliider.x && z < Car.coliider.z) {
				printf("%d", i);
				Boxes[i].newExplosion();
			}
		}
	}
}

