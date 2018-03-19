//高橋弘樹
#include"CItem.h"
#include"../../Key/CKey.h"
#include"../../Key/CMouse.h"
#include"../ShopScene/CShop.h"
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
#define ITEM_ICON	 TGA_FILE"IconSet.tga"
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

	alpha = 0.0f;
	alpha2 = 0.0f;

	//背景の呼び出し
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"BG.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();	

	gluOrtho2D(-320.0f, 320.0f, -340.0f, 340.0f);
	mBackGround.SetVertex(BG_SIZE); //ここで大きさ変更
	mBackGround.SetColor(WHITE_COLOR);
	mBackGround.SetUv(mpTexture, BG_SIZE);

	//数値表示
	mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	mAtkNo[2].SetVertex(ATK_NUM_OUTFIT);
	mAtkNo[2].SetColor(WHITE_COLOR);
	mAtkNo[2].position = CVector2(ATK_POS_3);
	mAtkNo[2].ZERO;

	mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	mAtkNo[1].SetVertex(ATK_NUM_OUTFIT);
	mAtkNo[1].SetColor(WHITE_COLOR);
	mAtkNo[1].position = CVector2(ATK_POS_2);
	mAtkNo[1].ZERO;

	mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	mAtkNo[0].SetVertex(ATK_NUM_OUTFIT);
	mAtkNo[0].SetColor(WHITE_COLOR);
	mAtkNo[0].position = CVector2( ATK_POS_1);
	mAtkNo[0].ZERO;

	//選択中アイコンの下に描画する四角形
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(ITEM_ICON);	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mSelectPicture.SetVertex(SELECT_MARKER_OUTFIT);
	mSelectPicture.SetColor(RED_COLOR);

	if (status == WEAPON0)mSelectPicture.position = CVector2(SELECT_MARKER_POS_0);
	else if (status == WEAPON1)mSelectPicture.position = CVector2(SELECT_MARKER_POS_1);
	else if (status == WEAPON2)mSelectPicture.position = CVector2(SELECT_MARKER_POS_2);
	else if (status == WEAPON3)mSelectPicture.position = CVector2(SELECT_MARKER_POS_3);
	else if (status == WEAPON4)mSelectPicture.position = CVector2(SELECT_MARKER_POS_4);
	else mSelectPicture.position = CVector2(SELECT_MARKER_POS_0);
	mSelectPicture.SetUv(mpMenu, 0, 0, 0, 0);

	//装備中テキストの表示
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"selectedicon.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mSelectText.SetVertex(SELECT_TEXT_OUTFIT);
	mSelectText.SetColor(WHITE_COLOR);
	mSelectText.position = CVector2(SELECT_TEXT_POS);
	mSelectText.SetUv(mpMenu, 0, 0, 600, 300);

	//確定ボタンの表示
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"Decisionbutton.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mDecisionButton.SetVertex(SELECT_TEXT_OUTFIT);
	mDecisionButton.SetColor(WHITE_COLOR);
	mDecisionButton.position = CVector2(DECISION_BUTTON_POS);
	mDecisionButton.SetUv(mpMenu, 0, 0, 600, 300);

	//装備Boardの表示
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"BoardD.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mCurrentOutfit[WEAPON0].SetVertex(CURRENT_OUTFIT);
	mCurrentOutfit[WEAPON0].SetColor(WHITE_COLOR);
	mCurrentOutfit[WEAPON0].position = CVector2(CURRENT_POS);
	mCurrentOutfit[WEAPON0].SetUv(CURRENT_UV);


	//装備Boardの表示
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"Board0.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mCurrentOutfit[WEAPON1].SetVertex(CURRENT_OUTFIT);
	mCurrentOutfit[WEAPON1].SetColor(WHITE_COLOR);
	mCurrentOutfit[WEAPON1].position = CVector2(CURRENT_POS);
	mCurrentOutfit[WEAPON1].SetUv(CURRENT_UV);

	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"Board1.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mCurrentOutfit[WEAPON2].SetVertex(CURRENT_OUTFIT);
	mCurrentOutfit[WEAPON2].SetColor(WHITE_COLOR);
	mCurrentOutfit[WEAPON2].position = CVector2(CURRENT_POS);
	mCurrentOutfit[WEAPON2].SetUv(CURRENT_UV);

	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"Board2.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mCurrentOutfit[WEAPON3].SetVertex(CURRENT_OUTFIT);
	mCurrentOutfit[WEAPON3].SetColor(WHITE_COLOR);
	mCurrentOutfit[WEAPON3].position = CVector2(CURRENT_POS);
	mCurrentOutfit[WEAPON3].SetUv(CURRENT_UV);

	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"Board3.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mCurrentOutfit[WEAPON4].SetVertex(CURRENT_OUTFIT);
	mCurrentOutfit[WEAPON4].SetColor(WHITE_COLOR);
	mCurrentOutfit[WEAPON4].position = CVector2(CURRENT_POS);
	mCurrentOutfit[WEAPON4].SetUv(CURRENT_UV);

	////戻るボタンの呼び出し
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(BACK);	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-320.0f, 320.0f, -240.0f, 240.0f);
	mBackButton.SetVertex(BACK_RECT);
	mBackButton.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	mBackButton.SetUv(mpMenu,BACK_CG);
	mBackButton.position = BACK_POS;


	int rectcnt = RECT_WIDE;

	for (int i = 0; i < TIP_ARRAY; i++){

		rectcnt--;
		//装備品のアイコン群
		mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
		mpMenu->load(ITEM_ICON);	//テクスチャファイル読み込み
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		mOutfitIcon[i].SetVertex(OUTFIT_ICON);
		mOutfitIcon[i].SetColor(WHITE_COLOR);
		mOutfitIcon[i].position = CVector2(rectx, recty);
		mOutfitIcon[i].SetUv(mpMenu, mTexXL, 0, mTexXR, 400);
		rectx += 180.0f;
		mTexXL += 400;
		mTexXR += 400;
		if (rectcnt == 0){ rectx = FIRST_X; recty -= 180; rectcnt = RECT_WIDE; };

	}

    //装備が確定した事を知らせるポップアップ
    mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"itempop.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mPopUp.SetVertex(POP_SIZE);
	mPopUp.SetColor(WHITE_COLOR);
	mPopUp.position = CVector2(0,0);
	mPopUp.SetUv(mpMenu, 0, 0, 600, 400);


	/*カーソル四角作成*/
	mpTexCursor = new CTexture();
	mpTexCursor->load(TGA_FILE"cursor.tga");
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(mpTexCursor, CURSOR_CG);

}

