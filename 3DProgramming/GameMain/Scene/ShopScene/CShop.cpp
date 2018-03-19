//高橋弘樹
#include "CShop.h"
#include"../../../Define/Define.h"
#include "../../Key/CKey.h"
#include <fstream> 
#include<stdio.h>
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"

#define POCKET_MONEY_TEX		  0,601,900,800 
#define POCKET_MONEY_RECT -100.0f, 40, 100.0f, -40
/*texフェイル*/
#define CURSOR_CG 0,0,150,120

bool CShop::mBuyScene = false;
bool CShop::mSoldOut[WEAPON_TYPE];

CShop::~CShop(){
	if (mpNum) {
		//テクスチャを使っていればインスタンス削除
		delete mpNum;
		mpNum = 0;
	}
	if (mpWeaponName) {
		//テクスチャを使っていればインスタンス削除
		delete mpWeaponName;
		mpWeaponName = 0;
	}
	if (mpTexture) {
		//テクスチャを使っていればインスタンス削除
		delete mpTexture;
		mpTexture = 0;
	}

	if (mpDollar) {
		//テクスチャを使っていればインスタンス削除
		delete mpDollar;
		mpDollar = 0;
	}
	
	if (mpBuyButton) {
		//テクスチャを使っていればインスタンス削除
		delete mpBuyButton;
		mpBuyButton = 0;
	}
}

CShop::CShop() :mWeapnNo(WEAPON0){}

