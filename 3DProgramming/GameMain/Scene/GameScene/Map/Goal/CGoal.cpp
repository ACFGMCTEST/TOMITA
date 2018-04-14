#include "CGoal.h"
#include "windows.h"
#include "../../../../Key/CKey.h"
#include "../../../../../Define/Define.h"
#include "../CMap.h"
#include "../../../../Key/CMouse.h"
#include "../../CharaDate/CXCharPlayer.h"
#include "../../../../Collision/CCollisionManager.h"
#include <math.h>
/*大きさ*/
#define BOX_SIZE MAPCHIP_SIZE, -MAPCHIP_SIZE, MAPCHIP_SIZE, -MAPCHIP_SIZE, MAPCHIP_SIZE, -MAPCHIP_SIZE
/*あたり判定の設定値*/
#define OBB_POS CVector3(0.0f, 0.0f, 0.0f) 
#define OBB_SIZE new float[]{MAPCHIP_SIZE, MAPCHIP_SIZE*1.1f, MAPCHIP_SIZE} 
/*HPバーの設定値*/
#define HP_BAR_POS CVector3(mPosition.x,mPosition.y + 1.8f,mPosition.z)
#define HP_BAR_SIZE -0.4f, 0.4f, -0.1f, 0.0f
/*スピード*/
#define SPEED_DOWN_ALWAYS 0.0001f//常に下がる減速度
#define SPEED_Goal 0.1f//通常速度
#define SPEED_MAX ATTACK_POWER_MAX + 0.1f//最高加速
//#define SPEED_MAX 10.0f//最大加速度
#define SPEED_UP 0.01f//減速床に乗った時の上昇値
#define SPEED_DOWN 0.01f//加速床に乗った時の減速値
/*角度*/
#define ANGLE_90 90 //角度
#define ANGLE_45 45 //角度
#define ANGLE_1 1//角度
#define SET_OBB OBB_POS,OBB_SIZE,&mMatrix

/*ポジションを上げる処理*/
#define STAND_UP 0.1f

CGoal::CGoal(CVector3 pos,CTask::E_TAG tag){

	///*サイズ設定*/
	//SetVertex(BOX_SIZE);
	///*色設定*/
	//SetColor(WHITE_COLOR);
	///*テクスチャ設定*/
	//SetTex(CBox::E_TexBox::E_BOX);

	///*当たり判定インスタンス作成*/
	//mCBBox = new CCollider(CTask::E_COL_BOX);
	///*当たり判定設定*/
	//mCBBox->SetBoxOBB(SET_OBB);//設定
	//mCBBox->mpParent = this;
	//mCBBox->eTag = tag;



	///*レンダー順番決める*/
	//ePriority = CTask::E_HIGH_BOX;
	///*当たり判定追加*/
	//CCollisionManager::GetInstance()->Add(mCBBox->eTag, mCBBox);




	//mForward = CVector3(FORWARD);
	////ColInit();
	//mPosition = pos;

	
	/*mpParent = this;
	mState = E_IDLE;*/

	/*当たり判定インスタンス作成*/
	mCBBox = new CCollider(E_COL_BOX);
	/*親設定*/
	mCBBox->mpParent = this;
	/*ポジション設定*/
	mPos.x = pos.x;
	mPos.y = - MAPCHIP_SIZE;
	mPos.z = pos.z;
	for (int i = 0; i < BOX_FACE_NUM; i++)
	{
		mRect[i].mMatrix = mMatrix;

	}
	UpdateMatrix();

	/*サイズ設定*/
	SetVertex(BOX_SIZE);
	/*色設定*/
	SetColor(GRAY_COLOR);
	/*テクスチャ設定*/
	SetTex(CBox::E_TexBox::E_BOX);

	/*当たり判定設定*/
	mCBBox->SetBoxOBB(SET_OBB);//設定
	mCBBox->eTag = tag;
	/*レンダー順番決める*/
	ePriority = CTask::E_GOAL_PLAYER;
	/*当たり判定追加*/
	CCollisionManager::GetInstance()->Add(mCBBox->eTag, mCBBox);

	
	/*更新*/
	PosUpdate();
	/*エフェクト*/
	mEffect.Init(pos, mRotation);
	//はじめはアニメーションをしないようにしておく
	mEffect.DisableAnima();
};
/*当たり判定初期化*/
void CGoal::ColInit() {
	///*サイズ設定*/
	//SetVertex(BOX_SIZE);
	///*色設定*/
	//SetColor(WHITE_COLOR);
	///*テクスチャ設定*/
	//SetTex(CBox::E_TexBox::E_BOX);
	///*当たり判定インスタンス作成*/
	//mCBBox = new CCollider(CTask::E_COL_BOX);
	//mCBBox->mpParent = this;
	//mCBBox->eTag = tag;
	///*レンダー順番決める*/
	//ePriority = CTask::E_HIGH_BOX;
	///*当たり判定追加*/
	//CCollisionManager::GetInstance()->Add(mCBBox->eTag, mCBBox);
}
///*
//Init
//モデルと衝突判定の設定を行う
//*/
//void CGoal::Init(CModelX *model,CVector3 pos) {
//	ColInit();
//	mPosition = pos;
//	CModelXS::Init(model);
//	mCBBox->SetBoxOBB(OBB_POS, OBB_SIZE
//		, &mpCombinedMatrix[model->FindFrame("Armature_Bone")->mIndex]);
//	
//	PosUpdate();
//	/*エフェクト*/
//	mEffect.Init(pos, mRotation);
//	//はじめはアニメーションをしないようにしておく
//	mEffect.DisableAnima();
//}
/*
Init
モデルと衝突判定の設定を行う
*/
void CGoal::Init(CVector3 pos) {
	ColInit();
	mPosition = pos;
	
	/*当たり判定設定*/
	mCBBox->SetBoxOBB(SET_OBB);//設定
	PosUpdate();
	/*エフェクト*/
	mEffect.Init(pos, mRotation);
	//はじめはアニメーションをしないようにしておく
	mEffect.DisableAnima();
}


/*ポジションのアップデート関数*/
void CGoal::PosUpdate(){
	CMatrix44 rot_y, pos, matrix;
	//回転行列の作成
	rot_y.rotationY(mRotation.y);

	/////進行方向を計算
	//mForward = mForward * rot_y;
	////移動させる
	//mPosition += mForward * mVelocity;

	//移動行列を計算する
	pos.translate(mPosition);
	//回転移動行列を求める
	matrix = pos * rot_y;

	//頂点データの更新
	//CModelXS::Update(matrix);

	mCBBox->Update();

}

/*更新処理*/
void CGoal::Update(){

	/*ポジションの更新処理*/
	PosUpdate();

	mCBBox->Update();
}

/*Render*/
void CGoal::Render() {
	BillboardRender();
	CBox::UpdateMatrix();
	//CModelXS::Render();
	//CBox::Render();
#ifdef _DEBUG
	//mCBBox->Render();
#endif
}

//billboardの描画処理
void CGoal::BillboardRender(){
	//printf("演出します\n");
	mEffect.Update();
	mEffect.Render();
}

/*ゴールした時の演出*/
void CGoal::GoalPerformance(){
	mEffect.EnabledAnima();
}