//数字のテクスチャ設定を行う
void CItem::Number(int score, CRectangle2 &odifit, CRectangle2 &twdifit, CRectangle2 &thdifit){		//数字の処理
	//スコアを100で割ることで3桁目を取得
	int difit3 = score / 100;
	//スコアを 10で割ることで2桁目を取得
	int difit2 = (score - (difit3 * 100)) / 10;
	//スコアを  1で割ることで1桁目を取得
	int difit1 = score - ((difit3 * 100) + (difit2 * 10));
	//３ケタ目
	//どの数字が結果として出たかで処理を変える
	if (difit3 <= 0){ thdifit.ZERO; }
	if (difit3 == 1){ thdifit.ONE; }
	if (difit3 == 2){ thdifit.TWO; }
	if (difit3 == 3){ thdifit.THREE; }
	if (difit3 == 4){ thdifit.FOUR; }
	if (difit3 == 5){ thdifit.FIVE; }
	if (difit3 == 6){ thdifit.SIX; }
	if (difit3 == 7){ thdifit.SEVEN; }
	if (difit3 == 8){ thdifit.EIGHT; }
	if (difit3 == 9){ thdifit.NINE; }
	//2ケタ目
	//どの数字が結果として出たかで処理を変える
	if (difit2 <= 0){ twdifit.ZERO; }
	if (difit2 == 1){ twdifit.ONE; }
	if (difit2 == 2){ twdifit.TWO; }
	if (difit2 == 3){ twdifit.THREE; }
	if (difit2 == 4){ twdifit.FOUR; }
	if (difit2 == 5){ twdifit.FIVE; }
	if (difit2 == 6){ twdifit.SIX; }
	if (difit2 == 7){ twdifit.SEVEN; }
	if (difit2 == 8){ twdifit.EIGHT; }
	if (difit2 == 9){ twdifit.NINE; }
	//1ケタ目
	//どの数字が結果として出たかで処理を変える
	if (difit1 <= 0){ odifit.ZERO; }
	if (difit1 == 1){ odifit.ONE; }
	if (difit1 == 2){ odifit.TWO; }
	if (difit1 == 3){ odifit.THREE; }
	if (difit1 == 4){ odifit.FOUR; }
	if (difit1 == 5){ odifit.FIVE; }
	if (difit1 == 6){ odifit.SIX; }
	if (difit1 == 7){ odifit.SEVEN; }
	if (difit1 == 8){ odifit.EIGHT; }
	if (difit1 == 9){ odifit.NINE; }
}

