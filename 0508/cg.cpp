#include <GL/glut.h>

const GLfloat lightpos[4] = {0.0, 3.0, 5.0, 1.0};
const GLfloat red[4] = {1.0,0.0,0.0,1.0};

float timestep = 1e-6;

float spring_k = 10.0;

float ballx = 0;
float bally = 0;
float ballz = 2;

float ballvx = 0.001;
float ballvy = 0.005;
float ballvz = 0.0;

float ballr = 0.15;
float ballm = 5.0;

const float g = 9.8;

/*
F = m*dv/dt
F = m*(V(t+delta)-V(t))/delta
V(t+1) = delta*F/m + V(t)
 */


void init(){
    gluLookAt(2.0,3.0,4.0,0,0,0,0,0,1);//カメラの設定

    /*Lighting*/
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}



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
    ballvz = ballvz - timestep*g;
    // Spring
    ballvx = ballvx + timestep* (-spring_k) * ballx/ballm;
    ballvy = ballvy + timestep* (-spring_k) * bally/ballm;
    ballvz = ballvz + timestep* (-spring_k) * (ballz-6.0)/ballm;
    
    ballx +=ballvx;
    bally +=ballvy;
    ballz +=ballvz;

    if(ballz-ballr < 0){
		ballz = ballr;
    	ballvz = -ballvz*0.9;
    }
    //---ティーポットの描画
    glPushMatrix();
    glTranslated(ballx,bally,ballz);		//ティーポットの移動
    // glScalef(0.5, 0.5, 0.5);	//ティーポットの拡大縮小
    // glRotatef(rotF, 1, 1, 0);	//ティーポットの回転
    glutSolidSphere(0.3,20,20);     //
    glPopMatrix();

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
