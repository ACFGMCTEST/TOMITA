//高橋弘樹
#include"CQuest.h"
#include "../../Key/CKey.h"
#include"../../../Define/define.h"
#include <fstream> 
#include<stdio.h>
#include "../../Key/CMouse.h"
#include "../../Collision/CCollision2D.h"

#define QUEST_NAME0 TGA_FILE"questname0.tga"
#define QUEST_NAME1 TGA_FILE"questname1.tga"
#define QUEST_NAME2 TGA_FILE"questname2.tga"
#define QUEST_NAME3 TGA_FILE"questname3.tga"

#define NAME_SIZE -310.0f, 50.0f, 310.0f, -50.0f
#define NAME_Y -0//微調整用
#define NAME_INTRV 1.1f//ネームの間隔
//ネームボードのポジション
#define NAME_POS0	CVector2(0, 160 + NAME_Y)
#define NAME_POS1	CVector2(0,  0 + NAME_Y)
#define NAME_POS2	CVector2(0, -160 + NAME_Y)
//#define NAME_POS3	CVector2(0,-200)
//ネームボードの影
#define NAME_POS0S	CVector2(10, 150 + NAME_Y)
#define NAME_POS1S	CVector2(10,  -10 + NAME_Y)
#define NAME_POS2S	CVector2(10, -170 + NAME_Y)
//#define NAME_POS3S	CVector2(10,-210)


#define BACK       TGA_FILE"backbutton.tga"
/*texフェイル*/
#define CURSOR_CG 0,0,150,120

/*静的初期化*/
CQuest::E_CHOICE CQuest::eChoice = E_QUEST00;


CQuest::~CQuest(){
	if (mpTextureBG) {
		//テクスチャを使っていればインスタンス削除
		delete mpTextureBG;
		mpTextureBG = 0;
	}
	if (mpTextureQUEST_NAME0) {
		//テクスチャを使っていればインスタンス削除
		delete mpTextureQUEST_NAME0;
		mpTextureQUEST_NAME0 = 0;
	}
	if (mpMenuQUEST_NAME1) {
		//テクスチャを使っていればインスタンス削除
		delete mpMenuQUEST_NAME1;
		mpMenuQUEST_NAME1 = 0;
	}
	if (mpMenuQUEST_NAME2) {
		//テクスチャを使っていればインスタンス削除
		delete mpMenuQUEST_NAME2;
		mpMenuQUEST_NAME2 = 0;
	}
	if (mpMenuBACK) {
		//テクスチャを使っていればインスタンス削除
		delete mpMenuBACK;
		mpMenuBACK = 0;
	}

	if (mpTexCursor) {
		//テクスチャを使っていればインスタンス削除
		delete mpTexCursor;
		mpTexCursor = 0;
	}
	

}



void CQuest::Init(){

	alpha = 0.0f;
	alpha2 = 0.0f;

	//背景の呼び出し
	mpTextureBG = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTextureBG->load(TGA_FILE"BG.tga");	//テクスチャファイル読み込み
	
	mBG.SetVertex(BG_SIZE); //ここで大きさ変更
	mBG.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	mBG.SetUv(mpTextureBG, 0, 0, 1024, 768);



	////クエスト名00
	mpTextureQUEST_NAME0 = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTextureQUEST_NAME0->load(QUEST_NAME0);	//テクスチャファイル読み込み
	mQuestName00.SetVertex(NAME_SIZE);
	mQuestName00.SetColor(WHITE_COLOR);
	mQuestName00.SetUv(mpTextureQUEST_NAME0, TEST_CG);
	mQuestName00.position = NAME_POS0;

	mShadow[0] = mQuestName00;
	mShadow[0].SetColor(SKELETON_BLACK_COLOR);
	mShadow[0].position = NAME_POS0S;

	//クエスト名01
	mpMenuQUEST_NAME1 = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenuQUEST_NAME1->load(QUEST_NAME1);	//テクスチャファイル読み込み
	mQuestName01.SetVertex(NAME_SIZE);
	mQuestName01.SetColor(WHITE_COLOR);
	mQuestName01.SetUv(mpMenuQUEST_NAME1, TEST_CG);
	mQuestName01.position = NAME_POS1;

	mShadow[1] = mQuestName01;
	mShadow[1].SetColor(SKELETON_BLACK_COLOR);
	mShadow[1].position = NAME_POS1S;

	//クエスト名02
	mpMenuQUEST_NAME2 = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenuQUEST_NAME2->load(QUEST_NAME2);	//テクスチャファイル読み込み
	mQuestName02.SetVertex(NAME_SIZE);
	mQuestName02.SetColor(WHITE_COLOR);
	mQuestName02.SetUv(mpMenuQUEST_NAME2, TEST_CG);
	mQuestName02.position = NAME_POS2;

	mShadow[2] = mQuestName02;
	mShadow[2].SetColor(SKELETON_BLACK_COLOR);
	mShadow[2].position = NAME_POS2S;


	////戻るボタンの呼び出し
	mpMenuBACK = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenuBACK->load(BACK);	//テクスチャファイル読み込み
	mBackButton.SetVertex(BACK_RECT);
	mBackButton.SetColor(WHITE_COLOR);
	mBackButton.SetUv(mpMenuBACK, BACK_CG);
	mBackButton.position = BACK_POS;



	/*カーソル四角作成*/
	mpTexCursor = new CTexture();
	mpTexCursor->load(TGA_FILE"cursor.tga");
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(mpTexCursor, CURSOR_CG);

}




void CQuest::Update(){
	mQuestName00.SetColor(WHITE_COLOR);
	mQuestName01.SetColor(WHITE_COLOR);
	mQuestName02.SetColor(WHITE_COLOR);
	//mQuestName03.SetColor(WHITE_COLOR);
	mQuestName00.position = NAME_POS0;
	mQuestName01.position = NAME_POS1;
	mQuestName02.position = NAME_POS2;
	//mQuestName03.position = NAME_POS3;

	//クリック時に押し込まれたような形に
	if (CCollision2D::Collision2D(mCursor, mQuestName00)){mQuestName00.SetColor(GRAY_COLOR);
	if (CMouse::GetInstance()->mOneLeftFlag){ mQuestName00.position = NAME_POS0S; mQuestName00.SetColor(DARK_GRAY_COLOR); }
	}
	if (CCollision2D::Collision2D(mCursor, mQuestName01)){mQuestName01.SetColor(GRAY_COLOR);
	if (CMouse::GetInstance()->mOneLeftFlag){ mQuestName01.position = NAME_POS1S;  mQuestName01.SetColor(DARK_GRAY_COLOR); }
	}
	if (CCollision2D::Collision2D(mCursor, mQuestName02)){mQuestName02.SetColor(GRAY_COLOR);
	if (CMouse::GetInstance()->mOneLeftFlag){ mQuestName02.position = NAME_POS2S; mQuestName02.SetColor(DARK_GRAY_COLOR); }
	}
	
	mBackButton.SetColor(WHITE_COLOR);
	if (CCollision2D::Collision2D(mCursor, mBackButton)){
mBackButton.SetColor(GRAY_COLOR);
	}
	mCursor.position = CMouse::GetInstance()->mPos;

};

/*
描画処理のみを行う。
*/
void CQuest::Render() {
	CRectangle2::Disp2D_Start();//描画はじめ
	mBG.Render();
	for (int i = 0; i < BOARD; i++)
	{
		mShadow[i].Render();
	}

	mQuestName00.Render();
	mQuestName01.Render();
	mQuestName02.Render();
	mBackButton.Render();

	mCursor.Render();
	CRectangle2::Disp2D_Exit();;//描画終了
	


}