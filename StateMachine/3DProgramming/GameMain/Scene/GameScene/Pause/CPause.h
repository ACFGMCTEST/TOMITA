//高橋弘樹

#ifndef CPAUSE_HPP
#define CPAUSE_HPP
#include "../../../../Base/CBase.h"
#include "../../../Graphic/CRectangle2.h"
#include "../../CScene.h"


class CPause{
public:
	static bool mSceneChangeFlag;//シーンが変わるフラグ

	CRectangle2 mPauseLogo;	//ポーズロゴ
	CRectangle2 mBG;        //バックグラウンドの略 （背景)
	CRectangle2 mBack;		//ゲームへ戻る
	CRectangle2 mTitleBack;		//タイトル終了
	CRectangle2 mCursor;//カーソル

	CTexture	*mpTexture;
	CTexture	*mpTexCursor;

	
	static bool mGoTitle;
	static bool mBackGame;

	/*状態選択*/
	enum EStatus
	{
		E_GAMESTART,
		E_GAMEEXIT
	};
	EStatus eStatus;

	~CPause();
	CPause(){};
	void Init();
	void Update();
	void Render();

};
#endif
