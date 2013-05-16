#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <string>

#include <GL/glut.h>
#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>

using namespace std;


/* Constants*/
const int timer = 25;
const float timeStep = 1e-2f;
const float red[4] = {1,0,0,1};
const float lightpos[4] = {0.0, 3.0, 5.0, 1.0};

/* Variables*/
int winWidth = 512;
int winHeight = 512;

void myDisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,(float)winWidth/(float)winHeight,0.0001,20);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glTranslated(0,0,-2);
	glutSolidSphere(1,10,10);
	glPopMatrix();
	glutSwapBuffers();
}

void myInit(){
	/*Camera*/
    gluLookAt(2.0,3.0,4.0,0,0,0,0,0,1);

    /*Lighting*/
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    /*Depth*/
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void myIdle(){
	glutPostRedisplay();
}

void myReshape(int w, int h){
	winWidth = w;
	winHeight = h;

	glViewport(0, 0, winWidth, winHeight);
}

void myTimer(int value){

}

int main(int argc, char* argv[]){
    //---GLUTの初期化
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(winWidth, winHeight);		//ウィンドウサイズの設定
    glutCreateWindow("ARTISTIC CG");	//ウィンドウの生成

    //---GLUTへの関数の登録
    glutDisplayFunc(myDisplay);			//Display関数の登録
    glutIdleFunc(myIdle);				//Idle関数の登録
    glutTimerFunc(timer, myTimer, 0);
    glutReshapeFunc(myReshape);
    //glutKeyboardFunc();
    //glutSpecialFunc();
    //glutMouseFunc();

    myInit();

    //---ループの開始
    glutMainLoop();

    return 0;
}
