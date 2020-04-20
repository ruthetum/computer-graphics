// ������Ʈ �ɼ� - Linker 
// -lopengl32
// -lfreeglut
// -lglu32
// -lwinmm
// -lgdi32 
// �߰� 

#include <GL/glut.h>

GLboolean IsSphere = true;	// � ����� �׸��� �����ϱ� ���� ��������
GLboolean IsSmall = true;	// choice big or small

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);	// ������ �ʱ�ȭ��(glClearColor())���� ȭ�� ���� 
	glColor3f(0.5, 0.0, 0.5);
	
	// ���, ũ�� ���ǿ� ���� �׸���
	if ((IsSphere) && (IsSmall)) {
		glutWireSphere(0.2, 15, 15);
	} else if ((IsSphere) && (!IsSmall)) {
		glutWireSphere(0.4, 15, 15);
	} else if ((!IsSphere) && (IsSmall)) {
		glutWireTorus(0.1, 0.3, 40, 20);
	} else {
		glutWireTorus(0.2, 0.3, 40, 20);
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

// submenu - choice big or small
void MySubMenu (int entryID) {
	if (entryID==1) {
		IsSmall = true;
	} else if (entryID==2){
		IsSmall = false;
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
	GLint MySubMenuID = glutCreateMenu(MySubMenu);	// ���� �޴� �ݹ�
	// ���� �޴� �׸� �߰� 
	glutAddMenuEntry("Small One", 1);
	glutAddMenuEntry("Big One", 2);
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);	// ���� �޴� �ݹ� 
	// �޴� �׸� �߰� 
	glutAddMenuEntry("Draw Sphere", 1);
	glutAddMenuEntry("Draw Torus", 2);
	glutAddSubMenu("Change Size", MySubMenuID);	// ���� �޴� - MySubMenu() 
	glutAddMenuEntry("Exit", 3);
	// ���콺 ������ ��ư Ŭ�� �� �޴� �˾� 
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(MyDisplay);
	
  	glutMainLoop();
  	return 0;
}
