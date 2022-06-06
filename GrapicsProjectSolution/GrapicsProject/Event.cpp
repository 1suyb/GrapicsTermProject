#include "Event.h"
#include "Includes.h"
#include "Model.h"
#include "Scene.h"

float Acceleration;
float Speed;
bool InCarView;
static bool Accelerate = true;
static bool Decelerate = false;

static POINT ptLastMousePosit;
static POINT ptCurrentMousePosit;
static bool bMousing;


void Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			printf("hello");
			ptLastMousePosit.x = ptCurrentMousePosit.x = x;
			ptLastMousePosit.y = ptCurrentMousePosit.y = y;
			bMousing = true;
		}
		else {
			bMousing = false;
		}
		break;
	case GLUT_MIDDLE_BUTTON:
	case GLUT_RIGHT_BUTTON:
		break;
	default:
		break;
	}
}
void Motion(int x, int y) {
	printf("buy");
	if (InCarView) {
		return;
	}
	if (bMousing) {
		printf("\n\n\n\n");
		ptLastMousePosit.x = x;
		ptLastMousePosit.y = y;
		Cam.Rotate((float)ptCurrentMousePosit.x - (float)ptLastMousePosit.x, glm::vec3(0, 1, 0));
	}

	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {

	GLfloat angle = 5.f;
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
		Car.Rotate(angle, r);

		break;
	case 'd':
	case 'D' :
		Car.Rotate(-angle, r);
		break;
	case 'f' :
	case'F' :
		InCarView = !InCarView;
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
	glm::vec3 front = glm::normalize(Car.front-Car.position);

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
		Speed *= 0.5f;
	}
	Car.Move(front * Speed);


	printf("%f\n", Acceleration);
	printf("%f\n", Speed);
}
