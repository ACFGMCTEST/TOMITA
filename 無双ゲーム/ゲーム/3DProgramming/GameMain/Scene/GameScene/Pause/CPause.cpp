#include"CPause.h"
#include "../../../Key/CKey.h"

CPause *CPause::mpPause = 0;

//GetInstance
CPause* CPause::GetInstance() {
	if (mpPause == 0) {
		mpPause = new CPause();
	}
	return mpPause;
}


CPause::~CPause() {

}

CPause::CPause() : mPauseFlag(false){
#define BUTTON_SET(x,y,py) CVector2(x,y),\
 CVector2(DISP_2D_X - x/2,DISP_2D_Y/2 * py - y/2)  //ポジション
	//Cursor設定
	mCursor.SetVerPos(BUTTON_SET(70,70,0));
	//ポーズ画面
	mPause.SetVerPos(BUTTON_SET(570, 70, 3));
	//メインにもどる
	mMainBack.SetVerPos(BUTTON_SET(370, 70, 2));
	//タイトルに戻る
	mCursor.SetVerPos(BUTTON_SET(370, 70, 1));

}

/*更新処理*/
void CPause::Update() {
	//エスケープキーで切り替え
	if (CKey::once(VK_ESCAPE)) {
		if (mPauseFlag) mPauseFlag = false;
		else mPauseFlag = true;
	}

};
/*
描画処理のみを行う。
*/
void CPause::Render() {

	CRectangle2::Disp2D_Start();//2D処理開始

	if (mPauseFlag) {
		mCursor.Render();
		mPause.Render();//ポーズ画面
		mMainBack.Render();//メインに戻る
		mTitleBack.Render();
	}
	
	CRectangle2::Disp2D_Exit();//2D処理終了

}