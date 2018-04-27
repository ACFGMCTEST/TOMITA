//�����O��

#ifndef CPAUSE_HPP
#define CPAUSE_HPP
#include "../../../../Base/CBase.h"
#include "../../../Graphic/CRectangle2.h"
#include "../../CScene.h"


class CPause{
public:
	static bool mSceneChangeFlag;//�V�[�����ς��t���O

	CRectangle2 mPauseLogo;	//�|�[�Y���S
	CRectangle2 mBG;        //�o�b�N�O���E���h�̗� �i�w�i)
	CRectangle2 mBack;		//�Q�[���֖߂�
	CRectangle2 mTitleBack;		//�^�C�g���I��
	CRectangle2 mCursor;//�J�[�\��

	CTexture	*mpTexture;
	CTexture	*mpTexCursor;

	
	static bool mGoTitle;
	static bool mBackGame;

	/*��ԑI��*/
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
