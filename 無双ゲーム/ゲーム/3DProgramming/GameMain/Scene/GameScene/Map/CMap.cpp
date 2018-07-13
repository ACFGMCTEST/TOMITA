#include "CMap.h"
#include "../../../../Define/Define.h"
#include "../../../Graphic/CLoadTexManager.h"
/*仮の地形サイズ*/
#define MAP_Y 0.1f
#define GROUND_SIZE CVector3(100.0f,MAP_Y,100.0f)
//#define F_MAP MODEL_FILE"Ground\\ProvisionalGround.obj"//objファイルの場所
//#define F_MAP "x\\Ground.obj" 

CMap* CMap::mMap = 0;

//ミニマップ設定用
void CMap::SetMiniMap() {
	/*ミニマップ用の描画*/
	mpMiniRect = new CBillBoard();
	const SVer ver(500.0f);//サイズ
	const CVector3 pos = CVector3(0.0f, 10.0f, 0.0f);//調整用の距離
	mpMiniRect->SetVertex(&MapCamera, ver, &mPos, pos);//ビルボードの設定
#define TEX_SIZE 0.0f,0.0f, 500.0f, 500.0f //ミニマップのサイズ
																		//テクスチャの設定
	mpMiniRect->SetUv(CLoadTexManager::GetInstance()->
		mpMiniMap[CLoadTexManager::GRID], TEX_SIZE);
	/*タスクマネージャーに追加*/
	CTaskManager::GetInstance()->Add(mpMiniRect);
	mpMiniRect->mRenderFlag = false;
}
//GetInstance
CMap* CMap::GetInstance() {
	if (mMap == 0) {
		mMap = new CMap();
	}
	return mMap;
}
/*初期化処理*/
void CMap::Init() {

	mGround.Load(MODEL_FILE"Ground\\map.obj");
	mGround.AddCollisionManager();
	/*空設定*/
	mSky.TexDirectory(MODEL_FILE"Sky\\");
	mSky.Load(MODEL_FILE"Sky\\sky.obj");
	/*地形設定*/
	mGroundX.TexDirectory(MODEL_FILE"Ground\\");
	mGroundX.NoAnimaLoad(MODEL_FILE"Ground\\Map.x");
	/*ミニマップの設定*/
	SetMiniMap();
};
/*更新処理*/
void CMap::Update(){
	
};
/*描画処理*/
void CMap::Render(){
	//mGround.Render();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//色は置き換えてマッピング
	mSky.Render();
	mGroundX.Render();

};
/*ミニマップ用描画*/
void CMap::MiniMapRender() {
	mGroundX.Render();
}