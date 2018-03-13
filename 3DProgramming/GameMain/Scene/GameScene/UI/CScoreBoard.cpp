//高橋弘樹
#include"CScoreBoard.h"
#include"../../../Key/CKey.h"
#include"../../../Key/CMouse.h"
#include <fstream> 
#include <time.h>
#include<stdio.h>
#include"../../CSceneManager.h"
#define DISP_2D_Y 768 //縦幅

#define BACK_GROUND     -400.0f, 300.0f, 400.0f, -300.0f
////////////////////////////////////////////////////////////////
#define ZERO	 SetUv(mpNumber,   0,   0,  100, 100);
#define ONE		 SetUv(mpNumber, 100,   0,  200, 100);
#define TWO		 SetUv(mpNumber, 200,   0,  300, 100);
#define THREE	 SetUv(mpNumber, 300,   0,  400, 100);
#define FOUR	 SetUv(mpNumber, 400,   0,  500, 100);
#define FIVE	 SetUv(mpNumber, 500,   0,  600, 100);
#define SIX		 SetUv(mpNumber, 600,   0,  700, 100);
#define SEVEN	 SetUv(mpNumber, 700,   0,  800, 100);
#define EIGHT	 SetUv(mpNumber, 800,   0,  900, 100);
#define NINE	 SetUv(mpNumber, 900,   0, 1000, 100);

////////////////////////////////////////////////////////////////
//ポジション等の座標情報

#define NAME_SET	 mpTexture, 0, 0, 400, 200

#define VS_SET	 mpTexture, 0, 0, 400, 400

#define S1_EFFECT_SET	 mpTexture, 0, 0, 800, 600
#define S1_EFFECT_SIZE -DISP_X/2,DISP_Y/2,DISP_X/2,-DISP_Y/2

#define	S1_COLOR mSkillCollarR,mSkillCollarG, mSkillCollarB	//フェード処理用アルファはフロートで適当に入れてください

////////////////////////////////////////////////////////////////
#define P_NAME_POS   CVector2(-280, 280)

#define P_SCORE_SET -mcDefaultNumX, mcDefaultNumY, mcDefaultNumX, -mcDefaultNumY

//#define P_SCORE_SET -20.0f*mNumSizeLimit, 17.5f*mNumSizeLimit, 20.0f*mNumSizeLimit, -17.5f*mNumSizeLimit


#define P_SCORE_POS2 CVector2(-140, 260)
#define P_SCORE_POS1 CVector2(-100, 260)

#define SCORE_BPOS3  CVector2(-200, 110)

#define PSCORE_BPOS2 CVector2(-270, 110)
#define PSCORE_BPOS1 CVector2(-150, 110)

#define ESCORE_BPOS2 CVector2( 150, 110)
#define ESCORE_BPOS1 CVector2( 270, 110)

////////////////////////////////////////////////////////////////
#define E_NAME_POS   CVector2( 280, 270)


#define E_SCORE_POS2 CVector2( 100, 260)
#define E_SCORE_POS1 CVector2( 140, 260)

#define E_SCORE_SET -mcDefaultNumX, mcDefaultNumY, mcDefaultNumX, -mcDefaultNumY
////////////////////////////////////////////////////////////////

//その他
#define GAGE_ICON	      -20.0f,  40.0f, 20.0f,   -40.0f
#define BACK_BUTTON		 -320.0f, -180.0f, -220.0f, -240.0f

#define VS_POS   CVector2( 0, 270)

#define HYPHEN		      -50.0f, 25.0f,  50.0f, -25.0f


#define FIRST_X	100			//アイコンの初期ｘ値
#define FIRST_Y	180		//アイコンの初期ｙ値
#define RECT_WIDE 3
#define REFRESH 0.0f

#define ITEM_MENU	  TGA_FILE"itembutton.tga"
#define BACK	  TGA_FILE"backbutton.tga"


CScoreBoard *CScoreBoard::mSceneManager;

int CScoreBoard::mPlayerScore = 0;
int CScoreBoard::mEnemyScore =  0;

bool CScoreBoard::mGameEnd = false;

bool CScoreBoard::mcFirstAction = true;

float CScoreBoard::skillgage = 0.0f;

