#include "CPlayerRun.h"
#include "../CPlayer.h"
/*アニメのスピード*/
#define ANIMA_SPEED_RUN 60

//変更する関数
void CPlayerRun::ChangeState(){
	/*アイドリングする場合*/
	if ( !(CKey::push('W') || CKey::push('A') || CKey::push('S') || CKey::push('D') ) ){
		mNextRegisterName = PL_STATE_IDLING;
	}/*回避する場合*/
	else if (CKey::push(KEY_AVOID)) {
		mNextRegisterName = PL_STATE_AVOID;//回避に移行
	}/*ジャンプする場合*/
	else if (CKey::once(KEY_JUMP)){
		mNextRegisterName = PL_STATE_JUMP;//ジャンプ
	}
	/*攻撃する場合*/
	else if (CKey::once(KEY_ATTACK)){
		mNextRegisterName = PL_STATE_ATTACK;//攻撃
	}
	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}
/*初めに呼び出し*/
void CPlayerRun::Start(){}
/*更新処理*/
void CPlayerRun::Update(){
	CPlayer *pl;
	pl = dynamic_cast<CPlayer*>(mpParent);
	pl->ChangeAnimation(CPlayer::E_RUN, true, ANIMA_SPEED_RUN);
	SPEED_RUN_ACC(pl->mVelocity);//プレイヤー移動速度計算
	pl->PlayerMoveRot();//プレイヤー向きを決める
	pl->State(PL_STATE_RUN);
}

CPlayerRun::CPlayerRun()
{
}

CPlayerRun::~CPlayerRun()
{
}