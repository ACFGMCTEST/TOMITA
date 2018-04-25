#include"CPause.h"
#include "../../../Graphic/CTexture.h"
#include "../../../Key/CKey.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CMouse.h"
#include "../../../Collision/CCollision2D.h"
#include <fstream> 
#include<stdio.h>
#include <Windows.h>
/*ポジション*/
#define POS_PAUZE CVector2(0, DISP_2D_Y / 2)
#define POS_BACK_BUTTON CVector2(0, -30)
#define POS_GUIDE_BUTTON CVector2(0, -130)
#define POS_TITLE_BACK_BUTTON CVector2(0, -230)
/*サイズ*/
#define BG_SIZE -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y
#define TITLE_SIZE -200.0f, 80.0f, 200.0f, -80.0f
#define BUTTON_PERCENT 3
#define BUTTON_SIZE -400/BUTTON_PERCENT, 160.0f/BUTTON_PERCENT, 400.0f/BUTTON_PERCENT, -160.0f/BUTTON_PERCENT
#define GAME_STATE_SIZE -120.0f, -80.0f, 120.0f, -140.0f
#define GAME_EXIT_SIZE - 120.0f, -160.0f, 120.0f, -220.0f

/*texフェイル*/
#define FILTER_CG 0,0,10,10
#define PAUSE_LOGO_CG	  0,0,400,160
#define PAUSE_MENU_LOGO_CG	  0,0,420,160
#define CURSOR_CG 0,0,150,120
#define OPERA_CG 0,0,750,400
/*tga場所*/
#define TEX_FILTER			TGA_FILE"Pause\\filter.tga"
#define TEX_PAUZE			TGA_FILE"Pause\\pause.tga"
#define TEX_RESUME			TGA_FILE"Pause\\resume.tga"
#define TEX_QUIT			TGA_FILE"Pause\\quit.tga"
#define TEX_GUIDE			TGA_FILE"Pause\\guide.tga"
#define TEX_CURSOR			TGA_FILE"cursor.tga"
#define TEX_OPERA			TGA_FILE"Tutorial/allOperation.tga" 

bool CPause::mSceneChangeFlag = false;//シーンが変わるフラグ
bool CPause::mGoTitle = false;
bool CPause::mBackGame = false;
/*コンストラクタ*/
CPause::CPause():mOperationFlag(false){

}
/*デストラクタ*/
CPause::~CPause(){

}

void CPause::Init(){
	

}




void CPause::Update(){
	
};

/*
描画処理のみを行う。
*/
void CPause::Render() {

	CRectangle2::Disp2D_Start();//2D処理開始

	
	/*描画終了*/

	CRectangle2::Disp2D_Exit();//2D処理終了

}