bool CScoreBoard::mFlagSkill0 = false;

bool CScoreBoard::mResult = false;


CScoreBoard::CScoreBoard() :rectnum(0), effectalpha(0), mAlpha(mcAlphaMin), mFlagSceneChage(false), mFlash(0), mInit(false), mNumMin(false){

}

CScoreBoard::~CScoreBoard(){
	if (mpTexture) {
		//テクスチャを使っていればインスタンス削除
		delete mpTexture;
		mpTexture = nullptr;
	}
	if (mpNumber) {
		//テクスチャを使っていればインスタンス削除
		delete mpNumber;
		mpNumber = nullptr;
	}
	if (mpFrame) {
		//テクスチャを使っていればインスタンス削除
		delete mpFrame;
		mpFrame = nullptr;
	}
	if (mpLighting) {
		//テクスチャを使っていればインスタンス削除
		delete mpLighting;
		mpLighting = nullptr;
	}
	if (mpHyphen) {
		//テクスチャを使っていればインスタンス削除
		delete mpHyphen;
		mpHyphen = nullptr;
	}
}

//GetInstance
CScoreBoard* CScoreBoard::GetInstance(){
	if (mSceneManager == 0) {
		mSceneManager = new CScoreBoard();
	}
	return mSceneManager;
}

void CScoreBoard::Init(){
	srand((unsigned)time(NULL));
	mGoalManager = E_NORMAL;
	skillgage = REFRESH;
	mcFirstAction = true;
	/*初期化*/
	mGameClear .Init();
	mGameOver  .Init();
	mGameResult.Init();
	mCountDown .Init();
	mTutorial.Init();


	//mSkillEffect
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"SkillEffect1.tga");	//テクスチャファイル読み込み
	mSkillEffect.SetVertex(S1_EFFECT_SIZE); //ここで大きさ変更
	mSkillEffect.SetColor(S1_COLOR, 0.8f);
	mSkillEffect.SetUv(S1_EFFECT_SET);



	//プレイヤーネーム
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"P_Name.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mPlayer.SetVertex(-120.0f, 60.0f, 120.0f, -60.0f);
	mPlayer.SetColor(WHITE_COLOR);
	mPlayer.position = P_NAME_POS;
	mPlayer.SetUv(NAME_SET);

	//エネミ―ネーム
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"E_Name.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mEnemy.SetVertex(-110.0f, 50.0f, 110.0f, -50.0f);
	mEnemy.SetColor(WHITE_COLOR);
	mEnemy.position = E_NAME_POS;
	mEnemy.SetUv(NAME_SET);


	//VSマーク
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"vs.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mVs.SetVertex(-80.0f,80.0f, 80.0f, -80.0f);
	mVs.SetColor(WHITE_COLOR);
	mVs.position = VS_POS;
	mVs.SetUv(VS_SET);
	///////////////////////////////////////////////////////////////////////////////////////

	//プレイヤースコア

	///////////////////////////////////////////////////////////////////////////////////////


	//2桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mPlScore2.SetVertex(P_SCORE_SET);
	mPlScore2.SetColor(WHITE_COLOR);
	mPlScore2.position = P_SCORE_POS2;
	mPlScore2.ZERO;

	//1桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mPlScore1.SetVertex(P_SCORE_SET);
	mPlScore1.SetColor(WHITE_COLOR);
	mPlScore1.position = P_SCORE_POS1;
	mPlScore1.ZERO;

	/////////////////////////////////////////////////////////////////////
	//エネミ―スコア
	/////////////////////////////////////////////////////////////////////


	//2桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mEnScore2.SetVertex(E_SCORE_SET);
	mEnScore2.SetColor(WHITE_COLOR);
	mEnScore2.position = E_SCORE_POS2;
	mEnScore2.ZERO;

	//1桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mEnScore1.SetVertex(E_SCORE_SET);
	mEnScore1.SetColor(WHITE_COLOR);
	mEnScore1.position = E_SCORE_POS1;
	mEnScore1.ZERO;

	/////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////

	//スキルゲージ
	mpGauge = new CTexture();	//テクスチャクラスのインスタンス作成
	mpGauge->load(TGA_FILE"gauge.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mSkillGauge.SetVertex(-skillgage, 0.0f, 0.0f, -50.0f);
	mSkillGauge.SetColor(WHITE_COLOR);
	mSkillGauge.position = CVector2(147, -220);
	mSkillGauge.SetUv(mpGauge, 0, 0, skillgage, 50);


	mSkillGaugeBack.SetVertex(0, 0.0f, 200.0f, -50.0f);
	mSkillGaugeBack.SetColor(DARK_GRAY_COLOR);
	mSkillGaugeBack.position = CVector2(147, -220);
	mSkillGaugeBack.SetUv(mpGauge, 0, 0, 200, 50);

	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	
	//frame
	mpFrame = new CTexture();	//テクスチャクラスのインスタンス作成
	mpFrame->load(TGA_FILE"frame.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mGaugeFrame.SetVertex(0.0f, 50.0f, 350, -50.0f);
	mGaugeFrame.SetColor(WHITE_COLOR);
	mGaugeFrame.position = CVector2(90, -240);
	mGaugeFrame.SetUv(mpFrame, 0, 0, 350, 100);

	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	//フレームライト
	mpLighting = new CTexture();	//テクスチャクラスのインスタンス作成
	mpLighting->load(TGA_FILE"lighting.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mFrameLighting.SetVertex(-mLightingSize, mLightingSize, mLightingSize, -mLightingSize);
	mFrameLighting.SetColor(W_COLOR, mcAlphaMin);
	mFrameLighting.position = CVector2(360, -238);
	mFrameLighting.SetUv(mpLighting, 0, 0, 200, 200);

	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////

	//ハイフン
	mpHyphen = new CTexture();	//テクスチャクラスのインスタンス作成
	mpHyphen->load(TGA_FILE"hyphen.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mHyphen.SetVertex(HYPHEN);
	mHyphen.SetColor(W_COLOR, 1.0f);
	mHyphen.position = CVector2(0, 110);
	mHyphen.SetUv(mpHyphen, 0, 0, 400, 200);

	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////

	///*カーソル四角作成*/
	//mCursor.SetVertex(CURSOR_SIZE);
	//mCursor.SetColor(WHITE_COLOR);

	//mPlScore3.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_RED_BLUE);

	status = 0;//デフォルトで0
	/*シーンチェンジフラグ初期化*/
	mFlagSceneChage = false;

	/*ポイント初期化*/
	mEnemyScore = 0;
	mPlayerScore = 0;
	/*クリアフラグ初期化*/
	mGameEnd = false;

	/*グラデーション用意*/
	mEnScore1.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_RED_PURPLE);
	mEnScore2.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_RED_PURPLE);
	mEnScore3.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_RED_PURPLE);

	mPlScore1.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_CYAN_GREEN);
	mPlScore2.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_CYAN_GREEN);
	mPlScore3.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_CYAN_GREEN);

}


