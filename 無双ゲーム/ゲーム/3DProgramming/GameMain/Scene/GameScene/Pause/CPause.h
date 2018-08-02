#ifndef CPAUSE_HPP
#define CPAUSE_HPP
#include "../../../Graphic/CRectangle2.h"
#include "../../CScene.h"


class CPause{
private:
	bool mPauseFlag;//表示非表示
	/*ポリゴン*/
	CRectangle2 mCursor;//かーソル
	CRectangle2 mPause;//ポーズ画面
	CRectangle2 mMainBack;//メインに戻る
	CRectangle2 mTitleBack;//タイトルに戻る
	/*テクスチャ*/
	CTexture	mTexCursor;//Cursor
	CTexture	mTexPause;//ポーズ画面
	CTexture	mTexMainBack;//メインにもどる
	CTexture	mTexTitleBack;//タイトルに戻る
	static CPause *mpPause;
	CPause();
	 ~CPause();
public:
	static CPause *GetInstance();


	//描画
	void Render();
	//更新
	void Update();

};
#endif