//更新処理を行う
void CItem::Update(){
	//カーソルポジション
	mCursor.position = CMouse::GetInstance()->mPos;
	//攻撃力のナンバー設定
	Number(mSaveAtk, mAtkNo[0], mAtkNo[1], mAtkNo[2]);
	//常に更新を行いたいやつ
	mBackButton.SetColor(WHITE_COLOR);
	if (CCollision2D::Collision2D(mCursor, mBackButton)){ mBackButton.SetColor(GRAY_COLOR); }

	//確定buttonを押したときの処理
	if (CCollision2D::Collision2D(mCursor, mDecisionButton)){ //カーソルがあっている?
		mDecisionButton.SetColor(GRAY_COLOR);
		if (CMouse::GetInstance()->mOneLeftFlag){
			
			mPopUpFlag = true;
			mDecisionButton.SetColor(DARK_GRAY_COLOR);
		//選択中の武器によって処理を変更する。
			if (mSelectWeapon == WEAPON0){ status = WEAPON0; }
			if (mSelectWeapon == WEAPON1){ status = WEAPON1; }
			if (mSelectWeapon == WEAPON2){ status = WEAPON2; }
			if (mSelectWeapon == WEAPON3){ status = WEAPON3; }
			if (mSelectWeapon == WEAPON4){ status = WEAPON4; }

		}//マウス左クリック
	}
	else{
		mDecisionButton.SetColor(WHITE_COLOR);
	}
	if (mPopUpFlag){
		mPopTime -= POP_TIME;
		if (mPopTime <= 0){
			mPopUpFlag = false;
			mPopTime = FPS;
		}
	}
	//デフォルトハンマーは購入という概念が存在しない為ソールドアウトは武器のリストよりも数値が少ない
	//装備アイコン0を押したときの処理
	if (CCollision2D::Collision2D(mCursor, mOutfitIcon[WEAPON0])){ //カーソルがあっている?
		if (CMouse::GetInstance()->mOneLeftFlag){
			mSelectPicture.position = CVector2(SELECT_MARKER_POS_0);/*選択中四角形のポジション変更*/ 
			mSelectWeapon = WEAPON0;//ステータスを変更する
			mSaveAtk = WEAPON_ATKD;
		}//マウス左クリック
	}
	//装備アイコン1を押したときの処理
	if (CCollision2D::Collision2D(mCursor, mOutfitIcon[WEAPON1]) && CShop::mSoldOut[WEAPON0]){ //カーソルがあっている?
		if (CMouse::GetInstance()->mOneLeftFlag){
			mSelectPicture.position = CVector2(SELECT_MARKER_POS_1);/*選択中四角形のポジション変更*/
			mSelectWeapon = WEAPON1;
			mSaveAtk = WEAPON_ATK0;
		}//マウス左クリック
	}
	//装備アイコン2を押したときの処理
	if (CCollision2D::Collision2D(mCursor, mOutfitIcon[WEAPON2]) && CShop::mSoldOut[WEAPON1]){ //カーソルがあっている?
		if (CMouse::GetInstance()->mOneLeftFlag){
			mSelectPicture.position = CVector2(SELECT_MARKER_POS_2);/*選択中四角形のポジション変更*/
			mSelectWeapon = WEAPON2;
			mSaveAtk = WEAPON_ATK1;
		}//マウス左クリック
	}

	//
	////装備アイコン3を押したときの処理
	//if (CCollision2D::Collision2D(mCursor, mOutfitIcon[WEAPON3]) && CShop::mSoldOut[WEAPON2]){ //カーソルがあっている?
	//	if (CMouse::GetInstance()->mOneLeftFlag){
	//		mSelectPicture.position = CVector2(SELECT_MARKER_POS_3);/*選択中四角形のポジション変更*/
	//		mSelectWeapon = WEAPON3;
	//		mSaveAtk = WEAPON_ATK2;
	//	}//マウス左クリック
	//}
	////装備アイコン4を押したときの処理
	//if (CCollision2D::Collision2D(mCursor, mOutfitIcon[WEAPON4]) && CShop::mSoldOut[WEAPON3]){ //カーソルがあっている?
	//	if (CMouse::GetInstance()->mOneLeftFlag){
	//		mSelectPicture.position = CVector2(SELECT_MARKER_POS_4);/*選択中四角形のポジション変更*/
	//		mSelectWeapon = WEAPON4;
	//		mSaveAtk = WEAPON_ATK3;
	//	}//マウス左クリック
	//}
	//

	//武器の攻撃力とスキルを変更する。
	switch (status)
	{
	case WEAPON0:
		mAtk = WEAPON_ATKD;
		mSkillNo = WEAPON0;
		break;
	case WEAPON1:
		mAtk = WEAPON_ATK0;
		mSkillNo = WEAPON1;
		break;
	case WEAPON2:
		mAtk = WEAPON_ATK1;
		mSkillNo = WEAPON2;
		break;
	case WEAPON3:
		mAtk = WEAPON_ATK2;
		mSkillNo = WEAPON3;
		break;
	case WEAPON4:
		mAtk = WEAPON_ATK3;
		mSkillNo = WEAPON4;
		break;
	default:
		break;
	}




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
	case WEAPON3:
		mCurrentOutfit[WEAPON3].Render();
		break;
	case WEAPON4:
		mCurrentOutfit[WEAPON4].Render();
		break;
	
	
	default: 
		break;
	}





	//選択中
	mSelectText.Render();

	//装備中アイテムの名前
	

	//デフォルト
	mOutfitIcon[WEAPON0].Render();
	if (CShop::mSoldOut[WEAPON0])mOutfitIcon[WEAPON1].Render();
	if (CShop::mSoldOut[WEAPON1])mOutfitIcon[WEAPON2].Render();

