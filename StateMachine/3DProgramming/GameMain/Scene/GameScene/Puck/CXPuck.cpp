﻿#include "CXPuck.h"
#include "windows.h"
#include "../../../Key/CKey.h"
#include "../../../../Define/Define.h"
#include "../Map/CMap.h"
#include "../../../Key/CMouse.h"
#include "../CharaDate/CXCharPlayer.h"
#include <math.h>

#include "../../../Collision/CCollision.h"
#include "../../../Scene/GameScene/Map/Goal/CXGoal.h"
#include "../../../Scene/GameScene/UI/CScoreBoard.h"

#define OBB_POS CVector3(0.0f, 1.0f, 0.0f) 
#define OBB_SIZE CVector3(1.5f,0.5f, 1.5f)
#define OBB_SPHERE_SIZE 1.0f
/*HPバーの設定値*/
#define HP_BAR_POS CVector3(mPosition.x,mPosition.y + 1.8f,mPosition.z)
#define HP_BAR_SIZE -0.4f, 0.4f, -0.1f, 0.0f
/*スピード*/
#define SPEED_DOWN_ALWAYS 0.0001f//常に下がる減速度
#define SPEED_PUCK 0.1f//通常速度
#define SPEED_MAX ATTACK_POWER_MAX + 0.1f//最高加速
//#define SPEED_MAX 10.0f//最大加速度
#define SPEED_UP 0.01f//減速床に乗った時の上昇値
#define SPEED_DOWN 0.01f//加速床に乗った時の減速値
/*角度*/
#define ANGLE_90 90 //角度
#define ANGLE_45 45 //角度
#define ANGLE_1 1//角度


/*ジャンプのスピード*/
#define JUMP_SPEED 1.2f//ジャンプするスピード

/*ポジションを上げる処理*/
#define STAND_UP 0.6f

CXPuck::CXPuck() : mVelocity(0.0f), mSaveSpeed(0.0f), mRefFlag(true), mFlagJump(false),
mGravitTime(GRA_INIT_TIME_COUNT), mGoalStandUpFlag(false), mRefrectVec(0.0f, 0.0f, 0.0f), mFlagSlope(false){
	mForward = CVector3(FORWARD);
	mpParent = this;
	mState = E_IDLE;
	ePriority = CTask::E_PUCK;

};
/*当たり判定初期化*/
void CXPuck::ColInit() {
	/*ボックス*/
	mpCBRefBox = new CCollider(E_COL_BOX);
	mpCBRefBox->mpParent = this;
	/*球*/
	mpCBSphere = new CCollider(E_COL_SPHEPE);
	mpCBSphere->mpParent = this;
}
/*
Init
モデルと衝突判定の設定を行う
*/
void CXPuck::Init(CModelX *model) {
	ColInit();

	CModelXS::Init(model);


	/*当たり判定(ボックス)*/
	mpCBRefBox->SetBoxOBB(OBB_POS, OBB_SIZE
		, &mpCombinedMatrix[model->FindFrame("Armature_Bone")->mIndex]);
	/*当たり判定(球)*/
	mpCBSphere->SetShere(OBB_SPHERE_SIZE, OBB_POS, &mpCombinedMatrix[model->FindFrame("Armature_Bone")->mIndex]);
	mSaveSpeed = SPEED_PUCK;
	mVelocity = mSaveSpeed;
	mVelocity = 0.0f;;
	PosUpdate();

}


/*ポジションのアップデート関数*/
void CXPuck::PosUpdate(){

	CMatrix44 rot, pos, matrix;
	//回転行列の作成
	rot.rotationX(mRotation.x);
	rot.rotationY(mRotation.y);
	rot.rotationZ(mRotation.z);
	


	////移動させる
	//mPosition += mForward * mVelocity;

	//移動行列を計算する
	pos.translate(mPosition);
	//回転移動行列を求める
	matrix = pos * rot;

	//頂点データの更新
	CModelXS::Update(matrix);

	mpCBSphere->Update();
	mpCBRefBox->Update();

}

/*重力*/
void CXPuck::Gravity(){
	/*地面についていないなら*/
	mPosition.y -= GRAVITY(mGravitTime);
	mGravitTime += GRA_TIME_UP;//時間が経つ

	/*地面に埋まった場合*/
	if (mPosition.y <= 0){
		mPosition.y = 0;
		mGravitTime = GRA_ACCELERA;//初期値
	}
}


