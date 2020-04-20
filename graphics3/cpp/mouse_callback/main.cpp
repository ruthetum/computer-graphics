// 프로젝트 옵션 - Linker 
//-lopengl32
//-lfreeglut
//-lglu32
//-lwinmm
//-lgdi32 
// 추가 

// 마우스 드래그할 때 사각형이 그려지는 색과 마우스 버튼을 놓았을 때(Release) 그려지는 사각형의 색이 다르도록 수정

#include <GL/glut.h>


// 전역변수 선언 (콜백함수 간 값 전달 위해서)
GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY; 

// 사각형 그리기 
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

void MyMouseClick(GLint Button, GLint State, GLint x, GLint y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		TopLeftX = x;
		TopLeftY = y;
	}
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_UP) {
		glColor3f(1.0, 0.0, 0.0);
		glutPostRedisplay();
	}
}

void MyMouseMove(GLint x, GLint y) {
	BottomRightX = x;
	BottomRightY = y;
	glColor3f(0.5, 0.5, 0.5);
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Display square with Mouse Callback");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0 ,1.0, 0.0, 1.0, -1.0, 1.0);
	
	// 콜백 함수 등록 
	glutDisplayFunc(MyDisplay);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	
  	glutMainLoop();
  	return 0;
}