//数字のテクスチャ設定を行う
void CScoreBoard::Number(int score, CRectangle2 &odifit, CRectangle2 &twdifit, CRectangle2 &thdifit){		//数字の処理

	//スコアを100で割ることで3桁目を取得
	difit3 = score / 100;
	//スコアを 10で割ることで2桁目を取得
	difit2 = (score - (difit3 * 100)) / 10;
	//スコアを  1で割ることで1桁目を取得
	difit1 = score - ((difit3 * 100) + (difit2 * 10));

	//３ケタ目
	//どの数字が結果として出たかで処理を変える
	//０～９
	if (difit3 <= 0){
		thdifit.ZERO;
	}
	if (difit3 == 1){
		thdifit.ONE;
	}
	if (difit3 == 2){
		thdifit.TWO;
	}
	if (difit3 == 3){
		thdifit.THREE;
	}
	if (difit3 == 4){
		thdifit.FOUR;
	}
	if (difit3 == 5){
		thdifit.FIVE;
	}
	if (difit3 == 6){
		thdifit.SIX;
	}
	if (difit3 == 7){
		thdifit.SEVEN;
	}
	if (difit3 == 8){
		thdifit.EIGHT;
	}
	if (difit3 == 9){
		thdifit.NINE;
	}



	//2ケタ目
	//どの数字が結果として出たかで処理を変える
	//０～９
	if (difit2 <= 0){
		twdifit.ZERO;
	}
	if (difit2 == 1){
		twdifit.ONE;
	}
	if (difit2 == 2){
		twdifit.TWO;
	}
	if (difit2 == 3){
		twdifit.THREE;
	}
	if (difit2 == 4){
		twdifit.FOUR;
	}
	if (difit2 == 5){
		twdifit.FIVE;
	}
	if (difit2 == 6){
		twdifit.SIX;
	}
	if (difit2 == 7){
		twdifit.SEVEN;
	}
	if (difit2 == 8){
		twdifit.EIGHT;
	}
	if (difit2 == 9){
		twdifit.NINE;
	}


	//1ケタ目
	//どの数字が結果として出たかで処理を変える
	//０～９
	if (difit1 <= 0){
		odifit.ZERO;
	}
	if (difit1 == 1){
		odifit.ONE;
	}
	if (difit1 == 2){
		odifit.TWO;
	}
	if (difit1 == 3){
		odifit.THREE;
	}
	if (difit1 == 4){
		odifit.FOUR;
	}
	if (difit1 == 5){
		odifit.FIVE;
	}
	if (difit1 == 6){
		odifit.SIX;
	}
	if (difit1 == 7){
		odifit.SEVEN;
	}
	if (difit1 == 8){
		odifit.EIGHT;
	}
	if (difit1 == 9){
		odifit.NINE;
	}

}

