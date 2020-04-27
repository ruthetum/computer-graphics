// 프로젝트 옵션 - Linker 
// -lopengl32
// -lfreeglut
// -lglu32
// -lwinmm
// -lgdi32 
// 추가 

#include <GL/glut.h>

// Shape 값에 따라 display 모델 결정
GLint Shape = 1;
// Render 값에 따라 (solid:1), (wireframe:2) 결정
GLint Render = 1; 
// Color 값에 따라 마우스 버튼을 놓았을 때 redisplay할 색상 결정 : (red:1), (green:2), (blue:3), (default:0)
GLint Color = 0;
// Mode 값에 따라 idle 콜백 상태 결정 : (init:0), (move:1), (stop:2)
GLint Mode = 0;
// 마우스 콜백에서 마우스 좌표 값 전달 
GLint TopLeftX= 125, TopLeftY = 125, BottomRightX = 275, BottomRightY = 275; 
// Animation에 사용할 idle 콜백을 위한 전역변수 
GLfloat Delta = 0.0;
// 메뉴의 설정값이 변할 때 그림 제어
GLint Toggle = 1;

GLint Rotate = 1; 

GLint tlx, tly, brx, bry;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (Color == 0) {
		glColor3f(1.0, 0.0, 0.0);
	}
	
	tlx = TopLeftX < BottomRightX ? TopLeftX : BottomRightX;
	brx = TopLeftX >= BottomRightX ? TopLeftX : BottomRightX;
	tly = 500 - TopLeftY < 500 - BottomRightY ? 500-TopLeftY : 500-BottomRightY;
	bry = 500 - TopLeftY >= 500 - BottomRightY ? 500 - TopLeftY : 500 - BottomRightY;
	
	glViewport(tlx+Delta, tly, brx-tlx, bry-tly);
	
	
	if (Toggle == 1){
		if (Render == 1){
			if (Shape == 1) {
				glutSolidCube(0.8);
				if (Rotate == 1) {
					glRotatef(300,1,1,1);
					Rotate--;
				}
			}
			else if (Shape == 2) {glutSolidSphere(0.5, 20, 30);}
			else if (Shape == 3) {glutSolidTorus(0.2, 0.5, 20, 30);}
			else if (Shape == 4) {glutSolidCone(0.5, 5, 20, 30);}
			else if (Shape == 5) {glutSolidTetrahedron();}
			else if (Shape == 6) {glutSolidIcosahedron();}
			else if (Shape == 7) {glutSolidTeapot(0.5);}
		} else if (Render == 2) {
			if (Shape == 1) {glutWireCube(0.8);}
			else if (Shape == 2) {glutWireSphere(0.5, 20, 30);}
			else if (Shape == 3) {glutWireTorus(0.2, 0.5, 20, 30);}
			else if (Shape == 4) {glutWireCone(0.5, 5, 20, 30);}
			else if (Shape == 5) {glutWireTetrahedron();}
			else if (Shape == 6) {glutWireIcosahedron();}
			else if (Shape == 7) {glutWireTeapot(0.5);}
		}
	}
	glEnd();
	glutSwapBuffers();
}

//
void MyMainMenu(int entryID) {
	glutPostRedisplay();
}

//
void MyShapeMenu(int entryID) {
	if (entryID == 1) {
		Shape = 1;
	} else if (entryID == 2) {
		Shape = 2;
	} else if (entryID == 3) {
		Shape = 3;
	} else if (entryID == 4) {
		Shape = 4;
	} else if (entryID == 5) {
		Shape = 5;
	} else if (entryID == 6) {
		Shape = 6;
	} else if (entryID == 7) {
		Shape = 7;
	}
	glutPostRedisplay();
}

//
void MyRenderingMenu(int entryID) {
	if (entryID == 1) {
		Render = 1;
	} else if (entryID == 2) {
		Render = 2;
	}
	Toggle = 0;
}

//
void MyColorMenu(int entryID) {
	if (entryID == 1) {
		Color = 1;
	} else if (entryID == 2) {
		Color = 2;
	} else if (entryID == 3) {
		Color = 3;
	}
	Toggle = 0;
}

//
void MyAnimationMenu(int entryID) {
	if (entryID == 1) {
		Mode = 1;
	} else if (entryID == 2) {
		Mode = 2;
	}
} 

void MyMouseClick(GLint Button, GLint State, GLint x, GLint y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		TopLeftX = x;
		TopLeftY = y;
	}
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_UP) {
		if (Color == 1){
			glColor3f(1.0, 0.0, 0.0);
		} else if (Color == 2) {
			glColor3f(0.0, 1.0, 0.0);
		} else if (Color == 3) {
			glColor3f(0.0, 0.0, 1.0);
		}
		Mode = 0;
		glutPostRedisplay();
	}
}

void MyMouseMove(GLint x, GLint y) {
	Toggle = 1;
	if (Color == 0){
		Color = 1;
	}
	BottomRightX = x;
	BottomRightY = y;
	glColor3f(0.5, 0.5, 0.5);
	glutPostRedisplay();
}

void MyIdle() {
	if (Mode == 0) {
		Delta = 0.0;
	} else if (Mode == 1) {
		Delta += 0.01;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
  	glutCreateWindow("중간고사 온라인 과제");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	
	//shape 서브 메뉴
	GLint MyShapeMenuID = glutCreateMenu(MyShapeMenu);
	glutAddMenuEntry("Cube", 1);
	glutAddMenuEntry("Sphere", 2);
	glutAddMenuEntry("Torus", 3);
	glutAddMenuEntry("Cone", 4);
	glutAddMenuEntry("Tetrahedron", 5);
	glutAddMenuEntry("Icosahedron", 6);
	glutAddMenuEntry("Teapot", 7);
	// Rendering 서브 메뉴
	GLint MyRenderingMenuID = glutCreateMenu(MyRenderingMenu);
	glutAddMenuEntry("Solid", 1);
	glutAddMenuEntry("Wireframe", 2);
	// Color 서브 메뉴 
	GLint MyColorMenuID = glutCreateMenu(MyColorMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	// Animation 서브 메뉴 
	GLint MyAnimationMenuID = glutCreateMenu(MyAnimationMenu);
	glutAddMenuEntry("Move", 1);
	glutAddMenuEntry("Stop", 2);
	// 메인 메뉴 등록 및 서브 메뉴 id로 추가 
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddSubMenu("Shape", MyShapeMenuID);
	glutAddSubMenu("Rendering", MyRenderingMenuID);
	glutAddSubMenu("Color", MyColorMenuID);
	glutAddSubMenu("Animation", MyAnimationMenuID);
	// 콜백 함수 등록 
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(MyDisplay);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutIdleFunc(MyIdle);
	
  	glutMainLoop();
  	return 0;
}
