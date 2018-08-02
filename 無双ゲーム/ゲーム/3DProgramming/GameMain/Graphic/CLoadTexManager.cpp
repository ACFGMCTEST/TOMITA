#include "CLoadTexManager.h"
#include "../../Define/Define.h"
#include "../Task/CTaskManager.h"

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
	/*���߂�G�t�F�N�g*/
	mpSaveUp = new CTexture();
	mpSaveUp->Load(TGA_FILE"GameEffect\\SaveUp.tga");
	/*HP2D*/
	mpHp2DFrame = new CTexture();
	mpHp2DGauge = new CTexture();
	mpMp2DGauge = new CTexture();
	mpMp2DGaugeEffect = new CTexture();
	mpMp2DFrame = new CTexture();
	mpHp2DFrame->Load(TGA_FILE"UI\\Frame.tga");
	mpHp2DGauge->Load(TGA_FILE"UI\\Gauge.tga");
	mpMp2DGauge->Load(TGA_FILE"UI\\MpGauge.tga");
	mpMp2DFrame->Load(TGA_FILE"UI\\MpFrame.tga");
	mpMp2DGaugeEffect->Load(TGA_FILE"UI\\MpGaugeMaxEffect.tga");
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

/*�q�b�g�G�t�F�N�g*/
void CLoadTexManager::HitEffect(CVector3 pos) {
	/*�G�t�F�N�g�̐ݒ�*/
#define EFF_SIZE 10.0f,10.0f//�T�C�Y
#define EFF_POS(pos) CVector3(pos.x,pos.y + 2.0f, pos.z)//�G�t�F�N�g�̃|�W�V����
#define TEX_EFF_SIZE 0.0f,0.0f,2000,250//�e�N�X�`���̃T�C�Y
#define EFF_SET_ANIMA 8,250//�ݒ�̃A�j���[�V����
#define EFF_SPEED  0.02f//�Đ��X�s�[�h
	CEffect2D *pEffect = new CEffect2D();
	/*�G�t�F�N�g�̐ݒ�*/
	pEffect->Init(CLoadTexManager::GetInstance()->mpHit,
		EFF_SIZE, STexVer(TEX_EFF_SIZE));//�摜�Ⓒ�_�����
	pEffect->SetAnima(EFF_SET_ANIMA);//�A�j���[�V�����̏���
	CTaskManager::GetInstance()->Add(pEffect);


	pEffect->StartAnima(
		EFF_SPEED, pos);
}


CLoadTexManager::~CLoadTexManager()
{
	/*�e�N�X�`���f���[�g�@�r���{�[�g*/
	P_DELETE(mpSpark);						//�Ή�
	P_DELETE(mpHit);
	P_DELETE(mpSaveUp);
	/*�Q�[�W*/
	P_DELETE(mpHp2DFrame);
	P_DELETE(mpHp2DGauge);
	P_DELETE(mpMp2DGauge);
	P_DELETE(mpMp2DFrame);
	P_DELETE(mpMp2DGaugeEffect);
	P_DELETE(mpSkyBox);
	/*�~�j�}�b�v*/
	for (int i = 0; i < CLoadTexManager::E_ARRAY; i++)
	{
		P_DELETE(mpMiniMap[i]);
	}
}