// 프로젝트 옵션 - Linker 
// -lopengl32
// -lfreeglut
// -lglu32
// -lwinmm
// -lgdi32 
// 추가 

#include <GL/glut.h>

GLfloat Delta = 0.0; // idle 콜백에서 계산한 값을 MyDisplay에서 사용하기 위해 

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);	// 기존의 초기화색(glClearColor())으로 화면 지움 
	glColor3f(0.0, 0.5, 0.8);
	glBegin(GL_POLYGON);
		glVertex3f(-1.0+Delta, -0.5, 0.0);
    	glVertex3f(0.0+Delta, -0.5, 0.0);
    	glVertex3f(0.0+Delta, 0.5, 0.0);
    	glVertex3f(-1.0+Delta, 0.5, 0.0);
	glEnd();
	glutSwapBuffers();	// 더블 더버드 사용 (reduce flickering)
}

void MyIdle() {
	Delta += 0.001;
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);	// 더블 버퍼드 사용하기 위해 명시
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Display moving square with Idle Callback");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	
	// 콜백 함수 등록 
	glutDisplayFunc(MyDisplay);
	glutIdleFunc(MyIdle);
	
  	glutMainLoop();
  	return 0;
}
