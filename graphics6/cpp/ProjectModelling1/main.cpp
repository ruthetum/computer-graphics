// ������Ʈ �ɼ� - Linker 
//-lopengl32
//-lfreeglut
//-lglu32
//-lwinmm
//-lgdi32 
// �߰� 

#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265358972

float getRadian(float num) {
	return num * (PI / 180);
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

// ���콺 �����ӿ� ���� ���� ����� �������� 
GLint clickedX, clickedY;
GLint ViewX = 0, ViewY = 0;

// flatshade�� wireframe ��۸��� ���� ��������
int FlatShaded = 0, WireFramed = 0; 

// ���콺 Ŭ�� Ȯ�ο�
int mouseClicked = 0; 

GLfloat etX = 0.0, etY = 0.0, etZ = -1.0;

float Rotate = 0.0, Rad, deltaX, deltaRotate;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// 0,1,2 : �ٶ󺸴� ���� ��ġ
	// 3,4,5 : �ٶ� ��ġ
	// 6,7,8 : ī�޶� ���� ����
	gluLookAt(
		0.0, 0.0, 0.0,
		etX, 1.0, etZ,
		0.0, 1.0, 0.0
	);
	// ���콺�� ������ ���� ������ ��ȭ��Ű����
	// Mymousemove ���� �ԷµǴ� ��ȭ���� �����Ͽ�
	// gluLookat �Ķ���͸� ���� : https://huiyu.tistory.com/entry/gluLookAt%ED%95%A8%EC%88%98
	
	// Ź�� �׸��� + Ź�� ���� ������ ������Ʈ 3�� �̻� Ź�ڿ� �׸���
	// �ϳ��� �����ϴ� ��, �ι�°�� ���۸��ؼ� ������� ��, ����°�� ���� ���� �����
	// �̹� �𵨸� ��ǥ �����͸� import �Ͽ� ��� ���� 
	
	
	glutSolidTeapot(0.2);
	
	glFlush();
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
				FlatShaded = 0;
				glShadeModel(GL_SMOOTH); // ���̴� �������� ���� �������� ä�� 
			} else {
				FlatShaded = 1;
				glShadeModel(GL_FLAT);	// ó������ ������ ���� ä������ ������ ����
			}
			glutPostRedisplay();
			break;
		// ���̾� ������ ��۸�
		case 'w':
		case 'W':
			if (WireFramed) {
				WireFramed = 0;
				glShadeModel(GL_SMOOTH); // ���̴� �������� ���� �������� ä�� 
			} else {
				WireFramed = 1;
				glShadeModel(GL_FLAT);	// ó������ ������ ���� ä������ ������ ����
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
	deltaX = (float)(ViewX - clickedX);
	deltaRotate = deltaX / 500.0;
	Rotate = deltaRotate * 180.0;
	Rad = getRadian(Rotate);
	etX = (GLfloat) (sin(Rad));
	etZ = (GLfloat) (-1 * cos(Rad));
	
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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
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
	
  	glutMainLoop();
  	return 0;
}
