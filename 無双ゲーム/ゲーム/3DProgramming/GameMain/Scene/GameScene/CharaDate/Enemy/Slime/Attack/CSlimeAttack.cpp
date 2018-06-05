#include "CSlimeAttack.h"
#include "../CSlime.h"
/*スピードのフレーム数で動きを早くする*/
/*フレーム*/
#define FRAME_VEL_ATTACK 10
#define FRAME_VEL_ATTACK_END 20
/*アニメーションのスピード*/
#define ANIMA_SPEED_SLOW 300;
#define ANIMA_SPEED_HIGH 60;
/*攻撃移動*/
#define BASE_SPEED 0.2f
//変更する関数
void CSlimeAttack::ChangeState(){
	/*アイドリングする*/
	CSlime *sli= dynamic_cast<CSlime*>(mpParent);
	if (sli->mAnimationTime >
		sli->mpModel->mAnimationSet[sli->mAnimationIndex]->mMaxTime) {
		mNextRegisterName = SLI_STATE_IDLING;
	}
	/*ダメージを受けているなら*/
	if (sli->mFlagDamage) {
		mNextRegisterName = SLI_STATE_DAMAGE;//ダメージ
	}
	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}
/*初めに呼び出し*/
void CSlimeAttack::Start(){
	mAnimaSpeed = ANIMA_SPEED_SLOW;//初期化
}
/*攻撃の移動速さ調整*/
void CSlimeAttack::AttackSpeed(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*攻撃の速さをいじる*/
	if (FRAME_VEL_ATTACK <= sli->mAnimationTime && 
		sli->mAnimationTime <= FRAME_VEL_ATTACK_END) {
		mAnimaSpeed = ANIMA_SPEED_HIGH;//動きを早くする
		sli->mVelocity = BASE_SPEED;
	}
	else {
		mAnimaSpeed = ANIMA_SPEED_SLOW;//動きを遅くする
		sli->mVelocity = 0.0f;
	}
	sli->Move();
}
/*更新処理*/
void CSlimeAttack::Update()
{
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*アニメーション*/
	sli->ChangeAnimation(CSlime::E_ATTACK, false, mAnimaSpeed);
	/*攻撃*/
	AttackSpeed();//攻撃で少し前に移動させる
}
//遷移時の処理
// isNextをfalseに戻す処理はここで行うとよい
void CSlimeAttack::OnChangeEvent()
{

}

CSlimeAttack::CSlimeAttack()
{
}

CSlimeAttack::~CSlimeAttack()
{
}