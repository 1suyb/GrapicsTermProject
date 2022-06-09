#include "Includes.h"
#include "Scene.h"
#include "Event.h"
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("CarRacingGame");

	init();
	glutIdleFunc(MyIdle); //파티클 및 파편 업데이트
	glutDisplayFunc(render);	
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(30, Timer, 1);
	glutKeyboardUpFunc(UpKeyboard);
	glutMainLoop();
}
