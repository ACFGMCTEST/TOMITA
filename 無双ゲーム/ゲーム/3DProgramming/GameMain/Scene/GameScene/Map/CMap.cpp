#include "CMap.h"
#include "../../../../Define/Define.h"
/*仮の地形サイズ*/
#define MAP_Y 0.1f
#define GROUND_SIZE CVector3(100.0f,MAP_Y,100.0f)
#define F_MAP MODEL_FILE"Ground\\map.obj"//objファイルの場所
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
void CMap::Init(){

	mGround.LoadFile(F_MAP);
	mGround.AddCollisionManager();

#define SIZE_DOUB 4//スカイボックスのサイズ
	float y1 = SIZE_DOUB * (mGround.mRight + mGround.mBottom) / 2;
	float y2 =  -5.0f* SIZE_DOUB;
	mSkyBox.SetVertex
	(
		mGround.mRight * SIZE_DOUB, mGround.mLeft * SIZE_DOUB,
		y1,y2,
		mGround.mBottom * SIZE_DOUB, mGround.mTop * SIZE_DOUB
	);
	mSkyBox.SetTex(CBox::E_TexBox::E_SKY_BOX);
	mGroundX.FileName(MODEL_FILE"Ground\\");
	mGroundX.NoAnimaLoad(MODEL_FILE"Ground\\Map.x");
	mRespawn = mGroundX.FindFrame("Armature")->mCombinedMatrix;
};
/*更新処理*/
void CMap::Update(){
	
};
/*描画処理*/
void CMap::Render(){
	//mGround.Render();
	mSkyBox.Render();
	mGroundX.Render();
};