//初期設定を行う
void CShop::Init(){

	//初回は売り切れにしておく事によって購入には条件があると思わせる
	mSoldOut[WEAPON2] = true;
	mSoldOut[WEAPON3] = true;

	mWeapnAtk[WEAPON0] = WEAPON_ATK0;//武器攻撃力
	mWeapnAtk[WEAPON1] = WEAPON_ATK1;
	mWeapnAtk[WEAPON2] = WEAPON_ATK2;
	mWeapnAtk[WEAPON3] = WEAPON_ATK3;

	mPrice   [WEAPON0] = WEAPON_PRICE0;//武器攻撃力
	mPrice   [WEAPON1] = WEAPON_PRICE1;
	mPrice   [WEAPON2] = WEAPON_PRICE2;
	mPrice   [WEAPON3] = WEAPON_PRICE3;

	//背景の呼び出し
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"BG.tga");	//テクスチャファイル読み込み

	mBackGround.SetVertex(BG_SIZE); //ここで大きさ変更
	mBackGround.SetColor(WHITE_COLOR);
	mBackGround.SetUv(mpTexture, 0, 0, 1024, 768);

	//ボードの呼び出し
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"Board0.tga");	//テクスチャファイル読み込み

	mBoard[WEAPON0].SetVertex(-mcBoardX, mcBoardY, mcBoardX, -mcBoardY); //ここで大きさ変更
	mBoard[WEAPON0].SetColor(WHITE_COLOR);
	mBoard[WEAPON0].position = CVector2(0, 90);
	mBoard[WEAPON0].SetUv(mpTexture, 0, 0, 600, 494);

	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"Board1.tga");	//テクスチャファイル読み込み
	mBoard[WEAPON1].SetVertex(-mcBoardX, mcBoardY, mcBoardX, -mcBoardY); //ここで大きさ変更
	mBoard[WEAPON1].SetColor(WHITE_COLOR);
	mBoard[WEAPON1].position = CVector2(0, 90);
	mBoard[WEAPON1].SetUv(mpTexture, 0, 0, 600, 494);
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"Board2.tga");	//テクスチャファイル読み込み
	mBoard[WEAPON2].SetVertex(-mcBoardX, mcBoardY, mcBoardX, -mcBoardY); //ここで大きさ変更
	mBoard[WEAPON2].SetColor(WHITE_COLOR);
	mBoard[WEAPON2].position = CVector2(0, 90);
	mBoard[WEAPON2].SetUv(mpTexture, 0, 0, 600, 494);
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"Board3.tga");	//テクスチャファイル読み込み
	mBoard[WEAPON3].SetVertex(-mcBoardX, mcBoardY, mcBoardX, -mcBoardY); //ここで大きさ変更
	mBoard[WEAPON3].SetColor(WHITE_COLOR);
	mBoard[WEAPON3].position = CVector2(0, 90);
	mBoard[WEAPON3].SetUv(mpTexture, 0, 0, 600, 494);



	//SoldOutの基本設定をボードと同じにする
	for (int i = 0; i < WEAPON_TYPE; i++){
		mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
		mpTexture->load(TGA_FILE"soldout.tga");	//テクスチャファイル読み込む
		mSoldOutTex[i].SetVertex(-mcBoardX, mcBoardY, mcBoardX, -mcBoardY);
		mSoldOutTex[i].SetColor(WHITE_COLOR);
		mSoldOutTex[i].position = CVector2(0, 90);
		mSoldOutTex[i].SetUv(mpTexture, 0, 0, 600, 494);
	}

	float WeaponNameX = NAME_X;
	float WeaponNameY = NAME_Y;

	int WeaponNameTexY1 = NAME_TEX_Y1;
	int WeaponNameTexY2 = NAME_TEX_Y2;

		//所持金

		mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
		mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
		mPocketMoney[2].SetVertex(ATK_NUM_RECT);
		mPocketMoney[2].SetColor(WHITE_COLOR);
		mPocketMoney[2].position = P_POS3;
		mPocketMoney[2].ZERO;

		mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
		mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
		mPocketMoney[1].SetVertex(ATK_NUM_RECT);
		mPocketMoney[1].SetColor(WHITE_COLOR);
		mPocketMoney[1].position = P_POS2;
		mPocketMoney[1].ZERO;

		mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
		mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
		mPocketMoney[0].SetVertex(ATK_NUM_RECT);
		mPocketMoney[0].SetColor(WHITE_COLOR);
		mPocketMoney[0].position = P_POS1;
		mPocketMoney[0].ZERO;
	

		//選択中の価格設定
		mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
		mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
		mPriceSave[2].SetVertex(ATK_NUM_RECT);
		mPriceSave[2].SetColor(WHITE_COLOR);
		mPriceSave[2].position = PS_POS3;
		mPriceSave[2].ZERO;

		mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
		mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
		mPriceSave[1].SetVertex(ATK_NUM_RECT);
		mPriceSave[1].SetColor(WHITE_COLOR);
		mPriceSave[1].position = PS_POS2;
		mPriceSave[1].ZERO;

		mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
		mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
		mPriceSave[0].SetVertex(ATK_NUM_RECT);
		mPriceSave[0].SetColor(WHITE_COLOR);
		mPriceSave[0].position = PS_POS1;
		mPriceSave[0].ZERO;


	for (int i = 0; i < WEAPON_TYPE; i++){
		
		//武器ネーム
		mpWeaponName = new CTexture();	//テクスチャクラスのインスタンス作成
		mpWeaponName->load(TGA_FILE"WeaponName.tga");	//テクスチャファイル読み込み
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		mWeaponName[i].SetVertex(WEAPON_NAME_RECT);
		mWeaponName[i].SetColor(WHITE_COLOR);
		mWeaponName[i].position = CVector2(WEAPON_NAME_POS);
		mWeaponName[i].SetUv(mpWeaponName, WEAPON_NAME_TEX);	
		//////////////////////////////////////////////////////////////////////////////////////

		mpDollar = new CTexture();	//テクスチャクラスのインスタンス作成
		mpDollar->load(TGA_FILE"Dollar.tga");	//テクスチャファイル読み込み
		mDollar[i].SetVertex(DOLLAR_RECT);
		mDollar[i].SetColor(WHITE_COLOR);
		mDollar[i].position = CVector2(DOLLAR_POS);
		mDollar[i].DOLLAR;
	
		//価格初期設定
		mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
		mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
		mPrice3[i].SetVertex(NUM_RECT);
		mPrice3[i].SetColor(WHITE_COLOR);
		mPrice3[i].position = CVector2(PRICE_3_POS);
		mPrice3[i].ZERO;
		mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
		mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
		mPrice2[i].SetVertex(NUM_RECT);
		mPrice2[i].SetColor(WHITE_COLOR);
		mPrice2[i].position = CVector2(PRICE_2_POS);
		mPrice2[i].ZERO;
		mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
		mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
		mPrice1[i].SetVertex(NUM_RECT);
		mPrice1[i].SetColor(WHITE_COLOR);
		mPrice1[i].position = CVector2(PRICE_1_POS);
		mPrice1[i].ZERO;
		//////////////////////////////////////////////////////////////////////////////////////
		
		WeaponNameX += NAME_FIRST_SET_MOVE;
		WeaponNameTexY1 += NAME_FIRST_SET_MOVE;
		WeaponNameTexY2 += NAME_FIRST_SET_MOVE;

	}
	//武器攻撃力
	mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	mWeaponAtk3.SetVertex(ATK_NUM_RECT);
	mWeaponAtk3.SetColor(BLACK_COLOR);
	mWeaponAtk3.position = CVector2(ATK_NUM3_POS);
	mWeaponAtk3.ZERO;
	mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	mWeaponAtk2.SetVertex(ATK_NUM_RECT);
	mWeaponAtk2.SetColor(BLACK_COLOR);
	mWeaponAtk2.position = CVector2(ATK_NUM2_POS);
	mWeaponAtk2.ZERO;
	mpNum = new CTexture();	//テクスチャクラスのインスタンス作成
	mpNum->load(TGA_FILE"Number.tga");	//テクスチャファイル読み込み
	mWeaponAtk1.SetVertex(ATK_NUM_RECT);
	mWeaponAtk1.SetColor(BLACK_COLOR);
	mWeaponAtk1.position = CVector2(ATK_NUM1_POS);
	mWeaponAtk1.ZERO;

	//所持金TEXT
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"ResultTips.tga");	//テクスチャファイル読み込み

	mPocketMoneyText.SetVertex(POCKET_MONEY_RECT);
	mPocketMoneyText.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	mPocketMoneyText.SetUv(mpTexture, POCKET_MONEY_TEX);
	mPocketMoneyText.position = MONEY_TEXT_POS;

	////戻るボタンの呼び出し
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"backbutton.tga");	//テクスチャファイル読み込み

	mBackButton.SetVertex(BACK_RECT);
	mBackButton.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	mBackButton.SetUv(mpTexture, BACK_CG);
	mBackButton.position = BACK_POS;



	/*カーソル四角作成*/
	mpTexCursor = new CTexture();
	mpTexCursor->load(TGA_FILE"cursor.tga");
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(mpTexCursor, CURSOR_CG);



	
	//価格テクスチャを貼っていく
	Number(mPrice[WEAPON0], mPrice1[WEAPON0], mPrice2[WEAPON0], mPrice3[WEAPON0]); 
	Number(mPrice[WEAPON1], mPrice1[WEAPON1], mPrice2[WEAPON1], mPrice3[WEAPON1]);
	Number(mPrice[WEAPON2], mPrice1[WEAPON2], mPrice2[WEAPON2], mPrice3[WEAPON2]);
	Number(mPrice[WEAPON3], mPrice1[WEAPON3], mPrice2[WEAPON3], mPrice3[WEAPON3]);

	//ポジションの初期設定
	mBoard[WEAPON0].position = CVector2(mWeaponPos0, 90);
	mBoard[WEAPON1].position = CVector2(mWeaponPos0 + mWeaponPos1, 90);
	mBoard[WEAPON2].position = CVector2(mWeaponPos0 + mWeaponPos2, 90);
	mBoard[WEAPON3].position = CVector2(mWeaponPos0 + mWeaponPos3, 90);


	////////購入確認画面の設定//////////////////////////////////////////////////////////////////////////
	//購入ボタン
	mpBuyButton = new CTexture();	//テクスチャクラスのインスタンス作成
	mpBuyButton->load(TGA_FILE"buynow.tga");	//テクスチャファイル読み込み
	mBuy.SetVertex(BUY_BOX_RECT);
	mBuy.SetColor(WHITE_COLOR);
	mBuy.position = CVector2(180, -70);
	mBuy.SetUv(mpBuyButton, BUY_BOX_TEX);

	mBuyShadow = mBuy;
	mBuyShadow.SetColor(SKELETON_BLACK_COLOR);
	mBuyShadow.position = CVector2(183, -75);

	//イエスボタン
	mpBuyButton = new CTexture();	//テクスチャクラスのインスタンス作成
	mpBuyButton->load(TGA_FILE"YesNo.tga");	//テクスチャファイル読み込み
	mYes.SetVertex(YES_NO_RECT);
	mYes.SetColor(WHITE_COLOR);
	mYes.position = CVector2(-120, -100);
	mYes.SetUv(mpBuyButton, YES_TEX);

	//ノーボタン
	mpBuyButton = new CTexture();	//テクスチャクラスのインスタンス作成
	mpBuyButton->load(TGA_FILE"YesNo.tga");	//テクスチャファイル読み込み
	mNo.SetVertex(YES_NO_RECT);
	mNo.SetColor(WHITE_COLOR);
	mNo.position = CVector2(120, -100);
	mNo.SetUv(mpBuyButton, NO_TEX);



	//半透明の背景の呼び出し
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"BG.tga");	//テクスチャファイル読み込み

	mSmoke.SetVertex(BUY_WINDOW_SIZE); //ここで大きさ変更
	mSmoke.SetColor(SKELETON_BLACK_COLOR);
	mSmoke.SetUv(mpTexture, 0, 0, 10, 10);


	status = 0;//デフォルトで0
}

