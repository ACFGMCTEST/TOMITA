#include "CKingSlimeAttack.h"
#include "../CKingSlime.h"

/*スピードのフレーム数で動きを早くする*/
/*フレーム*/
#define FRAME_VEL_ATTACK 10
#define FRAME_VEL_ATTACK_END 20
/*アニメーションのスピード*/
#define ANIMA_AJUST 0.5f //全体のアニメーション調整用
#define ANIMA_SPEED_SLOW 300 * ANIMA_AJUST
#define ANIMA_SPEED_HIGH 60 * ANIMA_AJUST
/*攻撃移動*/
#define BASE_SPEED 0.4f
/*攻撃の移動速さ調整*/
void CKingSlimeAttack::AttackSpeed() {
	CKingSlime *sli = dynamic_cast<CKingSlime*>(mpParent);
	/*攻撃の速さをいじる*/
	if (FRAME_VEL_ATTACK <= sli->mAnimationTime &&
		sli->mAnimationTime <= FRAME_VEL_ATTACK_END) {
		mAnimaSpeed = ANIMA_SPEED_HIGH;//動きを早くする
		sli->mVelocity = BASE_SPEED;
		sli->mFlagAttack = true;
	}
	else {
		mAnimaSpeed = ANIMA_SPEED_SLOW;//動きを遅くする
		sli->mVelocity = 0.0f;
		sli->mFlagAttack = false;
	}
	sli->Move();
}

CKingSlimeAttack::CKingSlimeAttack() {}
CKingSlimeAttack::~CKingSlimeAttack(){}