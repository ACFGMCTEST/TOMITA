/*
タイトルクラス
*/
#ifndef TITLE_HPP
#define TITLE_HPP
#include "../../Graphic/CRectangle2.h"

/*SCROLL用の値*/
#define TEX_BG_SCROLL	800
#define SCROLL_SPEED	0.5f

class CTitle{
private:
	/*ポリゴン*/
	CRectangle2 mPushKey;//押してくださいロゴポリゴン
	/*テクスチャ*/
	CTexture mTexPushKey;//押してくださいロゴポリゴン
	/*BGのScroll引継ぎ変数*/
	static float mScrollLeft;
	static float mScrollRight;
public:
	/*継承用ポリゴン*/
	CRectangle2 mTitleLogo;//タイトルロゴポリゴン
	CRectangle2 mCursor;//カーソル
	CRectangle2 mBG; //背景ポリゴン
	/*継承用テクスチャ*/
	CTexture mTexTitleLogo;//タイトルロゴテクスチャ
	CTexture mTexBG; //背景
	CTexture mTexCursor; //カーソル
	/*フェードアウト開始フラグ*/
	bool mFlagFadeOut;

	
	~CTitle();
	CTitle();
	/*BGのScroll処理*/
	void Scroll();
	/*更新処理*/
	void Update();
	/*シーン遷移するときに使う*/
	bool SceneFlag();
	/*描画処理*/
	void Render();
	/*BGのSCROLL引継ぎInit*/
	void BgScrollInit();


};
#endif
