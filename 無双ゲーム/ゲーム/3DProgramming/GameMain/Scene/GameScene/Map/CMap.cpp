#include "CMap.h"
#include "../../../../Define/Define.h"
/*仮の地形サイズ*/
#define MAP_Y 0.1f
#define GROUND_SIZE CVector3(100.0f,MAP_Y,100.0f)

/*初期化処理*/
void CMap::Init(){
	mGround.LoadFile("x\\Ground.obj");
	mGround.AddCollisionManager();
};
/*更新処理*/
void CMap::Update(){
	
};
/*描画処理*/
void CMap::Render(){
	mGround.Render();
};
