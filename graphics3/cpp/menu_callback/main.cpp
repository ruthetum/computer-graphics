// ������Ʈ �ɼ� - Linker 
// -lopengl32
// -lfreeglut
// -lglu32
// -lwinmm
// -lgdi32 
// �߰� 

#include <GL/glut.h>

GLboolean IsSphere = true;	// � ����� �׸��� �����ϱ� ���� ��������

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);	// ������ �ʱ�ȭ��(glClearColor())���� ȭ�� ���� 
	glColor3f(0.5, 0.0, 0.5);
	
	// IsSphere ���� ���� �׸��� 
	if (IsSphere){
		glutWireSphere(0.2, 15, 15);
	}  else {
		glutWireTorus(0.1, 0.3, 40, 20);
	}
	glFlush();
}

// �޴����� Ŭ���� �� �޾Ƽ� IsSphere �� ���� 
void MyMainMenu(int entryID) {
	if (entryID==1) {
		IsSphere = true;
	} else if (entryID==2){
		IsSphere = false;
	} else if (entryID==3){
		exit(0);
	}
	glutPostRedisplay();
} 
 
int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);	// ���� ���۵� ����ϱ� ���� ���
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("OpenGL with Menu Callback");
  	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	
	// �ݹ� �Լ� ��� 
	// �޴� �ݹ� �����, id�� ���� 
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	// �޴� �߰� 
	glutAddMenuEntry("Draw Sphere", 1);
	glutAddMenuEntry("Draw Torus", 2);
	glutAddMenuEntry("Exit", 3);
	// ���콺 ������ ��ư Ŭ�� �� �޴� �˾� 
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(MyDisplay);
	
  	glutMainLoop();
  	return 0;
}
