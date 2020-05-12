// 프로젝트 옵션 - Linker 
//-lopengl32
//-lfreeglut
//-lglu32
//-lwinmm
//-lgdi32 
// 추가 

#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265358972

float getRadian(float num) {
	return num * (PI / 180);
}

// 조명 설정 
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

// 마우스 움직임에 따른 시점 변경용 전역변수 
GLint clickedX, clickedY;
GLint ViewX = 0, ViewY = 0;

// flatshade와 wireframe 토글링을 위한 전역변수
int FlatShaded = 0, WireFramed = 0; 

// 마우스 클릭 확인용
int mouseClicked = 0; 

GLfloat etX = 0.0, etY = 0.0, etZ = -1.0;

float Rotate = 0.0, Rad, deltaX, deltaRotate;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// 0,1,2 : 바라보는 눈의 위치
	// 3,4,5 : 바라볼 위치
	// 6,7,8 : 카메라 상향 벡터
	gluLookAt(
		0.0, 0.0, 0.0,
		etX, 1.0, etZ,
		0.0, 1.0, 0.0
	);
	// 마우스의 움직에 따라 시점을 변화시키려면
	// Mymousemove 에서 입력되는 변화량을 참고하여
	// gluLookat 파라미터를 변경 : https://huiyu.tistory.com/entry/gluLookAt%ED%95%A8%EC%88%98
	
	// 탁자 그리기 + 탁자 위에 주전자 오브젝트 3개 이상 탁자에 그리기
	// 하나는 제공하는 모델, 두번째는 구글링해서 만들어진 모델, 세번째는 내가 직접 만들기
	// 이미 모델링 좌표 데이터를 import 하여 사용 가능 
	
	
	glutSolidTeapot(0.2);
	
	glFlush();
}

// 키보드 콜백함수
void MyKeyboard(unsigned char KeyPressed, int x, int y) {
	switch(KeyPressed) {
		case 'q':
		case 'Q':
		case '\033':
			exit(0);
			break;
		// 솔리드 렌더링 
		case 's':
		case 'S':
			if (FlatShaded) {
				FlatShaded = 0;
				glShadeModel(GL_SMOOTH); // 보이는 폴리곤을 따라서 정점색을 채움 
			} else {
				FlatShaded = 1;
				glShadeModel(GL_FLAT);	// 처음으로 지정된 색이 채워지는 색으로 결정
			}
			glutPostRedisplay();
			break;
		// 와이어 프레임 토글링
		case 'w':
		case 'W':
			if (WireFramed) {
				WireFramed = 0;
				glShadeModel(GL_SMOOTH); // 보이는 폴리곤을 따라서 정점색을 채움 
			} else {
				WireFramed = 1;
				glShadeModel(GL_FLAT);	// 처음으로 지정된 색이 채워지는 색으로 결정
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
  	glutCreateWindow("OpenGL Project I by 2016310285 김희동");
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
