#include "Event.h"
#include "Includes.h"
#include "Model.h"
#include "Scene.h"

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
	CarMoveEvent();
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

}
