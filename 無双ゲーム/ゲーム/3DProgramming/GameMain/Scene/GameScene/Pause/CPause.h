#ifndef CPAUSE_HPP
#define CPAUSE_HPP
#include "../../../Graphic/CRectangle2.h"
#include "../../CScene.h"


class CPause{
private:
	bool mOperationFlag;//Operation�\��
public:
	static bool mSceneChangeFlag;//�V�[�����ς��t���O

	CRectangle2 mPauseLogo;	//�|�[�Y���S
	CRectangle2 mBG;        //�o�b�N�O���E���h�̗� �i�w�i)
	/*�{�^��*/
	CRectangle2 mBackButton;		//�Q�[���֖߂�
	CRectangle2 mTitleBackButton;	//�^�C�g���I��
	CRectangle2 mGuideButton;//��������{�^��

	CRectangle2 mCursor;//�J�[�\��
	CRectangle2 mOperation;//�������

	/*�e�N�X�`��*/
	CTexture	mTexFilter;	//�t�B���^
	CTexture	mTexPauze;	//�|�[�Y
	CTexture	mTexCursor;	//�J�[�\��
	CTexture	mTexResume;	//�Q�[���ɖ߂�
	CTexture	mTexQuit;	//�I������
	CTexture	mTexOperation;//�������
	CTexture	mTexGuideButton;//��������ɍs���{�^��

	
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
	CPause();
	void Init();
	void Update();
	void Render();

};
#endif
