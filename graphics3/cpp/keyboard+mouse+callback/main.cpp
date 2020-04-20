// 프로젝트 옵션 - Linker 
//-lopengl32
//-lfreeglut
//-lglu32
//-lwinmm
//-lgdi32 
// 추가 

#include <GL/glut.h>

// R, r 누르고 그리면 빨간색 사각형
// G, g 누르고 그리면 초록색 사각형 
// B, b 누르고 그리면 파란색 사각형

// 전역변수 선언 (콜백함수 간 값 전달 위해서)
GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;

void MyDisplay() {
	glViewport(0, 0, 500, 500);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glVertex3f(TopLeftX / 500.0, (500-TopLeftY) / 500.0, 0.0);
    	glVertex3f(TopLeftX / 500.0, (500-BottomRightY) / 500.0, 0.0);
    	glVertex3f(BottomRightX / 500.0, (500-BottomRightY) / 500.0, 0.0);
    	glVertex3f(BottomRightX / 500.0, (500-TopLeftY) / 500.0, 0.0);
	glEnd();
	glFlush();
}

// 키보드 콜백함수
// R or r : glColor3f()로 빨간색(1, 0, 0) 설정
// G or g : glColor3f()로 초록색(0, 1, 0) 설정
// B or b : glColor3f()로 파란색(0, 0, 1) 설정
void MyKeyboard(unsigned char KeyPressed, int x, int y) {
	switch(KeyPressed) {
		case 'R':
			glColor3f(1.0, 0.0, 0.0);
			break;
		case 'r':
			glColor3f(1.0, 0.0, 0.0);
			break;
		case 'G':
			glColor3f(0.0, 1.0, 0.0);
			break;
		case 'g':
			glColor3f(0.0, 1.0, 0.0);
			break;
		case 'B':
			glColor3f(0.0, 0.0, 1.0);
			break;
		case 'b':
			glColor3f(0.0, 0.0, 1.0);
			break;
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
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Display square with Keyboard and Mouse Callback");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0 ,1.0, 0.0, 1.0, -1.0, 1.0);
	
	// 콜백 함수 등록 
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	
  	glutMainLoop();
  	return 0;
}
