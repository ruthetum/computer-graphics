// ������Ʈ �ɼ� - Linker 
//-lopengl32
//-lfreeglut
//-lglu32
//-lwinmm
//-lgdi32 
// �߰� 

#include <GL/glut.h>

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
int ViewX = 0, ViewY = 0;

// flatshade�� wireframe ��۸��� ���� ��������
int FlatShaded = 0, WireFramed = 0; 

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// 0,1,2 : �ٶ󺸴� ���� ��ġ
	// 3,4,5 : �ٶ� ��ġ
	// 6,7,8 : ī�޶� ���� ���� 
	gluLookAt(
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.1,
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

void MyMouseMove(GLint x, GLint y) {
	
	// ���콺 ������ X, Y�� ���������� ViewX, ViewY�� �Ҵ��Ͽ� 
	// ���콺 ���� ��ư�� ������ ��
	// gluLookAt�� �Ķ���� ���� ������ �� �ְ� 
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
	glutMotionFunc(MyMouseMove);
	glutReshapeFunc(MyReshape);
	
  	glutMainLoop();
  	return 0;
}
