#include "CTrampoline.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollisionManager.h"
#define BOX_Y MAPCHIP_SIZE  * 0.2f
/*大きさ*/
#define BOX_SIZE -MAPCHIP_SIZE, MAPCHIP_SIZE, -BOX_Y, BOX_Y, -MAPCHIP_SIZE, MAPCHIP_SIZE

/*あたり判定:ボックス設定*/
#define OBB_POS CVector3(0.0f,0.0f,0.0f) 
#define OBB_SIZE new float[]{MAPCHIP_SIZE, BOX_Y, MAPCHIP_SIZE} 
#define SET_OBB OBB_POS,OBB_SIZE,&mMatrix

/*更新*/
CTrampoline::CTrampoline(CVector3 pos){
	/*当たり判定インスタンス作成*/
	mpColBox = new CCollider(E_COL_BOX);
	/*親設定*/
	//mpParent = this;
	mpColBox->mpParent = this;
	/*ポジション設定*/
	mPos.x = pos.x;
	mPos.y = BOX_Y;
	mPos.z = pos.z;
	for (int i = 0; i < BOX_FACE_NUM; i++)
	{
		mRect[i].mMatrix = mMatrix;

	}
	UpdateMatrix();

	/*サイズ設定*/
	SetVertex(BOX_SIZE);
	/*色設定*/
	SetColor(YELLOW_COLOR);
	/*テクスチャ設定*/
	SetTex(CBox::E_TexBox::E_BOX);
	/*当たり判定設定*/
	mpColBox->SetBoxOBB(SET_OBB);//設定
	/*タグ設定*/
	mpColBox->eTag = CTask::E_TAG::E_TAG_TRAMPOLINE;
	/*レンダー順番決める*/
	ePriority = CTask::E_TRAMPOLINE;
	/*当たり判定設定*/
	CCollisionManager::GetInstance()->Add(mpColBox->eTag, mpColBox);

}
/*更新*/
void CTrampoline::Update(){
	mpColBox->Update();
}
/*描画*/
void CTrampoline::Render(){

	for (int i = 0; i < BOX_FACE_NUM; i++)
	{
		mRect[i].mMatrix = mMatrix;

	}
	UpdateMatrix();

	CBox::Render();
}

