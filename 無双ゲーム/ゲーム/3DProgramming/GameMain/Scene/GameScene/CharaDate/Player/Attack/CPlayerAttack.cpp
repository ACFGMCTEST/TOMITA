#include "CPlayerAttack.h"
#include "../CPlayer.h"
#include "../../../../../Convenient/CConvenient.h"

/*スピードのフレーム数でvelocityを変更する*/
/*フレーム*/
#define FRAME_VEL_ATTACK1 0
#define FRAME_VEL_ATTACK2 20
#define FRAME_VEL_ATTACK3 30
/*スピード*/
#define BASE_SPEED 0.4f
#define VEL_ATTACK1 BASE_SPEED * 0.5f
#define VEL_ATTACK2 0
#define VEL_ATTACK3 BASE_SPEED * 0.7f
/*アニメのスピード*/
#define ANIMA_SPEED_ATTCK 30
/*キー入力待ち*/
#define KEY_TIME 0.3f

//変更する関数
void CPlayerAttack::ChangeState(){
	/*ジャンプする場合*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = F_PL_JUMP;//ジャンプ
	}
	/*アイドリングする*/
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime ||
		mFlagChangeAnima){
		mNextRegisterName = F_PL_IDLING;
	}

	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}

/*初めに呼び出し*/
void CPlayerAttack::Start(){
	mAnimaSpeed = 0;//初期化
	mTimeKey = 0;
	mFlagChangeAnima = false;
	mAnimaSpeed = ANIMA_SPEED_ATTCK;
}

/*攻撃の移動速さ調整*/
void CPlayerAttack::AttackSpeed(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*攻撃の速さをいじる*/
	if (FRAME_VEL_ATTACK1 <= pl->mAnimationTime && pl->mAnimationTime <= FRAME_VEL_ATTACK2){ //少し動く
		pl->mVelocity = VEL_ATTACK1;
		mAnimaSpeed = 0;
	}
	else if (FRAME_VEL_ATTACK2 <= pl->mAnimationTime && pl->mAnimationTime <= FRAME_VEL_ATTACK3){//ちょっと止まる
		pl->mVelocity = VEL_ATTACK2;
		mAnimaSpeed = 0;
	}
	else{//一番動く
		pl->mVelocity = VEL_ATTACK3;
	}
	pl->Move();
}

/*攻撃キー　待ち時間*/
void CPlayerAttack::KeyUpdate() {
	/*アニメーションが動いていない場合*/
	if (mAnimaSpeed == 0) {
		//時間がたつ間にキー入力すると時間リセット
		if (!CConvenient::Time(&mTimeKey, KEY_TIME)) {
			if (CKey::once(KEY_ATTACK)) {
				mTimeKey = 0;
				mAnimaSpeed = ANIMA_SPEED_ATTCK;
			}
		}
		/*時間経過*/
		else {
			mFlagChangeAnima = true;//切り替える
		}
	}

}

/*更新処理*/
void CPlayerAttack::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*アニメーション*/
	pl->ChangeAnimation(F_PL_ATTACK, false, mAnimaSpeed);
	/*攻撃*/
	AttackSpeed();//攻撃で少し前に移動させる
	KeyUpdate();//キー入力待ち
	pl->State(F_PL_ATTACK);//ステータスを入れる

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