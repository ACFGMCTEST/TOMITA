//‚‹´O÷
#ifndef COUNTDOWN_HPP
#define COUNTDOWN_HPP
#include"../../../Base/CBase.h"
#include "../../Graphic/CRectangle2.h"
#include "../../Scene/CSceneManager.h"
#include"../CScene.h"

class CCountDown :public CScene{
public:

	CRectangle2 mNumberBox;	//ÅİÊŞ°
	CRectangle2 mReadyBox;

	CTexture	*mpTexture;
	CTexture	*mpReady;
	
	const float cmCountInit = FPS * 5;//mCount‚Ì‰Šú’l

	float mCount;
	float mAlpha;
	//float mAlpha2;

	/*ó‘Ô‘I‘ğ*/
	enum EStatus
	{
		E_GAMESTART,
		E_GAMEEXIT
	};

	EStatus eStatus;

	~CCountDown();
	CCountDown(){};
	void Init();
	void Update();
	void Render();

};
#endif
