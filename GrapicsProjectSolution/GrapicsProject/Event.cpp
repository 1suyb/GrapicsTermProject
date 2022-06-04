#include "Event.h"
#include "Includes.h"
#include "Model.h"

float Acceleration;
float Speed;
static bool Accelerate = false;
static bool Decelerate = false;
static bool InCarView = true;



void EventCall() {
	//glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(30, Timer, 1);
	//glutReshapeFunc(Reshape);
	//glutTimerFunc();
}

void Mouse(int button, int state, int x, int y) {

}
void Keyboard(unsigned char key, int x, int y) {

	GLfloat angle = 20.f;
	glm::vec3 r(0, 1, 0);
	if (key == 'w' || key == 'W') {
		Accelerate = true;
	}
	else {
		Accelerate = false;
	}
	if (key == 's' || key == 'S') {
		Decelerate = true;
	}
	else {
		Decelerate = false;
	}

	switch(key)
	{
	case 'w':
	case 'W' :
		
		break;
	case 'a':
	case 'A' :
		if (InCarView) {
			Car.Rotate(angle, r);
			Cam.Rotate(angle, r);
		}
		break;
	case 's' :
	case 'S' :

		break;
	case 'd':
	case 'D' :
		if (InCarView) {
			Car.Rotate(-angle, r);
			Cam.Rotate(-angle, r);
		}
		break;

	default:
		
		break;
	}
	glutPostRedisplay();
}
void Reshape(int w, int h) {

}
void Timer(int value) {
	CarMoveEvent();
	glutPostRedisplay();
	glutTimerFunc(30, Timer, 1);

}
void Idel() {
	Accelerate = false;
	Decelerate = false;
}

void CarMoveEvent() {
	glm::vec3 front = Car.front;
	if (Speed > 0) {
		Speed -= 0.0001f;
	}
	else if (Speed < 0) {
		Speed += 0.0001f;
	}

	if (Accelerate) {
		Acceleration += 0.0001f;
		if (Acceleration < 0) {
			Acceleration = -1 * Acceleration;
		}
	}
	else if (Decelerate) {
		Acceleration -= 0.0001f;
		if (Acceleration > 0) {
			Acceleration = -1 * Acceleration;
		}
	}
	else {
		if (Acceleration > 0) {
			Acceleration -= 0.0001f;
		}
		else if (Acceleration < 0) {
			Acceleration += 0.0001f;
		}
	}

	if (Acceleration != 0) {
		Speed += Acceleration;
	}
	else {
		if (Speed > 0) {
			Speed -= 0.0002f;
		}
		else if (Speed < 0) {
			Speed += 0.0002f;
		}
	}

	if (Speed > 0) {
		Car.Move(front * Speed);
		Cam.Move(front * Speed);
	}
	else if (Speed < 0) {
		Car.Move(front * Speed);
		Cam.Move(front * Speed);
	}

	printf("%f\n", Acceleration);
	printf("%f\n", Speed);
}
