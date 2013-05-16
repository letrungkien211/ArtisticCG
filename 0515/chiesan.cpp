#include <GL/glut.h>
#include <math.h>

const GLfloat lightpos[4] = {0.0, 3.0, 5.0, 1.0}; //照明の座標＋反射率（基本１でok）
const GLfloat red[4] = {1.0, 0.0, 0.0, 1.0};

const int N = 50;
float timestep = 0.0001;

float spring_k = 10.0;

float ballr = 0.15;
float ballm = 10.0;

/*float ballx = -1.0;
float bally = 0.0;
float ballz = 2.0;

float ballvx = 0.001;
float ballvy = 0.0005;
float ballvz = 0.0;*/

float ballx[N];
float bally[N];
float ballz[N];

float ballvx[N];
float ballvy[N];
float ballvz[N];

void myDisplay(){

  //---色情報をクリア
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  //---投影方法に関する設定の開始
  glMatrixMode(GL_PROJECTION);
  
  glLoadIdentity();
  
  //glOrtho(-1, 1, -1, 1, -1, 1);
  gluPerspective(60.0, 1.0, 0.0001, 20); //透視投影法によるレンダリング 3つめのパラメータを0にしない
  
  
  //---実際の描画に関する記述モードの開始
  glMatrixMode(GL_MODELVIEW);
  
  static double rotF = 0;
  rotF < 360 ? rotF += 0.2 : rotF = 0;//回転角の計算
  
  //glColor3f(1.0, 1.0, 0);
  
  for(int i = 0;i < N;i++){
  //重力
    ballvz[i] = ballvz[i] - timestep * 9.8;


    //ばね
    /*ballvx = ballvx + timestep * (-spring_k) * ballx / ballm;
      ballvy = ballvy + timestep * (-spring_k) * bally / ballm;
      ballvz = ballvz + timestep * (-spring_k) * (ballz - 6.0) / ballm;*/

    float c = 1.0f;
    float v = sqrt(ballvx[i]*ballvx[i] + ballvy[i]*ballvy[i] + ballvz[i]*ballvz[i]);

  

    //空気抵抗
    /*ballvx = ballvx -  ballvx * v * c / ballm * timestep;
    ballvy = ballvy -  ballvy * v * c / ballm * timestep;
    ballvz = ballvz -  ballvz * v * c / ballm * timestep;  */

    /*ballvx = ballvx - (ballvx/abs(ballvx)) * ballvx * ballvx * c / ballm * timestep;
      ballvy = ballvy - (ballvy/abs(ballvy)) * ballvy * ballvy * c / ballm * timestep;
      ballvz = ballvz - (ballvz/abs(ballvz)) * ballvz * ballvz * c / ballm * timestep;*/

    ballx[i] += ballvx[i];
    bally[i] += ballvy[i];
    ballz[i] += ballvz[i]; 

    if(ballz[i]-ballr < 0){
     
      ballz[i] = ballr;  
      ballvz[i] = -ballvz[i] * 0.9;
    }

    if(ballx[i] < -2.5 + ballr){
      ballx[i] = -2.5 + ballr;
      ballvx[i] = -ballvx[i];
    }
    if(ballx[i] > 2.5 - ballr){
      ballx[i] = 2.5 - ballr;
      ballvx[i] = -ballvx[i];
    }

    if(bally[i] < -2.5 + ballr){
      bally[i] = -2.5 + ballr;
      ballvy[i] = -ballvy[i];
    }
    if(bally[i] > 2.5 - ballr){
      bally[i] = 2.5 - ballr;
      ballvy[i] = -ballvy[i];
    }




  }

  /*float distX = ballx[0] - ballx[1];
  float distY = bally[0] - bally[1];
  float distZ = ballz[0] - ballz[1];

  float distSquare = distX*distX + distY*distY + distZ*distZ;*/

  for(int i = 0;i < N-1;i++){
    for(int j = i+1;j < N;j++){
      float distX = ballx[i] - ballx[j];
      float distY = bally[i] - bally[j];
      float distZ = ballz[i] - ballz[j];

      float distSquare = distX*distX + distY*distY + distZ*distZ;

      if(distSquare < 4*ballr*ballr) {
	//内積
	float dot1 = (ballvx[i]*distX + ballvy[i]*distY + ballvz[i]*distZ)/sqrt(distSquare);
	float dot2 = (ballvx[j]*distX + ballvy[j]*distY + ballvz[j]*distZ)/sqrt(distSquare);

	ballvx[i] = ballvx[i] - dot1 * distX / sqrt(distSquare);
	ballvy[i] = ballvy[i] - dot1 * distY / sqrt(distSquare);
	ballvz[i] = ballvz[i] - dot1 * distZ / sqrt(distSquare);

	ballvx[j] = ballvx[j] - dot2 * distX / sqrt(distSquare);
	ballvy[j] = ballvy[j] - dot2 * distY / sqrt(distSquare);
	ballvz[j] = ballvz[j] - dot2 * distZ / sqrt(distSquare);

	ballvx[i] = ballvx[i] + dot2 * distX / sqrt(distSquare);
	ballvy[i] = ballvy[i] + dot2 * distY / sqrt(distSquare);
	ballvz[i] = ballvz[i] + dot2 * distZ / sqrt(distSquare);

	ballvx[j] = ballvx[j] + dot1 * distX / sqrt(distSquare);
	ballvy[j] = ballvy[j] + dot1 * distY / sqrt(distSquare);
	ballvz[j] = ballvz[j] + dot1 * distZ / sqrt(distSquare);
      }
    }
  }

  /*if(distSquare < 4*ballr*ballr) {
  //内積
  float dot1 = (ballvx[0]*distX + ballvy[0]*distY + ballvz[0]*distZ)/sqrt(distSquare);
  float dot2 = (ballvx[1]*distX + ballvy[1]*distY + ballvz[1]*distZ)/sqrt(distSquare);

  ballvx[0] = ballvx[0] - dot1 * distX / sqrt(distSquare);
  ballvy[0] = ballvy[0] - dot1 * distY / sqrt(distSquare);
  ballvz[0] = ballvz[0] - dot1 * distZ / sqrt(distSquare);

  ballvx[1] = ballvx[1] - dot2 * distX / sqrt(distSquare);
  ballvy[1] = ballvy[1] - dot2 * distY / sqrt(distSquare);
  ballvz[1] = ballvz[1] - dot2 * distZ / sqrt(distSquare);

  ballvx[0] = ballvx[0] + dot2 * distX / sqrt(distSquare);
  ballvy[0] = ballvy[0] + dot2 * distY / sqrt(distSquare);
  ballvz[0] = ballvz[0] + dot2 * distZ / sqrt(distSquare);

  ballvx[1] = ballvx[1] + dot1 * distX / sqrt(distSquare);
  ballvy[1] = ballvy[1] + dot1 * distY / sqrt(distSquare);
  ballvz[1] = ballvz[1] + dot1 * distZ / sqrt(distSquare);
  }*/

  for(int i = 0;i < N;i++){  
    //---ティーポットの描画
    glPushMatrix();
    
    
    glTranslated(ballx[i],bally[i],ballz[i]);		//ティーポットの移動
    //glScalef(0.5, 0.5, 0.5);	//ティーポットの拡大縮小
    //glRotatef(rotF, 1, 1, 0);	//ティーポットの回転
    //glutWireTeapot(1);			//半径1のティーポットをシーンに生成
    glutSolidSphere(ballr, 20,20);
    glPopMatrix();
  }
  
  //地面の描画
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

void init(){
  gluLookAt(2,3,4,0,0,0,0,0,1);//カメラの設定
  
  /*ballx[0] = 2.0;
  bally[0] = 0.0;
  ballz[0] = 2.0 - 0.05;

  ballx[1] = -2.0;
  bally[1] = 0.0;
  ballz[1] = 2.0 + 0.05;

  ballvx[0] = -0.001;
  ballvy[0] = 0;
  ballvz[0] = 0;

  ballvx[1] = 0.001;
  ballvy[1] = 0;
  ballvz[1] = 0;*/

  for(int i = 0;i < N;i++){
    ballx[i] = -2.0 + 1.0*(i%5) + (i%3)*0.1;
    bally[i] = -2.0 + 1.0*(i/5) + ((i+1)%3)*0.1;
    ballz[i] = 2.0;

    if(i % 2 == 0){
      ballvx[i] = 0.001;
    }
    else{
      ballvx[i] = -0.001;
      ballvy[i] = 0;
      ballvz[i] = 0;
    }
  }


  //光源
  glEnable(GL_LIGHTING);  //照明をonにするという合図
  glEnable(GL_LIGHT0);  //照明は８個までつけられて、その１つ目をonにする合図
  glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  
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
