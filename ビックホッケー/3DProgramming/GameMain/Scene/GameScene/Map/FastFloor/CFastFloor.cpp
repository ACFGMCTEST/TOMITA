#include "CFastFloor.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollisionManager.h"
/*大きさ*/
#define SIZE -MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f, MAPCHIP_SIZE, -MAPCHIP_SIZE, MAPCHIP_SIZE

/*あたり判定:ボックス設定*/
#define OBB_POS CVector4(0.0f,0.0f,0.0f) 
#define OBB_SIZE new float[]{MAPCHIP_SIZE, MAPCHIP_SIZE, MAPCHIP_SIZE} 
#define SET_OBB OBB_POS,OBB_SIZE,&mMatrix

/*スクロール速さ*/
#define SCROLL_SPEED 1.0f
/*更新*/
CFastFloor::CFastFloor(CVector4 pos){
	/*当たり判定インスタンス作成*/
	mpColBox = new CCollider(E_COL_BOX);
	/*親設定*/
	//mpParent = this;
	mpColBox->mpParent = this;
	/*ポジション設定*/
	/*ポジション設定*/
	mPos.x = pos.x;
	mPos.y = pos.y;
	mPos.z = pos.z;
	CBox::UpdateMatrix();
	/*サイズ設定*/
	SetVertex(SIZE);
	/*色設定*/
	SetColor(WHITE_COLOR);
	/*テクスチャ設定*/
	SetTex(CBox::E_TexBox::E_SPEED_UP);

	/*当たり判定設定*/
	mpColBox->SetBoxOBB(SET_OBB);//設定
	mpColBox->eTag = CTask::E_TAG::E_TAG_FAST_FLOOR;
	/*レンダー順番決める*/
	ePriority = CTask::E_FAST_FLOOR;
	/*当たり判定追加*/
	CCollisionManager::GetInstance()->Add(mpColBox->eTag, mpColBox);
}
/*更新*/
void CFastFloor::Update(){
	CBox::UpdateMatrix();
	TexVerticalScroll(SCROLL_SPEED);
	mpColBox->Update();
}
/*描画*/
void CFastFloor::Render(){
	CBox::Render2();
}

