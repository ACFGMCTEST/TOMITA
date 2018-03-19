//高橋弘樹 && 冨田健斗
#include"CHome.h"
#include "../Define\Define.h"
#include <fstream> 
#include <stdio.h>
#include "../GameMain\Key\CKey.h"
#include "../../Key/CMouse.h"
#include "../../Collision/CCollision2D.h"
/*サイズマクロ*/
#define BG_SIZE -DISP_X,DISP_Y,DISP_X,-DISP_Y

#define MENU_SIZE   -150, 150, 150, -150

#define BIG_SIZE    -200, 200, 200, -200

#define TEST_SIZE	- 40, 400,  40, -400

#define MOVE_R		   0,   0, 100, 1000

#define MOVE_L		   0,   0,-100, 1000

#define HOME_ICON_CG  0, 0, 300, 300

#define CURSOR_CG 0,0,150,120

#define RE_MOVE_Y    -50

#define TEXT_BOX_SIZE -310.0f, 220.0f, 80.0f, -80.0f

#define UNITY_CHAN_SIZE   -223.0f, 346.5f, 223.0f, -346.5f
#define UNITY_CHAN_UV           0,      0,    446,     693
#define LOOP_SPEED		0.01f
CHome::~CHome(){
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

void CHome::Init(){

	mStatus = QUEST;
	alpha = 0.0f;
	alpha2 = 0.0f;

	//背景の呼び出し
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"BG.tga");	//テクスチャファイル読み込み
	mBG.SetVertex(BG_SIZE); //ここで大きさ変更
	mBG.SetColor(WHITE_COLOR);
	mBG.SetUv(mpTexture, BG_SIZE);

	//クエスト選択ボタン呼び出し
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"questicon.tga");	//テクスチャファイル読み込み
	mSelectButton.SetVertex(MENU_SIZE);
	mSelectButton.SetColor(WHITE_COLOR);
	mSelectButton.SetUv(mpMenu, HOME_ICON_CG);
	
	//ショップボタンの呼び出し	
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"shopicon.tga");	//テクスチャファイル読み込み
	mShopButton.SetVertex(MENU_SIZE);
	mShopButton.SetColor(WHITE_COLOR);
	mShopButton.SetUv(mpMenu, HOME_ICON_CG);

	//アイテム画面の呼び出し。
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"itemicon.tga");	//テクスチャファイル読み込み
	mItemButton.SetVertex(MENU_SIZE);
	mItemButton.SetColor(WHITE_COLOR);
	mItemButton.SetUv(mpMenu, HOME_ICON_CG);

	//タイトルバック画面の呼び出し
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"exiticon.tga");	//テクスチャファイル読み込み
	mTitleButton.SetVertex(MENU_SIZE);
	mTitleButton.SetColor(WHITE_COLOR);
	mTitleButton.SetUv(mpMenu, HOME_ICON_CG);

	//メニューのポジションを指定する。
	mSelectButton.position = CVector2(mMenuPos0            , 0);
	mShopButton  .position = CVector2(mMenuPos0 + mMenuPos1, 0);
	mItemButton  .position = CVector2(mMenuPos0 + mMenuPos2, 0);
	mTitleButton .position = CVector2(mMenuPos0 + mMenuPos3, 0);

	/*カーソル四角作成*/
	mpTexCursor = new CTexture();
	mpTexCursor->load(TGA_FILE"cursor.tga");
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(mpTexCursor, CURSOR_CG);

	 // E_GREEN_YELLOW,	//緑から黄
	 // E_YELLOW_RED,	//黄から赤
	 // E_RED_PURPLE,	//赤から紫
	 // E_PURPLE_BLUE,	//紫から青
	 // E_BLUE_CYAN,	//青から青緑
	 // E_CYAN_GREEN,	//青緑から緑

	mSelectButton.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_RED_PURPLE);
	mShopButton.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_YELLOW_RED);
	mItemButton.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_GREEN_YELLOW);
	mTitleButton.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_BLUE_CYAN);
}


//項目全体の移動処理
void CHome::AllMove(bool zeroover){
	if ( zeroover){ mMenuPos0 += MOVE_SPEED; mMenuPos1 += MOVE_SPEED; mMenuPos2 += MOVE_SPEED; mMenuPos3 += MOVE_SPEED; }
	if (!zeroover){ mMenuPos0 -= MOVE_SPEED; mMenuPos1 -= MOVE_SPEED; mMenuPos2 -= MOVE_SPEED; mMenuPos3 -= MOVE_SPEED; }
}

