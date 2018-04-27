//高橋弘樹
//冨田健斗
#ifndef CShop_HPP
#define CShop_HPP

#include  "../../Graphic/CRectangle2.h"
#include "../ItemScene/CItem.h"

#define WEAPON_TYPE 4
#define DIGIT 3 //桁数
//////////num/////////////////////////////////////////////////////////////
#define DOLLAR	 SetUv(mpDollar,0,   0,  100, 100);
#define ZERO	 SetUv(mpNum,   0,   0,  100, 100);
#define ONE		 SetUv(mpNum, 100,   0,  200, 100);
#define TWO		 SetUv(mpNum, 200,   0,  300, 100);
#define THREE	 SetUv(mpNum, 300,   0,  400, 100);
#define FOUR	 SetUv(mpNum, 400,   0,  500, 100);
#define FIVE	 SetUv(mpNum, 500,   0,  600, 100);
#define SIX		 SetUv(mpNum, 600,   0,  700, 100);
#define SEVEN	 SetUv(mpNum, 700,   0,  800, 100);
#define EIGHT	 SetUv(mpNum, 800,   0,  900, 100);
#define NINE	 SetUv(mpNum, 900,   0, 1000, 100);
//////////////////////////////////////////////////////////////////////////
#define DOLLAR_RECT -25.0f, 25.0f, 25.0f, -25.0f
#define NUM_RECT	-25.0f, 25.0f, 25.0f, -25.0f
//////////////////////////////////////////////////////////////////////////
#define DOLLAR_POS  WeaponNameX-60.0f, WeaponNameY+50.0f
#define PRICE_3_POS WeaponNameX-20.0f, WeaponNameY+50.0f
#define PRICE_2_POS WeaponNameX+20.0f, WeaponNameY+50.0f
#define PRICE_1_POS WeaponNameX+60.0f, WeaponNameY+50.0f
//////////////////////////////////////////////////////////////////////////
#define WEAPON_NAME_RECT -75.0f, 25.0f, 75.0f, -25.0f
#define WEAPON_NAME_POS WeaponNameX, WeaponNameY
#define WEAPON_NAME_TEX  0, WeaponNameTexY1, 900, WeaponNameTexY2
//////////////////////////////////////////////////////////////////////////
#define ATK_NUM3_POS - 200, -70
#define ATK_NUM2_POS - 150, -70
#define ATK_NUM1_POS - 100, -70

//武器攻撃力&価格
//////////////////////////////////////////////////////////////////////////
#define WEAPON_ATKD	100		//デフォルトハンマー
#define WEAPON_ATK0 130
#define WEAPON_ATK1 120
#define WEAPON_ATK2 222
#define WEAPON_ATK3 110

#define WEAPON_PRICE0 200
#define WEAPON_PRICE1 320
#define WEAPON_PRICE2 422
#define WEAPON_PRICE3 510

#define BOARD_Y  90

#define MOVE_SPEED 50

#define NAME_FIRST_SET_MOVE 200.0f

#define NAME_X -300
#define NAME_Y -200

#define NAME_TEX_Y1 0
#define NAME_TEX_Y2 200
//////購入ボタンの設定/////////////////////////////////////////////////////////////////////////////////////////
#define BUY_BOX_TEX   0,0,900,200 

#define YES_TEX		  0,  0,900,200 
#define NO_TEX		  0,201,900,400 

#define BUY_BOX_RECT -75.0f, mMoveY, 75.0f, -mMoveY

#define YES_NO_RECT -100.0f, 40, 100.0f, -40

#define ATK_NUM_RECT     -25.0f, mMoveY, 25.0f, -mMoveY

///////購入画面の設定/////////////////////////////////////////////////////////////////////////////
#define BUY_WINDOW_SIZE -300,200,300,-200 //背景のサイズ

#define P_POS1 CVector2( 340, -260) //ポケットマネーのポジション
#define P_POS2 CVector2( 280, -260)
#define P_POS3 CVector2( 220, -260)

#define MONEY_TEXT_POS CVector2( 120, -260)

