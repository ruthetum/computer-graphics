// ������Ʈ �ɼ� - Linker 
// -lopengl32
// -lfreeglut
// -lglu32
// -lwinmm
// -lgdi32 
// �߰� 

#include <GL/glut.h>

GLfloat Delta = 0.0; // idle �ݹ鿡�� ����� ���� MyDisplay���� ����ϱ� ���� 

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);	// ������ �ʱ�ȭ��(glClearColor())���� ȭ�� ���� 
	glColor3f(0.0, 0.5, 0.8);
	glBegin(GL_POLYGON);
		glVertex3f(-1.0+Delta, -0.5, 0.0);
    	glVertex3f(0.0+Delta, -0.5, 0.0);
    	glVertex3f(0.0+Delta, 0.5, 0.0);
    	glVertex3f(-1.0+Delta, 0.5, 0.0);
	glEnd();
	glutSwapBuffers();	// ���� ������ ��� (reduce flickering)
}

void MyIdle() {
	Delta += 0.001;
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);	// ���� ���۵� ����ϱ� ���� ���
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Display moving square with Idle Callback");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	
	// �ݹ� �Լ� ��� 
	glutDisplayFunc(MyDisplay);
	glutIdleFunc(MyIdle);
	
  	glutMainLoop();
  	return 0;
}
