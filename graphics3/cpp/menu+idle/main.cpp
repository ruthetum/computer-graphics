// ������Ʈ �ɼ� - Linker 
// -lopengl32
// -lfreeglut
// -lglu32
// -lwinmm
// -lgdi32 
// �߰� 

#include <GL/glut.h>

// Mode=0 : init(�ʱ�ȭ������ ����)
// Mode=1 : start(��Ÿ �� ����)
// Mode=2 : stop (��Ÿ �� ���� ����)  
GLint Mode = 0;
GLfloat Delta = 0.0;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.5, 0.8);
	if (Mode==0) {
		// init, �ʱ� ȭ�鿡�� ���� 
		glBegin(GL_POLYGON);
			glVertex3f(-1.0, -0.5, 0.0);
    		glVertex3f(0.0, -0.5, 0.0);
    		glVertex3f(0.0, 0.5, 0.0);
    		glVertex3f(-1.0, 0.5, 0.0);
	} else {
		// start, Delta����ŭ �̵� 
		glBegin(GL_POLYGON);
			glVertex3f(-1.0+Delta, -0.5, 0.0);
    		glVertex3f(0.0+Delta, -0.5, 0.0);
    		glVertex3f(0.0+Delta, 0.5, 0.0);
    		glVertex3f(-1.0+Delta, 0.5, 0.0);
	}
	glEnd();
	glutSwapBuffers();
}

// MainMenu���� �� ID���� ���� Mode ���� 
void MyMainMenu(int entryID) {
	if (entryID==1) {
		Mode = 0;
	} else if (entryID==2){
		Mode = 1;
	} else if (entryID==3){
		Mode = 2;
	} else if (entryID==4) {
		exit(0);
	}
	glutPostRedisplay();
}

// Mode=0 : Delta �� 0���� �ʱ�ȭ
// Mode=1 : Delta �� ����
// Mode=1�� �����ϰ�� Delta���� �������� �����Ƿ� Mode=2(Stop)�� ��� Delta���� �������� ����. 
void MyIdle() {
	if (Mode == 0) {
		Delta = 0.0;
	} else if (Mode == 1) {
		Delta += 0.001;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Display moving square with Idle and Menu Callback");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Init", 1);
	glutAddMenuEntry("Start", 2);
	glutAddMenuEntry("Stop", 3);
	glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(MyDisplay);
	glutIdleFunc(MyIdle);
	
  	glutMainLoop();
  	return 0;
}
