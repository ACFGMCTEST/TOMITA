/*
�^�C�g���N���X
*/
#ifndef TITLE_HPP
#define TITLE_HPP
#include "../../Graphic/CRectangle2.h"

/*SCROLL�p�̒l*/
#define TEX_BG_SCROLL	800
#define SCROLL_SPEED	0.5f

class CTitle{
private:
	/*�|���S��*/
	CRectangle2 mPushKey;//�����Ă����������S�|���S��
	/*�e�N�X�`��*/
	CTexture mTexPushKey;//�����Ă����������S�|���S��
	/*BG��Scroll���p���ϐ�*/
	static float mScrollLeft;
	static float mScrollRight;
public:
	/*�p���p�|���S��*/
	CRectangle2 mTitleLogo;//�^�C�g�����S�|���S��
	CRectangle2 mCursor;//�J�[�\��
	CRectangle2 mBG; //�w�i�|���S��
	/*�p���p�e�N�X�`��*/
	CTexture mTexTitleLogo;//�^�C�g�����S�e�N�X�`��
	CTexture mTexBG; //�w�i
	CTexture mTexCursor; //�J�[�\��
	/*�t�F�[�h�A�E�g�J�n�t���O*/
	bool mFlagFadeOut;

	
	~CTitle();
	CTitle();
	/*BG��Scroll����*/
	void Scroll();
	/*�X�V����*/
	void Update();
	/*�V�[���J�ڂ���Ƃ��Ɏg��*/
	bool SceneFlag();
	/*�`�揈��*/
	void Render();
	/*BG��SCROLL���p��Init*/
	void BgScrollInit();


};
#endif
