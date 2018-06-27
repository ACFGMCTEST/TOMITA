#include "CKingSlimeAttack.h"
#include "../CKingSlime.h"

/*�X�s�[�h�̃t���[�����œ����𑁂�����*/
/*�t���[��*/
#define FRAME_VEL_ATTACK 10
#define FRAME_VEL_ATTACK_END 20
/*�A�j���[�V�����̃X�s�[�h*/
#define ANIMA_AJUST 0.5f //�S�̂̃A�j���[�V���������p
#define ANIMA_SPEED_SLOW 300 * ANIMA_AJUST
#define ANIMA_SPEED_HIGH 60 * ANIMA_AJUST
/*�U���ړ�*/
#define BASE_SPEED 0.4f
/*�U���̈ړ���������*/
void CKingSlimeAttack::AttackSpeed() {
	CKingSlime *sli = dynamic_cast<CKingSlime*>(mpParent);
	/*�U���̑�����������*/
	if (FRAME_VEL_ATTACK <= sli->mAnimationTime &&
		sli->mAnimationTime <= FRAME_VEL_ATTACK_END) {
		mAnimaSpeed = ANIMA_SPEED_HIGH;//�����𑁂�����
		sli->mVelocity = BASE_SPEED;
		sli->mFlagAttack = true;
	}
	else {
		mAnimaSpeed = ANIMA_SPEED_SLOW;//������x������
		sli->mVelocity = 0.0f;
		sli->mFlagAttack = false;
	}
	sli->Move();
}

CKingSlimeAttack::CKingSlimeAttack() {}
CKingSlimeAttack::~CKingSlimeAttack(){}