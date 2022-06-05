#include "Event.h"
#include "Includes.h"
#include "Model.h"

float Speed;
static bool InCarView = true;


void EventCall() {
	//glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	//glutReshapeFunc(Reshape);
	//glutTimerFunc();
}

void Mouse(int button, int state, int x, int y) {

}
void Keyboard(unsigned char key, int x, int y) {
	glm::vec3 front = Car.front;
	GLfloat angle = 20.f;
	glm::vec3 r(0, 1, 0);
	switch(key)
	{
	case 'w':
	case 'W' :
		if (InCarView) {
			Car.Move(front * Speed);
			Cam.Move(front * Speed);
		}
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
		if (InCarView) {
			Car.Move(-front * Speed);
			Cam.Move(-front * Speed);
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
void Timer() {

}
