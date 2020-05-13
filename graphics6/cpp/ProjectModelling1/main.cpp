// 프로젝트 옵션 - Linker 
//-lopengl32
//-lfreeglut
//-lglu32
//-lwinmm
//-lgdi32 
// 추가 

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265358972
#define LIST_SIZE 7

// 마우스 움직임에 따른 시점 변경용 전역변수 
GLint clickedX, clickedY;
GLint ViewX = 0, ViewY = 0;

// 키보드 콜백을 통한 모델 렌더링 종류 결정 
int FlatShaded = 1, WireFramed = 0; 

// 모델 좌표
GLfloat etX = 0.0, etY = 0.0, etZ = -1.0;

// 탁자 상판 
GLfloat upperTableVertices[8][3] = {
	{ -0.5, -0.1, 0.5},
	{ -0.5, 0.0, 0.5},
	{ 0.5, 0.0, 0.5}, 
	{ 0.5, -0.1, 0.5}, 
	{ -0.5, -0.1, -0.5}, 
	{ -0.5, 0.0, -0.5}, 
	{ 0.5, 0.0, -0.5},
	{ 0.5, -0.1, -0.5}
};
// 탁자 다리 
GLfloat LFLegVertices[8][3] = {
	{ -0.5, -0.4, 0.5},
	{ -0.5, -0.1, 0.5},
	{ -0.4, -0.1, 0.5}, 
	{ -0.4, -0.4, 0.5}, 
	{ -0.5, -0.4, 0.4},
	{ -0.5, -0.1, 0.4},
	{ -0.4, -0.1, 0.4}, 
	{ -0.4, -0.4, 0.4}
};
GLfloat RFLegVertices[8][3] = {
	{ 0.4, -0.4, 0.5},
	{ 0.4, -0.1, 0.5},
	{ 0.5, -0.1, 0.5}, 
	{ 0.5, -0.4, 0.5}, 
	{ 0.4, -0.4, 0.4},
	{ 0.4, -0.1, 0.4},
	{ 0.5, -0.1, 0.4}, 
	{ 0.5, -0.4, 0.4}
};
GLfloat LBLegVertices[8][3] = {
	{ -0.5, -0.4, -0.4},
	{ -0.5, -0.1, -0.4},
	{ -0.4, -0.1, -0.4}, 
	{ -0.4, -0.4, -0.4}, 
	{ -0.5, -0.4, -0.5},
	{ -0.5, -0.1, -0.5},
	{ -0.4, -0.1, -0.5}, 
	{ -0.4, -0.4, -0.5}
};
GLfloat RBLegVertices[8][3] = {
	{ 0.5, -0.4, -0.4},
	{ 0.5, -0.1, -0.4},
	{ 0.4, -0.1, -0.4}, 
	{ 0.4, -0.4, -0.4}, 
	{ 0.5, -0.4, -0.5},
	{ 0.5, -0.1, -0.5},
	{ 0.4, -0.1, -0.5}, 
	{ 0.4, -0.4, -0.5}
};

// 사탕 막대
GLfloat CandyStick[8][3] = {
	{ -0.41, 0.0, -0.39},
	{ -0.41, 0.52, -0.39},
	{ -0.39, 0.52, -0.39}, 
	{ -0.39, 0.0, -0.39}, 
	{ -0.41, 0.0, -0.41},
	{ -0.41, 0.52, -0.41},
	{ -0.39, 0.52, -0.41}, 
	{ -0.39, 0.0, -0.41}
};

// color 리스트 
GLfloat MyColors[8][3] = {
	{0.1, 0.1, 0.1}, 
	{0.1, 0.1, 0.1},
	{0.1, 0.1, 0.1}, 
	{0.1, 0.1, 0.1}, 
	{0.1, 0.1, 0.1}, 
	{0.1, 0.1, 0.1}, 
	{0.1, 0.1, 0.1},  
	{0.1, 0.1, 0.1}
};
// 큐브 정점(6면) 정점 순서 리스트
GLubyte MyVertexList[24] = {
	0, 3, 2, 1,
	2, 3, 7, 6,
	0, 4, 7, 3,
	1, 2, 6, 5,
	4, 5, 6, 7,
	0, 1, 5, 4
};