//	if (CShop::mSoldOut[WEAPON2])mOutfitIcon[WEAPON3].Render();
//	if (CShop::mSoldOut[WEAPON3])mOutfitIcon[WEAPON4].Render();

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
/*












　　              　ｎ .／）)　　　　　　　／
	 　       　　ｒ‐┘ｲﾚk(_             <　　キリンです。
	          　.’,g｀.器├┘Yヽ　　　    ＼
		   　／ * 　 ン┴ｫ┼┬爻
		   . Lンノ￣　　　｀┼┤└〒ｪ
			　 　 　 　 　 　 寸　┌┼テｭ
						  　　 寸└┘┌斤ｭ，
							 　 寸┌┼┴‐代ｭ，
					             ┼┘┌┼┼┼ｭ
			              　　　　寸 .└┘└┘├
							     　┬┐┌┐┌┼┴┼┐
							       ┴┼┼┘└┼┐└┴┼┼┐
				　 　 　 　 　 　 代.└┘┌┐└┘┌┐└┘└┼ ，
		   　 　 　 　 　 　 　 　 ┼┐┌┼┘┌┐├┘┌┬┐└┼‐､.,,,,,＿___ ,ｨ冖ﾊ
				    　 　 　 　 　 ┼┘└┘┌┼┼┼┐├┼┘┌┤｀'''''''''''''''''''''ゝ ィ´
				 　　 　 　   　 　 ,┌┐┌ぃ┼┤├┼ヤ┴┘┌┼┤
							  　 　 /┼┘ｲ　 　.｀¨¨’.T´┬千ヽt┼┴‐!
					  　 　 　 　 ／┼イ 　! 　 　 　 　 !. ┼┤　 ＼┬┼ ,
			   　　 　 　 　 　 ,ｲXイ　 |┼┘　 　 　　　’┼ﾁ'. 　 　.｀　,┌┼，
					  　  　 　{┘ｲ 　　|└!　　　　 　 　　ヾ┼ﾊ　　　　 ｀ヾ┬┴,
						   　　 ＼ ヽ 　 }　/　　 　 　 　 　 　ﾍ┘ﾊ　 　 　　 ｀'┬ﾊ
						   　　　 ＼＼ﾙｲ 　 　 　 　 　 　.　ﾉ　,ｲ　　　　 　 　 ヽ　											
							        ヽ,＼ 　 　 　 　 　　　./ /　　　　 　 　 　　　'.ﾊ.
							　　　　 ハ__｀ｰｭ. 　 　 　 　 / / 　 　 　 　 　　　　　 '.　､
			    　 　 　 　 　 　 　 / f´　＼ﾊ　　　　　 / /　　　　　　　　　　　　　} ハ
					 　 　 　　 　 ／.丿　ｨ　 ｀’　　　.／ ﾉ　 　 　 　 　 　　　　　　ﾉ__ .,’
						      　 ∠ ヲ　　　 　 　 　 ∠ ヲ　　　　　　　　　　　　　　{_ イ


*/