#include "CHighBox.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollisionManager.h"
#include "../../../../Collision/ColType/CColTriangle.h"
/*大きさ*/
#define BOX_SIZE -MAPCHIP_SIZE, MAPCHIP_SIZE, -MAPCHIP_SIZE, MAPCHIP_SIZE/2, -MAPCHIP_SIZE, MAPCHIP_SIZE

/*あたり判定:ボックス設定*/
#define OBB_BOX_POS CVector3(0.0f,0.0f,0.0f) 
#define OBB_BOX_SIZE CVector3(MAPCHIP_SIZE, MAPCHIP_SIZE/2, MAPCHIP_SIZE)
#define SET_BOX_OBB OBB_BOX_POS,OBB_BOX_SIZE,&mMatrix

/*コンストラクタ*/
CHighBox::CHighBox(CVector3 pos){
	/*当たり判定インスタンス作成*/
	mpColBox = new CCollider(E_COL_BOX);
	/*親設定*/
	mpColBox->mpParent = this;
	/*ポジション設定*/
	mPos.x = pos.x;
	mPos.y = MAPCHIP_SIZE;
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
	SetTex(CBox::E_TexBox::E_BOX);
	/*当たり判定設定*/
	mpColBox->SetBoxOBB(SET_BOX_OBB);//設定

	mpColBox->eTag = CTask::E_TAG::E_TAG_BOX;
	/*レンダー順番決める*/
	ePriority = CTask::E_HIGH_BOX;
	/*当たり判定追加*/
//	CCollisionManager::GetInstance()->Add(mpColBox->eTag, mpColBox);
	CColTriangle2* t = new CColTriangle2();
	t->Init(this,
		CVector3(-MAPCHIP_SIZE, MAPCHIP_SIZE/2, MAPCHIP_SIZE),
		CVector3(MAPCHIP_SIZE, MAPCHIP_SIZE/2, -MAPCHIP_SIZE),
		CVector3(-MAPCHIP_SIZE, MAPCHIP_SIZE/2, -MAPCHIP_SIZE),
		CVector3(),
		&mMatrix);
	t->eTag = CTask::E_TAG::E_TAG_GROUND;							//タグ決める
	t->eColTag = E_COL_TRIANGLE;
	CCollisionManager::GetInstance()->Add(t->eTag, t);

	t = new CColTriangle2();
	t->Init(this,
		CVector3(-MAPCHIP_SIZE, MAPCHIP_SIZE/2, MAPCHIP_SIZE),
		CVector3(MAPCHIP_SIZE, MAPCHIP_SIZE/2, MAPCHIP_SIZE),
		CVector3(MAPCHIP_SIZE, MAPCHIP_SIZE/2, -MAPCHIP_SIZE),
		CVector3(),
		&mMatrix);
	t->eTag = CTask::E_TAG::E_TAG_GROUND;							//タグ決める
	t->eColTag = E_COL_TRIANGLE;
	CCollisionManager::GetInstance()->Add(t->eTag, t);
}
/*更新*/
void CHighBox::Update(){
	mpColBox->Update();
}
/*描画*/
void CHighBox::Render(){
	CBox::UpdateMatrix();
	CBox::Render();
}

