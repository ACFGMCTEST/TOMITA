//高橋弘樹 && 冨田健斗
#ifndef HOME_HPP
#define HOME_HPP
#include "../Base\CBase.h"
#include "../GameMain\Graphic\CRectangle2.h"
#include "../GameMain\Scene\CScene.h"

#define MOVE_SPEED 25

class CHome :public CScene{
public:
	CRectangle2 mBG;		    //ゲームタイトル（背景）
	CRectangle2 mSelectButton;	//ゲーム開始
	CRectangle2 mOptionButton;  //ゲーム終了
	CRectangle2 mShopButton;    //ショップボタン
	CRectangle2 mItemButton;    //ショップボタン
	CRectangle2 mTitleButton;   //ホームボタン
	CRectangle2 mTextBox;	    //テキストボックス

	CRectangle2 mRightButton;
	CRectangle2 mLeftButton;

	CRectangle2 mCursor;//カーソル

	CTexture	*mpTexture;
	CTexture	*mpTexCursor;
	CTexture	*mpMenu;

	float alpha;
	float alpha2;

	int mStatus;  //メニュー移動処理のステータス

	const float mcMenuX = 150;				     //ボードのデフォルトサイズ
	const float mcMenuY = 105;

	const float mcBoardSubX = 90;
	const float mcBoardSubY = 65;

	enum E_MENU
	{
		QUEST,//クエスト
		SHOP,//ショップ
		ITEM,//アイテム
		TITLE,//タイトル
	};
	bool mHiddenFlag = false;			//隠蔽Flag

	bool mMove=false;

	float mMenuPos0 = 0;		//menuのポジション
	float mMenuPos1 = 400;
	float mMenuPos2 = 800;
	float mMenuPos3 = 1200;

	~CHome();
	CHome(){};
	void Init();
	void AllMove(bool zeroover);
	void Update();
	void Render();

};
#endif
