#include "CSlowFloor.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollisionManager.h"
/*大きさ*/
#define BOX_SIZE -MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f, MAPCHIP_SIZE, -MAPCHIP_SIZE, MAPCHIP_SIZE

/*あたり判定:ボックス設定*/
#define OBB_POS CVector3(0.0f,0.0f,0.0f)
#define OBB_SIZE CVector3(MAPCHIP_SIZE, MAPCHIP_SIZE, MAPCHIP_SIZE)
#define SET_OBB OBB_POS,OBB_SIZE,&mMatrix

/*スクロール速さ*/
#define SCROLL_SPEED -1.0f
/*更新*/
CSlowFloor::CSlowFloor(CVector3 pos){
	/*当たり判定インスタンス作成*/
	mpColBox = new CCollider(E_COL_BOX);
	/*親設定*/
	//mpParent = this;
	mpColBox->mpParent = this;
	/*ポジション設定*/
	mPos.x = pos.x;
	mPos.y = pos.y;
	mPos.z = pos.z;
	for (int i = 0; i < BOX_FACE_NUM; i++)
	{
		mRect[i].mMatrix = mMatrix;

	}
	UpdateMatrix();
	/*サイズ設定*/
	SetVertex(BOX_SIZE);
	/*色設定*/
	SetColor(WHITE_COLOR);
	/*テクスチャ設定*/
	SetTex(CBox::E_TexBox::E_SPEED_DOWN);
	/*当たり判定設定*/
	mpColBox->SetBoxOBB(SET_OBB);//設定
	mpColBox->eTag = CTask::E_TAG::E_TAG_SLOW_FLOOR;
	/*レンダー順番決める*/
	ePriority = CTask::E_SLOW_FLOOR;
	/*当たり判定追加*/
	CCollisionManager::GetInstance()->Add(mpColBox->eTag, mpColBox);
}
/*更新*/
void CSlowFloor::Update(){

	for (int i = 0; i < BOX_FACE_NUM; i++)
	{
		mRect[i].mMatrix = mMatrix;

	}
	UpdateMatrix();
	TexVerticalScroll(SCROLL_SPEED);
	mpColBox->Update();
}
/*描画*/
void CSlowFloor::Render(){
	CBox::Render2();
}

