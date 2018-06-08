
#ifndef LOAD_TEX_MANAGER_HPP
#define LOAD_TEX_MANAGER_HPP
#include "CTexture.h"
/*�e�N�X�`���̃T�C�Y*/
#define T_MANA_HP_SIZE  STexVer(0,0,490,46)


class  CLoadTexManager
{
private:
	static CLoadTexManager *mLoadTexManager;
	CLoadTexManager();
	~CLoadTexManager();

public:
	static CLoadTexManager *GetInstance(); //GetInstance
	/*�r���{�[�h�̃��[�h*/
	CTexture *mpSpark;//�Ή�
	CTexture *mpHit;//�q�b�g�G�t�F�N�g
	CTexture *mpHp2DFrame;//�v���C���[��HP(frame)
	CTexture *mpHp2DGauge;//�v���C���[��HP(gauge)
	CTexture *mpSkyBox;//�X�J�C�{�b�N�X
private:

};

#endif