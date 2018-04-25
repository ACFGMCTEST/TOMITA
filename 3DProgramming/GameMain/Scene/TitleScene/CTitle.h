//�����O��
#ifndef CTITLE_HPP
#define CTITLE_HPP
#include"../../../Base/CBase.h"
#include "../../Graphic/CRectangle2.h"
#include"../CScene.h"


class CTitle :public CScene{
public:
	CRectangle2 mTitleLogo;	//�^�C�g�����S
	CRectangle2 mShadow;	//�^�C�g�����S
	CRectangle2 mBG;        //�o�b�N�O���E���h�̗� �i�w�i)

	CRectangle2 mUnityChanLicense;	//���j�e�B������License

	CRectangle2 mGameStart;	//�Q�[���J�n
	CRectangle2 mGameExit;	//�Q�[���I��
	CRectangle2 mCursor;	//�J�[�\��

	
	CTexture	*mpBg;
	CTexture	*mpTextureLight_Frame;
	CTexture	*mpTexturetitle;
	CTexture	*mpTexturecursor;
	CTexture	*mpMenu;

	bool mMaxSize;

	//�{�^���Q��̃f�t�H���g�T�C�Y
	const float mButtonX = 150.0f;
	const float mButtonY = 75.0f;

	const float mChangeSize = 5.0f;

	const float mExpansionLimit = 1.5f;

	//�{�^���Q��̃X�P�[�����O�p�ϐ�
	float mScalingRectX;
	float mScalingRectY;


	float mAlpha;
	/*��ԑI��*/
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
