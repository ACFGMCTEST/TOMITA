#include "CMouse.h"
#include "../../Define/Define.h"




GLFWwindow *CMouse::window;
/*�T�C�Y*/
#define RECT_SIZE -100.0f, 100.0f, 100.0f, -100.0f

CMouse* CMouse::mpMouse = 0;


//GetInstance
CMouse* CMouse::GetInstance() {
	if (mpMouse == 0) {
		mpMouse = new CMouse();
	}
	return mpMouse;
}
/*�R���X�g���N�^*/
CMouse::CMouse()
{
	mRect.SetVertex(RECT_SIZE);
	mRect.SetColor(WHITE_COLOR);
}
/*�f�X�g���N�^*/
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
	winRect.bottom = 0;*/


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