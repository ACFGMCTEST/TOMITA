#ifndef CGAMEOVER_HPP
#define CGAMEOVER_HPP
#include"../../../3DBase/C3DBase.h"
#include "../../Graphic/CRectangle2.h"
#include"../CScene.h"

/*�Q�[���I�[�o�[�̃N���X*/
class CGameOver :public CScene{
public:
	CRectangle2 mGameOverLogo;	//�^�C�g�����S
	CRectangle2 mBG;        //�o�b�N�O���E���h�̗� �i�w�i)
	/*�e�N�X�`��*/
	CTexture	mTexOverLogo;//�Q�[���I�[�o�[



	float mAlpha=0.0f;
	float mAlpha2=0.0f;

	/*��ԑI��*/
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
