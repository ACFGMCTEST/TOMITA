#include "CXGoal.h"
#include "windows.h"
#include "../../../../Key/CKey.h"
#include "../../../../../Define/Define.h"
#include "../CMap.h"
#include "../../../../Key/CMouse.h"
#include "../../CharaDate/CXCharPlayer.h"
#include <math.h>

/*あたり判定の設定値*/
#define OBB_POS CVector3(0.0f, 0.0f, 0.0f) 
#define OBB_SIZE new float[]{MAPCHIP_SIZE, 0.8f, 0.4f} 
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
#define ANGLE_1 1//角度\


/*ポジションを上げる処理*/
#define STAND_UP 0.1f

CXGoal::CXGoal(){
	mForward = CVector3(FORWARD);
	mpParent = this;
	mState = E_IDLE;
	

};
/*当たり判定初期化*/
void CXGoal::ColInit() {

	/*当たり判定インスタンス作成*/
	mCBBox = new CCollider(CTask::E_COL_BOX);
	mCBBox->mpParent = this;
}
/*
Init
モデルと衝突判定の設定を行う
*/
void CXGoal::Init(CModelX *model,CVector3 pos) {
	ColInit();
	mPosition = pos;
	CModelXS::Init(model);
	mCBBox->SetBoxOBB(OBB_POS, OBB_SIZE
		, &mpCombinedMatrix[model->FindFrame("Armature_Bone")->mIndex]);
	
	PosUpdate();
	/*エフェクト*/
	mEffect.Init(pos, mRotation);
	//はじめはアニメーションをしないようにしておく
	mEffect.DisableAnima();
}

/*ポジションのアップデート関数*/
void CXGoal::PosUpdate(){
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
	CModelXS::Update(matrix);

	mCBBox->Update();

}

/*更新処理*/
void CXGoal::Update(){

	/*ポジションの更新処理*/
	PosUpdate();

	mCBBox->Update();
}

/*Render*/
void CXGoal::Render() {
	CModelXS::Render();
#ifdef _DEBUG
	mCBBox->Render();
#endif
}

//billboardの描画処理
void CXGoal::BillboardRender(){

	mEffect.Update();
	mEffect.Render();
}

/*ゴールした時の演出*/
void CXGoal::GoalPerformance(){
	mEffect.EnabledAnima();
}