// 프로젝트 옵션 - Linker 
// -lopengl32
// -lfreeglut
// -lglu32
// -lwinmm
// -lgdi32 
// 추가 

#include <GL/glut.h>

GLboolean IsSphere = true;	// 어떤 모양을 그릴지 선택하기 위한 전역변수
GLboolean IsSmall = true;	// choice big or small

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);	// 기존의 초기화색(glClearColor())으로 화면 지움 
	glColor3f(0.5, 0.0, 0.5);
	
	// 모양, 크기 조건에 따라 그리기
	if ((IsSphere) && (IsSmall)) {
		glutWireSphere(0.2, 15, 15);
	} else if ((IsSphere) && (!IsSmall)) {
		glutWireSphere(0.4, 15, 15);
	} else if ((!IsSphere) && (IsSmall)) {
		glutWireTorus(0.1, 0.3, 40, 20);
	} else {
		glutWireTorus(0.2, 0.3, 40, 20);
	}
	glFlush();
}

// 메뉴에서 클릭한 값 받아서 IsSphere 값 변경 
void MyMainMenu(int entryID) {
	if (entryID==1) {
		IsSphere = true;
	} else if (entryID==2){
		IsSphere = false;
	} else if (entryID==3){
		exit(0);
	}
	glutPostRedisplay();
}

// submenu - choice big or small
void MySubMenu (int entryID) {
	if (entryID==1) {
		IsSmall = true;
	} else if (entryID==2){
		IsSmall = false;
	}
	glutPostRedisplay();
}
 
int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB);	// 더블 버퍼드 사용하기 위해 명시
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("OpenGL with Menu Callback");
  	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	
	// 콜백 함수 등록 
	GLint MySubMenuID = glutCreateMenu(MySubMenu);	// 서브 메뉴 콜백
	// 서브 메뉴 항목 추가 
	glutAddMenuEntry("Small One", 1);
	glutAddMenuEntry("Big One", 2);
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);	// 메인 메뉴 콜백 
	// 메뉴 항목 추가 
	glutAddMenuEntry("Draw Sphere", 1);
	glutAddMenuEntry("Draw Torus", 2);
	glutAddSubMenu("Change Size", MySubMenuID);	// 서브 메뉴 - MySubMenu() 
	glutAddMenuEntry("Exit", 3);
	// 마우스 오른쪽 버튼 클릭 시 메뉴 팝업 
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(MyDisplay);
	
  	glutMainLoop();
  	return 0;
}
