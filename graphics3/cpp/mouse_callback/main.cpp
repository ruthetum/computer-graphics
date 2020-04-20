// ������Ʈ �ɼ� - Linker 
//-lopengl32
//-lfreeglut
//-lglu32
//-lwinmm
//-lgdi32 
// �߰� 

// ���콺 �巡���� �� �簢���� �׷����� ���� ���콺 ��ư�� ������ ��(Release) �׷����� �簢���� ���� �ٸ����� ����

#include <GL/glut.h>


// �������� ���� (�ݹ��Լ� �� �� ���� ���ؼ�)
GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY; 

// �簢�� �׸��� 
void MyDisplay() {
	glViewport(0, 0, 500, 500);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glVertex3f(TopLeftX / 500.0, (500-TopLeftY) / 500.0, 0.0);
    	glVertex3f(TopLeftX / 500.0, (500-BottomRightY) / 500.0, 0.0);
    	glVertex3f(BottomRightX / 500.0, (500-BottomRightY) / 500.0, 0.0);
    	glVertex3f(BottomRightX / 500.0, (500-TopLeftY) / 500.0, 0.0);
	glEnd();
	glFlush();
}

void MyMouseClick(GLint Button, GLint State, GLint x, GLint y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		TopLeftX = x;
		TopLeftY = y;
	}
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_UP) {
		glColor3f(1.0, 0.0, 0.0);
		glutPostRedisplay();
	}
}

void MyMouseMove(GLint x, GLint y) {
	BottomRightX = x;
	BottomRightY = y;
	glColor3f(0.5, 0.5, 0.5);
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Display square with Mouse Callback");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0 ,1.0, 0.0, 1.0, -1.0, 1.0);
	
	// �ݹ� �Լ� ��� 
	glutDisplayFunc(MyDisplay);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	
  	glutMainLoop();
  	return 0;
}
