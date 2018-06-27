#include "CPlayerAvoid.h"
#include "../CPlayer.h"
/*スピードのフレーム数でvelocityを変更する*/
/*フレーム*/
#define FRAME_VEL_ATTACK1 0
#define FRAME_VEL_ATTACK2 30
#define FRAME_VEL_ATTACK3 40
/*スピード*/
#define VEL_ATTACK1 0.05f
#define VEL_ATTACK2 0
#define VEL_ATTACK3 0.07f
/*アニメのスピード*/
#define ANIMA_SPEED 20
/*回避スピード*/
#define AVOID_SPEED SPEED_RUN  * 1.4f
//変更する関数
void CPlayerAvoid::ChangeState(){
	/*ジャンプする場合*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = F_PL_JUMP;//ジャンプ
	}
	/*アイドリングする*/
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	if (pl->mAnimationTime > 
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime){
		mNextRegisterName = F_PL_IDLING;
	}

	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}
/*初めに呼び出し*/
void CPlayerAvoid::Start(){
	
}
/*更新処理*/
void CPlayerAvoid::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*アニメーション*/
	pl->ChangeAnimation(F_PL_AVOID, false, ANIMA_SPEED);
	pl->mVelocity = AVOID_SPEED;
	pl->Move();
	pl->State(F_PL_AVOID);
}
//遷移時の処理
// isNextをfalseに戻す処理はここで行うとよい
void CPlayerAvoid::OnChangeEvent()
{

}

CPlayerAvoid::CPlayerAvoid()
{
}

CPlayerAvoid::~CPlayerAvoid()
{
}