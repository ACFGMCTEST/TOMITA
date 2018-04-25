//高橋弘樹
#include"CItem.h"
#include"../../Key/CKey.h"
#include"../../Key/CMouse.h"
#include"../../Collision/CCollision2D.h"
#include <fstream> 
#include<stdio.h>

#define DISP_2D_Y 768 //縦幅

#define BACK_GROUND     -400.0f, 300.0f, 400.0f, -300.0f
///////////////////////////////////////

///////////////////////////////////////
//装備中項目
#define CURRENT_OUTFIT	-200.0f, 160.0f,  200.0f,   -160.0f

#define CURRENT_UV	    mpMenu, 0, 0, 600, 494

#define CURRENT_POS	   -190, 60

//選択中テキスト
#define SELECT_TEXT_OUTFIT	-100.0f, 30.0f,  100.0f,   -30.0f

#define SELECT_TEXT_POS	-190, 260

//選択中のアイコンの下に描画する四角形の設定

#define SELECT_MARKER_OUTFIT   -85.0f, 85.0f, 85.0f, -85.0f

#define DECISION_BUTTON_POS -190, -180

#define SELECT_MARKER_POS_0		100, 180
#define SELECT_MARKER_POS_1		280, 180
#define SELECT_MARKER_POS_2		100,   0
#define SELECT_MARKER_POS_3		280,   0
#define SELECT_MARKER_POS_4		100,-180


///その他
//#define CURRENT_NAME	-280.0f, -20.0f, -200.0f, -80.0f
#define CURRENT_STATUS	-280.0f, -100.0f, -200.0f, -160.0f
#define CURRENT_ICON	-140.0f, -20.0f, -20.0f,  -160.0f
#define POP_SIZE        -300, 200, 300, -200
#define POP_TIME	    1.0f
///////////////////////////////////////
//その他
#define OUTFIT_ICON	      -80.0f,  80.0f, 80.0f,   -80.0f
#define BACK_BUTTON		-320.0f, -180.0f, -220.0f, -240.0f

#define FIRST_X	100			//アイコンの初期ｘ値
#define FIRST_Y	180		//アイコンの初期ｙ値
#define TEX_L	  0			//テクスチャ設定の初期値
#define TEX_R	400
#define RECT_WIDE 2

#define ATK_NUM_OUTFIT -25,25,25,-25

#define ATK_POS_3  -310, -55
#define ATK_POS_2  -270, -55
#define ATK_POS_1  -230, -55


#define ITEM_MENU	 TGA_FILE"itembutton.tga"
#define ITEM_ICON	 TGA_FILE"IconSetAll.tga"
#define BACK	     TGA_FILE"backbutton.tga"

/*texフェイル*/
#define CURSOR_CG 0,0,150,120

float CItem::mMoney = 100;

//デフォルトハンマーを基準にする
int   CItem::mAtk = WEAPON_ATKD;
int   CItem::mSaveAtk = WEAPON_ATKD;
int   CItem::mSkillNo = WEAPON0;
int   CItem::status   = WEAPON0;
int   CItem::mSelectWeapon = WEAPON0;

CItem::CItem() :rectnum(0){
	rectx = FIRST_X;
	recty = FIRST_Y;
	mTexXL = TEX_L;
	mTexXR = TEX_R;
}

CItem::~CItem(){
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
	if (mpNum) {
		//テクスチャを使っていればインスタンス削除
		delete mpNum;
		mpNum = 0;
	}
}

//初期設定を行う
void CItem::Init(){

	
}

//更新処理を行う
void CItem::Update(){
	


};

//描画処理を行う。
void CItem::Render() {
	CRectangle2::Disp2D_Start();//描画開始
	mBackGround.	Render();
	
	mSelectPicture.Render();

	mDecisionButton.Render();

	//装備ボードの描画	
	switch (mSelectWeapon)
	{
	case WEAPON0:
		mCurrentOutfit[WEAPON0].Render();
		break;
	case WEAPON1:
		mCurrentOutfit[WEAPON1].Render();
		break;
	case WEAPON2:
		mCurrentOutfit[WEAPON2].Render();
		break;
	}





	//選択中
	mSelectText.Render();

	//装備中アイテムの名前

	mAtkNo[0].Render();
	mAtkNo[1].Render();
	mAtkNo[2].Render();
	
	mBackButton.Render();

	if (mPopUpFlag){
		mPopUp.Render();
	}

	mCursor.Render();
	CRectangle2::Disp2D_Exit();//描画終了

}