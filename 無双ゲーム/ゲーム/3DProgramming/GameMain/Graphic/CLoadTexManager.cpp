#include "CLoadTexManager.h"
#include "../../Define/Define.h"
#include "../Task/CTaskManager.h"

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
	/*ためるエフェクト*/
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

/*ヒットエフェクト*/
void CLoadTexManager::HitEffect(CVector3 pos) {
	/*エフェクトの設定*/
#define EFF_SIZE 10.0f,10.0f//サイズ
#define EFF_POS(pos) CVector3(pos.x,pos.y + 2.0f, pos.z)//エフェクトのポジション
#define TEX_EFF_SIZE 0.0f,0.0f,2000,250//テクスチャのサイズ
#define EFF_SET_ANIMA 8,250//設定のアニメーション
#define EFF_SPEED  0.02f//再生スピード
	CEffect2D *pEffect = new CEffect2D();
	/*エフェクトの設定*/
	pEffect->Init(CLoadTexManager::GetInstance()->mpHit,
		EFF_SIZE, STexVer(TEX_EFF_SIZE));//画像や頂点数代入
	pEffect->SetAnima(EFF_SET_ANIMA);//アニメーションの準備
	CTaskManager::GetInstance()->Add(pEffect);


	pEffect->StartAnima(
		EFF_SPEED, pos);
}


CLoadTexManager::~CLoadTexManager()
{
	/*テクスチャデリート　ビルボート*/
	P_DELETE(mpSpark);						//火花
	P_DELETE(mpHit);
	P_DELETE(mpSaveUp);
	/*ゲージ*/
	P_DELETE(mpHp2DFrame);
	P_DELETE(mpHp2DGauge);
	P_DELETE(mpMp2DGauge);
	P_DELETE(mpMp2DFrame);
	P_DELETE(mpMp2DGaugeEffect);
	P_DELETE(mpSkyBox);
	/*ミニマップ*/
	for (int i = 0; i < CLoadTexManager::E_ARRAY; i++)
	{
		P_DELETE(mpMiniMap[i]);
	}
}