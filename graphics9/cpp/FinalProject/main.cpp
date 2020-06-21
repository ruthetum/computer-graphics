// 프로젝트 옵션 - Linker 
//-lopengl32
//-lfreeglut
//-lglu32
//-lwinmm
//-lgdi32 
// 추가 

#include<windows.h>
#include<MMSystem.h>
#include <GL/glut.h>
#include <math.h>

static double time = 0;  // Run_time 변수
static double time2 = 0; // Jap_time 변수

GLfloat R_Arm_x = 0; // 오른쪽 어깨
GLfloat R_Arm_y = 0; // 오른쪽 팔
GLfloat L_Arm_x = 0; // 왼쪽 어깨
GLfloat L_Arm_y = 0; // 왼쪽 팔
GLfloat R_Leg_x = 0; // 오른 허벅지
GLfloat R_Leg_y = 0; // 오른 종아리
GLfloat L_Leg_x = 0; // 왼 허벅지
GLfloat L_Leg_y = 0; // 왼 종아리

GLUquadricObj* cyl;// 실린더 객체 선언
GLUquadricObj* hme;

int a = 0; // x축 기준(값이 1일 때 x축을 기준으로 회전)
int b = 0; // y축 기준(값이 1일 때 y축을 기준으로 회전)
int c = 0; // z축 기준(값이 1일 때 z축을 기준으로 회전)

static int frame = 0; // wireframe 모드와 solid rendering 모드 구분 변수
static int key = 3;  // 동작 모드
static int state = 1;

GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;
GLint clickedX, clickedY, ViewX, ViewY;//마우스 좌표 이동 값 저장 변수
GLfloat rotateLR = 0.0, rotateUD = 0.0;

#define NORMAL 	3
#define HANDSUP	1
#define JUMP	2
#define UP		1
#define DOWN	0

void Change_Wire_Or_Solid(int i) {          // 솔리드, 와이어 선택
	if (frame == 1)
		gluQuadricDrawStyle(cyl, GLU_LINE); // 스타일을 와이어로 변경
}
/*
뚱이 왼팔을 그리는 함수
*/
void DrawL_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);       // 색 설정
	cyl = gluNewQuadric();   // 실린더 객체 생성
	glRotatef(x, a, b, c);  // 파라미터 값만큼 회전
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축 기준으로 90도 회전(실린더 생성 시 각도 변경을 위해)
	glTranslatef(0.25, 0.0, 0.0);    // 왼쪽 어깨 시작점으로 이동
	glRotatef(15.0, 0.0, 1.0, 0.0); // 왼쪽 어깨를 y축을 기준으로 15도 회전
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
}

/*
뚱이 왼쪽 손을 그리는 함수
*/
void DrawL_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);       // 색 설정
	cyl = gluNewQuadric();   // 실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.19); // 왼손 시작점
	glRotatef(y, a, b, c);        // 파라미터 값만큼 회전
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.025, 0.2, 15, 1);           // 실린더를 그림
	glPopMatrix();
}
/*
뚱이 오른팔을 그리는 함수
*/
void DrawR_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);     // 색 설정
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glRotatef(x, a, b, c);  // 파라미터 값만큼 회전
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축을 기준으로 90도 회전(실린더 생성 시 각도 변경을 위해)
	glTranslatef(-0.25, 0.0, 0.0); //우측 어깨 시작점으로 이동
	glRotatef(-15.0, 0.0, 1.0, 0.0); //우측 어깨 -15도 y축기준 회전
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// 실린더 그림

}
/*
뚱이 오른쪽 손을 그리는 함수
*/
void DrawR_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58); // 색 설정
	cyl = gluNewQuadric();//실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.19);//오른쪽 손 시작점
	glRotatef(y, a, b, c);// 파라미터값 만큼 회전
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.025, 0.2, 50, 1);// 실린더 그림
	glPopMatrix();
}
// 뚱이 몸통 
void DrawBody(int x, int a, int b, int c) {
	glTranslatef(0.0, -0.3, 0.0);
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);
	cyl = gluNewQuadric();//실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glRotatef(x, a, b, c);//파라미터값 만큼 회전
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.2, 0.2, 0.45, 50, 1);// 실린더 그림
	glPopMatrix();
}
// 뚱이 바지 
void DrawPants() {
	glTranslatef(0.0, -0.45, 0.0);
	glPushMatrix();// 처음 저장 좌표 다시 저장
	cyl = gluNewQuadric();
	Change_Wire_Or_Solid(frame);
	glColor3f(0.82, 0.86, 0.11);
	glRotatef(-90.0, 1.0, 0.0, 0.0);//파라미터만큼 회전
	gluCylinder(cyl, 0.2, 0.2, 0.1, 50, 1);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glPopMatrix();// 처음 저장 좌표 다시 저장
	
}
/*
로봇 왼쪽 허벅지를 그리는 함수
*/
void DrawL_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);
	cyl = gluNewQuadric();//실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(0.1, 0.0, 0.42);//왼쪽 허벅지 시작점
	glRotatef(x, a, b, c);//파라미터만큼 회전
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);// 실린더 그림

}
/*
로봇 왼쪽 종아리를 그리는 함수
*/
void DrawL_foot(int y, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);
	cyl = gluNewQuadric();//실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.15);//왼쪽 종아리 시작점
	glRotatef(y, a, b, c);//파라미터만큼 회전
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.025, 0.2, 50, 1);// 실린더 그림
	glPopMatrix();
}
/*
로봇 오른쪽 허벅지를 그리는 함수
*/
void DrawR_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);
	cyl = gluNewQuadric();//실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(-0.1, 0.0, 0.42);//오른쪽 허벅지 시작점
	glRotatef(x, a, b, c);//파라미터만큼 회전
	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);// 실린더 그림

}
/*
뚱이 오른쪽 종아리를 그리는 함수
*/
void DrawR_foot(int y, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0.97, 0.7, 0.58);
	cyl = gluNewQuadric();//실린더 객체 생성

	glTranslatef(0.0, 0.0, 0.15);//오른쪽 종아리 시작점
	glRotatef(y, a, b, c);//파라미터만큼 회전

	Change_Wire_Or_Solid(frame);
	gluCylinder(cyl, 0.05, 0.025, 0.2, 15, 1);// 실린더 그림
	glPopMatrix();
}
 
