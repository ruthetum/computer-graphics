// 프로젝트 옵션 - Linker 
// -lopengl32
// -lfreeglut
// -lglu32
// -lwinmm
// -lgdi32 
// 추가 

#include <GL/glut.h>

// Mode=0 : init(초기화면으로 정지)
// Mode=1 : start(델타 값 증가)
// Mode=2 : stop (델타 값 증가 멈춤)  
GLint Mode = 0;
GLfloat Delta = 0.0;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.5, 0.8);
	if (Mode==0) {
		// init, 초기 화면에서 정지 
		glBegin(GL_POLYGON);
			glVertex3f(-1.0, -0.5, 0.0);
    		glVertex3f(0.0, -0.5, 0.0);
    		glVertex3f(0.0, 0.5, 0.0);
    		glVertex3f(-1.0, 0.5, 0.0);
	} else {
		// start, Delta값만큼 이동 
		glBegin(GL_POLYGON);
			glVertex3f(-1.0+Delta, -0.5, 0.0);
    		glVertex3f(0.0+Delta, -0.5, 0.0);
    		glVertex3f(0.0+Delta, 0.5, 0.0);
    		glVertex3f(-1.0+Delta, 0.5, 0.0);
	}
	glEnd();
	glutSwapBuffers();
}

// MainMenu에서 고른 ID값에 따른 Mode 설정 
void MyMainMenu(int entryID) {
	if (entryID==1) {
		Mode = 0;
	} else if (entryID==2){
		Mode = 1;
	} else if (entryID==3){
		Mode = 2;
	} else if (entryID==4) {
		exit(0);
	}
	glutPostRedisplay();
}

// Mode=0 : Delta 값 0으로 초기화
// Mode=1 : Delta 값 증가
// Mode=1을 제외하고는 Delta값이 증가하지 않으므로 Mode=2(Stop)의 경우 Delta값이 증가하지 않음. 
void MyIdle() {
	if (Mode == 0) {
		Delta = 0.0;
	} else if (Mode == 1) {
		Delta += 0.001;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("Display moving square with Idle and Menu Callback");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Init", 1);
	glutAddMenuEntry("Start", 2);
	glutAddMenuEntry("Stop", 3);
	glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(MyDisplay);
	glutIdleFunc(MyIdle);
	
  	glutMainLoop();
  	return 0;
}
