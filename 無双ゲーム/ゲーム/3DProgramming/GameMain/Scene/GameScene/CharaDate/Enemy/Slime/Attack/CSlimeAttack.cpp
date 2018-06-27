#include "CSlimeAttack.h"
#include "../CSlime.h"
/*�X�s�[�h�̃t���[�����œ����𑁂�����*/
/*�t���[��*/
#define FRAME_VEL_ATTACK 10
#define FRAME_VEL_ATTACK_END 20
/*�A�j���[�V�����̃X�s�[�h*/
#define ANIMA_AJUST 0.5f //�S�̂̃A�j���[�V���������p
#define ANIMA_SPEED_SLOW 300 * ANIMA_AJUST
#define ANIMA_SPEED_HIGH 60 * ANIMA_AJUST
/*�U���ړ�*/
#define BASE_SPEED 0.2f

//�ύX����֐�
void CSlimeAttack::ChangeState(){
	/*�A�C�h�����O����*/
	CSlime *sli= dynamic_cast<CSlime*>(mpParent);
	if (sli->mAnimationTime >
		sli->mpModel->mAnimationSet[sli->mAnimationIndex]->mMaxTime) {
		mNextRegisterName = F_SLI_IDLING;
	}
	/*�_���[�W���󂯂Ă���Ȃ�*/
	if (sli->mFlagDamage) {
		mNextRegisterName = F_SLI_DAMAGE;//�_���[�W
	}
	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}

/*���߂ɌĂяo��*/
void CSlimeAttack::Start(){
	mAnimaSpeed = ANIMA_SPEED_SLOW;//������
}

/*�U���̈ړ���������*/
void CSlimeAttack::AttackSpeed(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
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

/*�X�V����*/
void CSlimeAttack::Update()
{
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*�A�j���[�V����*/
	sli->ChangeAnimation(F_SLI_ATTACK,F_SLI_KING_ATTACK, false, mAnimaSpeed);
	/*�U��*/
	AttackSpeed();//�U���ŏ����O�Ɉړ�������
	sli->State(F_SLI_ATTACK);
}

//�J�ڎ��̏���
// isNext��false�ɖ߂������͂����ōs���Ƃ悢
void CSlimeAttack::OnChangeEvent()
{

}

CSlimeAttack::CSlimeAttack()
{
}

CSlimeAttack::~CSlimeAttack()
{
}