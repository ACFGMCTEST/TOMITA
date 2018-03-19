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
	mSceneChangeFlag = false;
	mGoTitle = false;
	mBackGame = false;
	mOperationFlag = false;
	//背景の呼び出し
	mTexFilter.load(TEX_FILTER);
	mBG.SetVertex(BG_SIZE); //ここで大きさ変更
	mBG.SetColor(B_COLOR, 0.5f);
	mBG.SetUv(&mTexFilter, FILTER_CG);
	//ポーズロゴの呼び出し
	mTexPauze.load(TEX_PAUZE);
	mPauseLogo.SetVertex(TITLE_SIZE); //ここで大きさ変更
	mPauseLogo.SetColor(W_COLOR, 1.0f);
	mPauseLogo.position = POS_PAUZE;
	mPauseLogo.SetUv(&mTexPauze, PAUSE_LOGO_CG);
	//ゲームへ戻るの呼び出し
	mTexResume.load(TEX_RESUME);
	mBackButton.SetVertex(BUTTON_SIZE); //ここで大きさ変更
	mBackButton.SetColor(W_COLOR, 1.0f);
	mBackButton.position = POS_BACK_BUTTON;
	mBackButton.SetUv(&mTexResume, PAUSE_MENU_LOGO_CG);
	//タイトルへ戻るの呼び出し
	mTexQuit.load(TEX_QUIT);
	mTitleBackButton.SetVertex(BUTTON_SIZE); //ここで大きさ変更
	mTitleBackButton.SetColor(W_COLOR, 1.0f);
	mTitleBackButton.position = POS_TITLE_BACK_BUTTON;
	mTitleBackButton.SetUv(&mTexQuit, PAUSE_MENU_LOGO_CG);
	/*操作ボタン作成*/
	mTexGuideButton.load(TEX_GUIDE);
	mGuideButton.SetVertex(BUTTON_SIZE);
	mGuideButton.position = POS_GUIDE_BUTTON;
	mGuideButton.SetUv(&mTexGuideButton, PAUSE_MENU_LOGO_CG);
	/*カーソル四角作成*/
	mTexCursor.load(TEX_CURSOR);
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(&mTexCursor, CURSOR_CG);
	/*操作説明作成*/
	mTexOperation.load(TEX_OPERA);
	mOperation.SetVertex(BG_SIZE);
	mOperation.SetUv(&mTexOperation, OPERA_CG);


}




void CPause::Update(){
	/*Operationが出ている場合*/
	if (mOperationFlag){
		/*右クリックを押した場合 || エンターボタンを押した場合*/
		if (CMouse::GetInstance()->mOneLeftFlag || CKey::once(VK_RETURN)){
			mOperationFlag = false;
		}
	}
	else{
		//ゲームへ戻る
		if (CCollision2D::Collision2D(mCursor, mBackButton)){ //カーソルがあっている?
			mBackButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag)//マウス左クリック
				mBackGame = true;
		}
		else{
			mBackButton.SetColor(W_COLOR, 1.0f);
		}
		//タイトルへ移動
		if (CCollision2D::Collision2D(mCursor, mTitleBackButton)){ //カーソルがあっている?
			mTitleBackButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag){//マウス左クリック
				//CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);
				mSceneChangeFlag = true;
			}
		}
		else{
			mTitleBackButton.SetColor(W_COLOR, 1.0f);
		}
		//操作説明
		if (CCollision2D::Collision2D(mCursor, mGuideButton)){ //カーソルがあっている?
			mGuideButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag){//マウス左クリック
				//CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);
				mOperationFlag = true;
			}
		}
		else{
			mGuideButton.SetColor(W_COLOR, 1.0f);
		}
	}

	mCursor.position = CMouse::GetInstance()->mPos;
};

/*
描画処理のみを行う。
*/
void CPause::Render() {

	CRectangle2::Disp2D_Start();//2D処理開始

	/*この場所に描画処理を入れる*/
	mBG.Render();
	mPauseLogo.Render();
	mTitleBackButton.Render();
	mGuideButton.Render();
	mBackButton.Render();
	if (mOperationFlag)mOperation.Render();//フラグ建てっているときのみ
	mCursor.Render();


	/*描画終了*/

	CRectangle2::Disp2D_Exit();//2D処理終了

}