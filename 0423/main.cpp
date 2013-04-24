#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "GrayScott.h"

#define F	0.004
#define K	0.02
#define N	512
#define M	512
#define RU	0.2
#define RV	0.078
#define PR	3

GrayScott* gs;
GLfloat* bits;
bool stopFlag = true;
bool lMouseFlag = false;
int mx;
int my;


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (!stopFlag)
	{
		if (lMouseFlag)
			gs->put(mx, my);

		gs->update();
	}

	static const float S = N * M / 4;

	int index = 0;

	for (int j = 0; j < M; j++)
	{
		for (int i = 0; i < N; i++)
		{
			float P = (i - N / 2) * (i - N / 2) + (j - M / 2) * (j - M / 2);

			float col1 = (1.0 - gs->u[i+1][j+1]) * (1.0 - P / S);
			float col2 = gs->v[i+1][j+1] * 3.0 * sqrt(P / S);

			bits[index++] = col1 - col2 * 0.5;
			bits[index++] = col2;
			bits[index++] = col1 - col2 * 0.5;
		}
	}

	glRasterPos2i(-1 , -1);
	glDrawPixels(N, M, GL_RGB, GL_FLOAT, bits);

	glutSwapBuffers();
}

void idle(void)
{
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 'q':
		case 'Q':
		case '\033':
			exit(0);
		case 'a':
		case 'A':
			stopFlag = !stopFlag;
		default:
	  break;
	}
}

void mouse(int button, int state, int x, int y)
{
	mx = x;
	my = M - y;

	lMouseFlag = (state == GLUT_DOWN);
}

void motion(int x ,int y)
{
	mx = x;
	my = M - y;
}

void exitFunc(void)
{
	if (gs != 0)
		delete gs;

	if (bits != 0)
		delete [] bits;
}

int main(int argc, char* argv[])
{
	printf("Gray Scott 2D Model\n");

	printf(" initializing GrayScott...\n");
	gs = new GrayScott(N, M, F, K, RU, RV, PR);

	bits = new GLfloat[N*M*3];

	printf(" initializing OpenGL...\n");
	glutInit(&argc, argv);							// initialize glut
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);	// color mode is RGBA, use double buffering
	glutInitWindowSize(N, M);						// initial window size is 128x128
	glutCreateWindow("Gray Scott Model");			// Window name

	glutDisplayFunc(display);						// the function called when displaying
	glutIdleFunc(idle);								// the function called when idling
	glutKeyboardFunc(keyboard);						// the function called when keyboard event occurred
	glutMouseFunc(mouse);							// the function called when mouse event occurred
	glutMotionFunc(motion);

//	atexit(exitFunc);

	glutMainLoop();									// start

	return 0;
}