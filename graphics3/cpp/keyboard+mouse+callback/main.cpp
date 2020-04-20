// ������Ʈ �ɼ� - Linker 
//-lopengl32
//-lfreeglut
//-lglu32
//-lwinmm
//-lgdi32 
// �߰� 

#include <GL/glut.h>

// R, r ������ �׸��� ������ �簢��
// G, g ������ �׸��� �ʷϻ� �簢�� 
// B, b ������ �׸��� �Ķ��� �簢��

// �������� ���� (�ݹ��Լ� �� �� ���� ���ؼ�)
GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;

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

// Ű���� �ݹ��Լ�
// R or r : glColor3f()�� ������(1, 0, 0) ����
// G or g : glColor3f()�� �ʷϻ�(0, 1, 0) ����
// B or b : glColor3f()�� �Ķ���(0, 0, 1) ����
void MyKeyboard(unsigned char KeyPressed, int x, int y) {
	switch(KeyPressed) {
		case 'R':
			glColor3f(1.0, 0.0, 0.0);
			break;
		case 'r':
			glColor3f(1.0, 0.0, 0.0);
			break;
		case 'G':
			glColor3f(0.0, 1.0, 0.0);
			break;
		case 'g':
			glColor3f(0.0, 1.0, 0.0);
			break;
		case 'B':
			glColor3f(0.0, 0.0, 1.0);
			break;
		case 'b':
			glColor3f(0.0, 0.0, 1.0);
			break;
	}
}

// ���콺 �ݹ�
 void MyMouseClick(GLint Button, GLint State, GLint x, GLint y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		TopLeftX = x;
		TopLeftY = y;
	}
}

void MyMouseMove(GLint x, GLint y) {
	BottomRightX = x;
	BottomRightY = y;
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Display square with Keyboard and Mouse Callback");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0 ,1.0, 0.0, 1.0, -1.0, 1.0);
	
	// �ݹ� �Լ� ��� 
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	
  	glutMainLoop();
  	return 0;
}
