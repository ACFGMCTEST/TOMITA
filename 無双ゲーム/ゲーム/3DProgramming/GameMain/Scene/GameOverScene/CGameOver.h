#ifndef CGAMEOVER_HPP
#define CGAMEOVER_HPP
#include"../../../3DBase/C3DBase.h"
#include "../../Graphic/CRectangle2.h"
#include"../CScene.h"

/*ゲームオーバーのクラス*/
class CGameOver :public CScene{
public:
	CRectangle2 mGameOverLogo;	//タイトルロゴ
	CRectangle2 mBG;        //バックグラウンドの略 （背景)
	/*テクスチャ*/
	CTexture	mTexOverLogo;//ゲームオーバー



	float mAlpha=0.0f;
	float mAlpha2=0.0f;

	/*状態選択*/
	enum EStatus
	{
		E_GAMESTART,
		E_GAMEEXIT
	};
	EStatus eStatus;

	~CGameOver();
	CGameOver(){};
	void Init();
	void Update();
	void Render();

};
#endif