void CHome::Update(){
	//カーソルポジション
	mCursor.position = CMouse::GetInstance()->mPos;
	//メニューのサイズを常時アップデートする(変動するため)
	mSelectButton.SetVertex(MENU_SIZE);
	mShopButton.SetVertex(MENU_SIZE);
	mItemButton.SetVertex(MENU_SIZE);
	mTitleButton.SetVertex(MENU_SIZE);
	//カラーもアップデートする
	if (mStatus != QUEST) mSelectButton.SetColor(WHITE_COLOR);
	if (mStatus != SHOP)mShopButton.SetColor(WHITE_COLOR);
	if (mStatus != ITEM)mItemButton.SetColor(WHITE_COLOR);
	if (mStatus != TITLE)mTitleButton.SetColor(WHITE_COLOR);

	//ポジションの更新。Yは０とする
	mSelectButton.position = CVector2(mMenuPos0, 0);
	mShopButton.position   = CVector2(mMenuPos1, 0);
	mItemButton.position   = CVector2(mMenuPos2, 0);
	mTitleButton.position  = CVector2(mMenuPos3, 0);

//ライトボタンレフトボタンの遷移処理
	switch (mStatus)
	{
	case QUEST:
		//メニューのサイズを大きくする。
		mSelectButton.SetVertex(BIG_SIZE);
		mSelectButton.GradationLoop(LOOP_SPEED);
		//少し下に下げる
		mSelectButton.position = CVector2(mMenuPos0, RE_MOVE_Y);
		//ステータスを変更する
		//マウスカーソルが合っているか
		if (CCollision2D::Collision2D(mCursor, mShopButton)){
			mShopButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag){ mMove = true; mStatus = SHOP; }}
		     if (mMenuPos0 < 0)    { AllMove(true); } //ポジションが0より大きい時か小さい時かでmoveを指定する
		else if (mMenuPos0 > 0)    { AllMove(false); }
		     if (mMenuPos0 != 0.0f){ mMove = false; }//メニューが移動するとクリックを有効化

		break;
	case SHOP:
		mShopButton.SetVertex(BIG_SIZE);
		mShopButton.GradationLoop(LOOP_SPEED);
		mShopButton.position = CVector2(mMenuPos1, RE_MOVE_Y);
		if (CCollision2D::Collision2D(mCursor, mItemButton))  {
			mItemButton.SetColor(GRAY_COLOR);
		if (CMouse::GetInstance()->mOneLeftFlag){ mMove = true; mStatus = ITEM; } }

		if (CCollision2D::Collision2D(mCursor, mSelectButton)){
			mSelectButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag){ mMove = true; mStatus = QUEST; }}

		     if (mMenuPos1 < 0)    { AllMove(true);  }
		else if (mMenuPos1 > 0)    { AllMove(false); }
		     if (mMenuPos1 != 0.0f){ mMove = false; }

		break;
	case ITEM:
		mItemButton.SetVertex(BIG_SIZE);
		mItemButton.GradationLoop(LOOP_SPEED);
		mItemButton.position = CVector2(mMenuPos2, RE_MOVE_Y);
		if (CCollision2D::Collision2D(mCursor, mTitleButton)){
			mTitleButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag){ mMove = true; mStatus = TITLE; }}
		if (CCollision2D::Collision2D(mCursor, mShopButton )){ 
			mShopButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag){ mMove = true; mStatus = SHOP; }}
		     if (mMenuPos2 < 0)     { AllMove(true); }
		else if (mMenuPos2> 0)      { AllMove(false);}
		     if (mMenuPos2 != 0.0f) { mMove = false; }
		
		break;
	case TITLE:
		mTitleButton.SetVertex(BIG_SIZE);
		mTitleButton.GradationLoop(LOOP_SPEED);
		mTitleButton.position = CVector2(mMenuPos3, RE_MOVE_Y);
		if (CCollision2D::Collision2D(mCursor, mItemButton)){
			mItemButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag) { mMove = true; mStatus = ITEM; }}
		     if (mMenuPos3 < 0)    { AllMove(true); }
		else if (mMenuPos3 > 0)    { AllMove(false); }
	     	 if (mMenuPos3 != 0.0f){ mMove = false; }
		
		break;
	}

};

/*
描画処理のみを行う。
*/
void CHome::Render() {
	CRectangle2::Disp2D_Start();//描画はじめ
	mBG.Render();	
	mSelectButton.Render();
	mShopButton.Render();
	mItemButton.Render();
	mTitleButton.Render();

	mCursor.Render();
	CRectangle2::Disp2D_Exit();//描画終わり
}