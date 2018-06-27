#include "CMap.h"
#include "../../../../Define/Define.h"
/*仮の地形サイズ*/
#define MAP_Y 0.1f
#define GROUND_SIZE CVector3(100.0f,MAP_Y,100.0f)
//#define F_MAP MODEL_FILE"Ground\\ProvisionalGround.obj"//objファイルの場所
//#define F_MAP "x\\Ground.obj" 

CMap* CMap::mMap = 0;


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
	mRespawn = mGroundX.FindFrame("Armature")->mCombinedMatrix;
	
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
