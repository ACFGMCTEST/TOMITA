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


CSceneManager Main;

int WinPosX, WinPosY;
/* display�֐�
1�b�Ԃ�60����s�����
*/
void display() {
	//�e�o�b�t�@�[���N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Main.SceneMain();

	CMouse::GetInstance()->Update();
}


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

	glMatrixMode(GL_PROJECTION);		//�s����v���W�F�N�V�������[�h�֕ύX
	glLoadIdentity();
	gluPerspective(75.0, (double)width / (double)height, 1.0, 2000.0);


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

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(DISP_X, DISP_Y, "BlowOffBlow", NULL, NULL);
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
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// �E�B���h�E�̃T�C�Y�ύX���ɌĂяo�������̓o�^
	
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

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		reshape(window, winX,winY);

		idle();
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
