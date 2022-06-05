#include "Event.h"
#include "Includes.h"
#include "Model.h"

float Speed;
static bool InCarView = true;

//장애물
bool animate = false;

void EventCall() {
	//glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	//glutReshapeFunc(Reshape);
	glutTimerFunc(500,Timer,1);
}

void Mouse(int button, int state, int x, int y) {

}
void Keyboard(unsigned char key, int x, int y) {
	glm::vec3 front = Car.front;
	GLfloat angle = 20.f;
	glm::vec3 r(0, 1, 0);
	switch(key)
	{
	//애니메이션 on/off
	case 't':
		animate = !animate;
		if (animate) {
			printf("animate\n");
		}
		else {
			printf("!animate\n");
		}
		break;

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
//void Reshape(int w, int h) {
//
//}


void Timer(int Value) {
	//update boxes
	float dt = 0.1;
	if (animate)
	{
		for (int i = 0; i < boxes.size(); i++) {

			//add gradient force
			glm::vec3 gravity(0, 0, -9.8);
			boxes[i].force += gravity * boxes[i].m;

			//update velocity
			boxes[i].v += boxes[i].force / boxes[i].m * dt;

			//update position
			boxes[i].p += boxes[i].v * dt;

			//바닥에서 안 튀어오르게
			//modify position and velocity according to constraints
			if (boxes[i].p[2] - boxes[i].r < -10) {
				boxes[i].p[2] = -10; // + boxes[i].r;
				/*boxes[i].v *= 0.9;
				boxes[i].v[2] *= -1;*/
			}

			Contact(10.0);

			//clear force
			boxes[i].force = glm::vec3(0, 0, 0);

		}
	}
	addBox(glm::vec3(-10, -10, -5), glm::vec3(10, 10, 20));

	glutPostRedisplay();
	glutTimerFunc(500, Timer, 1);
}