#define PS_POS1 CVector2(  60, 100) //選択中の価格ポジション
#define PS_POS2 CVector2(  00, 100)
#define PS_POS3 CVector2( -60, 100)

class CShop{
public:

	CItem mItem;								//アイテム

	CRectangle2 mBackGround;	             	 //背景

	CRectangle2 mWeaponName[WEAPON_TYPE];		 //武器の名前
	//CRectangle2 mNamePlate [WEAPON_TYPE];		 //武器の名前(Board上)

	CRectangle2 mWeaponAtk3;					 //攻撃力3桁目
	CRectangle2 mWeaponAtk2;					 //攻撃力2桁目
	CRectangle2 mWeaponAtk1;					 //攻撃力1桁目

	CRectangle2 mDollar[WEAPON_TYPE];		     //価格の横に付ける＄マーク
	CRectangle2 mPrice3[WEAPON_TYPE];	    	 //値段3桁目
	CRectangle2 mPrice2[WEAPON_TYPE];	     	 //値段2桁目
	CRectangle2 mPrice1[WEAPON_TYPE];		     //値段1桁目

	CRectangle2 mPocketMoney[DIGIT];             //所持金の表示
	CRectangle2 mPriceSave[DIGIT];			 //選択中の価格

	CRectangle2 mBoard[WEAPON_TYPE];	     //要素を乗っける用のお皿
	CRectangle2 mSoldOutTex[WEAPON_TYPE];	     //要素を乗っける用のお皿

	CRectangle2 mBackButton;					 //戻るボタン

	CRectangle2 mCursor;						 //カーソル

	////ここから購入関係
	CRectangle2 mBuy;							 //購入ボタン

	CRectangle2 mBuyShadow;

	CRectangle2 mText;					         //確認用テキスト

	CRectangle2 mYes;							 //イエスボタン

	CRectangle2 mNo;						     //ノーボタン

	CRectangle2 mSmoke;							 //半透明の黒色っぽいやつ

	CRectangle2 mPocketMoneyText;					//所持金

	/////////////////////////////////////////////////////////////////////////////////

	int mMoney=999;								 //所持金（仮）

	float mWeaponPos0 = 0;						 //武器ボードのポジション
	float mWeaponPos1 = 650;
	float mWeaponPos2 = 1300;
	float mWeaponPos3 = 1950;

	const float mcDefaultHidden = 25.0f;		 //一時的に隠す時のDefault数値

	float mMoveY = 25.0f;					     //メニュー変更時の上下変更用

	const float mcBoardX = 300;				     //ボードのデフォルトサイズ
	const float mcBoardY = 210;

	const float mcBoardSubX = 90;
	const float mcBoardSubY = 65;

	float mBoardX = mcBoardX*10;				 //初回のボードサイズ
	float mBoardY = mcBoardY*10;

	int mWeapnNo;						//武器ナンバー
	int mPrice   [WEAPON_TYPE];			//アイテムの価格
	int mPriceSelect;					//選択中のアイテムの価格

	int mWeapnAtk[WEAPON_TYPE];         //武器攻撃力

	static bool mSoldOut[WEAPON_TYPE];
	//bool mBuyFlag[WEAPON_TYPE];


	bool mHiddenFlag = false;			//隠蔽Flag
	static bool mBuyScene ;				//購入scene

	enum E_WEAPON
	{
		WEAPON0,//みょるにる
		WEAPON1,//ツナ
		WEAPON2,//ピコハン
		WEAPON3,//ﾊﾞﾄﾙﾊﾝﾏ-
	};

	CTexture	*mpTexture;
	CTexture	*mpWeaponName;
	CTexture	*mpDollar;
	CTexture	*mpNum;
	CTexture    *mpBuyButton;
	CTexture	*mpTexCursor;
	int status;

	~CShop();
	CShop();
	void Number(int Score, CRectangle2 &odifit, CRectangle2 &twdifit, CRectangle2 &thdifit);//スコア用の数字表示の関数
	void Init();
	void Update();
	void Render();
	void AllMove(bool zeroover);
};
#endif
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