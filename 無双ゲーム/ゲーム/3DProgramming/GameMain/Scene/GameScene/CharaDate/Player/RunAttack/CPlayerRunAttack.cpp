#include "CPlayerRunAttack.h"
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

//変更する関数
void CPlayerRunAttack::ChangeState(){
	/*ジャンプする場合*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = PL_STATE_JUMP;//ジャンプ
	}
	/*アイドリングする*/
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime){
		mNextRegisterName = PL_STATE_IDLING;
	}

	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}
/*初めに呼び出し*/
void CPlayerRunAttack::Start(){
	
}
/*更新処理*/
void CPlayerRunAttack::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*アニメーション*/
	pl->ChangeAnimation(CTask::E_RUN_ATTACK, false, ANIMA_SPEED_RUN_ATTCK);
	pl->Move();
	pl->State(PL_STATE_RUN_ATTACK);
}
//遷移時の処理
// isNextをfalseに戻す処理はここで行うとよい
void CPlayerRunAttack::OnChangeEvent()
{

}

CPlayerRunAttack::CPlayerRunAttack()
{
}

CPlayerRunAttack::~CPlayerRunAttack()
{
}