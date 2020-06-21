// ������Ʈ �ɼ� - Linker 
//-lopengl32
//-lfreeglut
//-lglu32
//-lwinmm
//-lgdi32 
// �߰� 

#include<windows.h>
#include<MMSystem.h>
#include <GL/glut.h>
#include <math.h>

static double time = 0;  // Run_time ����
static double time2 = 0; // Jap_time ����

GLfloat R_Arm_x = 0; // ������ ���
GLfloat R_Arm_y = 0; // ������ ��
GLfloat L_Arm_x = 0; // ���� ���
GLfloat L_Arm_y = 0; // ���� ��
GLfloat R_Leg_x = 0; // ���� �����
GLfloat R_Leg_y = 0; // ���� ���Ƹ�
GLfloat L_Leg_x = 0; // �� �����
GLfloat L_Leg_y = 0; // �� ���Ƹ�

GLUquadricObj* cyl;// �Ǹ��� ��ü ����
GLUquadricObj* hme;

int a = 0; // x�� ����(���� 1�� �� x���� �������� ȸ��)
int b = 0; // y�� ����(���� 1�� �� y���� �������� ȸ��)
int c = 0; // z�� ����(���� 1�� �� z���� �������� ȸ��)

static int frame = 0; // wireframe ���� solid rendering ��� ���� ����
static int key = 3;  // ���� ���
static int state = 1;

GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;
GLint clickedX, clickedY, ViewX, ViewY;//���콺 ��ǥ �̵� �� ���� ����
GLfloat rotateLR = 0.0, rotateUD = 0.0;

#define NORMAL 	3
#define HANDSUP	1
#define JUMP	2
#define UP		1
#define DOWN	0

void Change_Wire_Or_Solid(int i) {          // �ָ���, ���̾� ����
	if (frame == 1)
		gluQuadricDrawStyle(cyl, GLU_LINE); // ��Ÿ���� ���̾�� ����
}
/*
���� ������ �׸��� �Լ�
*/
void DrawL_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);       // �� ����
	cyl = gluNewQuadric();   // �Ǹ��� ��ü ����
	glRotatef(x, a, b, c);  // �Ķ���� ����ŭ ȸ��
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ����� x�� �������� 90�� ȸ��(�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(0.25, 0.0, 0.0);    // ���� ��� ���������� �̵�
	glRotatef(15.0, 0.0, 1.0, 0.0); // ���� ����� y���� �������� 15�� ȸ��
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // �Ǹ����� �׸�
}

