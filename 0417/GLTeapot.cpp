#include <GL/glut.h>

void myDisplay(){

	//---�F�����N���A
	glClear(GL_COLOR_BUFFER_BIT);

	//---���e���@�Ɋւ���ݒ�̊J�n
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	//glOrtho(-1, 1, -1, 1, -1, 1);
	gluPerspective(60.0, 1.0, 0, 20);	//�������e�@�ɂ�郌���_�����O


	//---���ۂ̕`��Ɋւ���L�q���[�h�̊J�n
	glMatrixMode(GL_MODELVIEW);

	static double rotF = 0;
	rotF < 360 ? rotF += 0.2 : rotF = 0;//��]�p�̌v�Z

	glColor3f(1.0, 1.0, 0);

	//---�e�B�[�|�b�g�̕`��
	glPushMatrix();
		gluLookAt(0,0,0,0,0,-1,0,1,0);//�J�����̐ݒ�
		glTranslated(0,0,-2);		//�e�B�[�|�b�g�̈ړ�
		glScalef(0.5, 0.5, 0.5);	//�e�B�[�|�b�g�̊g��k��
		glRotatef(rotF, 1, 1, 0);	//�e�B�[�|�b�g�̉�]
		glutWireTeapot(1);			//���a1�̃e�B�[�|�b�g���V�[���ɐ���
	glPopMatrix();

	//---�o�b�t�@�̍X�V
	glutSwapBuffers();
}

void myIdle(){
	glutPostRedisplay();			//�ĕ`�施��
}

int main(int argc, char* argv[])
{

	//---GLUT�̏�����
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); 
	glutInitWindowSize(512, 512);		//�E�B���h�E�T�C�Y�̐ݒ�
	glutCreateWindow("ARTISTIC CG");	//�E�B���h�E�̐���


	//---GLUT�ւ̊֐��̓o�^
	glutDisplayFunc(myDisplay);			//Display�֐��̓o�^
	glutIdleFunc(myIdle);				//Idle�֐��̓o�^


	//---���[�v�̊J�n
	glutMainLoop();

	return 0;
}
