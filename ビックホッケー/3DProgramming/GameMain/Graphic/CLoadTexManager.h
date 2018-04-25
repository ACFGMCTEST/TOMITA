
#ifndef LOAD_TEX_MANAGER_HPP
#define LOAD_TEX_MANAGER_HPP
#include "CTexture.h"


/*�e�N�X�`���T�C�Y*/
#define TEX_SPEED_UP_SIZE		0,0,100,100
#define TEX_SPEED_DOWN_SIZE		0,0,100,100
#define TEX_NET_SIZE			0,0,200*CMap::mMapX,200
#define TEX_WALL_SIZE			0,0,300,300
#define TEX_SLOPE_SIZE			0,0,300,300
#define TEX_BOX_SIZE			0,0,300,300


class  CLoadTexManager
{
private:
	static CLoadTexManager *mLoadTexManager;
	CLoadTexManager();
	~CLoadTexManager();

public:
	static CLoadTexManager *GetInstance(); //GetInstance

	/*�{�b�N�X�̃��[�h*/
	CTexture *mpTile;//�^�C��
	CTexture *mpBox;//����
	CTexture *mpFastFloor;//������
	CTexture *mpSlowFloor;//������
	CTexture *mpTrampoline;//�g�����|����
	CTexture *mpSlope;//��
	CTexture *mpNet;//��
	CTexture *mpWall;//��
	/*�r���{�[�h�̃��[�h*/
	CTexture *mpSpark;//�Ή�
	CTexture *mpHammer;//�n���}�[



	

private:

};

#endif