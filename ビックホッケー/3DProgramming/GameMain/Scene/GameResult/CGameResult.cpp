//高橋弘樹　&& 冨田健斗　
#include"CGameResult.h"
#include "../../Graphic/CTexture.h"
#include "../../Key/CKey.h"
#include "../../../Define/Define.h"
#include "../../Key/CMouse.h"
#include "../GameScene/UI/CScoreBoard.h"
#include "../../Collision/CCollision2D.h"
#include <fstream> 
#include<stdio.h>
#include <Windows.h>


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

/*サイズ*/
#define BG_SIZE -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y
#define TITLE_SIZE -400.0f, 280.0f, 400.0f, -280.0f
#define GAME_STATE_SIZE -120.0f, -80.0f, 120.0f, -140.0f
#define GAME_EXIT_SIZE - 120.0f, -160.0f, 120.0f, -220.0f

#define PNUM_SIZE -25.0f,25.0f,25.0f,-25.0f

#define NUM_POS3  CVector2( 140,  70)	//ベースマネー
#define NUM_POS2  CVector2(  80,  70)
#define NUM_POS1  CVector2(  20,  70)

#define MNUM_POS1 CVector2( 140, -30) //倍率
#define MNUM_POS2 CVector2(  80, -30)

#define TNUM_POS1 CVector2( 140, -130) //トータルマネー
#define TNUM_POS2 CVector2(  80, -130)
#define TNUM_POS3 CVector2(  20, -130)

#define PNUM_POS1 CVector2( 140, -250) //ポケットマネー
#define PNUM_POS2 CVector2(  80, -250)
#define PNUM_POS3 CVector2(  20, -250)

#define ALPHA_HALF 0.5f
#define RESULT_FADE 0.2f //フェードスピード


//TIPSの設定
#define TIP_RECT -100.0f, 40, 100.0f, -40

#define TIP_POS0  CVector2( -210,  70)
#define TIP_POS1  CVector2( -210,  -30)	
#define TIP_POS2  CVector2( -210,  -130)	
#define TIP_POS3  CVector2( -210,  -250)	

#define TIP_TEX0		  0,  0,900,200 
#define TIP_TEX1		  0,201,900,400 
#define TIP_TEX2		  0,401,900,600 
#define TIP_TEX3		  0,601,900,800 

int CGameResult::mPrize = 0;

bool CGameResult::mFlagResult = false;

CGameResult::CGameResult() :mQuestMoney(0), mTotal(777){
}

CGameResult::~CGameResult(){
	P_DELETE(mpTexture);
	P_DELETE(mpTexture);
	P_DELETE(mpTexture);

}

