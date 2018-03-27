//高橋弘樹
#ifndef CGAMECLEAR_HPP
#define CGAMECLEAR_HPP
#include"../../../Base/CBase.h"
#include "../../Graphic/CRectangle2.h"
#include"../CScene.h"

#define END_TIME 3.0f

class CGameClear :public CScene{
public:
	CRectangle2 mClearLogo;	//タイトルロゴ
	CRectangle2 mBG;        //バックグラウンドの略 （背景)


	CTexture mTexBG;//背景のテクスチャ
	CTexture mTexClearLogo;//クリアロゴのテクスチャ

	/*状態選択*/
	enum EStatus
	{
		E_GAMESTART,
		E_GAMEEXIT
	};
	EStatus eStatus;

	~CGameClear();
	CGameClear(){};
	void Init();
	void Update();
	void Render();

};
#endif
