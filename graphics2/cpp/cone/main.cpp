#include <GL/glut.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0,500,500);
	// parameter
	// base ������, height ����, slices : z�� �ѷ� ���� �ٻ�ȭ, stacks : z�� ���� �� �ٻ�ȭ 
//	glutSolidCone(0.5, 5, 20, 30);	// solid rendering
	glutWireCone(0.5, 5, 5, 12);  // wireframe renderring
	glEnd();
	glFlush();	
}


int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Modeling Cone with GLUT");
	glutDisplayFunc(MyDisplay);
  	glutMainLoop();
  	return 0;
}
