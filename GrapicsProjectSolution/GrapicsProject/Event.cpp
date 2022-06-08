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

//장애물
bool animate = false;

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
	//애니메이션 on/off
	case 't':
	case 'T':
		animate = !animate;
		if (animate) {
			printf("animate\n");
		}
		else {
			printf("!animate\n");
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
	//update boxes

	float dt = 0.1;
	if (animate)
	{
		for (int i = 0; i < boxes.size(); i++) {

			//add gradient force
			glm::vec3 gravity(0, -10, 0);
			boxes[i].force += gravity * boxes[i].m;

			//update velocity
			boxes[i].v += boxes[i].force / boxes[i].m * dt;

			//update position
			boxes[i].p += boxes[i].v * dt;
						
			//modify position and velocity according to constraints
			if (boxes[i].p[1] - boxes[i].r < -10) {
				boxes[i].p[1] = -30;
				
				
			}

			Contact(10.0);

			//clear force
			boxes[i].force = glm::vec3(0, 0, 0);

		}
	}
	//장애물 생성
	//addBox(glm::vec3(-10, -10, -5), glm::vec3(10, 10, 20));


	glutPostRedisplay();
	glutTimerFunc(50, Timer, 1);

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
