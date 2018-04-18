//高橋弘樹　&& 冨田健斗　
#include"CGameClear.h"
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
/*テクスチャ場所*/

CGameClear::~CGameClear(){

}

void CGameClear::Init(){
	//背景の呼び出し
	mBG.SetVertex(BG_SIZE); //ここで大きさ変更
	mBG.SetColor(W_COLOR,0.0f);
	//mBG.SetUv(&mTexBG, TEST_CG);


	//クリアロゴの呼び出し
	mTexClearLogo.load(TGA_FILE"Clear.tga");
	mClearLogo.SetVertex(TITLE_SIZE); //ここで大きさ変更
	mClearLogo.SetColor(W_COLOR, 0.0f);
	mClearLogo.position = CVector2(0.0f, 200);
	mClearLogo.SetUv(&mTexClearLogo, TEST_CG);


}




void CGameClear::Update(){
	if (CScoreBoard::mPlayerScore >= LIMIT_SCORE){
		CScoreBoard::mGameEnd = true;

		/*フェード*/
		mClearLogo.Fade(FADE_SPEED, ALPHA_MAX);
		mBG.Fade(FADE_SPEED, ALPHA_MAX);
		
		/*透明でなくなったら*/
		if (mBG.triangle1.a >= ALPHA_MAX){
			/*シーン移行をするフラグを立てる*/
			CGameResult::mFlagResult = true;
		}

	}
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