#include "CPlayerAttack.h"
#include "../CPlayer.h"
#include "../../../../../Convenient/CConvenient.h"

/*�X�s�[�h�̃t���[������velocity��ύX����*/
/*�t���[��*/
#define FRAME_VEL_ATTACK1 0
#define FRAME_VEL_ATTACK2 20
#define FRAME_VEL_ATTACK3 30
/*�X�s�[�h*/
#define BASE_SPEED 0.4f
#define VEL_ATTACK1 BASE_SPEED * 0.5f
#define VEL_ATTACK2 0
#define VEL_ATTACK3 BASE_SPEED * 0.7f
/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED_ATTCK 30
/*�L�[���͑҂�*/
#define KEY_TIME 0.3f

//�ύX����֐�
void CPlayerAttack::ChangeState(){
	/*�W�����v����ꍇ*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = F_PL_JUMP;//�W�����v
	}
	/*�A�C�h�����O����*/
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime ||
		mFlagChangeAnima){
		mNextRegisterName = F_PL_IDLING;
	}

	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}

/*���߂ɌĂяo��*/
void CPlayerAttack::Start(){
	mAnimaSpeed = 0;//������
	mTimeKey = 0;
	mFlagChangeAnima = false;
	mAnimaSpeed = ANIMA_SPEED_ATTCK;
}

/*�U���̈ړ���������*/
void CPlayerAttack::AttackSpeed(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*�U���̑�����������*/
	if (FRAME_VEL_ATTACK1 <= pl->mAnimationTime && pl->mAnimationTime <= FRAME_VEL_ATTACK2){ //��������
		pl->mVelocity = VEL_ATTACK1;
		mAnimaSpeed = 0;
	}
	else if (FRAME_VEL_ATTACK2 <= pl->mAnimationTime && pl->mAnimationTime <= FRAME_VEL_ATTACK3){//������Ǝ~�܂�
		pl->mVelocity = VEL_ATTACK2;
		mAnimaSpeed = 0;
	}
	else{//��ԓ���
		pl->mVelocity = VEL_ATTACK3;
	}
	pl->Move();
}

/*�U���L�[�@�҂�����*/
void CPlayerAttack::KeyUpdate() {
	/*�A�j���[�V�����������Ă��Ȃ��ꍇ*/
	if (mAnimaSpeed == 0) {
		//���Ԃ����ԂɃL�[���͂���Ǝ��ԃ��Z�b�g
		if (!CConvenient::Time(&mTimeKey, KEY_TIME)) {
			if (CKey::once(KEY_ATTACK)) {
				mTimeKey = 0;
				mAnimaSpeed = ANIMA_SPEED_ATTCK;
			}
		}
		/*���Ԍo��*/
		else {
			mFlagChangeAnima = true;//�؂�ւ���
		}
	}

}

/*�X�V����*/
void CPlayerAttack::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*�A�j���[�V����*/
	pl->ChangeAnimation(F_PL_ATTACK, false, mAnimaSpeed);
	/*�U��*/
	AttackSpeed();//�U���ŏ����O�Ɉړ�������
	KeyUpdate();//�L�[���͑҂�
	pl->State(F_PL_ATTACK);//�X�e�[�^�X������

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