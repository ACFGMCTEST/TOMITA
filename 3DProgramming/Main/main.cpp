/*�쐬�ҁ@�y�c���l*/
#include <Windows.h>
#include "glew.h"
#include "glut.h"
#include "GLFW/glfw3.h"
#include "../Light/CLight.h"
#include "../GameMain/Scene/CSceneManager.h"
#include "../Define/define.h"
#include "../GameMain/Key/CMouse.h"
/*���C�g�ݒ�*/
#define LIGHT_SET_DIR 0,-1,1 //�g�U��
#define LIGHT_SET_AMB 0.9f, 0.9f, 0.9f //����
#define LIGHT_SET_COL 1.0f, 1.0f, 1.0f //�J���[
#define LIGHT_POS  0.0f, 0.1f, 0.0f, 0.0f //�|�W�V����

int WinPosX, WinPosY;//main.cpp�Őݒ�

CSceneManager Main;
/* display�֐�
1�b�Ԃ�60����s�����
*/
void display() {
	//�e�o�b�t�@�[���N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Main.SceneMain();

	CMouse::GetInstance()->Update();
	//��ʂɕ\��
//	glutSwapBuffers();
}


//
//
//
//
////�֐��̃v���g�^�C�v�錾
//void reshape(int, int);
//void idle();
//
//void main(int argc, char* argv[]) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);	//�f�B�X�v���C���[�h�ݒ�
//	//�E�B���h�E�̐ݒ�
//	glutInitWindowSize(DISP_X,DISP_Y,);
//	glutInitWindowPosition(0, 0);
//	glutCreateWindow("Hello 3DProgramming");	//�E�B���h�E�쐬
//	glClearColor(0.5f, 0.5f, 0.5f, 1.f);	//�N���A�F�𔒂ɐݒ�
//
//	glewInit();
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//
////���C�g�̐ݒ�
//	//�Œ�V�F�[�_�[�p
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	//���b�V���V�F�[�_�[�p
////	CLight::getLight(0)->setDir(CVector3D(0, -1, 1).GetNormalize());
////	CLight::getLight(0)->setColor(CVector3D(0.9f, 0.9f, 0.9f), CVector3D(1.0f, 1.0f, 1.0f));
//
//	//�e��֐��ݒ�
//	glutDisplayFunc(display);	//�`�掞�̊֐����w��
//	glutReshapeFunc(reshape);	//�E�B���h�E�ό`���̊֐����w��
//	glutIdleFunc(idle);			//�ҋ@���̊֐����w��
//
//	//���C�����[�v
//	glutMainLoop();
//
//	return;
//}
int winX, winY;
//
/*�E�B���h�E�T�C�Y�ύX���̏���
void reshape(int width, int height)
width:��ʕ�
height:��ʍ���
*/
void reshape(GLFWwindow* window, int width, int height) {
	winX = width; winY = height;
	glViewport(0, 0, width, height);	//��ʂ̕`��G���A�̎w��
//	CCamera::getCamera()->SetSize(width, height);
	glMatrixMode(GL_PROJECTION);		//�s����v���W�F�N�V�������[�h�֕ύX
	glLoadIdentity();
	gluPerspective(75.0, (double)width / (double)height, 1.0, 1000.0);
//	gluLookAt(0.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}
//
LARGE_INTEGER last_time;	//�O��̃J�E���^�l
//�P�b�ԂɂU�O��`�悷��悤�ɒ��߂���
void idle() {
	LARGE_INTEGER freq;		//��b������̃J�E���^��
	LARGE_INTEGER time;		//����̃J�E���^�l

	//��b�Ԃ̃J�E���^�����擾
	QueryPerformanceFrequency(&freq);

	if (last_time.QuadPart == 0) {
		QueryPerformanceCounter(&last_time);
	}
	do{
		//���݂̃V�X�e���̃J�E���g�����擾
		QueryPerformanceCounter(&time);

		//���̃J�E���g-�O��̃J�E���g < 1�b������̃J�E���g����60�Ŋ���(1/60�b������̃J�E���g��)
	} while (time.QuadPart - last_time.QuadPart < freq.QuadPart / 60);
	last_time = time;

	//�`�悷��֐����Ă�
	display();
}


int main(void)
{
	GLFWwindow* window;
	//CMouse::GetInstance()->Access(window);

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	//window = glfwCreateWindow(DISP_X, DISP_Y, "Hello World", glfwGetPrimaryMonitor(), NULL);
	window = glfwCreateWindow(DISP_X, DISP_Y, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	// GLEW ������������
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		// GLEW �̏������Ɏ��s����
//		std::cerr << "Can't initialize GLEW" << std::endl;
		return 1;
	}
	// ���������̃^�C�~���O��҂�  
	//glfwSwapInterval(1); 


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// �E�B���h�E�̃T�C�Y�ύX���ɌĂяo�������̓o�^
	//glfwSetWindowSizeCallback(window, reshape);
	reshape(window, DISP_X,DISP_Y);

	glfwSetFramebufferSizeCallback(window, reshape);

	//���b�V���V�F�[�_�[�p
	CLight::getLight(0)->setDir(CVector3(LIGHT_SET_DIR).GetNormalize());
	CLight::getLight(0)->setColor(CVector3(LIGHT_SET_AMB), CVector3(LIGHT_SET_COL));

	//���C�g�̐ݒ�
	//�Œ�V�F�[�_�[�p
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	static GLfloat lightPosition[4] = { LIGHT_POS }; //�����̈ʒu

	//static GLfloat lightDiffuse[3] = { 1.0, 1.0, 1.0 }; //�g�U��
	//static GLfloat lightAmbient[3] = { 0.25, 0.25, 0.25 }; //����
	//static GLfloat lightSpecular[3] = { 1.0, 1.0, 1.0 }; //���ʌ�
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		reshape(window, winX,winY);

		idle();
		/* Render here */
		//		glClear(GL_COLOR_BUFFER_BIT);

//		display();
		/*�}�E�X�擾*/
		double mx, my;
		glfwGetCursorPos(window, &mx, &my);
		mx = mx - winX / 2;
		my = -my + winY / 2;
		CMouse::GetInstance()->mPos = CVector2(mx, my);

		/*�N���b�N����Ă���*/
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)){
			if (!CMouse::GetInstance()->mLeftFlag)CMouse::GetInstance()->mOneLeftFlag = true;//��񂾂��L��
			else CMouse::GetInstance()->mOneLeftFlag = false;//��񂾂��L��
			CMouse::GetInstance()->mLeftFlag = true;//�����ƗL��
		}
		else{
			CMouse::GetInstance()->mLeftFlag = false;
			CMouse::GetInstance()->mOneLeftFlag = false;//��񂾂��L��
		}

		/*window���W�擾*/
		glfwGetWindowPos(window, &WinPosX, &WinPosY);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
