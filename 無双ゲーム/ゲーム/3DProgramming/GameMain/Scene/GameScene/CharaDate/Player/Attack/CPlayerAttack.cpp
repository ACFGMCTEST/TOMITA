#include "CPlayerAttack.h"
#include "../CPlayer.h"
/*�X�s�[�h�̃t���[������velocity��ύX����*/
/*�t���[��*/
#define FRAME_VEL_ATTACK1 0
#define FRAME_VEL_ATTACK2 30
#define FRAME_VEL_ATTACK3 40
/*�X�s�[�h*/
#define BASE_SPEED 0.2f
#define VEL_ATTACK1 BASE_SPEED * 0.5f
#define VEL_ATTACK2 0
#define VEL_ATTACK3 BASE_SPEED * 0.7f
/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED_ATTCK 60

//�ύX����֐�
void CPlayerAttack::ChangeState(){
	/*�W�����v����ꍇ*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = PL_STATE_JUMP;//�W�����v
	}
	/*�A�C�h�����O����*/
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime){
		mNextRegisterName = PL_STATE_IDLING;
	}

	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}

/*���߂ɌĂяo��*/
void CPlayerAttack::Start(){
	mAnimaSpeed = 0;//������
}

/*�U���̈ړ���������*/
void CPlayerAttack::AttackSpeed(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*�U���̑�����������*/
	if (FRAME_VEL_ATTACK1 <= pl->mAnimationTime && pl->mAnimationTime <= FRAME_VEL_ATTACK2){ //��������
		pl->mVelocity = VEL_ATTACK1;
	}
	else if (FRAME_VEL_ATTACK2 <= pl->mAnimationTime && pl->mAnimationTime <= FRAME_VEL_ATTACK3){//������Ǝ~�܂�
		pl->mVelocity = VEL_ATTACK2;
	}
	else{//��ԓ���
		pl->mVelocity = VEL_ATTACK3;
	}
	pl->Move();
}
/*�X�V����*/
void CPlayerAttack::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*�A�j���[�V����*/
	pl->ChangeAnimation(CPlayer::E_ATTACK, false, ANIMA_SPEED_ATTCK);
	/*�U��*/
	AttackSpeed();//�U���ŏ����O�Ɉړ�������
	pl->State(PL_STATE_ATTACK);//�X�e�[�^�X������
}
//�J�ڎ��̏���
// isNext��false�ɖ߂������͂����ōs���Ƃ悢
void CPlayerAttack::OnChangeEvent()
{

}

CPlayerAttack::CPlayerAttack()
{
}

CPlayerAttack::~CPlayerAttack()
{
}