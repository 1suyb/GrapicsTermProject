#include "Event.h"
#include "Includes.h"
#include "Model.h"
#include "Scene.h"

float Speed;
static bool InCarView = true;
static POINT ptLastMousePosit;
static POINT ptCurrentMousePosit;
static bool bMousing;

void EventCall() {
	//glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
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