/*更新処理*/
void CXPuck::Update(){
	//mVelocity -= SPEED_DOWN_ALWAYS;//常に減速させる
	if (mVelocity < 0){//進行度がminusになると
		mVelocity = 0;
	}
	if (mVelocity > SPEED_MAX){//進行度が最高速になると
		mVelocity = SPEED_MAX;
	}
	mRefFlag = true; //跳ね返りを有効にする
	//移動させる
	mPosition += mForward * mVelocity;
	
	Jump();//ジャンプ処理

	/*スタンドアップフラグがあるとき*/
	if (mGoalStandUpFlag){
		StandUp();
	}
	else{
		Gravity();
	}

	/*ポジションの更新処理*/
	PosUpdate();
	/*坂にあたっていないようにする*/
	mFlagSlope = false;
	
}

/*Render*/
void CXPuck::Render() {
#ifdef _DEBUG
	mpCBSphere->Render();
	mpCBRefBox->Render();
#endif
	CModelXS::Render();

}

/*あたり判定の時に呼び出し*/
void CXPuck::ColReflect(const COBB &obb){

	if (mRefFlag){
		/*ボックスの向きが指定してなければ*/
		if (obb.mNormal == CVector3(0.0f, 0.0f, 0.0f)){
			float refx = abs(obb.mPos.x - mPosition.x);//反射角判断用
			float refz = abs(obb.mPos.z - mPosition.z);//反射角判断用
			/*x軸に大きければ左右に当たっている*/
			if (refz < refx){
				mForward.x *= -1;//逆方向に
			}
			/*z軸に大きければ左右に当たっている*/
			else{
				mForward.z *= -1;//逆方向に
			}

			mRefFlag = false; //跳ね返りを一回だけにする
		}
		/*ボックスの向きを設定している*/
		else{
			//if (obb.mNormal.x){ mForward.x *= -1.0f;/*逆向きに*/ }
			//if (obb.mNormal.y){ mForward.y *= -1.0f;/*逆向きに*/ }
			//if (obb.mNormal.z){ mForward.z *= -1.0f;/*逆向きに*/ }
			mForward = CCollision::Reflect(obb.mNormal, mForward);
		}
		//移動させる🄱
		mPosition += mForward * mVelocity;
		PosUpdate();
	}
}
/*あたり判定の時に呼び出し
rot = 回転地
*/
void CXPuck::ColReflect(CVector3 &rot, float &power){
	mVelocity += power;
	//printf("殴ったよ%f\n", power);
	CMatrix44 rot_y, pos, matrix;
	mForward = CVector3(FORWARD);
	//回転行列の作成
	rot_y.rotationY(rot.y);
	///進行方向を計算
	mForward = mForward * rot_y;

	//移動させる
	mPosition += mForward * mVelocity;
	PosUpdate();
}

bool CXPuck::ColReflect(CVector3 &v0, CVector3 &v1, CVector3 &v2, CVector3 &center, float &radius, CVector3 &fwd, CVector3 *rtn) {
	CVector3 cross;
	float length;
	if (!mRefFlag) return false;
	if (CCollision::IntersectTriangleSphere(v0, v1, v2, center, radius, &cross, &length)) {
		CVector3 V1(v1 - v0);
		CVector3 V2(v2 - v0);
		CVector3 normal(CVector3::Cross(V1, V2).GetNormalize());
		*rtn = CCollision::Reflect(normal, fwd);
		mRefFlag = false;
		return true;
	}
	return false;
}


/*あたり判定の時に呼び出し*/
void CXPuck::ColStop(const COBB &obb1, const COBB &obb2){

}

/*減速処理*/
void CXPuck::ColSlow(){
	mVelocity -= SPEED_DOWN;
	if (mVelocity < 0){
		mVelocity = 0;
	}
}

/*加速処理*/
void CXPuck::ColFast(){
	mVelocity += SPEED_UP;
	if (mVelocity >= SPEED_MAX){
   		mVelocity = SPEED_MAX;
	}
}

/*ジャンプ処理*/
void CXPuck::Jump(){
	/*ジャンプのフラグが立っている時*/
	if (mFlagJump){
		float jumpVilocity = JUMP_SPEED - GRAVITY(mGravitTime);//動かす力
		/*ジャンプが重力より大きい場合*/
		if (jumpVilocity > GRAVITY(mGravitTime)){
			mPosition.y += jumpVilocity;
		}
		else{
			mFlagJump = false;
		}
	}
}

