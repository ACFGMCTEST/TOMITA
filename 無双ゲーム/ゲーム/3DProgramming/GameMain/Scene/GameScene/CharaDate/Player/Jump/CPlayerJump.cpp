#include "CPlayerJump.h"
#include "../CPlayer.h"
/*ジャンプのスピード*/
#define JUMP_SPEED 0.6f//ジャンプするスピード
/*アニメのスピード*/
#define ANIMA_SPEED_JUMP 50
#define ANIMA_SPEED_JUMP_LAND 30 //着地した

#define ANIMAKEY_ADJUST 10 //アニメーション調整用
//アニメーション KEY 調整
#define ANIMA_KEY_DEPRE 25 //アニメーションの踏み込み状態(最後)
#define ANIMA_KEY_JUMP_UP  30 //アニメーションのジャンプ中状態(最後)
#define ANIMA_KEY_JUMP_DOWN  40 //アニメーションのジャンプ落ちている状態(最後)
#define ANIMA_KEY_LAND  60 //アニメーション着地時(最後)

//変更する関数
void CPlayerJump::ChangeState(){
	/*アイドリングする場合*　地面についたとき*/
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime) {
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
	mVelocity = pl->mVelocity;//移動量を代入する
	pl->mFlagJump = true;//プレイヤーをジャンプさせる
	mFlagFall = false;
}


/*アニメーション*/
bool CPlayerJump::JumpAnima()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	bool flag = false;//ジャンプのアニメーション
	float speed = ANIMA_SPEED_JUMP;
	/*アニメーションの調整*/
	/*踏み込み中*/
	if (0 <= pl->mAnimationTime && pl->mAnimationTime < ANIMA_KEY_DEPRE) {
		flag = false;
	}
	/*ジャンプ中*/
	else if (ANIMA_KEY_DEPRE <= pl->mAnimationTime && pl->mAnimationTime < ANIMA_KEY_JUMP_UP) 
	{	
		flag =  true;
	}
	/*ジャンプ落ちている*/
	else if (ANIMA_KEY_JUMP_UP <= pl->mAnimationTime && pl->mAnimationTime < ANIMA_KEY_JUMP_DOWN) 
	{
		if (pl->mFlagJump) return true;

		flag = false;
	}
	/*着地時*/
	else if (ANIMA_KEY_JUMP_DOWN <= pl->mAnimationTime && pl->mAnimationTime <= ANIMA_KEY_LAND)
	{
		speed = ANIMA_SPEED_JUMP_LAND;
		if (pl->mFlagJump) return true;
		flag = false;
	}
	pl->ChangeAnimation(CPlayer::E_JUMP, false, speed);//アニメーションをする

	return flag;


}

/*更新処理*/
void CPlayerJump::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);

	
	/*アニメーションで判断*/
	if (JumpAnima()) {
		/*ジャンプ*/
		pl->mVelocity = mVelocity;
		pl->Move();//移動関数.横(x,z)の移動
		mPrevPosY = pl->mPosition.y;//現在のポジション記憶
		float jumpVilocity = JUMP_SPEED - GRAVITY(pl->mGravitTime);//動かす力
		/*ジャンプが0より大きい場合*/
		pl->mPosition.y += jumpVilocity;
	}
	/*落下中でない場合*/
	if (!mFlagFall) {
		pl->mFlagJump = true;//地面から飛ぶときの判定調整用
		/*落下中の場合*/
		float graSpeed = GRAVITY(pl->mGravitTime);
		if (JUMP_SPEED <= graSpeed * 2) {
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

CPlayerJump::CPlayerJump() {
}

CPlayerJump::~CPlayerJump()
{
}