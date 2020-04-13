#include <GL/glut.h>

void MyDisplay2() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0,500,500);
	// parameter
	// radius : 반지름, slices : 경선, stacks : 위선 
//	glutSolidSphere(0.5, 20, 30);	// solid rendering
	glutWireSphere(0.5, 20, 30);  // wireframe renderring
	glEnd();
	glFlush();	
}


int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Modeling Sphere with GLUT");
	glutDisplayFunc(MyDisplay2);
  	glutMainLoop();
  	return 0;
}
