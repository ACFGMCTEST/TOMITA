#ifndef CPAUSE_HPP
#define CPAUSE_HPP
#include "../../../Graphic/CRectangle2.h"
#include "../../CScene.h"


class CPause{
private:
	bool mPauseFlag;//�\����\��
	/*�|���S��*/
	CRectangle2 mCursor;//���[�\��
	CRectangle2 mPause;//�|�[�Y���
	CRectangle2 mMainBack;//���C���ɖ߂�
	CRectangle2 mTitleBack;//�^�C�g���ɖ߂�
	/*�e�N�X�`��*/
	CTexture	mTexCursor;//Cursor
	CTexture	mTexPause;//�|�[�Y���
	CTexture	mTexMainBack;//���C���ɂ��ǂ�
	CTexture	mTexTitleBack;//�^�C�g���ɖ߂�
	static CPause *mpPause;
	CPause();
	 ~CPause();
public:
	static CPause *GetInstance();


	//�`��
	void Render();
	//�X�V
	void Update();

};
#endif