// 머리를 그리는 함수 
void DrawHead() {
	glTranslatef(0.0, 0.001, 0.0);//머리 시작점
	glPushMatrix();// 처음 저장 좌표 다시 저장
	cyl = gluNewQuadric();
	Change_Wire_Or_Solid(frame);
	glColor3f(0.97, 0.7, 0.58);
	glRotatef(-90.0, 1.0, 0.0, 0.0);//파라미터만큼 회전
	gluCylinder(cyl, 0.20, 0.05, 0.3, 15, 1);//머리 그리기
	glRotatef(90.0, 1.0, 0.0, 0.0);					
				   /*왼쪽 눈 그리기*/
	glTranslatef(-0.1, 0.1, 0.13);//왼쪽 눈 시작점
	glColor3f(0.0, 0.0, 0.0);// 눈 컬러 설정(흑색)
	gluSphere(cyl, 0.03, 10, 10);

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

				   /*오른쪽 눈 그리기*/
	glTranslatef(0.1, 0.1, 0.13);//오른쪽 눈 시작점
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();// 처음 저장 좌표 다시 저장
}

// 뚱이 전체를 그리는 함수 
void DrawPatrick() {
	DrawBody(0, 0, 0, 0); // 몸통 함수 호출
	DrawHead(); // 머리 호출
	DrawR_Arm(R_Arm_x, 1, 0, 0);//우측팔뚝
	DrawR_Hand(R_Arm_y, 1, 0, 0);  //우측팔호출
	DrawL_Arm(L_Arm_x, 1, 0, 0);   //좌측팔뚝
	DrawL_Hand(L_Arm_y, 1, 0, 0);//좌측손호출
	DrawL_Legs(L_Leg_x, 1, 0, 0);  //좌측다리
	DrawL_foot(L_Leg_y, 1, 0, 0);  //좌측발		 
	DrawR_Legs(R_Leg_x, 1, 0, 0);  //우측다리
	DrawR_foot(R_Leg_y, 1, 0, 0);  //우측발	
	DrawPants();
}

void DrawHouse() {
	glTranslatef(0.0, -0.58, -0.5);
	glPushMatrix();// 처음 저장 좌표 다시 저장
	hme = gluNewQuadric();
	Change_Wire_Or_Solid(frame);
	glColor3f(0.28, 0.1, 0.07);
	glRotatef(-90.0, 1.0, 0.0, 0.0);//파라미터만큼 회전
	gluCylinder(hme, 0.80, 0.5, 1.5, 30, 1);//머리 그리기
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glPopMatrix();// 처음 저장 좌표 다시 저장
}

