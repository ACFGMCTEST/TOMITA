#include "CStatePlayerAttack.h"
#include "../../CXCharPlayer.h"

//変更する関数
void CStatePlayerAttack::ChangeState(){
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
void CStatePlayerAttack::Start()
{

}
/*更新処理*/
void CStatePlayerAttack::Update()
{
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	/*アニメーション*/
	pl->ChangeAnimation(CTask::E_ATTACK, false, ANIMA_SPEED_ATTCK);


}
//遷移時の処理
// isNextをfalseに戻す処理はここで行うとよい
void CStatePlayerAttack::OnChangeEvent()
{

}

CStatePlayerAttack::CStatePlayerAttack()
{
}

CStatePlayerAttack::~CStatePlayerAttack()
{
}