void CGameResult::Init(){
	mNumCount = 0;
	mPocketMoneySave = mItem.mMoney;
	mFlagResult = false;

	//背景の呼び出し


	mBG.SetVertex(BG_SIZE); //ここで大きさ変更
	mBG.SetColor(W_COLOR, mAlpha);
	//mBG.SetUv(mpTexture, TEST_CG);


	//タイトルロゴの呼び出し

	mResult.SetVertex(TITLE_SIZE); //ここで大きさ変更
	mResult.SetColor(W_COLOR, mAlpha);
	mResult.position = CVector2(0.0f, DISP_2D_Y / 2);
	//mResult.SetUv(mpTexture, TEST_CG);


	/////////元となる金額（クエスト固有金額）////////////////////////////////////////////////////////////////////
	//3桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mBaseMoney[2].SetVertex(NUM_SIZE);
	mBaseMoney[2].SetColor(GR_COLOR, mAlpha);
	mBaseMoney[2].position = NUM_POS3;
	mBaseMoney[2].ZERO;

	//2桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mBaseMoney[1].SetVertex(NUM_SIZE);
	mBaseMoney[1].SetColor(GR_COLOR, mAlpha);
	mBaseMoney[1].position = NUM_POS2;
	mBaseMoney[1].ZERO;

	//1桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mBaseMoney[0].SetVertex(NUM_SIZE);
	mBaseMoney[0].SetColor(GR_COLOR, mAlpha);
	mBaseMoney[0].position = NUM_POS1;
	mBaseMoney[0].ZERO;


	//////合計金額表示の初期設定////////////////////////////////////////////////////////////////////////////////////////
	//3桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mTotalMoney[2].SetVertex(NUM_SIZE);
	mTotalMoney[2].SetColor(BLE_COLOR, mAlpha);
	mTotalMoney[2].position = TNUM_POS3;
	mTotalMoney[2].ZERO;

	//2桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mTotalMoney[1].SetVertex(NUM_SIZE);
	mTotalMoney[1].SetColor(BLE_COLOR, mAlpha);
	mTotalMoney[1].position = TNUM_POS2;
	mTotalMoney[1].ZERO;

	//1桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mTotalMoney[0].SetVertex(NUM_SIZE);
	mTotalMoney[0].SetColor(BLE_COLOR, mAlpha);
	mTotalMoney[0].position = TNUM_POS1;
	mTotalMoney[0].ZERO;

	////////////倍率の表示//////////////////////////////////////////////////////////////////////////////////
	//3桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mMagnification[2].SetVertex(NUM_SIZE);
	mMagnification[2].SetColor(RE_COLOR, mAlpha);
	mMagnification[2].position = MNUM_POS1;
	mMagnification[2].ZERO;

	//2桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mMagnification[1].SetVertex(NUM_SIZE);
	mMagnification[1].SetColor(RE_COLOR, mAlpha);
	mMagnification[1].position = MNUM_POS2;
	mMagnification[1].ZERO;

	//1桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mMagnification[0].SetVertex(NUM_SIZE);
	mMagnification[0].SetColor(RE_COLOR, mAlpha);
	mMagnification[0].position = MNUM_POS1;
	mMagnification[0].ZERO;

	for (int i = 0; i < TIPS; i++)
	{
		//Resultチップス
		mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
		mpTexture->load(TGA_FILE"ResultTips.tga");	//テクスチャファイル読み込み
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		mTips[i].SetVertex(TIP_RECT);
		mTips[i].SetColor(W_COLOR, mAlpha);
	}


	////////////所持金の表示//////////////////////////////////////////////////////////////////////////////////
	//3桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mPocketMoney[2].SetVertex(PNUM_SIZE);
	mPocketMoney[2].SetColor(B_COLOR, mAlpha);
	mPocketMoney[2].position = PNUM_POS3;
	mPocketMoney[2].ZERO;

	//2桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mPocketMoney[1].SetVertex(PNUM_SIZE);
	mPocketMoney[1].SetColor(B_COLOR, mAlpha);
	mPocketMoney[1].position = PNUM_POS2;
	mPocketMoney[1].ZERO;

	//1桁目の表示
	mpNumber = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNumber->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mPocketMoney[0].SetVertex(PNUM_SIZE);
	mPocketMoney[0].SetColor(B_COLOR, mAlpha);
	mPocketMoney[0].position = PNUM_POS1;
	mPocketMoney[0].ZERO;



	mTips[0].position = TIP_POS0;
	mTips[1].position = TIP_POS1;
	mTips[2].position = TIP_POS2;
	mTips[3].position = TIP_POS3;
	mTips[0].SetUv(mpTexture, TIP_TEX0);
	mTips[1].SetUv(mpTexture, TIP_TEX1);
	mTips[2].SetUv(mpTexture, TIP_TEX2);
	mTips[3].SetUv(mpTexture, TIP_TEX3);


	/*カーソル四角作成*/
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor (WHITE_COLOR);

}

void CGameResult::Number(int score, CRectangle2 &odifit, CRectangle2 &twdifit, CRectangle2 &thdifit){		//数字の処理

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
	else if (difit3 == 1){
		thdifit.ONE;
	}
	else  if (difit3 == 2){
		thdifit.TWO;
	}
	else if(difit3 == 3){
		thdifit.THREE;
	}
	else if (difit3 == 4){
		thdifit.FOUR;
	}
	else if (difit3 == 5){
		thdifit.FIVE;
	}
	else if (difit3 == 6){
		thdifit.SIX;
	}
	else if (difit3 == 7){
		thdifit.SEVEN;
	}
	else if (difit3 == 8){
		thdifit.EIGHT;
	}
	else if (difit3 == 9){
		thdifit.NINE;
	}



	//2ケタ目
	//どの数字が結果として出たかで処理を変える
	//０～９
	if (difit2 <= 0){
		twdifit.ZERO;
	}
	else if (difit2 == 1){
		twdifit.ONE;
	}
	else if (difit2 == 2){
		twdifit.TWO;
	}
	else if (difit2 == 3){
		twdifit.THREE;
	}
	else if (difit2 == 4){
		twdifit.FOUR;
	}
	else if (difit2 == 5){
		twdifit.FIVE;
	}
	else if (difit2 == 6){
		twdifit.SIX;
	}
	else if (difit2 == 7){
		twdifit.SEVEN;
	}
	else if (difit2 == 8){
		twdifit.EIGHT;
	}
	else if (difit2 == 9){
		twdifit.NINE;
	}


	//1ケタ目
	//どの数字が結果として出たかで処理を変える
	//０～９
	if (difit1 <= 0){
		odifit.ZERO;
	}
	else if (difit1 == 1){
		odifit.ONE;
	}
	else if (difit1 == 2){
		odifit.TWO;
	}
	else if (difit1 == 3){
		odifit.THREE;
	}
	else if (difit1 == 4){
		odifit.FOUR;
	}
	else if (difit1 == 5){
		odifit.FIVE;
	}
	else if (difit1 == 6){
		odifit.SIX;
	}
	else if (difit1 == 7){
		odifit.SEVEN;
	}
	else if (difit1 == 8){
		odifit.EIGHT;
	}
	else if (difit1 == 9){
		odifit.NINE;
	}

}


