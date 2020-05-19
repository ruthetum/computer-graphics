// 프로젝트 옵션 - Linker 
// -lopengl32
// -lfreeglut
// -lglu32
// -lwinmm
// -lgdi32 
// 추가 

#include <GL/glut.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0,500,500);
	glColor3f(0.5, 0.5, 0.0);
	
	// glRotatef(GLfloat angle, GLfloat x, Glfloat y, Glfloat z) : x,y,z 벡터 축으로 회전 
	glRotatef(60, 1, 1, 0);
	// glScalef(GLfloat x, Glfloat y, Glfloat z) : 확대, 축소 
	glScalef(0.5, 0.8, 0.6);
	// glTranslatef(GLfloat x, Glfloat y, Glfloat z) : 평행이동 
	glTranslatef(0.2, 0, 0.7);
	
	
	glutWireTorus(0.2, 0.6, 10, 20);
	glEnd();
	glFlush();	
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Modeling Torus with Model Transformation");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
  	glutMainLoop();
  	return 0;
}
