
#ifndef LOAD_TEX_MANAGER_HPP
#define LOAD_TEX_MANAGER_HPP
#include "CTexture.h"
/*テクスチャのサイズ*/
#define T_MANA_HP_SIZE  STexVer(0,0,490,30)
#include "../Scene/GameScene/Effect/CEffect2D.h"

class  CLoadTexManager
{
private:
	static CLoadTexManager *mLoadTexManager;
	CLoadTexManager();
	~CLoadTexManager();

public:
	static CLoadTexManager *GetInstance(); //GetInstance
	/*ビルボードのロード*/
	CTexture *mpSpark;//火花
	CTexture *mpHit;//ヒットエフェクト
	CTexture *mpSaveUp;//ためるエフェクト
	CTexture *mpHp2DFrame;//プレイヤーのHP(frame)
	CTexture *mpHp2DGauge;//プレイヤーのHP(gauge)
	CTexture *mpMp2DGauge;//プレイヤーのMP(gauge)
	CTexture *mpMp2DFrame;;//プレイヤーのMP(frame)
	CTexture *mpMp2DGaugeEffect;//プレイヤーのMPエフェクト(gauge)
	/*ミニマップ用*/
	enum  E_MINIMAP
	{
		PLAYER,ENEMY,KING,MAP_FRAME,GRID,E_ARRAY
	};
	CTexture *mpMiniMap[E_ARRAY];//ミニマップ各種テクスチャ
	CTexture *mpSkyBox;//スカイボックス

	void HitEffect(CVector3 pos);//ヒットしたエフェクト
private:

};

#endif