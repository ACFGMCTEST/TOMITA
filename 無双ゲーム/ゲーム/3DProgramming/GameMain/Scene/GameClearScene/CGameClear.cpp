#include"CGameClear.h"
#include "../../Graphic/CTexture.h"
#include "../../Key/CKey.h"
#include "../../../Define/Define.h"
#include "../../Key/CMouse.h"
#include <fstream> 
#include<stdio.h>
#include <Windows.h>

/*サイズ*/
#define BG_SIZE -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y
#define TITLE_SIZE -200.0f, 80.0f, 200.0f, -80.0f
#define GAME_STATE_SIZE -120.0f, -80.0f, 120.0f, -140.0f
#define GAME_EXIT_SIZE - 120.0f, -160.0f, 120.0f, -220.0f


CGameClear::~CGameClear(){

}

void CGameClear::Init(){
	//背景の呼び出し
	mBG.SetVertex(BG_SIZE); //ここで大きさ変更
	mBG.SetColor(NO_A_WHITE_COLOR, 0.0f);
	mBG.SetUv(&mTexBG, TEST_CG);


	//クリアロゴの呼び出し
	mClearLogo.SetVertex(TITLE_SIZE); //ここで大きさ変更
	mClearLogo.SetColor(NO_A_WHITE_COLOR, 0.0f);
	mClearLogo.mPosition = CVector2(0.0f, 200);
	mClearLogo.SetUv(&mTexClearLogo, TEST_CG);


}




void CGameClear::Update(){

};

/*
描画処理のみを行う。
*/
void CGameClear::Render() {

	CRectangle2::Disp2D_Start();//2D処理開始

	/*この場所に描画処理を入れる*/
	mBG.Render();
	mClearLogo.Render();
	/*描画終了*/

	CRectangle2::Disp2D_Exit();//2D処理終了

}