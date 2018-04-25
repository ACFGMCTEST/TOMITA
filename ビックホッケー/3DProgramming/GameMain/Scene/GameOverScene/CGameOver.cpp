//高橋弘樹　&& 冨田健斗　
#include"CGameOver.h"
#include "../../Graphic/CTexture.h"
#include "../../Key/CKey.h"
#include "../../../Define/Define.h"
#include "../../Key/CMouse.h"
#include "../GameScene/UI/CScoreBoard.h"
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
	//背景の描画設定
	mBG.SetVertex(BG_SIZE); //ここで大きさ変更
	mBG.SetColor(B_COLOR, mAlpha2);
	//mBG.SetUv(mpTexture, TEST_CG);
///////////////////////////////////////////////////////////////////
	//ゲームオーバーテクスチャの読み込み
	mTexLogo.load(TGA_FILE"GameOver.tga");
	//ゲームオーバーロゴの描画設定
	mGameOverLogo.SetVertex(TITLE_SIZE); //ここで大きさ変更
	mGameOverLogo.SetColor(W_COLOR, mAlpha);
	mGameOverLogo.position = CVector2(0, DISP_2D_Y / 2);
	mGameOverLogo.SetUv(&mTexLogo, TEST_CG);
}

void CGameOver::Update(){
	if (CScoreBoard::mEnemyScore >= LIMIT_SCORE){
		CScoreBoard::mGameEnd = true;
		/*フェード*/
		mGameOverLogo.Fade(FADE_SPEED, ALPHA_MAX);
		mBG.Fade(FADE_SPEED, ALPHA_MAX);

		/*透明でなくなったら*/
		if (mBG.triangle1.a >= ALPHA_MAX){
			/*シーン移行をするフラグを立てる*/
			CScoreBoard::GetInstance()->mFlagSceneChage = true;
		}
	}
};

void CGameOver::Render() {
	CRectangle2::Disp2D_Start();//2D処理開始
	/*この場所に描画処理を入れる*/


	mBG.Render();
	mGameOverLogo.Render();


	/*描画終了*/
	CRectangle2::Disp2D_Exit();//2D処理終了
}