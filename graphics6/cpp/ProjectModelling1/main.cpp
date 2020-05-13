// ������Ʈ �ɼ� - Linker 
//-lopengl32
//-lfreeglut
//-lglu32
//-lwinmm
//-lgdi32 
// �߰� 

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265358972
#define LIST_SIZE 7

// ���콺 �����ӿ� ���� ���� ����� �������� 
GLint clickedX, clickedY;
GLint ViewX = 0, ViewY = 0;

// Ű���� �ݹ��� ���� �� ������ ���� ���� 
int FlatShaded = 1, WireFramed = 0; 

// �� ��ǥ
GLfloat etX = 0.0, etY = 0.0, etZ = -1.0;

// Ź�� ���� 
GLfloat upperTableVertices[8][3] = {
	{ -0.5, -0.1, 0.5},
	{ -0.5, 0.0, 0.5},
	{ 0.5, 0.0, 0.5}, 
	{ 0.5, -0.1, 0.5}, 
	{ -0.5, -0.1, -0.5}, 
	{ -0.5, 0.0, -0.5}, 
	{ 0.5, 0.0, -0.5},
	{ 0.5, -0.1, -0.5}
};
// Ź�� �ٸ� 
GLfloat LFLegVertices[8][3] = {
	{ -0.5, -0.4, 0.5},
	{ -0.5, -0.1, 0.5},
	{ -0.4, -0.1, 0.5}, 
	{ -0.4, -0.4, 0.5}, 
	{ -0.5, -0.4, 0.4},
	{ -0.5, -0.1, 0.4},
	{ -0.4, -0.1, 0.4}, 
	{ -0.4, -0.4, 0.4}
};
GLfloat RFLegVertices[8][3] = {
	{ 0.4, -0.4, 0.5},
	{ 0.4, -0.1, 0.5},
	{ 0.5, -0.1, 0.5}, 
	{ 0.5, -0.4, 0.5}, 
	{ 0.4, -0.4, 0.4},
	{ 0.4, -0.1, 0.4},
	{ 0.5, -0.1, 0.4}, 
	{ 0.5, -0.4, 0.4}
};
GLfloat LBLegVertices[8][3] = {
	{ -0.5, -0.4, -0.4},
	{ -0.5, -0.1, -0.4},
	{ -0.4, -0.1, -0.4}, 
	{ -0.4, -0.4, -0.4}, 
	{ -0.5, -0.4, -0.5},
	{ -0.5, -0.1, -0.5},
	{ -0.4, -0.1, -0.5}, 
	{ -0.4, -0.4, -0.5}
};
GLfloat RBLegVertices[8][3] = {
	{ 0.5, -0.4, -0.4},
	{ 0.5, -0.1, -0.4},
	{ 0.4, -0.1, -0.4}, 
	{ 0.4, -0.4, -0.4}, 
	{ 0.5, -0.4, -0.5},
	{ 0.5, -0.1, -0.5},
	{ 0.4, -0.1, -0.5}, 
	{ 0.4, -0.4, -0.5}
};

// ���� ����
GLfloat CandyStick[8][3] = {
	{ -0.41, 0.0, -0.39},
	{ -0.41, 0.52, -0.39},
	{ -0.39, 0.52, -0.39}, 
	{ -0.39, 0.0, -0.39}, 
	{ -0.41, 0.0, -0.41},
	{ -0.41, 0.52, -0.41},
	{ -0.39, 0.52, -0.41}, 
	{ -0.39, 0.0, -0.41}
};

// color ����Ʈ 
GLfloat MyColors[8][3] = {
	{0.1, 0.1, 0.1}, 
	{0.1, 0.1, 0.1},
	{0.1, 0.1, 0.1}, 
	{0.1, 0.1, 0.1}, 
	{0.1, 0.1, 0.1}, 
	{0.1, 0.1, 0.1}, 
	{0.1, 0.1, 0.1},  
	{0.1, 0.1, 0.1}
};
// ť�� ����(6��) ���� ���� ����Ʈ
GLubyte MyVertexList[24] = {
	0, 3, 2, 1,
	2, 3, 7, 6,
	0, 4, 7, 3,
	1, 2, 6, 5,
	4, 5, 6, 7,
	0, 1, 5, 4
};

GLuint pig;
void loadObj(char *fname) {
	FILE *fp;
	int read;
	GLfloat x, y, z;
	char ch;
	pig = glGenLists(1);
	fp = fopen(fname, "r");
	if (!fp)
		exit(1);
		
	glPointSize(2.0);
	glNewList(pig, GL_COMPILE);
	glPushMatrix();
	
	if (FlatShaded) {
		glBegin(GL_POLYGON);
	} else if (WireFramed) {
		glBegin(GL_LINE_STRIP);	
	}
	while(!(feof(fp))) {
		read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
		if (read==4 && ch=='v') {
			glVertex3f(x,y,z);
		}
	}
	glEnd();
	glPopMatrix();
	glEndList();
	fclose(fp);
}
void drawPig() {
	glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	glTranslatef(0.2, 0.0, -0.1);
	glScalef(0.2, 0.2, 0.2);
	glCallList(pig);
	glPopMatrix();
}

