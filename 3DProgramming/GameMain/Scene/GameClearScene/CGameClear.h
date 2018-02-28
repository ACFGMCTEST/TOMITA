//�����O��
#ifndef CGAMECLEAR_HPP
#define CGAMECLEAR_HPP
#include"../../../Base/CBase.h"
#include "../../Graphic/CRectangle2.h"
#include"../CScene.h"

#define END_TIME 3.0f

class CGameClear :public CScene{
public:
	CRectangle2 mClearLogo;	//�^�C�g�����S
	CRectangle2 mBG;        //�o�b�N�O���E���h�̗� �i�w�i)


	CTexture	*mpTexture;
	CTexture	*mpMenu;

	float mEnd;
	float mAlpha=0.0f;

	/*��ԑI��*/
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
