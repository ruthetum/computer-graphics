#include <GL/glut.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0,700,500);
	// parameter ���� 
	glutSolidTetrahedron();
//	glutWireTetrahedron();  // wireframe renderring
	glEnd();
	glFlush();	
}


int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(700, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Modeling �����ü with GLUT");
	glutDisplayFunc(MyDisplay);
  	glutMainLoop();
  	return 0;
}
