#include "CLoadTexManager.h"
#include "../../Define/Define.h"

/*�e�N�X�`���ꏊ �r���{�[�h*/
#define TEX_FILE_SPARK_EFFECT	TGA_FILE"GameEffect\\spark.tga"			//�S�[���G�t�F�N�g�ꏊ 

CLoadTexManager *CLoadTexManager::mLoadTexManager = 0;

//GetInstance
CLoadTexManager* CLoadTexManager::GetInstance(){
	if (mLoadTexManager == 0) {
		mLoadTexManager = new CLoadTexManager();
	}
	return mLoadTexManager;
}

CLoadTexManager::CLoadTexManager()
{
	/*�ΉԃG�t�F�N�g*/
	mpSpark = new CTexture();
	mpSpark->Load(TEX_FILE_SPARK_EFFECT);
	/*�q�b�g�G�t�F�N�g*/
	mpHit = new CTexture();
	mpHit->Load(TGA_FILE"GameEffect\\Hit.tga");
	/*HP2D*/
	mpHp2DFrame = new CTexture();
	mpHp2DGauge= new CTexture();
	mpHp2DFrame->Load(TGA_FILE"UI\\Frame.tga");
	mpHp2DGauge->Load(TGA_FILE"UI\\Gauge.tga");
	/*�X�J�C�{�b�N�X*/
	mpSkyBox = new CTexture();
	mpSkyBox->Load(TGA_FILE"SkyBox\\skyBox.tga");
	/*�~�j�}�b�v*/
	for (int i = 0; i < CLoadTexManager::E_ARRAY; i++)
	{
		mpMiniMap[i] = new CTexture();
	}
	mpMiniMap[E_MINIMAP::PLAYER]->Load(TGA_FILE"MiniMap\\Player.tga");
	mpMiniMap[E_MINIMAP::ENEMY]->Load(TGA_FILE"MiniMap\\Enemy.tga");
	mpMiniMap[E_MINIMAP::KING]->Load(TGA_FILE"MiniMap\\KingEnemy.tga");
	mpMiniMap[E_MINIMAP::MAP_FRAME]->Load(TGA_FILE"MiniMap\\MapFrame.tga");
	mpMiniMap[E_MINIMAP::GRID]-> Load(TGA_FILE"MiniMap\\Grid.tga");
}

CLoadTexManager::~CLoadTexManager()
{
	/*�e�N�X�`���f���[�g�@�r���{�[�g*/
	P_DELETE(mpSpark);						//�Ή�
	P_DELETE(mpHit);
	P_DELETE(mpHp2DFrame);
	P_DELETE(mpHp2DGauge);
	P_DELETE(mpSkyBox);
	/*�~�j�}�b�v*/
	for (int i = 0; i < CLoadTexManager::E_ARRAY; i++)
	{
		P_DELETE(mpMiniMap[i]);
	}
}