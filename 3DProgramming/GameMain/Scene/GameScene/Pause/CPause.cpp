//高橋弘樹　&& 冨田健斗　
#include"CPause.h"
#include "../../../Graphic/CTexture.h"
#include "../../../Key/CKey.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CMouse.h"
#include "../../GameScene/UI/CScoreBoard.h"
#include "../../../Collision/CCollision2D.h"
#include <fstream> 
#include<stdio.h>
#include <Windows.h>

/*サイズ*/
#define BG_SIZE -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y
#define TITLE_SIZE -200.0f, 80.0f, 200.0f, -80.0f
#define BUTTON_SIZE -189.0f, 72.0f, 189.0f, -72.0f
#define GAME_STATE_SIZE -120.0f, -80.0f, 120.0f, -140.0f
#define GAME_EXIT_SIZE - 120.0f, -160.0f, 120.0f, -220.0f
#define PAUSE_LOGO	  0,0,400,160
#define PAUSE_MENU_LOGO	  0,0,420,160
/*texフェイル*/
#define CURSOR_CG 0,0,150,120


bool CPause::mSceneChangeFlag = false;//シーンが変わるフラグ
bool CPause::mGoTitle = false;
bool CPause::mBackGame = false;

CPause::~CPause(){
	if (mpTexture) {
		//テクスチャを使っていればインスタンス削除
		delete mpTexture;
		mpTexture = 0;
	}

}

void CPause::Init(){
	mSceneChangeFlag = false;
	mGoTitle = false;
	mBackGame = false;
	//背景の呼び出し

	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"Cle_ar.tga");

	mBG.SetVertex(BG_SIZE); //ここで大きさ変更
	mBG.SetColor(B_COLOR, 0.5f);
	mBG.SetUv(mpTexture, TEST_CG);


	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"Pause.tga");

	//ポーズロゴの呼び出し
	
	mPauseLogo.SetVertex(TITLE_SIZE); //ここで大きさ変更
	mPauseLogo.SetColor(W_COLOR, 1.0f);
	mPauseLogo.position = CVector2(0, DISP_2D_Y / 2);
	mPauseLogo.SetUv(mpTexture, PAUSE_LOGO);



	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"Resume.tga");

	//ゲームへ戻るの呼び出し

	mBack.SetVertex(BUTTON_SIZE); //ここで大きさ変更
	mBack.SetColor(W_COLOR, 1.0f);
	mBack.position = CVector2(0, -50);
	mBack.SetUv(mpTexture, PAUSE_MENU_LOGO);




	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"Quit.tga");

	//タイトルへ戻るの呼び出し

	mTitleBack.SetVertex(BUTTON_SIZE); //ここで大きさ変更
	mTitleBack.SetColor(W_COLOR, 1.0f);
	mTitleBack.position = CVector2(0, -180);
	mTitleBack.SetUv(mpTexture, PAUSE_MENU_LOGO);


	/*カーソル四角作成*/
	mpTexCursor = new CTexture();
	mpTexCursor->load(TGA_FILE"cursor.tga");
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(mpTexCursor, CURSOR_CG);


}




void CPause::Update(){

	//ゲームへ戻る
	if (CCollision2D::Collision2D(mCursor, mBack)){ //カーソルがあっている?
		mBack.SetColor(GRAY_COLOR);
		if (CMouse::mOneLeftFlag)//マウス左クリック
		mBackGame = true;
	}
	else{
		mBack.SetColor(W_COLOR, 1.0f);
	}
	//タイトルへ移動
	if (CCollision2D::Collision2D(mCursor, mTitleBack)){ //カーソルがあっている?
		mTitleBack.SetColor(GRAY_COLOR);
		if (CMouse::mOneLeftFlag){//マウス左クリック
			//CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);
			mSceneChangeFlag = true;
		}
	}
	else{
		mTitleBack.SetColor(W_COLOR, 1.0f);
	}
	mCursor.position = CMouse::mPos;
};

/*
描画処理のみを行う。
*/
void CPause::Render() {

	CRectangle2::Disp2D_Start();//2D処理開始

	/*この場所に描画処理を入れる*/
	mBG.Render();
	mPauseLogo.Render();
	mTitleBack.Render();
	mBack.Render();
	mCursor.Render();

	/*描画終了*/

	CRectangle2::Disp2D_Exit();//2D処理終了

}