// ������Ʈ �ɼ� - Linker 
// -lopengl32
// -lfreeglut
// -lglu32
// -lwinmm
// -lgdi32 
// �߰� 

#include <GL/glut.h>

int MyListID;


void MyCreateList() {
	
	MyListID = glGenLists(1);
	// ���� �� ����� �� 
	// GLuint listOne, listTwo, listThree;
	// listOne = glGenList(3)
	// listTwo = listOne + 1;
	// listThree = listTwo + 1;
		 
	glNewList(MyListID, GL_COMPILE);	// ���常 
	
	glBegin(GL_POLYGON);
		glColor3f(0.5, 0.5, 0.5);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
	glEndList();
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	glCallList(MyListID);
	glFlush();
}

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("OpenGL with Display List");
  	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	glutDisplayFunc(MyDisplay);
	MyCreateList();
	
  	glutMainLoop();
  	return 0;
}