void Normal() {
	glLoadIdentity();//CTM 초기화
	 
	L_Arm_x = 0;
	R_Arm_x = 0;
	R_Arm_y = 0;
	L_Arm_y = 0;
	
	R_Leg_y = 0;
	L_Leg_y = 0;
	R_Leg_x = 0;
	L_Leg_x = 0;
									 ////////////////display////////////////

	cyl = gluNewQuadric(); //실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW); //모드 설정
	DrawHouse();    //지면 호출
	glLoadIdentity();//CTM 초기화
					 /*
					 로봇이 달리면서 앞,뒤로 뒤뚱거리고 몸이 틀어지는 것을 표현
					 */
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef(abs(long(sin(time)) * 16), 1, 0, 0);//x축으로 16도 까지 각도틀어짐(abs절대값을 줌으로써 몸체가 뒤로 꺾이지 않는 한계점을 설정)
	glRotatef(sin(time) * 16, 0, 1, 0); //y축으로 16도 까지 각도틀어짐, sin()함수를 사용하여 주기적인 움직임 설정

	float j = 0;
	j = abs(long(sin(time)*0.08));
	glPushMatrix();
	glTranslatef(0.0, j, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawPatrick();
	
	glutSwapBuffers();
}

void HandsUp() {
	glLoadIdentity();//CTM 초기화
	 
	L_Arm_x = (180) + sin(time2) * 10;
	R_Arm_x = (-0) - L_Arm_x;
	R_Arm_y = -abs(long(cos(time2)) * 80);
	L_Arm_y = -abs(long(-cos(time2)) * 80);
	
	R_Leg_y = 0;
	L_Leg_y = 0;
	R_Leg_x = 0;
	L_Leg_x = 0;
									 ////////////////display////////////////

	cyl = gluNewQuadric(); //실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW); //모드 설정
	DrawHouse();    //지면 호출
	glLoadIdentity();//CTM 초기화

					 /*
					 로봇이 달리면서 앞,뒤로 뒤뚱거리고 몸이 틀어지는 것을 표현
					 */
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef(abs(long(sin(time)) * 16), 1, 0, 0);//x축으로 16도 까지 각도틀어짐(abs절대값을 줌으로써 몸체가 뒤로 꺾이지 않는 한계점을 설정)
	glRotatef(sin(time) * 16, 0, 1, 0); //y축으로 16도 까지 각도틀어짐, sin()함수를 사용하여 주기적인 움직임 설정

	float i = 0;
	i = abs(long(sin(time)*0.08));
	glPushMatrix();
	glTranslatef(0.0, i, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawPatrick();
	
	glutSwapBuffers();
	  
}

void Jump() {
	glLoadIdentity();//CTM 초기화
	 
	L_Arm_x = (180) + sin(time2) * 10;
	R_Arm_x = (-0) - L_Arm_x;
	R_Arm_y = -abs(long(cos(time2)) * 80);
	L_Arm_y = -abs(long(-cos(time2)) * 80);
	
	R_Leg_y = 0;
	L_Leg_y = 0;
	R_Leg_x = 0;
	L_Leg_x = 0;
									 ////////////////display////////////////

	cyl = gluNewQuadric(); //실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW); //모드 설정
	DrawHouse();    //지면 호출
	glLoadIdentity();//CTM 초기화
					 
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef(sin(time) * 10, 0, 0, 1);
	glRotatef(abs(long(sin(time)) * 16), 1, 0, 0);//x축으로 16도 까지 각도틀어짐(abs절대값을 줌으로써 몸체가 뒤로 꺾이지 않는 한계점을 설정)
	glRotatef(sin(time) * 16, 0, 1, 0); //y축으로 16도 까지 각도틀어짐, sin()함수를 사용하여 주기적인 움직임 설정

	float i = 0;
	i = abs(long(sin(time)*0.08));
	glPushMatrix();
	glTranslatef(0.0, i, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawPatrick();
	
	glutSwapBuffers();
}

void DownHouse() {
	glLoadIdentity();//CTM 초기화
	
	hme = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW); //모드 설정
	
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
타이머 함수
각 장면마다 상태 표현을 다르게 두기 위해 대양한 시간 변수들이 쓰였다.
*/
void MyTimer(int Value) {
	time = time + 0.1;//달릴때 쓰인 타이머 변수
	time2 = time2 + 0.5;//잽을 날릴때 쓰인 타이머 변수
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1);
}

// 메뉴 콜백 
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

// 키보드 콜백 
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

// 마우스 콜백
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
	glutInit(&argc, argv);//초기화
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);//디스플레이 모드 설정
	glutInitWindowSize(600, 600);//윈도우 크기 설정
	glutInitWindowPosition(0, 0);//윈도우 초기 위치 설정
	glutCreateWindow("Graphics Final Project by 2016310285 김희동");//윈도우 생성
	glClearColor(0.0, 0.5, 1.0, 0.5);//초기 배경색 설정
	
	GLint PatrickMenuID = glutCreateMenu(PatrickMenu);
	glutAddMenuEntry("HANDS UP", 1);
	glutAddMenuEntry("JUMP", 2);
	glutAddMenuEntry("NORMAL", 3);
	GLint HouseMenuID = glutCreateMenu(HouseMenu);
	glutAddMenuEntry("UP", 1);
	glutAddMenuEntry("DOWN", 2);
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);//메뉴추가
	glutAddSubMenu("Patrick star", PatrickMenuID);
	glutAddSubMenu("Patrick's house'", HouseMenuID);
	glutAddMenuEntry("Exit", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);//오른쪽마우스클릭시메뉴팝업
	
	glutDisplayFunc(MyDisplay); //디스플레이
	glutMouseFunc(MyMouseClick);//마우스콜백 
	glutMotionFunc(MyMouseMove);//마우스콜백 
	glutKeyboardFunc(MyKeyboard); //키보드 콜백
	glutTimerFunc(40, MyTimer, 1); //타이머 함수
	
	glutMainLoop();
	return 0;
}
