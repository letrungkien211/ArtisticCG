#include <GL/glut.h>

void myDisplay(){

	//---色情報をクリア
	glClear(GL_COLOR_BUFFER_BIT);

	//---投影方法に関する設定の開始
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	//glOrtho(-1, 1, -1, 1, -1, 1);
	gluPerspective(60.0, 1.0, 0, 20);	//透視投影法によるレンダリング


	//---実際の描画に関する記述モードの開始
	glMatrixMode(GL_MODELVIEW);

	static double rotF = 0;
	rotF < 360 ? rotF += 0.2 : rotF = 0;//回転角の計算

	glColor3f(1.0, 1.0, 0);

	//---ティーポットの描画
	glPushMatrix();
		gluLookAt(0,0,0,0,0,-1,0,1,0);//カメラの設定
		glTranslated(0,0,-2);		//ティーポットの移動
		glScalef(0.5, 0.5, 0.5);	//ティーポットの拡大縮小
		glRotatef(rotF, 1, 1, 0);	//ティーポットの回転
		glutWireTeapot(1);			//半径1のティーポットをシーンに生成
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); 
	glutInitWindowSize(512, 512);		//ウィンドウサイズの設定
	glutCreateWindow("ARTISTIC CG");	//ウィンドウの生成


	//---GLUTへの関数の登録
	glutDisplayFunc(myDisplay);			//Display関数の登録
	glutIdleFunc(myIdle);				//Idle関数の登録


	//---ループの開始
	glutMainLoop();

	return 0;
}
