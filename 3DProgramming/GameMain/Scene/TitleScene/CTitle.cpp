//高橋弘樹　&& 冨田健斗　
#include"CTitle.h"
#include "../../Graphic/CTexture.h"
#include "../../Key/CKey.h"
#include "../../../Define/Define.h"
#include "../../Key/CMouse.h"
#include <fstream> 
#include<stdio.h>
#include <Windows.h>
#include "../../Collision/CCollision2D.h"

/*サイズ*/
#define BG_SIZE -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y
#define TITLE_SIZE -400.0f, 160.0f, 400.0f, -160.0f
#define LICENSE_SIZE 0.0f, 0.0f, 147.0f, -127.0f

#define GAME_STATE_SIZE -mScalingRectX, mScalingRectY, mScalingRectX, -mScalingRectY
#define GAME_EXIT_SIZE -mScalingRectX, mScalingRectY, mScalingRectX, -mScalingRectY

#define BUTTON_DEFAULT_SIZE -mButtonX, mButtonY, mButtonX, -mButtonY
/*テクスチャサイズ*/
#define TITLE_CG 0,0,1000,400
#define LICENSE_CG 0,0,147,127
#define START_CG 0,0,300,150
#define EXIT_CG 300,0,600,150
#define JAGGED_BALLOON_CG 0, 150, 600, 400

CTitle::~CTitle(){
	if (mpTexture) {
		//テクスチャを使っていればインスタンス削除
		delete mpTexture;
		mpTexture = 0;
	}

	
	if (mpMenu) {
		//テクスチャを使っていればインスタンス削除
		delete mpMenu;
		mpMenu = 0;
	}

}



void CTitle::Init(){
	mMaxSize = false;
	mScalingRectX = mButtonX;
	mScalingRectY = mButtonY;

	mAlpha = 0.0f;

	//背景の呼び出し

	mpBg = new CTexture();
	mpBg->load(TGA_FILE"BG.tga");

	mBG.SetVertex(BG_SIZE); //ここで大きさ変更
	mBG.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	mBG.SetUv(mpBg, BG_SIZE);

	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"Light_Frame.tga");

	//ゆにてぃちゃんライセンス

	mUnityChanLicense.SetVertex(LICENSE_SIZE); //ここで大きさ変更
	mUnityChanLicense.SetColor(WHITE_COLOR);
	mUnityChanLicense.position = CVector2(250, -170);
	mUnityChanLicense.SetUv(mpTexture, LICENSE_CG);



	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"title.tga");

	//タイトルロゴの呼び出し

	mTitleLogo.SetVertex(TITLE_SIZE); //ここで大きさ変更
	mTitleLogo.SetColor(WHITE_COLOR);
	mTitleLogo.position = CVector2(0, 170);
	mTitleLogo.SetUv(mpTexture, TITLE_CG);


	//タイトルロゴの呼び出し

	mShadow.SetVertex(TITLE_SIZE); //ここで大きさ変更
	mShadow.SetColor(0.0f, 0.0f, 0.0f, 0.5f);
	mShadow.position = CVector2(20, 150);
	mShadow.SetUv(mpTexture, TITLE_CG);





	//ゲーム開始の呼び出し
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"TitleSet.tga");	//テクスチャファイル読み込み


	mGameStart.SetVertex(GAME_STATE_SIZE);
	mGameStart.SetColor(WHITE_COLOR);
	mGameStart.position = CVector2(0, -80);
	mGameStart.SetUv(mpMenu, START_CG);

	////ゲーム終了の呼び出し
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"TitleSet.tga");	//テクスチャファイル読み込み


	mGameExit.SetVertex(GAME_EXIT_SIZE);
	mGameExit.SetColor(WHITE_COLOR);
	mGameExit.position = CVector2(0, -220);
	mGameExit.SetUv(mpMenu, EXIT_CG);

	////カーソルの呼び出し
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"cursor.tga");	//テクスチャファイル読み込み


	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(mpTexture, 0, 0, 150, 120);

	///*Gradation関数*/
	//mCursor.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_RED_PURPLE);
}




void CTitle::Update(){

	/*あたり判定*/
	if (CCollision2D::Collision2D(mCursor, mGameStart)){ //カーソルがあっている?
		mGameExit.SetVertex(BUTTON_DEFAULT_SIZE);
		mGameStart.SetVertex(GAME_STATE_SIZE);
		if (!mMaxSize){
			mScalingRectX += mChangeSize;
			mScalingRectY += mChangeSize;
			if (mScalingRectX >= mButtonX * mExpansionLimit)mMaxSize = true;
		}
		else if (mMaxSize){
			mScalingRectX -= mChangeSize;
			mScalingRectY -= mChangeSize;
			if (mScalingRectX <= mButtonX)mMaxSize = false;
		}
	}
	else
	if (CCollision2D::Collision2D(mCursor, mGameExit)){ //カーソルがあっている?
		mGameStart.SetVertex(BUTTON_DEFAULT_SIZE);
		mGameExit.SetVertex(GAME_STATE_SIZE);
		if (!mMaxSize){
			mScalingRectX += mChangeSize;
			mScalingRectY += mChangeSize;
			if (mScalingRectX >= mButtonX * mExpansionLimit)mMaxSize = true;
		}
		else if (mMaxSize){
			mScalingRectX -= mChangeSize;
			mScalingRectY -= mChangeSize;
			if (mScalingRectX <= mButtonX)mMaxSize = false;
		}
	}
	else
	{
		mScalingRectX = mButtonX;
		mScalingRectY = mButtonY;
		mGameStart.SetVertex(GAME_STATE_SIZE);
		mGameExit.SetVertex(GAME_STATE_SIZE);
	}

	mCursor.position = CMouse::mPos;

	//mCursor.GradationLoop(0.02f);
};

/*
描画処理のみを行う。
*/
void CTitle::Render() {

	CRectangle2::Disp2D_Start();//2D処理開始

	/*この場所に描画処理を入れる*/
	mBG.Render();
	mShadow.Render();
	mTitleLogo.Render();
	mGameStart.Render();
	mGameExit.Render();
	mUnityChanLicense.Render();
	mCursor.Render();
	/*描画終了*/

	CRectangle2::Disp2D_Exit();//2D処理終了



}