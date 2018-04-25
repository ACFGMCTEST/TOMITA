
#ifndef LOAD_TEX_MANAGER_HPP
#define LOAD_TEX_MANAGER_HPP
#include "CTexture.h"


/*テクスチャサイズ*/
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

	/*ボックスのロード*/
	CTexture *mpTile;//タイル
	CTexture *mpBox;//高台
	CTexture *mpFastFloor;//高速床
	CTexture *mpSlowFloor;//減速床
	CTexture *mpTrampoline;//トランポリン
	CTexture *mpSlope;//坂
	CTexture *mpNet;//網
	CTexture *mpWall;//壁
	/*ビルボードのロード*/
	CTexture *mpSpark;//火花
	CTexture *mpHammer;//ハンマー



	

private:

};

#endif