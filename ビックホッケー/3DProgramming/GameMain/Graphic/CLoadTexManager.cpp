#include "CLoadTexManager.h"
#include "../../Define/Define.h"

/*テクスチャ場所 ビルボード*/
#define TEX_FILE_HAMMER_EFFECT	TGA_FILE"GameEffect\\HammerEffect3.tga"	//ハンマーエフェクト場所
#define TEX_FILE_SPARK_EFFECT	TGA_FILE"GameEffect\\spark.tga"			//ゴールエフェクト場所 
/*テクスチャ場所　ボックス*/

#define TEX_FILE_BOX			TGA_FILE"Map\\Box.tga"//ボックス
#define TEX_FILE_SLOPE			TGA_FILE"Map\\Slope.tga"//ボックス
#define TEX_FILE_FAST_FLOOR		TGA_FILE"Map\\speedUp.tga" //高速床
#define TEX_FILE_SLOW_FLOOR		TGA_FILE"Map\\speedDown.tga"//減速床
#define TEX_FILE_NET			TGA_FILE"Map\\net.tga"//網
#define TEX_FILE_WALL			TGA_FILE"Map\\wall.tga"//壁


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
	/*インスタンス作成*/
	/*ボックス*/
	mpTile = new CTexture();//タイル
	mpBox = new CTexture();//高台
	mpFastFloor = new CTexture();//高速床
	mpSlowFloor = new CTexture();//減速床
	mpTrampoline = new CTexture();//トランポリン
	mpSlope = new CTexture();//坂
	mpNet = new CTexture();//網
	mpWall = new CTexture();//壁
	/*ビルボード*/
	mpSpark = new CTexture();
	mpHammer = new CTexture();


	/*テクスチャロード 	ボックス*/
	mpTile->load(TEX_FILE_FAST_FLOOR);//タイル
	mpBox->load(TEX_FILE_BOX);//ボックス
	mpFastFloor->load(TEX_FILE_FAST_FLOOR);
	mpSlowFloor->load(TEX_FILE_SLOW_FLOOR);//減速床
	//mpTrampoline->load()//トランポリン
	mpSlope->load(TEX_FILE_SLOPE);//坂
	mpNet->load(TEX_FILE_NET);//網
	mpWall->load(TEX_FILE_WALL);//壁


	/*テクスチャロード 	ビルボード*/
	mpSpark->load(TEX_FILE_SPARK_EFFECT);
	mpHammer->load(TEX_FILE_HAMMER_EFFECT);
}

CLoadTexManager::~CLoadTexManager()
{
	/*テクスチャデリート　ボックス*/
	if (mpTile != 0)P_DELETE(mpTile);						//タイル
	if (mpBox != 0)P_DELETE(mpBox);							//ボックス
	if (mpFastFloor != 0)P_DELETE(mpFastFloor);				//高速床
	if (mpSlowFloor != 0)P_DELETE(mpSlowFloor);				//減速床
	if (mpTrampoline != 0)P_DELETE(mpTrampoline);			//トランポリン
	if (mpSlope != 0)P_DELETE(mpSlope);						//坂
	if (mpNet != 0)P_DELETE(mpNet);							//網
	if (mpHammer != 0)P_DELETE(mpHammer);					//壁
	/*テクスチャデリート　ビルボート*/
	if (mpSpark != 0)P_DELETE(mpSpark);						//火花
	if (mpHammer != 0)P_DELETE(mpHammer);					//ハンマー

}