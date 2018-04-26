#include "CMap.h"
#include "../../../../Define/Define.h"
/*仮の地形サイズ*/
#define MAP_Y 0.1f
#define GROUND_SIZE CVector3(100.0f,MAP_Y,100.0f)

/*初期化処理*/
void CMap::Init(){
	mpGround = new CCollider(CTask::E_COL_BOX);
	/*地面設定*/
	mpGround->SetBoxOBB(CVector3(0.0f, -MAP_Y*4, 0.0f), GROUND_SIZE, &m44);
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_GROUND, mpGround);
	mpGround->SetColor(WHITE_COLOR);
};
/*更新処理*/
void CMap::Update(){
	mpGround->Update();
};
/*描画処理*/
void CMap::Render(){
	mpGround->Render();
};
