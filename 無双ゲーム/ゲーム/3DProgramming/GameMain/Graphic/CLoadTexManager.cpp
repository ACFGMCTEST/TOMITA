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
	/*火花エフェクト*/
	mpSpark = new CTexture();
	mpSpark->Load(TEX_FILE_SPARK_EFFECT);
	/*ヒットエフェクト*/
	mpHit = new CTexture();
	mpHit->Load(TGA_FILE"GameEffect\\Hit.tga");
	/*HP2D*/
	mpHp2DFrame = new CTexture();
	mpHp2DGauge= new CTexture();
	mpHp2DFrame->Load(TGA_FILE"UI\\Frame.tga");
	mpHp2DGauge->Load(TGA_FILE"UI\\Gauge.tga");
	/*スカイボックス*/
	mpSkyBox = new CTexture();
	mpSkyBox->Load(TGA_FILE"SkyBox\\skyBox.tga");
	/*ミニマップ*/
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
	/*テクスチャデリート　ビルボート*/
	P_DELETE(mpSpark);						//火花
	P_DELETE(mpHit);
	P_DELETE(mpHp2DFrame);
	P_DELETE(mpHp2DGauge);
	P_DELETE(mpSkyBox);
	/*ミニマップ*/
	for (int i = 0; i < CLoadTexManager::E_ARRAY; i++)
	{
		P_DELETE(mpMiniMap[i]);
	}
}