/*ジャンプ_フラグたて*/
void CXPuck::EnabledJump(){
	mFlagJump = true;
}


/*ゴールエネミー*/
void CXPuck::GoalEnemy(){
	mGoalStandUpFlag = true;//スタンドアップ用意
	mVelocity = 0;
	mPosition = GOAL_POS_PUCK_ENEMY;
	PosUpdate();
}
/*ゴールプレイヤー*/
void CXPuck::GoalPlayer(){
	mGoalStandUpFlag = true;//スタンドアップ用意
	mVelocity = 0;
	mPosition = GOAL_POS_PUCK_PLAYER;
	PosUpdate();
}

/*立ち上がり処理*/
void CXPuck::StandUp(){
	
	mGoalStandUpFlag = false;//スタンドアップ終了
}
/*移動処理*/
void CXPuck::Move(){
	//移動させる
	mPosition += mForward * mVelocity;
	PosUpdate();
}

/*坂の処理*/
void CXPuck::EnabledSlope(){
	mFlagSlope = true;//坂道をtrueに
	//mPosition = slope.MiddlePos(mPosition);//ポジションを合わせる
	//slope.SlpoeRot(&mRotation);//回転値を坂の方向に変更
	//mGravitTime = GRA_INIT_TIME_COUNT;//重力加速度リセット
}

/*当たり判定呼び出し
元の場所に戻すための関数
*/
bool CXPuck::Collision(const COBB &box, const CColSphere &sphere) {
	return Collision(box, sphere, true);
}
bool CXPuck::Collision(const COBB &box, const CColSphere &sphere, bool flgAjust) {


	CVector3 savePos = sphere.mPos;//計算用

	float lengthX = mPosition.x - savePos.x;  //球とポジションの距離
	float lengthY = mPosition.y - savePos.y;  //球とポジションの距離
	float lengthZ = mPosition.z - savePos.z;  //球とポジションの距離

	//BoxのX軸方向を求める
	CVector3 vx = box.mMatrixRotation * VEC_RIGHT;
	//BoxのY軸方向を求める
	CVector3 vy = box.mMatrixRotation * VEC_TOP;
	//BoxのZ軸方向を求める
	CVector3 vz = box.mMatrixRotation * VEC_FRONT;

	vx = box.mAxis[0];
	vy = box.mAxis[1];
	vz = box.mAxis[2];

	//四角形から球へのベクトルを求める
	CVector3 vectorBS = savePos - box.mPos;
	//四角形から球へ、四角形のX軸に対する長さとの差を求める
	float dx = sphere.mRadius + box.mLength[0] - fabs(vx.Dot(vectorBS));
	//四角形から球へ、四角形のY軸に対する長さとの差を求める
	float dy = sphere.mRadius + box.mLength[1] - fabs(vy.Dot(vectorBS));
	//四角形から球へ、四角形のZ軸に対する長さとの差を求める
	float dz = sphere.mRadius + box.mLength[2] - fabs(vz.Dot(vectorBS));


	//衝突しているか判定する
	if (dx > 0.0f && dy > 0.0f && dz > 0.0f) {
		if (!flgAjust) return true;
		if (dx > dy) {
			if (dy > dz) {
				//Z軸で戻す
				if (vz.Dot(vectorBS) > 0.0f) {
					mPosition = savePos + vz * dz;
					//跳ね返り方向設定
					/*mRefrectVec*/
				}
				else {
					mPosition = savePos - vz * dz;
				}
			}
			else {
					//Y軸で戻す
					if (vy.Dot(vectorBS) > 0.0f) {
						mPosition = savePos + vy * dy;
					}
					else {
						mPosition = savePos - vy * dy;
					}
			}
		}
		else{
			if (dx > dz) {

				//Z軸で戻す
				if (vz.Dot(vectorBS) > 0.0f) {
					mPosition = savePos + vz * dz;
				}
				else {
					mPosition = savePos - vz * dz;
				}
			}
			else {

				//X軸で戻す
				if (vx.Dot(vectorBS) > 0.0f) {
					mPosition = savePos + vx * dx;
				}
				else {
					mPosition = savePos - vx * dx;
				}
			}
		}
	}
	else {
		return false;
	}
	mPosition.x += lengthX;
	mPosition.y += lengthY;
	mPosition.z += lengthZ;

	/*マトリックスだけ更新*/
	CMatrix44 rot_y, pos, matrix;
	//回転行列の作成
	rot_y.rotationY(mRotation.y);

	//移動行列を計算する
	pos.translate(mPosition);
	//回転移動行列を求める
	matrix = pos * rot_y;
	//頂点データの更新
	CModelXS::MatrixUpdate(matrix);

	mGravitTime = GRA_INIT_TIME_COUNT;//重力加速度リセット

	RotReset();//回転値をリセット
	/*当たり判定更新*/
//	mpCBRefBox->Update();
//	mpCBSphere->Update();

	return true;
}



