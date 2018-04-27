#include "CMouse.h"
#include "../../Define/Define.h"

CVector2 CMouse::mPos = CVector2();
bool CMouse::mLeftFlag = false;
bool CMouse::mOneLeftFlag = false;
bool CMouse::mClipFlag = true;
CRectangle2 CMouse::mRect;

GLFWwindow *CMouse::window = 0;

float CMouse::mDirection = 0.0f;

/*�T�C�Y*/
#define RECT_SIZE -100.0f, 100.0f, 100.0f, -100.0f
CMouse::CMouse()
{
	mRect.SetVertex(RECT_SIZE);
	mRect.SetColor(WHITE_COLOR);
}

CMouse::~CMouse()
{
}

void CMouse::SetMousePos(float x, float y){
	SetCursorPos(x, y);//�J�[�\�����E�B���h�E�̒��S�ɂ��� �f�B�X�v���C���W
	x = x - (WinPosX + DISP_X / 2);//����
	y = y - (WinPosY + DISP_Y / 2);//����
	CMouse::mPos = CVector2(x, y); //OpenGL�̃E�C���h�E���W�ɐݒ�

}


void CMouse::Update(){
	

	RECT winRect;
/*
	winRect.left = 0;
	winRect.right = 0;
	winRect.top = 0;
	winRect.bottom = 0;
*/


	winRect.left	=  WinPosX;
	winRect.right	= (WinPosX + DISP_X);
	winRect.top		=  WinPosY;
	winRect.bottom	= (WinPosY + DISP_Y);

	/*�}�E�X�擾*/
	//if(mClipFlag)ClipCursor(&winRect);//��ʐ���
	ShowCursor(false);
	mRect.position = mPos;
}

void CMouse::Render(){
	mRect.Render();
}

void CMouse::Access(GLFWwindow *win){
	window = win;
}

extern int winX, winY;
void CMouse::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	float tmpx = xpos - winX / 2;
	bool lb = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
	if (mPos.x > tmpx && lb) {
		mDirection = 1.0f;
	}
	else if (mPos.x < tmpx && lb) {
		mDirection = -1.0f;
	}
	mPos.x = xpos - winX / 2;
	mPos.y = -ypos + winY / 2;
//	printf("%f, %f\n", mPos.x, mPos.y);
	return;

}

void CMouse::SetWindow(GLFWwindow* w) {
	window = w;
}

void CMouse::Update(GLFWwindow* window) {
	/*�}�E�X�擾*/
	double mx, my;
	glfwGetCursorPos(window, &mx, &my);
	mx = mx - winX / 2;
	my = -my + winY / 2;

	bool lb = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

	if (mPos.x > mx && lb) {
		mDirection = 1.0f;
	}
	else if (mPos.x < mx && lb) {
		mDirection = -1.0f;
	}

	mPos = CVector2(mx, my);
	ShowCursor(true);
	mRect.position = mPos;
//	printf("%f, %f\n", mPos.x, mPos.y);
	return;
}
