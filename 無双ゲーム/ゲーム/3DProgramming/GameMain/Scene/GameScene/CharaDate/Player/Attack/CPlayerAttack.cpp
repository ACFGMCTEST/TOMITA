#include "CPlayerAttack.h"
#include "../CPlayer.h"
#include "../../../../../Convenient/CConvenient.h"
#include "../../CSceneModel.h"

/*スピードのフレーム数でvelocityを変更する*/
/*フレーム*/
/*スピード*/
#define BASE_SPEED 0.4f
#define VEL_ATTACK1 BASE_SPEED * 0.5f
#define VEL_ATTACK2 BASE_SPEED * 0.7f
/*アニメのスピード*/
#define ANIMA_SPEED_ATTCK 60
/*キー入力待ち*/
#define KEY_TIME 0.1f

//変更する関数
void CPlayerAttack::ChangeState(){
	/*ジャンプする場合*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = F_PL_JUMP;//ジャンプ
	}
	/*アイドリングする*/
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	if (mFlagChangeAnima){
		mNextRegisterName = F_PL_IDLING;
	}

	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}

/*初めに呼び出し*/
void CPlayerAttack::Start(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	pl->mPower = ATTACK_POWER;
	eAttackFrame = EAttackFrame::Attack1sta;
	mAnimaSpeed = 0;//初期化
	mTimeKey = 0;
	mFlagChangeAnima = false;
	mAnimaSpeed = ANIMA_SPEED_ATTCK;
}

/*攻撃の移動速さ調整*/
void CPlayerAttack::AttackSpeed(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	switch (eAttackFrame)
	{
	case CPlayerAttack::Attack1sta:
	case CPlayerAttack::Attack1end:
		pl->mVelocity = VEL_ATTACK1;
		/*最大まで行くとチェンジで*/
		if (pl->mAnimationTime > Attack2sta) {
			mFlagChangeAnima = true;
		}
		//次のアニメーションに行こうとすると止まる
		if (Attack1end <= pl->mAnimationTime && pl->mAnimationTime <= Attack2sta) {
			pl->mVelocity = 0;
			/*キー入力でアニメーション再開*/
			if (CKey::once(KEY_ATTACK)) {
				eAttackFrame = Attack2sta;
				pl->mAnimationTime = Attack2sta;
			}
		}
		
		break;
	case CPlayerAttack::Attack2sta:
	case CPlayerAttack::Attack2end:
		pl->mVelocity = VEL_ATTACK2;
		//次のシーンに移行する
		if (pl->mAnimationTime >= Attack2end) {
			mFlagChangeAnima = true;
		}
		break;
	}
	pl->Move();
}

/*更新処理*/
void CPlayerAttack::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*アニメーション*/
	pl->ChangeAnimation(F_PL_ATTACK, false, mAnimaSpeed);
	/*攻撃*/
	AttackSpeed();//攻撃で少し前に移動させる

}
//遷移時の処理
// isNextをfalseに戻す処理はここで行うとよい
void CPlayerAttack::OnChangeEvent()
{

}

CPlayerAttack::CPlayerAttack()
{
}

CPlayerAttack::~CPlayerAttack()
{
}