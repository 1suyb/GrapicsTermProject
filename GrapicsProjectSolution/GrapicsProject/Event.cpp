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
	//�ִϸ��̼� on/off
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
	//��ֹ� ����
	//addBox(glm::vec3(-10, -10, -5), glm::vec3(10, 10, 20));


	glutPostRedisplay();
	glutTimerFunc(50, Timer, 1);

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
