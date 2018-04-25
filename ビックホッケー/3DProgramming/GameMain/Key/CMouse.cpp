#include "CMouse.h"
#include "../../Define/Define.h"




/*サイズ*/
#define RECT_SIZE -100.0f, 100.0f, 100.0f, -100.0f

CMouse* CMouse::mpMouse = 0;


//GetInstance
CMouse* CMouse::GetInstance() {
	if (mpMouse == 0) {
		mpMouse = new CMouse();
	}
	return mpMouse;
}
/*コンストラクタ*/
CMouse::CMouse()
{
	mRect.SetVertex(RECT_SIZE);
	mRect.SetColor(WHITE_COLOR);
}
/*デストラクタ*/
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


	winRect.left	=  WinPosX;
	winRect.right	= (WinPosX + DISP_X);
	winRect.top		=  WinPosY;
	winRect.bottom	= (WinPosY + DISP_Y);

	/*マウス取得*/
	ShowCursor(false);
	mRect.position = mPos;
}

void CMouse::Render(){
	mRect.Render();
}
