// ������Ʈ �ɼ� - Linker 
// -lopengl32
// -lfreeglut
// -lglu32
// -lwinmm
// -lgdi32 
// �߰� 

// Ű���� R(�Ǵ� r), G(�Ǵ� g), B(�Ǵ� b)�� ������ ��, ���� �簢���� ���� Red, Green, Blue�� ��Ÿ������ ����

#include <GL/glut.h>

// �簢�� �׸��� 
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glVertex3f(-0.5, -0.5, 0.0);
    	glVertex3f(0.5, -0.5, 0.0);
    	glVertex3f(0.5, 0.5, 0.0);
    	glVertex3f(-0.5, 0.5, 0.0);
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

// ������ ũ�� ���� �� �ְ� ���� 
void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat) NewWidth / (GLfloat) 500;
	GLfloat HeightFactor = (GLfloat) NewHeight / (GLfloat) 500;
	
	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	
	glOrtho(-1.0*WidthFactor, 1.0*WidthFactor, -1.0*HeightFactor, 1.0*HeightFactor, -1.0, 1.0);
}

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Display square with Keyboard Callback");
	glClearColor(1.0, 1.0, 1.0, 1.0); // ��� ��� 
	
	// �ݹ� �Լ� ��� 
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	
  	glutMainLoop();
  	return 0;
}
