#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

const GLfloat lightpos[4] = {0.0, 3.0, 5.0, 1.0};
const GLfloat red[4] = {1.0,0.0,0.0,1.0};

float timestep = 1e-7;

float spring_k = 10.0;

// float ballx = 0;
// float bally = 0;
// float ballz = 2;

// float ballvx = 0.001;
// float ballvy = 0.0005;
// float ballvz = 0.0;

float ballr = 0.15;
float ballm = 5.0;

#define N 10

float ballx[N];
float bally[N];
float ballz[N];

float ballvx[N];
float ballvy[N];
float ballvz[N];

const float g = 9.8;

/*
F = m*dv/dt
F = m*(V(t+delta)-V(t))/delta
V(t+1) = delta*F/m + V(t)
 */


void init(){
    gluLookAt(2.0,3.0,4.0,0,0,0,0,0,1);//カメラの設定

    for(int i = 0; i < N; i++){
	ballx[i] = -2.0+0.5*i;
	bally[i] = -2.0+0.1*(i/5);
	ballz[i] = 1;

	ballvx[i] = (1-2*(i%2))*0.01;
	ballvy[i] = 0.0;
	ballvz[i] = 0;

    }

    /*Lighting*/
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

#define sign(x) x >= 0 ? 1 : -1

void myDisplay(){
    //---実際の描画に関する記述モードの開始
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60,1,0.0001,20);

    glMatrixMode(GL_MODELVIEW);
    // static double rotF = 0;
    // rotF < 360 ? rotF += 0.2 : rotF = 0;//回転角の計算

    // glColor3f(1.0, 1.0, 0);

    // gravity

    for(int i = 0; i < N; i++){


	float v = sqrt(ballvx[i]*ballvx[i] + ballvy[i]*ballvy[i]+ ballvz[i]*ballvz[i]);

	float c = 1;

	ballvx[i] = ballvx[i] - ballvx[i]*v*c/ballm*timestep;
	ballvy[i] = ballvy[i] - ballvy[i]*v*c/ballm*timestep;
	ballvz[i] = ballvz[i] - ballvz[i]*v*c/ballm*timestep;

	ballvz[i] = ballvz[i] - timestep*g;

	ballx[i] +=ballvx[i];
	bally[i] +=ballvy[i];
	ballz[i] +=ballvz[i];

	if(ballz[i]-ballr < 0){
	    ballz[i] = ballr;
	    ballvz[i] = -ballvz[i]*0.9;
	}

	if(ballx[i]< -2.5 +ballr ){
	    ballx[i]= -2.5 +ballr ;
	    ballvx[i] = -ballvx[i]*0.9;
	}

	if(ballx[i]> 2.5 -ballr ){
	    ballx[i]= 2.5 -ballr ;
	    ballvx[i] = -ballvx[i]*0.9;
	}

	if(bally[i]< -2.5 +ballr ){
	    bally[i]= -2.5 +ballr ;
	    ballvy[i] = -ballvy[i]*0.9;
	}

	if(bally[i]> 2.5 -ballr ){
	    bally[i]= 2.5 -ballr ;
	    ballvy[i] = -ballvy[i]*0.9;
	}




	//---ティーポットの描画
	glPushMatrix();
	glTranslated(ballx[i],bally[i],ballz[i]);
	glutSolidSphere(0.3,20,20);
	glPopMatrix();
    }

    for(int i = 0; i< N-1; i++){
	for(int j = i+1; j<N; j++){
	    float distX = ballx[i] - ballx[j];
	    float distY = bally[i] - bally[j];
	    float distZ = ballz[i] - ballz[j];

	    float distSquare = distX*distX+distY*distY+distZ*distZ;

	    if(distSquare < ballr*ballr){
		float dot[2];
		dot[0] = (ballvx[i]*distX + ballvy[i]*distY + ballvz[i]*distZ)/sqrt(distSquare);
		dot[1] = (ballvx[j]*distX + ballvy[j]*distY + ballvz[j]*distZ)/sqrt(distSquare);

		ballvx[i] = ballvx[i] - dot[0]*distX/sqrt(distSquare)+ dot[1]*distX/sqrt(distSquare);
		ballvy[i] = ballvy[i] - dot[0]*distY/sqrt(distSquare)+ dot[1]*distY/sqrt(distSquare);
		ballvz[i] = ballvz[i] - dot[0]*distZ/sqrt(distSquare)+ dot[1]*distZ/sqrt(distSquare);

		ballvx[j] = ballvx[j] - dot[1]*distX/sqrt(distSquare)+ dot[0]*distX/sqrt(distSquare);
		ballvy[j] = ballvy[j] - dot[1]*distY/sqrt(distSquare)+ dot[0]*distY/sqrt(distSquare);
		ballvz[j] = ballvz[j] - dot[1]*distZ/sqrt(distSquare)+ dot[0]*distZ/sqrt(distSquare);

	    }
	}
    }

    glPushMatrix();

    glTranslated(0, 0, -2.5);
    glutSolidCube(5.0);
    glPopMatrix();

    //---バッファの更新
    glutSwapBuffers();
}

void myIdle(){
    glutPostRedisplay();			//再描画命令
}

int main(int argc, char* argv[])
{
    //---GLUTの初期化
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);		//ウィンドウサイズの設定
    glutCreateWindow("ARTISTIC CG");	//ウィンドウの生成


    //---GLUTへの関数の登録
    glutDisplayFunc(myDisplay);			//Display関数の登録
    glutIdleFunc(myIdle);				//Idle関数の登録

    init();

    //---ループの開始
    glutMainLoop();

    return 0;
}
