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
	mpSpark = new CTexture();
	/*�e�N�X�`�����[�h 	�r���{�[�h*/
	mpSpark->Load(TEX_FILE_SPARK_EFFECT);
}

CLoadTexManager::~CLoadTexManager()
{
	/*�e�N�X�`���f���[�g�@�r���{�[�g*/
	P_DELETE(mpSpark);						//�Ή�

}