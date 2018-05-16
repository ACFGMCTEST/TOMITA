#include "CStatePlayerRunAttack.h"
#include "../../CXCharPlayer.h"
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
void CStatePlayerRunAttack::ChangeState(){
	/*ジャンプする場合*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = PL_STATE_JUMP;//ジャンプ
	}
	/*アイドリングする*/
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime){
		mNextRegisterName = PL_STATE_IDLING;
	}

	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}
/*初めに呼び出し*/
void CStatePlayerRunAttack::Start(){
	
}
/*更新処理*/
void CStatePlayerRunAttack::Update()
{
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	/*アニメーション*/
	pl->ChangeAnimation(CTask::E_RUN_ATTACK, false, ANIMA_SPEED_RUN_ATTCK);
	pl->Move();
}
//遷移時の処理
// isNextをfalseに戻す処理はここで行うとよい
void CStatePlayerRunAttack::OnChangeEvent()
{

}

CStatePlayerRunAttack::CStatePlayerRunAttack()
{
}

CStatePlayerRunAttack::~CStatePlayerRunAttack()
{
}