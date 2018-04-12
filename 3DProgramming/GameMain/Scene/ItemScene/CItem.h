//高橋弘樹
#ifndef CItem_HPP
#define CItem_HPP
#include "../../Graphic/CRectangle2.h"
#define WEAPON_ATKD	100		//デフォルトハンマー
#define WEAPON_ATK0 130
#define WEAPON_ATK1 120
#define WEAPON_ATK2 222
#define WEAPON_ATK3 110

#define TIP_ARRAY 5
#define DIGIT 3

class CItem{
public:

	CRectangle2 mBackGround;		//背景
	
	CRectangle2 mCurrentOutfit[TIP_ARRAY];		//現在装備
	
	CRectangle2 mCurrentName;		//現在装備の名前

	CRectangle2 mCurrentStatus;		//現在装備のステータス

	CRectangle2 mCurrentIcon;		//装備中アイコン

	CRectangle2 mOutfitIcon[TIP_ARRAY];	//装備選択アイコン

	CRectangle2 mBackButton;	    //戻るボタン

	CRectangle2 mCursor;			//カーソル

	CRectangle2 mDecideButton;		//装備決定ボタン
	
	CRectangle2 mSelectText;		//装備中テキスト

	CRectangle2 mSelectPicture;		//選択中の装備アイコンの下に四角形を置く

	CRectangle2 mDecisionButton;    //決定ボタン

	CRectangle2 mAtkNo[DIGIT];				//攻撃力の数値	[3]は3桁の意

	CRectangle2 mPopUp;				//装備確定のお知らせ表示

	
	CTexture	*mpTexture;
	CTexture	*mpMenu;
	CTexture	*mpNum;
	CTexture	*mpTexCursor;


   enum E_WEAPONLIST
	{
		WEAPON0,//デフォルトハンマー
		WEAPON1,//ツナ
		WEAPON2,//ピコハン
	};



	bool mPopUpFlag=false;		//ポップアップ描画フラグ
	float mPopTime = FPS;


	float alpha;	//アルファチャンネル調整用
	float alpha2;

	static int mSaveAtk;		//表示用の武器攻撃力

	static float mMoney;	//所持金

	static int   mAtk;      //装備後の攻撃力

	static int   mSkillNo;  //スキルの番号

	static int mEquipped;	//現在の装備情報


	static int status ;	//武器選択のスイッチ用

	static int mSelectWeapon;	//武器選択時のスイッチ用

	int rectnum;	//四角形の数
	int rectx;		//四角形のｘ座標
	int recty;		//四角形のｙ座標
	int mTexXL;		//テクスチャX left
	int mTexXR;		//テクスチャX right


	~CItem();
	CItem();
	void Number(int Score, CRectangle2 &odifit, CRectangle2 &twdifit, CRectangle2 &thdifit);//スコア用の数字表示の関数
	void Init();
	void Update();
	void Render();

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