void CScoreBoard::Update(){
	/*デバック用*/
	if (CKey::once('U')){
		GoalEnemy();
	}
	switch (mGoalManager)
	{
	case E_NORMAL:
		mPlScore2.SetColor(WHITE_COLOR);
		mPlScore1.SetColor(WHITE_COLOR);

		mPlScore2.SetVertex(P_SCORE_SET);
		mPlScore1.SetVertex(P_SCORE_SET);

		mPlScore2.position = P_SCORE_POS2;
		mPlScore1.position = P_SCORE_POS1;

		mEnScore2.SetColor(WHITE_COLOR);
		mEnScore1.SetColor(WHITE_COLOR);

		mEnScore2.SetVertex(E_SCORE_SET);
		mEnScore1.SetVertex(E_SCORE_SET);

		mEnScore2.position = E_SCORE_POS2;
		mEnScore1.position = E_SCORE_POS1;

		mInit = false;

		break;
	case E_PLAYER:
		NumberUpdate(mPlScore2, mEnScore2, PSCORE_BPOS2, ESCORE_BPOS2);
		NumberUpdate(mPlScore1, mEnScore1, PSCORE_BPOS1, ESCORE_BPOS1);
		break;
	case E_ENEMY:
		NumberUpdate(mEnScore2, mPlScore2, ESCORE_BPOS2, PSCORE_BPOS2);
		NumberUpdate(mEnScore1, mPlScore1, ESCORE_BPOS1, PSCORE_BPOS1);
		break;

	default:

		break;
	}

	/*
	変数によって形変える四角形の更新処理
	*/

	//フレームのライティングに変数を持たせて伸縮自在にする。
	mFrameLighting.SetVertex(-mLightingSize, mLightingSize, mLightingSize, -mLightingSize);

	mFrameLighting.SetColor(1.0f, 1.0f, 1.0f, mAlpha);

	mSkillGauge.SetVertex(-2.0f, 0.0f, skillgage, -50.0f);

	mSkillGauge.SetUv(mpGauge, 0, 0, skillgage, 50);

	mBackButton.SetColor(WHITE_COLOR);		   //白色

	////カーソルのポジション
	//mCursor.position = CMouse::mPos;



	if (mFlagSkill0){
		mSkillEffect.SetColor(S1_COLOR, 0.8f);

		if (!mSkillCollarUnder){
			mSkillCollarR -= 0.01f;
			mSkillCollarG -= 0.01f;

			if (mSkillCollarR <= 0.7f){
				mSkillCollarUnder = true;
			}
		}
		else{
			mSkillCollarR += 0.01f;
			mSkillCollarG += 0.01f;
			if (mSkillCollarR >= 1.0f){
				mSkillCollarUnder = false;
			}
		}
	}
	else if (!mFlagSkill0){
		mSkillCollarR = 1.00f;
		mSkillCollarG = 1.00f;
	}

	//スキルゲージが溜まった時の点滅処理
	if (skillgage >= mcGageLimit || mFlagSkill0 == true)
	{
		if (mLightingSize <= 130.0f){
			mLightingSize += 1.0f;
			mAlpha -= 0.02f;
		}
		else{
			mLightingSize = mcLightingBoxSize;
			mAlpha = mcAlphaMax;
		}

	}
	else{
		mLightingSize = mcLightingBoxSize;
		mAlpha = mcAlphaMin;
	}

	//ファーストアクションでカウントダウンを行う。
	if (mcFirstAction){ mCountDown.Update(); }
	//チュートリアル*/
	else{mTutorial.Update();	}

	//Zゲームオーバーとゲームクリアをアップデート
	mGameOver.Update();
	mGameClear.Update();
	if (mResult){
		mGameResult.Update();
	}
};



