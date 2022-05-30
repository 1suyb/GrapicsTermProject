//#include "Includes.h"
#include "Scene.h"
#include "Box.h"


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("CarRacingGame");
	
	//init();
	init2();
	//glutDisplayFunc(render);
	glutDisplayFunc(Render);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(500, MyTimer, 1);


	glutMainLoop();
}
