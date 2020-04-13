#include <GL/glut.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0,500,500);
	// parameter
	// innerRadius, outerRddius : ��, �� ������, nsides : �ܸ� �ٻ�ȭ, rings : ���� �ٻ�ȭ 
//	glutSolidTorus(0.2, 0.3, 5, 30);	// solid rendering
	glutWireTorus(0.2, 0.6, 10, 20);  // wireframe renderring
	glEnd();
	glFlush();	
}


int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Modeling Torus with GLUT");
	glutDisplayFunc(MyDisplay);
  	glutMainLoop();
  	return 0;
}