/*回転値リセット*/
void CXPuck::RotReset(){
	mRotation.x = 0;
	mRotation.y = 0;
	mRotation.z = 0;
}

//void CXPuck::Collision(CCollider2* me, CCollider2* you) {
//
//	switch (me->eColTag) {
//	case E_COL_SPHEPE:
//		switch (you->eTag) {
//		case E_TAG_BOX:
//			if (you->eColTag == E_COL_BOX)
//				Collision(you->mObb, me->mColSphere);
//			break;
//		case E_TAG_GROUND:
//			if (you->eColTag == E_COL_BOX)
//				Collision(you->mObb, me->mColSphere);
//			break;
//		case E_TAG_SLOPE_REF:
//			if (you->eColTag == E_COL_TRIANGLE)
//				Collision(you->mObb, me->mColSphere);
//			break;
//		}
//
//	}
//}


/*パックの当たり判定*/
bool  CXPuck::Collision(CTask *Puck , CTask *Task_You ){


	CXPuck *puck = dynamic_cast<CXPuck*>(Puck->mpParent);//自分

	/*キャスト中身を見る*/
	CXCharPlayer *chara;
	/*ゴールキャスト*/
	CXGoal *goal;
	//OBB衝突判定



	/*キャスト*/
	CCollider *you;
	/*キャスト処理*/
	you = dynamic_cast<CCollider *>(Task_You);

	/*あたり判定が何か判断*/
	switch (Task_You->eTag)
	{
		/*地面*/
	case CTask::E_TAG_GROUND:
		switch (you->eColTag) {
		case CTask::E_COL_BOX:
			/*キャスト処理*/
			you = dynamic_cast<CCollider *>(Task_You);
			if (puck->Collision(you->mObb, puck->mpCBSphere->mColSphere)) {
				return true;
			}
			break;
		case CTask::E_COL_TRIANGLE:
			CCollider2 *col2 = dynamic_cast<CCollider2*>(Task_You);
			CVector3 cross;
			float length;
			CVector3 adjust;

			if (CCollision::IntersectTriangleSphere2(col2->mV[1][0], col2->mV[1][1], col2->mV[1][2], puck->mpCBSphere->mColSphere.mPos, puck->mpCBSphere->mColSphere.mRadius, &cross, &length, &adjust)) {
				mPosition = mPosition + adjust;
				return true;
			}
			break;
		}
//		return puck->Collision(you->mObb, puck->mpCBSphere->mColSphere);

		break;
		/*ボックス*/
	case CTask::E_TAG_BOX:
		/*球体の場合*/
//		if (puck->mpCBSphere == Puck){
			if (puck->Collision(you->mObb, puck->mpCBSphere->mColSphere)) {
				//puck->ColReflect(you->mObb);
				return true;
			}
//		}
		///*ボックスの場合*/
		//if (puck->mpCBRefBox == Puck){
		//	/*もし坂にあたっていないなら跳ね返る*/
		//	if (!puck->mFlagSlope){
		//		puck->ColReflect(you->mObb);
		//	}
		//}
		break;

//	case CTask::E_TAG_SLOPE_REF:
	case CTask::E_TAG_SLOPE:
		switch (you->eColTag) {
		case CTask::E_COL_BOX:
			/*キャスト処理*/
			you = dynamic_cast<CCollider *>(Task_You);
			if (puck->Collision(you->mObb, puck->mpCBSphere->mColSphere)) {
				return true;
			}
			break;
		case CTask::E_COL_TRIANGLE:
			CCollider2 *col2 = dynamic_cast<CCollider2*>(Task_You);
			CVector3 cross;
			float length;
			CVector3 adjust;

			if (CCollision::IntersectTriangleSphere2(col2->mV[1][0], col2->mV[1][1], col2->mV[1][2], puck->mpCBSphere->mColSphere.mPos, puck->mpCBSphere->mColSphere.mRadius, &cross, &length, &adjust)) {
				mPosition = mPosition + adjust;
				mRefFlag = false; //跳ね返えらせない
				return true;
			}
			break;
		}
		break;
	case CTask::E_TAG_WALL:
		switch(you->eColTag ) {
		case CTask::E_COL_BOX:
			if (puck->Collision(you->mObb, puck->mpCBSphere->mColSphere)) {
				puck->ColReflect(you->mObb);
				return true;
			}
			break;
		case CTask::E_COL_TRIANGLE:
			CCollider2 *col2 = dynamic_cast<CCollider2*>(Task_You);

			if (ColReflect(col2->mV[1][0], col2->mV[1][1], col2->mV[1][2], puck->mpCBSphere->mColSphere.mPos, puck->mpCBSphere->mColSphere.mRadius, mForward, &mForward)) {
				return true;
			}
			break;
		}

		///*キャスト処理*/
		//you = dynamic_cast<CCollider *>(Task_You);

		///*球体の場合*/
		//if (puck->mpCBSphere == Puck){
		//	return puck->Collision(you->mObb, puck->mpCBSphere->mColSphere);
		//}
		///*ボックスの場合*/
		//if (puck->mpCBRefBox == Puck){
		//	/*もし坂にあたっていないなら跳ね返る*/
		//	if (!puck->mFlagSlope){
		//		puck->ColReflect(you->mObb);
		//	}
		//}
		break;

		//減速床
	case CTask::E_TAG_SLOW_FLOOR:
		if (puck->Collision(you->mObb, puck->mpCBSphere->mColSphere, false)) {
			puck->ColSlow();
		}
		break;

		//加速床
	case CTask::E_TAG_FAST_FLOOR:
		if (puck->Collision(you->mObb, puck->mpCBSphere->mColSphere, false)) {
			puck->ColFast();
		}
		break;
		/*トランポリン*/
	case CTask::E_TAG_TRAMPOLINE:
		if (puck->Collision(you->mObb, puck->mpCBSphere->mColSphere, false)) {
			puck->EnabledJump();
		}
		break;
		/*ウエポン*/
	case CTask::E_TAG_WEAPON:

		chara = dynamic_cast<CXCharPlayer*>(Task_You->mpParent->mpParent);
		//キャラクターが攻撃状態か判断
		if (chara->mState == CXCharPlayer::E_ATTACK){
			if (puck->Collision(you->mObb, puck->mpCBSphere->mColSphere)) {
				puck = dynamic_cast<CXPuck*>(Puck->mpParent);//自分
				puck->ColReflect(chara->mRotation, chara->mPower);
				return true;
			}
		}
		break;

		/*ゴールプレイヤー*/
	case CTask::E_TAG_GOAL_PLAYER:
		if (Task_You->eColTag == E_COL_BOX && Puck->eColTag == E_COL_SPHEPE) {
			/*キャスト処理*/
			you = dynamic_cast<CCollider *>(Task_You);
			if (puck->Collision(you->mObb, puck->mpCBSphere->mColSphere)) {
				CScoreBoard::GetInstance()->GoalPlayer();
				puck->GoalPlayer();//プレイヤー側にゴールしたなら

				/*ゴール呼び出し*/
				goal = dynamic_cast<CXGoal*>(Task_You->mpParent);
				goal->GoalPerformance();
				return true;
			}
		}
		break;

		/*ゴールエネミー*/
	case CTask::E_TAG_GOAL_ENEMY:

		if (Task_You->eColTag == E_COL_BOX && Puck->eColTag == E_COL_SPHEPE) {
			/*キャスト処理*/
			you = dynamic_cast<CCollider *>(Task_You);
			if (puck->Collision(you->mObb, puck->mpCBSphere->mColSphere)) {
				CScoreBoard::GetInstance()->GoalEnemy();
				puck->GoalEnemy();//エネミー側にゴールしたなら

				/*ゴール呼び出し*/
				goal = dynamic_cast<CXGoal*>(Task_You->mpParent);
				goal->GoalPerformance();
				return true;
			}
		}
		break;

		/*坂*/
//	case CTask::E_TAG_SLOPE:
//
//		/*球体の場合*/
////		if (puck->mpCBSphere == Puck){
//
//			/*キャスト処理*/
//			you = dynamic_cast<CCollider *>(Task_You);
//			if (puck->Collision(you->mObb, puck->mpCBSphere->mColSphere)) {
//				/*坂にあたっているフラグを立てる*/
//				puck->EnabledSlope();
//				return true;
//			}
////		}
//
//		break;
	};
	return false;
}