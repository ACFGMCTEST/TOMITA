#include"CGameOver.h"
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

CGameOver::~CGameOver(){

}

void CGameOver::Init(){
	CTexture t;//フィルター用
	//背景の描画設定
	mBG.SetVertex(BG_SIZE); //ここで大きさ変更
	mBG.SetColor(NO_A_WHITE_COLOR, mAlpha2);
	mBG.SetUv(&t, TEST_CG);
///////////////////////////////////////////////////////////////////
	//ゲームオーバーテクスチャの読み込み
	mTexOverLogo.load(TGA_FILE"GameOver.tga");
	//ゲームオーバーロゴの描画設定
	mGameOverLogo.SetVertex(TITLE_SIZE); //ここで大きさ変更
	mGameOverLogo.SetColor(NO_A_WHITE_COLOR, mAlpha);
	mGameOverLogo.mPosition = CVector2(0, DISP_2D_Y / 2);
	mGameOverLogo.SetUv(&mTexOverLogo, TEST_CG);
}

void CGameOver::Update(){

};

void CGameOver::Render() {
	CRectangle2::Disp2D_Start();//2D処理開始
	/*この場所に描画処理を入れる*/


	mBG.Render();
	mGameOverLogo.Render();


	/*描画終了*/
	CRectangle2::Disp2D_Exit();//2D処理終了
}