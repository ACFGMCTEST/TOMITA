#include "CMouse.h"
#include "../../Define/Define.h"

CVector2 CMouse::mPos = CVector2();
bool CMouse::mLeftFlag = false;
bool CMouse::mOneLeftFlag = false;
bool CMouse::mClipFlag = true;
CRectangle2 CMouse::mRect;

GLFWwindow *CMouse::window;
/*サイズ*/
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
	SetCursorPos(x, y);//カーソルをウィンドウの中心にする ディスプレイ座標
	x = x - (WinPosX + DISP_X / 2);//調整
	y = y - (WinPosY + DISP_Y / 2);//調整
	CMouse::mPos = CVector2(x, y); //OpenGLのウインドウ座標に設定

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

	/*マウス取得*/
	//if(mClipFlag)ClipCursor(&winRect);//画面制御
	ShowCursor(false);
	mRect.position = mPos;
}

void CMouse::Render(){
	mRect.Render();
}

void CMouse::Access(GLFWwindow *win){
	window = win;
}