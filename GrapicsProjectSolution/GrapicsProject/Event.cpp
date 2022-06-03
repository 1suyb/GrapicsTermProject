#include "Event.h"
#include "Includes.h"
#include "Model.h"

float Speed;

//Model Car = Model();
//glm::vec3 Car_position = glm::vec3(0, 0, 0);
//GLfloat Car_rotation_angle = 0;
//glm::vec3 Car_rotation_axis = glm::vec3(0, 0, 0);

void EventCall() {
	//glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	//glutReshapeFunc(Reshape);
	//glutTimerFunc();
}

void Mouse(int button, int state, int x, int y) {

}
void Keyboard(unsigned char key, int x, int y) {
	glm::vec3 front = glm::normalize(Cam.at - Cam.eye);
	GLfloat angle = 20.f;
	glm::vec3 r(0, 1, 0);
	switch(key)
	{
	case 'w':
	case 'W' :
		//Car.Move(m);
		Cam.Move(front*Speed);
		break;
	case 'a':
	case 'A' :
		//Car.Rotate(angle, r);
		Cam.Rotate(angle, r);
		break;
	case 's' :
	case 'S' :
		//Car.Move(-m);
		Cam.Move(-front * Speed);
		break;
	case 'd':
	case 'D' :
		//Car.Rotate(-angle,r);
		Cam.Rotate(-angle, r);
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
