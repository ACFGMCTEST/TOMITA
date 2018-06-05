#include "CLoadTexManager.h"
#include "../../Define/Define.h"

/*テクスチャ場所 ビルボード*/
#define TEX_FILE_SPARK_EFFECT	TGA_FILE"GameEffect\\spark.tga"			//ゴールエフェクト場所 

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
	/*テクスチャロード 	ビルボード*/
	mpSpark->Load(TEX_FILE_SPARK_EFFECT);
}

CLoadTexManager::~CLoadTexManager()
{
	/*テクスチャデリート　ビルボート*/
	P_DELETE(mpSpark);						//火花

}