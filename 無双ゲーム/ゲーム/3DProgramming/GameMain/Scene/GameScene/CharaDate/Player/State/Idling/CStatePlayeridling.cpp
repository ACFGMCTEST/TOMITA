#include "CStatePlayeridling.h"
#include "../../CXCharPlayer.h"


//変更する関数
void CStatePlayerIdling::ChangeState(){
	/*方向キー入力した場合　走る*/
	if (CKey::push('A') || CKey::push('D') || CKey::push('S') || CKey::push('W')){
		mNextRegisterName = PL_STATE_RUN;//走る状態に移行
	}
	/*ジャンプする場合*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = PL_STATE_JUMP;//ジャンプ
	}
	/*攻撃する場合*/
	if (CKey::once(KEY_ATTACK)){
		mNextRegisterName = PL_STATE_ATTACK;//攻撃
	}
	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}

/*初めに呼び出し*/
void CStatePlayerIdling::Start(){
	CXCharPlayer *pl;
	pl = dynamic_cast<CXCharPlayer*>(mpParent);
	pl->mVelocity = 0;//動かないにする
}
/*更新処理*/
void CStatePlayerIdling::Update(){
	CXCharPlayer *pl;
	pl = dynamic_cast<CXCharPlayer*>(mpParent);
	/*アイドリングの処理*/
	pl->ChangeAnimation(CTask::E_IDLING, true, ANIMA_SPEED);

}

CStatePlayerIdling::CStatePlayerIdling()
{

}

CStatePlayerIdling::~CStatePlayerIdling()
{
}