/*
���� ���� ���� �׸��� �Լ�
*/
void DrawL_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);       // �� ����
	cyl = gluNewQuadric();   // �Ǹ��� ��ü ����
	glTranslatef(0.0, 0.0, 0.19); // �޼� ������
	glRotatef(y, a, b, c);        // �Ķ���� ����ŭ ȸ��
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.025, 0.2, 15, 1);           // �Ǹ����� �׸�
	glPopMatrix();
}
/*
���� �������� �׸��� �Լ�
*/
void DrawR_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);     // �� ����
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glRotatef(x, a, b, c);  // �Ķ���� ����ŭ ȸ��
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ����� x���� �������� 90�� ȸ��(�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(-0.25, 0.0, 0.0); //���� ��� ���������� �̵�
	glRotatef(-15.0, 0.0, 1.0, 0.0); //���� ��� -15�� y����� ȸ��
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// �Ǹ��� �׸�

}
/*
���� ������ ���� �׸��� �Լ�
*/
void DrawR_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58); // �� ����
	cyl = gluNewQuadric();//�Ǹ��� ��ü ����
	glTranslatef(0.0, 0.0, 0.19);//������ �� ������
	glRotatef(y, a, b, c);// �Ķ���Ͱ� ��ŭ ȸ��
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.025, 0.2, 50, 1);// �Ǹ��� �׸�
	glPopMatrix();
}
// ���� ���� 
void DrawBody(int x, int a, int b, int c) {
	glTranslatef(0.0, -0.3, 0.0);
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);
	cyl = gluNewQuadric();//�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glRotatef(x, a, b, c);//�Ķ���Ͱ� ��ŭ ȸ��
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.2, 0.2, 0.45, 50, 1);// �Ǹ��� �׸�
	glPopMatrix();
}
// ���� ���� 
void DrawPants() {
	glTranslatef(0.0, -0.45, 0.0);
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����
	cyl = gluNewQuadric();
	Change_Wire_Or_Solid(frame);
	glColor3f(0.82, 0.86, 0.11);
	glRotatef(-90.0, 1.0, 0.0, 0.0);//�Ķ���͸�ŭ ȸ��
	gluCylinder(cyl, 0.2, 0.2, 0.1, 50, 1);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glPopMatrix();// ó�� ���� ��ǥ �ٽ� ����
	
}
/*
�κ� ���� ������� �׸��� �Լ�
*/
void DrawL_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);
	cyl = gluNewQuadric();//�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(0.1, 0.0, 0.42);//���� ����� ������
	glRotatef(x, a, b, c);//�Ķ���͸�ŭ ȸ��
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);// �Ǹ��� �׸�

}
/*
�κ� ���� ���Ƹ��� �׸��� �Լ�
*/
void DrawL_foot(int y, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);
	cyl = gluNewQuadric();//�Ǹ��� ��ü ����
	glTranslatef(0.0, 0.0, 0.15);//���� ���Ƹ� ������
	glRotatef(y, a, b, c);//�Ķ���͸�ŭ ȸ��
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.025, 0.2, 50, 1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
�κ� ������ ������� �׸��� �Լ�
*/
void DrawR_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);
	cyl = gluNewQuadric();//�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(-0.1, 0.0, 0.42);//������ ����� ������
	glRotatef(x, a, b, c);//�Ķ���͸�ŭ ȸ��
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);// �Ǹ��� �׸�

}
/*
���� ������ ���Ƹ��� �׸��� �Լ�
*/
void DrawR_foot(int y, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);
	cyl = gluNewQuadric();//�Ǹ��� ��ü ����

	glTranslatef(0.0, 0.0, 0.15);//������ ���Ƹ� ������
	glRotatef(y, a, b, c);//�Ķ���͸�ŭ ȸ��

	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.025, 0.2, 15, 1);// �Ǹ��� �׸�
	glPopMatrix();
}
 
// �Ӹ��� �׸��� �Լ� 
void DrawHead() {
	glTranslatef(0.0, 0.001, 0.0);//�Ӹ� ������
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����
	cyl = gluNewQuadric();
	Change_Wire_Or_Solid(frame);
	glColor3f(0.97, 0.7, 0.58);
	glRotatef(-90.0, 1.0, 0.0, 0.0);//�Ķ���͸�ŭ ȸ��
	gluCylinder(cyl, 0.20, 0.05, 0.3, 15, 1);//�Ӹ� �׸���
	glRotatef(90.0, 1.0, 0.0, 0.0);					
				   /*���� �� �׸���*/
	glTranslatef(-0.1, 0.1, 0.13);//���� �� ������
	glColor3f(0.0, 0.0, 0.0);// �� �÷� ����(���)
	gluSphere(cyl, 0.03, 10, 10);

	glPopMatrix(); // ó�� ���� ��ǥ�� ���� ����.
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����

				   /*������ �� �׸���*/
	glTranslatef(0.1, 0.1, 0.13);//������ �� ������
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();// ó�� ���� ��ǥ �ٽ� ����
}

// ���� ��ü�� �׸��� �Լ� 
void DrawPatrick() {
	DrawBody(0, 0, 0, 0); // ���� �Լ� ȣ��
	DrawHead(); // �Ӹ� ȣ��
	DrawR_Arm(R_Arm_x, 1, 0, 0);//�����ȶ�
	DrawR_Hand(R_Arm_y, 1, 0, 0);  //������ȣ��
	DrawL_Arm(L_Arm_x, 1, 0, 0);   //�����ȶ�
	DrawL_Hand(L_Arm_y, 1, 0, 0);//������ȣ��
	DrawL_Legs(L_Leg_x, 1, 0, 0);  //�����ٸ�
	DrawL_foot(L_Leg_y, 1, 0, 0);  //������		 
	DrawR_Legs(R_Leg_x, 1, 0, 0);  //�����ٸ�
	DrawR_foot(R_Leg_y, 1, 0, 0);  //������	
	DrawPants();
}