/*
描画処理のみを行う。
*/
void CScoreBoard::Render() {
	CRectangle2::Disp2D_Start();//描画開始

	if (mFlagSkill0){
		mSkillEffect.Render();
	}

	mPlScore1.Render();
	mPlScore2.Render();

	mEnScore1.Render();
	mEnScore2.Render();

	mPlayer.Render();
	mEnemy.Render();
	mVs.Render();

	mSkillGaugeBack.Render();
	mSkillGauge.Render();
	mGaugeFrame.Render();
	mFrameLighting.Render();

	if (mGoalManager != E_NORMAL){
		mHyphen.Render();
	}

	//mCursor.Render();

	if (mcFirstAction){ mCountDown.Render(); }
	//チュートリアル*/
	else{ mTutorial.Render(); }

	mGameOver.Render();
	mGameClear.Render();
	mGameResult.Render();

	

	CRectangle2::Disp2D_Exit();//描画終了







}

//とりあえずこの中で使えればいい関数
void CScoreBoard::NumberUpdate(CRectangle2 &WinScore, CRectangle2 &LoseScore, CVector2 WinPos, CVector2 LosePos){
	//呼び出された時の初期動作　サイズを中央表示用に変更する
	if (!mInit){
		mNumRectX = mcDefaultNumX*mcNumSizeLimit;
		mNumRectY = mcDefaultNumY*mcNumSizeLimit;
		mInit	  = true;
		mNumMin	  = false;
	}
	//拡大された数値の縦幅を縮小する。
	if (mNumRectY > 0&&!mNumMin){
		mNumRectY -= 0.7f;
	}
	else{
		//最小値になった
		mNumMin = true;
	}
	//数値を更新する。
	if (mNumMin && mNumRectY< mcDefaultNumY*mcNumSizeLimit){

		Number(mPlayerScore, mPlScore1, mPlScore2, mPlScore3);
		Number(mEnemyScore, mEnScore1, mEnScore2, mEnScore3);
		
		mNumRectY += 1.0f;
	}
	else if(mNumMin){
		mGoalManager = E_NORMAL;
	}

	WinScore.SetVertex(-mNumRectX, mNumRectY, mNumRectX, -mNumRectY);
	LoseScore.SetVertex(-mcDefaultNumX*mcNumSizeLimit, mcDefaultNumY*mcNumSizeLimit, mcDefaultNumX*mcNumSizeLimit, -mcDefaultNumY*mcNumSizeLimit);

	WinScore.position = WinPos;
	LoseScore.position = LosePos;


	mColorChange = rand() % 5;


	/*グラデーション用意*/
	WinScore.GradationLoop(mcLoopSpeed);
}

/*当たり判定
ゴール判定　自分
*/
void CScoreBoard::GoalPlayer(){
	/*当たったよ*/
	if (mGameEnd == false){
		mGoalManager = E_ENEMY;
		mEnemyScore += 10;
	}

}
/*当たり判定
ゴール判定　相手
*/
void CScoreBoard::GoalEnemy(){
	/*当たったよ*/
	if (mGameEnd == false){
		mGoalManager = E_PLAYER;
		mPlayerScore += 10;
	}

}