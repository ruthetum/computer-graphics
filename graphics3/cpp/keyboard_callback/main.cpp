// 프로젝트 옵션 - Linker 
// -lopengl32
// -lfreeglut
// -lglu32
// -lwinmm
// -lgdi32 
// 추가 

// 키보드 R(또는 r), G(또는 g), B(또는 b)를 눌렀을 때, 각각 사각형의 색이 Red, Green, Blue로 나타나도록 수정

#include <GL/glut.h>

// 사각형 그리기 
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glVertex3f(-0.5, -0.5, 0.0);
    	glVertex3f(0.5, -0.5, 0.0);
    	glVertex3f(0.5, 0.5, 0.0);
    	glVertex3f(-0.5, 0.5, 0.0);
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

// 윈도우 크기 변경 시 왜곡 방지 
void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat) NewWidth / (GLfloat) 500;
	GLfloat HeightFactor = (GLfloat) NewHeight / (GLfloat) 500;
	
	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	
	glOrtho(-1.0*WidthFactor, 1.0*WidthFactor, -1.0*HeightFactor, 1.0*HeightFactor, -1.0, 1.0);
}

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Display square with Keyboard Callback");
	glClearColor(1.0, 1.0, 1.0, 1.0); // 배경 흰색 
	
	// 콜백 함수 등록 
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	
  	glutMainLoop();
  	return 0;
}
