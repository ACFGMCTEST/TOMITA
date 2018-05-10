#include "CStatePlayerRun.h"
#include "../../CXCharPlayer.h"

//変更する関数
void CStatePlayerRun::ChangeState(){
	/*アイドリングする場合*/
	if (CKey::push('W') || CKey::push('A') || CKey::push('S') || CKey::push('D')){}
	else{
		mNextRegisterName = PL_STATE_IDLING;
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
void CStatePlayerRun::Start(){}
/*更新処理*/
void CStatePlayerRun::Update(){
	CXCharPlayer *pl;
	pl = dynamic_cast<CXCharPlayer*>(mpParent);
	pl->ChangeAnimation(CTask::E_RUN, true, ANIMA_SPEED_RUN);
	SPEED_RUN_ACC(pl->mVelocity);//プレイヤー移動速度計算
	pl->PlayerMoveRot();//プレイヤー向きを決める
}

CStatePlayerRun::CStatePlayerRun()
{
}

CStatePlayerRun::~CStatePlayerRun()
{
}