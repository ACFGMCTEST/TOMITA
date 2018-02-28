#include "CNet.h"

#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollisionManager.h"
#include "../CMap.h"
#define NET_SIZE		-MAPCHIP_SIZE*CMap::mMapX, MAPCHIP_SIZE*CMap::mMapX,\
	- MAPCHIP_SIZE, MAPCHIP_SIZE * 2, \
	- MAPCHIP_SIZE*0.2f, MAPCHIP_SIZE*0.2f
/*あたり判定:ボックス設定*/
/*網設定*/
#define OBB_NET_POS CVector3(0.0f,0.0f,0.0f) 
#define OBB_NET_SIZE new float[]{MAPCHIP_SIZE*CMap::mMapX*1.2f, MAPCHIP_SIZE*4, MAPCHIP_SIZE*0.5f} 
#define SET_NET_OBB OBB_NET_POS,OBB_NET_SIZE,&mMatrix

/*コンストラクタ*/
CNet::CNet(CVector4 pos){
	/*当たり判定インスタンス作成*/
	mpColBox = new CCollider(E_COL_BOX);
	/*親設定*/
	//mpParent = this;
	mpColBox->mpParent = this;
	/*ポジション設定*/
	mPos.z = pos.z;
	mPos.y = pos.y;
	mPos.x = pos.x;

	for (int i = 0; i < BOX_FACE_NUM; i++)
	{
		mRect[i].mMatrix = mMatrix;

	}
	UpdateMatrix();
	/*サイズ設定*/
	SetVertex(NET_SIZE);
	/*色設定*/
	SetColor(WHITE_COLOR);
	/*テクスチャ設定*/
	SetTex(CBox::E_TexBox::E_NET);
	/*当たり判定設定*/
	mpColBox->SetBoxOBB(SET_NET_OBB);//設定
	mpColBox->eTag = CTask::E_TAG::E_TAG_NET;
	/*レンダー順番決める*/
	ePriority = CTask::E_NET;
	/*当たり判定追加*/
	CCollisionManager::GetInstance()->Add(mpColBox->eTag, mpColBox);
}
/*更新*/
void CNet::Update(){
	mpColBox->Update();
}
/*描画*/
void CNet::Render(){
	CBox::Render();
}

