#include "Includes.h"
#include "Scene.h"
#include "Event.h"
#include "Skybox.h"

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("CarRacingGame");

	init();
	glutDisplayFunc(render);	
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(30, Timer, 1);
	glutKeyboardUpFunc(UpKeyboard);
	glutMainLoop();
}