GLuint pig;
void loadObj(char *fname) {
	FILE *fp;
	int read;
	GLfloat x, y, z;
	char ch;
	pig = glGenLists(1);
	fp = fopen(fname, "r");
	if (!fp)
		exit(1);
		
	glPointSize(2.0);
	glNewList(pig, GL_COMPILE);
	glPushMatrix();
	
	if (FlatShaded) {
		glBegin(GL_POLYGON);
	} else if (WireFramed) {
		glBegin(GL_LINE_STRIP);	
	}
	while(!(feof(fp))) {
		read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
		if (read==4 && ch=='v') {
			glVertex3f(x,y,z);
		}
	}
	glEnd();
	glPopMatrix();
	glEndList();
	fclose(fp);
}
void drawPig() {
	glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	glTranslatef(0.2, 0.0, -0.1);
	glScalef(0.2, 0.2, 0.2);
	glCallList(pig);
	glPopMatrix();
}

GLuint myList;
void MyDisplayList() {
	
	myList = glGenLists(LIST_SIZE);
	
	glNewList(myList, GL_COMPILE);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, MyColors);
		glVertexPointer(3, GL_FLOAT, 0, upperTableVertices);
		for (GLint i=0; i<6; i++) {
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
		}
	glEndList();
	
	glNewList(myList+1, GL_COMPILE);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, MyColors);
		glVertexPointer(3, GL_FLOAT, 0, LFLegVertices);
		for (GLint i=0; i<6; i++) {
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
		}
	glEndList();
	
	glNewList(myList+2, GL_COMPILE);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, MyColors);
		glVertexPointer(3, GL_FLOAT, 0, RFLegVertices);
		for (GLint i=0; i<6; i++) {
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
		}
	glEndList();
	
	glNewList(myList+3, GL_COMPILE);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, MyColors);
		glVertexPointer(3, GL_FLOAT, 0, LBLegVertices);
		for (GLint i=0; i<6; i++) {
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
		}
	glEndList();
	
	glNewList(myList+4, GL_COMPILE);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, MyColors);
		glVertexPointer(3, GL_FLOAT, 0, RBLegVertices);
		for (GLint i=0; i<6; i++) {
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
		}
	glEndList();
	
	glNewList(myList+5, GL_COMPILE);
		glTranslatef(-0.3, 0.06, 0.2);
		if (FlatShaded) {
			glutSolidTeapot(0.1);
		}
		if (WireFramed){
			glutWireTeapot(0.1);
		}
	glEndList();
	
	glNewList(myList+6, GL_COMPILE);
		glTranslatef(-0.1, 0.64, -0.6);
		if (FlatShaded) {
			glutSolidSphere(0.2, 20, 30);
		}
		if (WireFramed){
			glutWireSphere(0.2, 20, 30);
		}
		glTranslatef(0.4, -0.7, 0.4);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, MyColors);
		glVertexPointer(3, GL_FLOAT, 0, CandyStick);
		for (GLint i=0; i<6; i++) {
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
		}
	glEndList();
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

// 회전용 radian 구하기 함수 
float getRadian(float num) {
	return num * (PI / 180);
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// 0,1,2 : 바라보는 눈의 위치
	// 3,4,5 : 바라볼 위치
	// 6,7,8 : 카메라 상향 벡터
	gluLookAt(
		0.0, 0.0, 0.0,
		etX, etY, etZ,
		0.0, 1.0, 0.0
	);
	
	for (int i=0;i<LIST_SIZE;i++) {
		glCallList(myList+i);
	}
	drawPig();
	glutSwapBuffers();
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
				glShadeModel(GL_SMOOTH); // 보이는 폴리곤을 따라서 정점색을 채움
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			} else {
				FlatShaded = 1;
				WireFramed = 0;
				glShadeModel(GL_FLAT);	// 처음으로 지정된 색이 채워지는 색으로 결정
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			glutPostRedisplay();
			break;
		// 와이어 프레임 토글링
		case 'w':
		case 'W':
			if (WireFramed) {
				glShadeModel(GL_SMOOTH); // 보이는 폴리곤을 따라서 정점색을 채움
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			} else {
				WireFramed = 1;
				FlatShaded = 0;
				glShadeModel(GL_FLAT);	// 처음으로 지정된 색이 채워지는 색으로 결정
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
	
	float deltaX = (float)(ViewX - clickedX);
	float deltaXRotate = deltaX / 500.0;
	float RotateX = deltaXRotate * 360.0;
	float Rad = getRadian(RotateX);
	etX = (GLfloat) (sin(Rad));
	etZ = (GLfloat) (-1 * cos(Rad));
	
	float deltaY = (float)(clickedY - ViewY);
	float deltaYRotate = deltaY / 500.0;
	etY = deltaYRotate * 3;
	
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
	MyDisplayList();
	loadObj("pig.obj");
	
  	glutMainLoop();
  	return 0;
}
