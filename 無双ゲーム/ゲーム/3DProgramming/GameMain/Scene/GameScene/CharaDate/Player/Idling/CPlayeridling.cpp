#include "CPlayeridling.h"
#include "../CPlayer.h"

/*アニメのスピード*/
#define ANIMA_SPEED 60 * 2

//変更する関数
void CPlayerIdling::ChangeState(){
	/*方向キー入力した場合　走る*/
	if (CKey::push('A') || CKey::push('D') || CKey::push('S') || CKey::push('W')){
		mNextRegisterName = F_PL_RUN;//走る状態に移行
	}
	/*回避する場合*/
	else if (CKey::push(KEY_AVOID)) {
		mNextRegisterName = F_PL_AVOID;//回避に移行
	}
	/*ジャンプする場合*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = F_PL_JUMP;//ジャンプ
	}
	/*攻撃する場合*/
	if (CKey::once(KEY_ATTACK)){
		mNextRegisterName = F_PL_ATTACK;//攻撃
	}
	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}

/*初めに呼び出し*/
void CPlayerIdling::Start(){
	CPlayer *pl;
	pl = dynamic_cast<CPlayer*>(mpParent);
	pl->mVelocity = 0;//動かないにする
}
/*更新処理*/
void CPlayerIdling::Update(){
	CPlayer *pl;
	pl = dynamic_cast<CPlayer*>(mpParent);
	/*アイドリングの処理*/
	pl->ChangeAnimation(F_PL_IDLING, true, ANIMA_SPEED);

}

CPlayerIdling::CPlayerIdling()
{

}

CPlayerIdling::~CPlayerIdling()
{
}