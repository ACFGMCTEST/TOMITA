#include "CPlayerJump.h"
#include "../CPlayer.h"
/*ジャンプのスピード*/
#define JUMP_SPEED 0.3f//ジャンプするスピード
/*アニメのスピード*/
#define ANIMA_SPEED_JUMP 30

//変更する関数
void CPlayerJump::ChangeState(){
	/*アイドリングする場合*　地面についたとき*/
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	if (!pl->mFlagJump){
		mNextRegisterName = PL_STATE_IDLING;//アイドリングする
	}
	/*攻撃する場合*/
	if (CKey::once(KEY_ATTACK)){
		mNextRegisterName = PL_STATE_ATTACK;//攻撃
	}
	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}
/*初めに呼び出し*/
void CPlayerJump::Start()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	pl->mFlagJump = true;//プレイヤーをジャンプさせる
	mFlagFall = false;
}
/*更新処理*/
void CPlayerJump::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*アニメーション*/
	pl->ChangeAnimation(CPlayer::E_JUMP, true, ANIMA_SPEED_JUMP);

	/*ジャンプ*/
	pl->Move();//移動関数.横(x,z)の移動
	mPrevPosY = pl->mPosition.y;//現在のポジション記憶
	float jumpVilocity = JUMP_SPEED - GRAVITY(pl->mGravitTime);//動かす力
	/*ジャンプが0より大きい場合*/
	pl->mPosition.y += jumpVilocity;
	/*落下中でない場合*/
	if (!mFlagFall){
		pl->mFlagJump = true;//地面から飛ぶときの判定調整用
		/*落下中の場合*/
		float graSpeed = GRAVITY(pl->mGravitTime);
		if (JUMP_SPEED <= graSpeed*2){
			mFlagFall = true;
		}
	}
	pl->State(PL_STATE_JUMP);


}
//遷移時の処理
// isNextをfalseに戻す処理はここで行うとよい
void CPlayerJump::OnChangeEvent()
{

}

CPlayerJump::CPlayerJump()
{
}

CPlayerJump::~CPlayerJump()
{
}