void DrawHouse() {
	glTranslatef(0.0, -0.58, -0.5);
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����
	hme = gluNewQuadric();
	Change_Wire_Or_Solid(frame);
	glColor3f(0.28, 0.1, 0.07);
	glRotatef(-90.0, 1.0, 0.0, 0.0);//�Ķ���͸�ŭ ȸ��
	gluCylinder(hme, 0.80, 0.5, 1.5, 30, 1);//�Ӹ� �׸���
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glPopMatrix();// ó�� ���� ��ǥ �ٽ� ����
}

void Normal() {
	glLoadIdentity();//CTM �ʱ�ȭ
	 
	L_Arm_x = 0;
	R_Arm_x = 0;
	R_Arm_y = 0;
	L_Arm_y = 0;
	
	R_Leg_y = 0;
	L_Leg_y = 0;
	R_Leg_x = 0;
	L_Leg_x = 0;
									 ////////////////display////////////////

	cyl = gluNewQuadric(); //�Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); //��� ����
	DrawHouse();    //���� ȣ��
	glLoadIdentity();//CTM �ʱ�ȭ
					 /*
					 �κ��� �޸��鼭 ��,�ڷ� �ڶװŸ��� ���� Ʋ������ ���� ǥ��
					 */
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef(abs(long(sin(time)) * 16), 1, 0, 0);//x������ 16�� ���� ����Ʋ����(abs���밪�� �����ν� ��ü�� �ڷ� ������ �ʴ� �Ѱ����� ����)
	glRotatef(sin(time) * 16, 0, 1, 0); //y������ 16�� ���� ����Ʋ����, sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

	float j = 0;
	j = abs(long(sin(time)*0.08));
	glPushMatrix();
	glTranslatef(0.0, j, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawPatrick();
	
	glutSwapBuffers();
}

void HandsUp() {
	glLoadIdentity();//CTM �ʱ�ȭ
	 
	L_Arm_x = (180) + sin(time2) * 10;
	R_Arm_x = (-0) - L_Arm_x;
	R_Arm_y = -abs(long(cos(time2)) * 80);
	L_Arm_y = -abs(long(-cos(time2)) * 80);
	
	R_Leg_y = 0;
	L_Leg_y = 0;
	R_Leg_x = 0;
	L_Leg_x = 0;
									 ////////////////display////////////////

	cyl = gluNewQuadric(); //�Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); //��� ����
	DrawHouse();    //���� ȣ��
	glLoadIdentity();//CTM �ʱ�ȭ

					 /*
					 �κ��� �޸��鼭 ��,�ڷ� �ڶװŸ��� ���� Ʋ������ ���� ǥ��
					 */
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef(abs(long(sin(time)) * 16), 1, 0, 0);//x������ 16�� ���� ����Ʋ����(abs���밪�� �����ν� ��ü�� �ڷ� ������ �ʴ� �Ѱ����� ����)
	glRotatef(sin(time) * 16, 0, 1, 0); //y������ 16�� ���� ����Ʋ����, sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

	float i = 0;
	i = abs(long(sin(time)*0.08));
	glPushMatrix();
	glTranslatef(0.0, i, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawPatrick();
	
	glutSwapBuffers();
	  
}

void Jump() {
	glLoadIdentity();//CTM �ʱ�ȭ
	 
	L_Arm_x = (180) + sin(time2) * 10;
	R_Arm_x = (-0) - L_Arm_x;
	R_Arm_y = -abs(long(cos(time2)) * 80);
	L_Arm_y = -abs(long(-cos(time2)) * 80);
	
	R_Leg_y = 0;
	L_Leg_y = 0;
	R_Leg_x = 0;
	L_Leg_x = 0;
									 ////////////////display////////////////

	cyl = gluNewQuadric(); //�Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); //��� ����
	DrawHouse();    //���� ȣ��
	glLoadIdentity();//CTM �ʱ�ȭ
					 
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef(sin(time) * 10, 0, 0, 1);
	glRotatef(abs(long(sin(time)) * 16), 1, 0, 0);//x������ 16�� ���� ����Ʋ����(abs���밪�� �����ν� ��ü�� �ڷ� ������ �ʴ� �Ѱ����� ����)
	glRotatef(sin(time) * 16, 0, 1, 0); //y������ 16�� ���� ����Ʋ����, sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

	float i = 0;
	i = abs(long(sin(time)*0.08));
	glPushMatrix();
	glTranslatef(0.0, i, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawPatrick();
	
	glutSwapBuffers();
}

void DownHouse() {
	glLoadIdentity();//CTM �ʱ�ȭ
	
	hme = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); //��� ����
	
	DrawHouse();
	
	glutSwapBuffers();
}

void MyDisplay() {
	if (state == UP) {
		if (key == NORMAL) {
			Normal();
			glPopMatrix();
		} else if (key == HANDSUP) {
			HandsUp();
			glPopMatrix();
		} else {
			Jump();
			glPopMatrix();
		}
	} else {
		DownHouse();
	}
	
	
}
/*
Ÿ�̸� �Լ�
�� ��鸶�� ���� ǥ���� �ٸ��� �α� ���� ����� �ð� �������� ������.
*/
void MyTimer(int Value) {
	time = time + 0.1;//�޸��� ���� Ÿ�̸� ����
	time2 = time2 + 0.5;//���� ������ ���� Ÿ�̸� ����
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1);
}

// �޴� �ݹ� 
void MyMainMenu(int entryID) {
	if (entryID==1) {
		exit(0);
	}
	glutPostRedisplay();
}

void PatrickMenu(int entryID) {
	key = entryID;
	glutPostRedisplay();
}

void HouseMenu(int entryID) {
	state = entryID;
	glutPostRedisplay();
}

// Ű���� �ݹ� 
void MyKeyboard(unsigned char KeyPressed, int x, int y) {
	switch (KeyPressed) {
		case 'w':
		case 'W':
			frame = 1;
			break;
		case 's':
		case 'S':
			frame = 0;
			break;
		case 'q':
		case 'Q': 
			exit(0);
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
	glutInit(&argc, argv);//�ʱ�ȭ
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);//���÷��� ��� ����
	glutInitWindowSize(600, 600);//������ ũ�� ����
	glutInitWindowPosition(0, 0);//������ �ʱ� ��ġ ����
	glutCreateWindow("Graphics Final Project by 2016310285 ����");//������ ����
	glClearColor(0.0, 0.5, 1.0, 0.5);//�ʱ� ���� ����
	
	GLint PatrickMenuID = glutCreateMenu(PatrickMenu);
	glutAddMenuEntry("HANDS UP", 1);
	glutAddMenuEntry("JUMP", 2);
	glutAddMenuEntry("NORMAL", 3);
	GLint HouseMenuID = glutCreateMenu(HouseMenu);
	glutAddMenuEntry("UP", 1);
	glutAddMenuEntry("DOWN", 2);
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);//�޴��߰�
	glutAddSubMenu("Patrick star", PatrickMenuID);
	glutAddSubMenu("Patrick's house'", HouseMenuID);
	glutAddMenuEntry("Exit", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);//�����ʸ��콺Ŭ���ø޴��˾�
	
	glutDisplayFunc(MyDisplay); //���÷���
	glutMouseFunc(MyMouseClick);//���콺�ݹ� 
	glutMotionFunc(MyMouseMove);//���콺�ݹ� 
	glutKeyboardFunc(MyKeyboard); //Ű���� �ݹ�
	glutTimerFunc(40, MyTimer, 1); //Ÿ�̸� �Լ�
	
	glutMainLoop();
	return 0;
}
