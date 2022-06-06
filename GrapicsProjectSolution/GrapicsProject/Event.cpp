#include "Event.h"
#include "Includes.h"
#include "Model.h"
#include "Scene.h"

float Acceleration;
float Speed;
static bool Accelerate = false;
static bool Decelerate = false;
static bool InCarView = true;
static POINT ptLastMousePosit;
static POINT ptCurrentMousePosit;
static bool bMousing;


void EventCall() {
	//glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(30, Timer, 1);
	//glutReshapeFunc(Reshape);
	//glutTimerFunc();
}

void Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			ptLastMousePosit.x = ptCurrentMousePosit.x = x;
			ptLastMousePosit.y = ptCurrentMousePosit.y = y;
			bMousing = true;
		}
		else
			bMousing = false;
		break;
	case GLUT_MIDDLE_BUTTON:
	case GLUT_RIGHT_BUTTON:
		break;
	default:
		break;
	}
}
void Motion(int x, int y) {
	ptCurrentMousePosit.x = x;
	ptCurrentMousePosit.y = y;

	if (bMousing)
	{
		g_fSpinX -= (ptCurrentMousePosit.x - ptLastMousePosit.x);
		g_fSpinY -= (ptCurrentMousePosit.y - ptLastMousePosit.y);
	}

	ptLastMousePosit.x = ptCurrentMousePosit.x;
	ptLastMousePosit.y = ptCurrentMousePosit.y;

	glutPostRedisplay();
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
	case 'a':
	case 'A' :
		if (InCarView) {
			Car.Rotate(angle, r);
			Cam.Rotate(angle, r);
		}
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
	glm::vec3 front = glm::normalize(Cam.at);
	//if (Speed > 0) {
	//	Speed -= 0.0001f;
	//}
	//else if (Speed < 0) {
	//	Speed += 0.0001f;
	//}

	if (Accelerate) {
		Acceleration = 0.05f;
		if (Speed < 1.f) {
			Speed += Acceleration;
		}
	}
	else if (Decelerate) {
		Acceleration = -0.05f;
		if (Speed > -1.f) {
			Speed += Acceleration;
		}
	}
	else {
		Acceleration = 0;
		if (Speed > 0) {
			Speed *= 0.5f;
		}
		else if (Speed < 0) {
			Speed *= 0.5f;
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