//数字のテクスチャ設定を行う
void CShop::Number(int score, CRectangle2 &odifit, CRectangle2 &twdifit, CRectangle2 &thdifit){		//数字の処理
	//スコアを100で割ることで3桁目を取得
	int difit3 = score / 100;
	//スコアを 10で割ることで2桁目を取得
	int difit2 = (score - (difit3 * 100)) / 10;
	//スコアを  1で割ることで1桁目を取得
	int difit1 = score - ((difit3 * 100) + (difit2 * 10));
	//３ケタ目
	//どの数字が結果として出たかで処理を変える
	if (difit3 <= 0){thdifit. ZERO;}
	if (difit3 == 1){thdifit.  ONE;}
	if (difit3 == 2){thdifit.  TWO;}
	if (difit3 == 3){thdifit.THREE;}
	if (difit3 == 4){thdifit. FOUR;}
	if (difit3 == 5){thdifit. FIVE;}
	if (difit3 == 6){thdifit.  SIX;}
	if (difit3 == 7){thdifit.SEVEN;}
	if (difit3 == 8){thdifit.EIGHT;}
	if (difit3 == 9){thdifit. NINE;}
	//2ケタ目
	//どの数字が結果として出たかで処理を変える
	if (difit2 <= 0){twdifit. ZERO;}
	if (difit2 == 1){twdifit.  ONE;}
	if (difit2 == 2){twdifit.  TWO;}
	if (difit2 == 3){twdifit.THREE;}
	if (difit2 == 4){twdifit. FOUR;}
	if (difit2 == 5){twdifit. FIVE;}
	if (difit2 == 6){twdifit.  SIX;}
	if (difit2 == 7){twdifit.SEVEN;}
	if (difit2 == 8){twdifit.EIGHT;}
	if (difit2 == 9){twdifit. NINE;}
	//1ケタ目
	//どの数字が結果として出たかで処理を変える
	if (difit1 <= 0){odifit. ZERO;}
	if (difit1 == 1){odifit.  ONE;}
	if (difit1 == 2){odifit.  TWO;}
	if (difit1 == 3){odifit.THREE;}
	if (difit1 == 4){odifit. FOUR;}
	if (difit1 == 5){odifit. FIVE;}
	if (difit1 == 6){odifit.  SIX;}
	if (difit1 == 7){odifit.SEVEN;}
	if (difit1 == 8){odifit.EIGHT;}
	if (difit1 == 9){odifit. NINE;}
}

