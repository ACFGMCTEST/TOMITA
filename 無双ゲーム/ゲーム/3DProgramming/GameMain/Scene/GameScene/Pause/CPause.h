#ifndef CPAUSE_HPP
#define CPAUSE_HPP
#include "../../../Graphic/CRectangle2.h"
#include "../../CScene.h"


class CPause{
private:
	bool mOperationFlag;//Operation表示
public:
	static bool mSceneChangeFlag;//シーンが変わるフラグ

	CRectangle2 mPauseLogo;	//ポーズロゴ
	CRectangle2 mBG;        //バックグラウンドの略 （背景)
	/*ボタン*/
	CRectangle2 mBackButton;		//ゲームへ戻る
	CRectangle2 mTitleBackButton;	//タイトル終了
	CRectangle2 mGuideButton;//操作説明ボタン

	CRectangle2 mCursor;//カーソル
	CRectangle2 mOperation;//操作説明

	/*テクスチャ*/
	CTexture	mTexFilter;	//フィルタ
	CTexture	mTexPauze;	//ポーズ
	CTexture	mTexCursor;	//カーソル
	CTexture	mTexResume;	//ゲームに戻る
	CTexture	mTexQuit;	//終了する
	CTexture	mTexOperation;//操作説明
	CTexture	mTexGuideButton;//操作説明に行くボタン

	
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
	CPause();
	void Init();
	void Update();
	void Render();

};
#endif
