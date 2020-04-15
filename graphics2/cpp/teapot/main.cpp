#include <GL/glut.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0,500,500);
	// parameter
	// size : 한 변의 길이 
	glutSolidTeapot(0.5);	// solid rendering
//	glutWireTeapot(0.5);  // wireframe renderring
	glEnd();
	glFlush();	
}


int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Modeling Teapot with GLUT");
	glutDisplayFunc(MyDisplay);
  	glutMainLoop();
  	return 0;
}
