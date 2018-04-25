//高橋弘樹
#ifndef CTITLE_HPP
#define CTITLE_HPP
#include"../../../Base/CBase.h"
#include "../../Graphic/CRectangle2.h"
#include"../CScene.h"


class CTitle :public CScene{
public:
	CRectangle2 mTitleLogo;	//タイトルロゴ
	CRectangle2 mShadow;	//タイトルロゴ
	CRectangle2 mBG;        //バックグラウンドの略 （背景)

	CRectangle2 mUnityChanLicense;	//ユニティちゃんのLicense

	CRectangle2 mGameStart;	//ゲーム開始
	CRectangle2 mGameExit;	//ゲーム終了
	CRectangle2 mCursor;	//カーソル

	
	CTexture	*mpBg;
	CTexture	*mpTextureLight_Frame;
	CTexture	*mpTexturetitle;
	CTexture	*mpTexturecursor;
	CTexture	*mpMenu;

	bool mMaxSize;

	//ボタン２種のデフォルトサイズ
	const float mButtonX = 150.0f;
	const float mButtonY = 75.0f;

	const float mChangeSize = 5.0f;

	const float mExpansionLimit = 1.5f;

	//ボタン２種のスケーリング用変数
	float mScalingRectX;
	float mScalingRectY;


	float mAlpha;
	/*状態選択*/
	enum EStatus
	{
		E_GAMESTART,
		E_GAMEEXIT
	};
	EStatus eStatus;

	~CTitle();
	CTitle(){
		mpBg = 0;
		mpTextureLight_Frame = 0;
		mpTexturetitle = 0;
		mpTexturecursor = 0;
		mpMenu = 0;
	};
	void Init();
	void Update();
	void Render();

};
#endif