GLuint myList;
void MyDisplayList() {
	
	myList = glGenLists(LIST_SIZE);
	
	glNewList(myList, GL_COMPILE);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, MyColors);
		glVertexPointer(3, GL_FLOAT, 0, upperTableVertices);
		for (GLint i=0; i<6; i++) {
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
		}
	glEndList();
	
	glNewList(myList+1, GL_COMPILE);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, MyColors);
		glVertexPointer(3, GL_FLOAT, 0, LFLegVertices);
		for (GLint i=0; i<6; i++) {
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
		}
	glEndList();
	
	glNewList(myList+2, GL_COMPILE);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, MyColors);
		glVertexPointer(3, GL_FLOAT, 0, RFLegVertices);
		for (GLint i=0; i<6; i++) {
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
		}
	glEndList();
	
	glNewList(myList+3, GL_COMPILE);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, MyColors);
		glVertexPointer(3, GL_FLOAT, 0, LBLegVertices);
		for (GLint i=0; i<6; i++) {
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
		}
	glEndList();
	
	glNewList(myList+4, GL_COMPILE);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, MyColors);
		glVertexPointer(3, GL_FLOAT, 0, RBLegVertices);
		for (GLint i=0; i<6; i++) {
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
		}
	glEndList();
	
	glNewList(myList+5, GL_COMPILE);
		glTranslatef(-0.3, 0.06, 0.2);
		if (FlatShaded) {
			glutSolidTeapot(0.1);
		}
		if (WireFramed){
			glutWireTeapot(0.1);
		}
	glEndList();
	
	glNewList(myList+6, GL_COMPILE);
		glTranslatef(-0.1, 0.64, -0.6);
		if (FlatShaded) {
			glutSolidSphere(0.2, 20, 30);
		}
		if (WireFramed){
			glutWireSphere(0.2, 20, 30);
		}
		glTranslatef(0.4, -0.7, 0.4);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, MyColors);
		glVertexPointer(3, GL_FLOAT, 0, CandyStick);
		for (GLint i=0; i<6; i++) {
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
		}
	glEndList();
} 

// ���� ���� 
void InitLight() {
	GLfloat mat_diffuse[] = {0.5, 0.4, 0.3, 1.0};
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_ambient[] = {0.5, 0.4, 0.3, 1.0};
	GLfloat mat_shininess[] = {15.0};

	GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_diffuse[] = {0.8, 0.8, 0.8, 1.0};
	GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat light_position[] = {-3, 6, 3.0, 0.0};

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);

	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

// ȸ���� radian ���ϱ� �Լ� 
float getRadian(float num) {
	return num * (PI / 180);
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// 0,1,2 : �ٶ󺸴� ���� ��ġ
	// 3,4,5 : �ٶ� ��ġ
	// 6,7,8 : ī�޶� ���� ����
	gluLookAt(
		0.0, 0.0, 0.0,
		etX, etY, etZ,
		0.0, 1.0, 0.0
	);
	
	for (int i=0;i<LIST_SIZE;i++) {
		glCallList(myList+i);
	}
	drawPig();
	glutSwapBuffers();
}

// Ű���� �ݹ��Լ�
void MyKeyboard(unsigned char KeyPressed, int x, int y) {
	switch(KeyPressed) {
		case 'q':
		case 'Q':
		case '\033':
			exit(0);
			break;
		// �ָ��� ������ 
		case 's':
		case 'S':
			if (FlatShaded) {
				glShadeModel(GL_SMOOTH); // ���̴� �������� ���� �������� ä��
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			} else {
				FlatShaded = 1;
				WireFramed = 0;
				glShadeModel(GL_FLAT);	// ó������ ������ ���� ä������ ������ ����
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			glutPostRedisplay();
			break;
		// ���̾� ������ ��۸�
		case 'w':
		case 'W':
			if (WireFramed) {
				glShadeModel(GL_SMOOTH); // ���̴� �������� ���� �������� ä��
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			} else {
				WireFramed = 1;
				FlatShaded = 0;
				glShadeModel(GL_FLAT);	// ó������ ������ ���� ä������ ������ ����
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			glutPostRedisplay();
			break;
			
			// glPolygonModel : http://egloos.zum.com/nom3203/v/2628901
			
			glutPostRedisplay();
			break; 
	}
}

void MyMouseClick(GLint Button, GLint State, GLint x, GLint y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		ViewX = x;
		ViewY = y;
		clickedX = x;
		clickedY = y;
	}
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		glutPostRedisplay();
	}
}

void MyMouseMove(GLint x, GLint y) {
	ViewX = x;
	ViewY = y;
	
	float deltaX = (float)(ViewX - clickedX);
	float deltaXRotate = deltaX / 500.0;
	float RotateX = deltaXRotate * 360.0;
	float Rad = getRadian(RotateX);
	etX = (GLfloat) (sin(Rad));
	etZ = (GLfloat) (-1 * cos(Rad));
	
	float deltaY = (float)(clickedY - ViewY);
	float deltaYRotate = deltaY / 500.0;
	etY = deltaYRotate * 3;
	
	glutPostRedisplay();
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
} 

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("OpenGL Project I by 2016310285 ����");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	
	InitLight();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutReshapeFunc(MyReshape);
	MyDisplayList();
	loadObj("pig.obj");
	
  	glutMainLoop();
  	return 0;
}