void CGameResult::Update(){

	if (mFlagResult){
		switch (mPrize)
		{
		case E_Quest0:
			mQuestMoney = PRIZE0;
			break;

		case E_Quest1:
			mQuestMoney = PRIZE1;
			break;

		case E_Quest2:
			mQuestMoney = PRIZE2;
			break;

		case E_Quest3:
			mQuestMoney = PRIZE3;
			break;

		default:
			break;
		}


		mDifference = (CScoreBoard::mPlayerScore / 10) - (CScoreBoard::mEnemyScore / 10);

		mTotal = mQuestMoney*mDifference;



		//if (CKey::push('J')){
		//	mPocketMoneySave += 0.01f;
		//}

		//mItem.mMoney = mPocketMoneySave;

		Number(mTotal, mTotalMoney[0], mTotalMoney[1], mTotalMoney[2]);

		Number(mQuestMoney, mBaseMoney[0], mBaseMoney[1], mBaseMoney[2]);

		Number(mDifference, mMagnification[0], mMagnification[1], mMagnification[2]);

		Number(mItem.mMoney, mPocketMoney[0], mPocketMoney[1], mPocketMoney[2]);

		if (CScoreBoard::mPlayerScore >= LIMIT_SCORE){
			
			/*フェード*/
			mBG.Fade(RESULT_FADE, ALPHA_HALF);
			mResult.Fade(RESULT_FADE, ALPHA_MAX);
			for (int i = 0; i < 3; i++)
			{
				mTotalMoney[i].Fade(RESULT_FADE, ALPHA_MAX);
				mPocketMoney[i].Fade(RESULT_FADE, ALPHA_MAX);
			}
			for (int i = 0; i < TIPS; i++)
			{
				mTips[i].Fade(RESULT_FADE, ALPHA_MAX);
			}
			for (int i = 1; i < 3; i++)
			{
				mBaseMoney[i].Fade(RESULT_FADE, ALPHA_MAX);
			}
			mMagnification[0].Fade(RESULT_FADE, ALPHA_MAX);

			/*カウントが所持金に達したら*/
			if (mNumCount < mTotal){
				mNumCount += 1.0f;
				mPocketMoneySave += 1.0f;
				mItem.mMoney = mPocketMoneySave;
			} //画面をクリックするとシーンを移行する
			else if (
				CMouse::GetInstance()->mOneLeftFlag ||
				CKey::push(VK_RETURN))//マウス左クリック
			{
				mFlagResult = false;
				CScoreBoard::GetInstance()->mFlagSceneChage = true;
			}
		}

	}

	mCursor.position = CMouse::GetInstance()->mPos;

}

/*
描画処理のみを行う。
*/
void CGameResult::Render() {

	CRectangle2::Disp2D_Start();//2D処理開始

	/*この場所に描画処理を入れる*/
	

	for (int i = 0; i < DIGIT; i++)
	{
		mTips[i].Render();
		mBaseMoney[i]    .Render();
		mTotalMoney[i]   .Render();
		mPocketMoney[i]  .Render();
	}
	for (int i = 0; i < TIPS; i++)
	{
		mTips[i].Render();
	}
	for (int i = 0; i < DIGIT-1; i++)
	{
		mMagnification[i].Render();
	}


	
	/*描画終了*/
	CRectangle2::Disp2D_Exit();//2D処理終了

}