//項目全体の移動処理
void CShop::AllMove(bool zeroover){
	if ( zeroover){mWeaponPos0 += MOVE_SPEED;mWeaponPos1 += MOVE_SPEED;mWeaponPos2 += MOVE_SPEED;mWeaponPos3 += MOVE_SPEED;}
	if (!zeroover){mWeaponPos0 -= MOVE_SPEED;mWeaponPos1 -= MOVE_SPEED;mWeaponPos2 -= MOVE_SPEED;mWeaponPos3 -= MOVE_SPEED;}
}

//更新処理を行う
void CShop::Update(){
	if (CKey::push('W')){
		mItem.mMoney += 100;
	}

	//常に初期値での更新を行いたいやつ
	mWeaponName[WEAPON0].SetColor(WHITE_COLOR);
	mWeaponName[WEAPON1].SetColor(WHITE_COLOR);
	mWeaponName[WEAPON2].SetColor(WHITE_COLOR);
	mWeaponName[WEAPON3].SetColor(WHITE_COLOR);
	mBackButton.SetColor(WHITE_COLOR);
	mBuy.SetColor(WHITE_COLOR);
	mBuy.position = CVector2(180, -70);
	if (mBuyScene)mBuy.position = CVector2(183, -75);
	//ソールドアウトのポジションをボードと同じ位置にする
	for  (int i = 0; i < WEAPON_TYPE; i++)
	{
		mSoldOutTex[i].position = mBoard[i].position;
	}
	//backButtonと接触した時に判別できるように色を変える
	if (CCollision2D::Collision2D(mCursor, mBackButton)){ mBackButton.SetColor(GRAY_COLOR); }
	//ソールドアウトフラグが立っている時は赤色で表示する
	if (mSoldOut[WEAPON0])mBoard[WEAPON0].SetColor(DARK_GRAY_COLOR);
	if (mSoldOut[WEAPON1])mBoard[WEAPON1].SetColor(DARK_GRAY_COLOR);
	if (mSoldOut[WEAPON2])mBoard[WEAPON2].SetColor(DARK_GRAY_COLOR);
	if (mSoldOut[WEAPON3])mBoard[WEAPON3].SetColor(DARK_GRAY_COLOR);

	//無理やり所持金を増やせる奴
	if (CKey::push('W')){ mItem.mMoney += 10.0f; }


	//所持金のナンバーテクスチャ更新
	Number(mItem.mMoney, mPocketMoney[0], mPocketMoney[1], mPocketMoney[2]);
	//選択中の価格のテクスチャ変更
	Number(mPriceSelect, mPriceSave[0], mPriceSave[1], mPriceSave[2]);

	//武器攻撃力の更新
	mWeaponAtk1.SetVertex(ATK_NUM_RECT);
	mWeaponAtk2.SetVertex(ATK_NUM_RECT);
	mWeaponAtk3.SetVertex(ATK_NUM_RECT);
	mBuy.SetVertex(BUY_BOX_RECT);
	mBuyShadow.SetVertex(BUY_BOX_RECT);
	//隠す四角形の処理
	if (mHiddenFlag&&mMoveY>0){ mMoveY =0; }
	else if (!mHiddenFlag&&mMoveY < mcDefaultHidden){ mMoveY++; }
	//武器ボードの更新
	mBoard[WEAPON0].position = CVector2(mWeaponPos0, BOARD_Y);
	mBoard[WEAPON1].position = CVector2(mWeaponPos1, BOARD_Y);
	mBoard[WEAPON2].position = CVector2(mWeaponPos2, BOARD_Y);
	mBoard[WEAPON3].position = CVector2(mWeaponPos3, BOARD_Y);
	//武器詳細の表示の為の処理
	if (!mBuyScene){//購入確認画面でなければ処理を行う
		if (CCollision2D::Collision2D(mCursor, mWeaponName[WEAPON0]) ||
			CCollision2D::Collision2D(mCursor, mBoard[WEAPON0])){ //カーソルがあっている?
			mWeaponName[WEAPON0].SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag)//マウス左クリック
				mWeapnNo = WEAPON0;
			mHiddenFlag = true;
		}
		if (CCollision2D::Collision2D(mCursor, mWeaponName[WEAPON1]) ||
			CCollision2D::Collision2D(mCursor, mBoard[WEAPON1])){ //カーソルがあっている?
			mWeaponName[WEAPON1].SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag)//マウス左クリック
				mWeapnNo = WEAPON1;
			mHiddenFlag = true;
		}
		if (CCollision2D::Collision2D(mCursor, mWeaponName[WEAPON2]) ||
			CCollision2D::Collision2D(mCursor, mBoard[WEAPON2])){ //カーソルがあっている?
			mWeaponName[WEAPON2].SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag)//マウス左クリック
				mWeapnNo = WEAPON2;
			mHiddenFlag = true;
		}
		if (CCollision2D::Collision2D(mCursor, mWeaponName[WEAPON3]) ||
			CCollision2D::Collision2D(mCursor, mBoard[WEAPON3])){ //カーソルがあっている?
			mWeaponName[WEAPON3].SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag)//マウス左クリック
				mWeapnNo = WEAPON3;
			mHiddenFlag = true;
		}
		
		//購入ボタンを押したときの処理
		if (CCollision2D::Collision2D(mCursor, mBuy)){ //カーソルがあっている
			mBuy.SetColor(DARK_GRAY_COLOR);
			//ソールドアウトになると購入ボタンを無効にする
			for (int i = 0; i <WEAPON_TYPE; i++)
			{
				if (mWeapnNo == i&&!mSoldOut[i] && !mSoldOut[i]){
					if (CMouse::GetInstance()->mOneLeftFlag){ mBuyScene = true;/*購入を真に*/ 
					}/*マウス左クリック*/ 
				}
			}
		}
	}
	else{
		//イエスボタンを押したときの処理
		if (CCollision2D::Collision2D(mCursor, mYes)){ //カーソルがあっている?
			if (CMouse::GetInstance()->mOneLeftFlag){ 
				//WEAPON0を選択している//売り切れになっていない場合
				if (mWeapnNo == WEAPON0){
					//所持金が購入する武器の価格を超えている場合
					if (mPrice[WEAPON0] < mItem.mMoney)
					{
						mItem.mMoney -= mPrice[WEAPON0];
						
						//購入時の処理 売り切れ処理等
						
						//ボードを赤にして売り切れを示す
						mBoard[WEAPON0].SetColor(RED_COLOR);
						mSoldOut[WEAPON0] = true;
						//購入画面を閉じる
						mBuyScene = false;
					}
				}
				//WEAPON1を選択している
				else if (mWeapnNo == WEAPON1&&!mSoldOut[WEAPON1]){
					//所持金が購入する武器の価格を超えている場合
					if (mPrice[WEAPON1] < mItem.mMoney)
					{ 
						mItem.mMoney -= mPrice[WEAPON1];
						mBoard[WEAPON1].SetColor(RED_COLOR);
						mSoldOut[WEAPON1] = true;
						mBuyScene = false;
					}
				}
				//WEAPON2を選択している
				else if (mWeapnNo == WEAPON2&&!mSoldOut[WEAPON2]){
					//所持金が購入する武器の価格を超えている場合
					if (mPrice[WEAPON2] < mItem.mMoney)
					{ 
						mItem.mMoney -= mPrice[WEAPON2];
						mBoard[WEAPON2].SetColor(RED_COLOR);
						mSoldOut[WEAPON2] = true;
						mBuyScene = false;
					}
				}
				//WEAPON3を選択している
				else if (mWeapnNo == WEAPON3&&!mSoldOut[WEAPON3]){
					//所持金が購入する武器の価格を超えている場合
					if (mPrice[WEAPON3] < mItem.mMoney)
					{
						mItem.mMoney -= mPrice[WEAPON3];
						mBoard[WEAPON3].SetColor(RED_COLOR);
						mSoldOut[WEAPON3] = true;
						mBuyScene = false;
					}
				}
				else{ mBuyScene = false; }
			}//マウス左クリック
		}
		//ノーボタンを押したときの処理
		if (CCollision2D::Collision2D(mCursor, mNo)){ //カーソルがあっている?
			if (CMouse::GetInstance()->mOneLeftFlag){ mBuyScene = false;/*購入を真に*/ }//マウス左クリック
		}
	}

	//選択した武器によってポジションを変動させる。
	switch (mWeapnNo)
	{
	case WEAPON0:
		//ソールドアウトの時は購入ボタンを不活性化する
		if (mSoldOut[WEAPON0])mBuy.SetColor(DARK_GRAY_COLOR);
		//価格設定を武器毎に更新する
		mPriceSelect = mPrice[WEAPON0];
		//数字テクスチャ
		Number(mWeapnAtk[WEAPON0], mWeaponAtk1, mWeaponAtk2, mWeaponAtk3);
		//隠蔽フラグと移動フラグを管理して移動処理を行う
		if (mWeaponPos0 == 0)mHiddenFlag = false;
		if (mWeaponPos0 < 0/*ポジション０*/) { AllMove(true); }
		else if (mWeaponPos0 > 0) { AllMove(false); }
	    break;

	case WEAPON1:
		if (mSoldOut[WEAPON1])mBuy.SetColor(DARK_GRAY_COLOR);
		mPriceSelect = mPrice[WEAPON1];
		Number(mWeapnAtk[WEAPON1], mWeaponAtk1, mWeaponAtk2, mWeaponAtk3);
		if (mWeaponPos1 == 0)mHiddenFlag = false;
		if (mWeaponPos1 < 0) { AllMove(true); }
		else if (mWeaponPos1 > 0) { AllMove(false); }
		break;

	case WEAPON2 :
		if (mSoldOut[WEAPON2])mBuy.SetColor(DARK_GRAY_COLOR);
		mPriceSelect = mPrice[WEAPON2];
		Number(mWeapnAtk[WEAPON2], mWeaponAtk1, mWeaponAtk2, mWeaponAtk3);
		if (mWeaponPos2 == 0)mHiddenFlag = false;
		if (mWeaponPos2 < 0) { AllMove(true); }
		else if (mWeaponPos2 > 0) { AllMove(false); }
		break;

	case WEAPON3:
		if (mSoldOut[WEAPON3])mBuy.SetColor(DARK_GRAY_COLOR);
		mPriceSelect = mPrice[WEAPON3];
		Number(mWeapnAtk[WEAPON3], mWeaponAtk1, mWeaponAtk2, mWeaponAtk3);
		if (mWeaponPos3 == 0)mHiddenFlag = false;
		if (mWeaponPos3 < 0) { AllMove(true); }
		else if (mWeaponPos3 > 0) { AllMove(false); }
		break;

	default:
		break;
	}
	mBoard[WEAPON0].SetVertex(-mBoardX, mBoardY, mBoardX, -mBoardY); //ここで大きさ変更
	mCursor.position = CMouse::GetInstance()->mPos;	//カーソルのポジション
	//ボードの移動処理
	if (mBoardX >= mcBoardX + mcBoardSubX){mBoardX -= mcBoardSubX;}
	if (mBoardY >= mcBoardY + mcBoardSubY){mBoardY -= mcBoardSubY;}
};

//描画する
void CShop::Render() {

	CRectangle2::Disp2D_Start();//描画開始
	mBackGround.Render();
	mBackButton.Render();
	for (int i = 0; i < WEAPON_TYPE; i++) { 
		mBoard[i].Render();
		mWeaponName[i].Render();
		mDollar[i]    .Render();
		mPrice3[i]    .Render();
		mPrice2[i]    .Render();
		mPrice1[i]    .Render();
	};
	for (int i = 0; i < DIGIT; i++)
	{
		mPocketMoney[i].Render();
	}
	mBuyShadow.Render();
	mBuy.Render();
	mWeaponAtk3.Render();
	mWeaponAtk2.Render();
	mWeaponAtk1.Render();
	mPocketMoneyText.Render();
	for (int i = 0; i < WEAPON_TYPE; i++) {
		if (mSoldOut[i]){
			mSoldOutTex[i].Render();
		}
	}
	if (mBuyScene){
		mSmoke.Render();
		for (int i = 0; i < DIGIT; i++)
		{
			mPriceSave[i].Render();
		}
		mYes.Render();
		mNo.Render();
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