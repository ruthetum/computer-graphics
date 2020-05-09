// ������Ʈ �ɼ� - Linker 
// -lopengl32
// -lfreeglut
// -lglu32
// -lwinmm
// -lgdi32 
// �߰� 

#include <GL/glut.h>

GLfloat MyVertices[8][3] = {
	{-0.25, -0.25, 0.25},
	{-0.25, 0.25, 0.25}, 
	{0.25, 0.25, 0.25},
	{0.25, -0.25, 0.25},
	{-0.25, -0.25, -0.25},
	{-0.25, 0.25, -0.25}, 
	{0.25, 0.25, -0.25},
	{0.25, -0.25, -0.25}
};

GLfloat MyColors[8][3] = {
	{0.2, 0.2, 0.2}, 
	{1.0, 0.0, 0.0},
	{1.0, 1.0, 0.0}, 
	{0.0, 1.0, 0.0},
	{0.0, 0.0, 1.0}, 
	{1.0, 0.0, 1.0},
	{1.0, 1.0, 1.0}, 
	{0.0, 1.0, 1.0}
};

GLubyte MyVertexList[24] = {
	0, 3, 2, 1,
	2, 3, 7, 6,
	0, 4, 7, 3,
	1, 2, 6, 5,
	4, 5, 6, 7,
	0, 1, 5, 4
};

void MyDisplay() {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(0.5, 0.5, 0.5);
//	glFrontFace(GL_CCW);	// �ݽð� ���� (default) 
//	glEnable(GL_CULL_FACE);	// ȭ�鿡 �� ���̴� ���� ���� 
//	glEnableClientState(GL_COLOR_ARRAY);	// ���� �迭 ��� Ȱ��ȭ 
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glColorPointer(3, GL_FLOAT, 0, MyColors);
//	glColorPointer(3, GL_FLOAT, 0, MyVertices);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glRotatef(30.0, 1.0, 1.0, 1.0);
//	for (GLint i=0; i<6; i++) {
//		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
//	}
//	// glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);
//	glFlush();
	glBegin(GL_POLYGON);
		glColor3fv(MyColors[0]); glVertex3fv(MyVertices[0]);
		glColor3fv(MyColors[3]); glVertex3fv(MyVertices[3]);
		glColor3fv(MyColors[2]); glVertex3fv(MyVertices[2]);
		glColor3fv(MyColors[1]); glVertex3fv(MyVertices[1]);
	glEnd();
}

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("OpenGL");
  	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	glutDisplayFunc(MyDisplay);
	
  	glutMainLoop();
  	return 0;
}
