#include "CPlayerAttack.h"
#include "../CPlayer.h"
#include "../../../../../Convenient/CConvenient.h"
#include "../../CSceneModel.h"

/*�X�s�[�h�̃t���[������velocity��ύX����*/
/*�t���[��*/
/*�X�s�[�h*/
#define BASE_SPEED 0.4f
#define VEL_ATTACK1 BASE_SPEED * 0.5f
#define VEL_ATTACK2 BASE_SPEED * 0.7f
/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED_ATTCK 60
/*�L�[���͑҂�*/
#define KEY_TIME 0.1f

//�ύX����֐�
void CPlayerAttack::ChangeState(){
	/*�W�����v����ꍇ*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = F_PL_JUMP;//�W�����v
	}
	/*�A�C�h�����O����*/
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	if (mFlagChangeAnima){
		mNextRegisterName = F_PL_IDLING;
	}

	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}

/*���߂ɌĂяo��*/
void CPlayerAttack::Start(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	pl->mPower = ATTACK_POWER;
	eAttackFrame = EAttackFrame::Attack1sta;
	mAnimaSpeed = 0;//������
	mTimeKey = 0;
	mFlagChangeAnima = false;
	mAnimaSpeed = ANIMA_SPEED_ATTCK;
}

/*�U���̈ړ���������*/
void CPlayerAttack::AttackSpeed(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	switch (eAttackFrame)
	{
	case CPlayerAttack::Attack1sta:
	case CPlayerAttack::Attack1end:
		pl->mVelocity = VEL_ATTACK1;
		/*�ő�܂ōs���ƃ`�F���W��*/
		if (pl->mAnimationTime > Attack2sta) {
			mFlagChangeAnima = true;
		}
		//���̃A�j���[�V�����ɍs�����Ƃ���Ǝ~�܂�
		if (Attack1end <= pl->mAnimationTime && pl->mAnimationTime <= Attack2sta) {
			pl->mVelocity = 0;
			/*�L�[���͂ŃA�j���[�V�����ĊJ*/
			if (CKey::once(KEY_ATTACK)) {
				eAttackFrame = Attack2sta;
				pl->mAnimationTime = Attack2sta;
			}
		}
		
		break;
	case CPlayerAttack::Attack2sta:
	case CPlayerAttack::Attack2end:
		pl->mVelocity = VEL_ATTACK2;
		//���̃V�[���Ɉڍs����
		if (pl->mAnimationTime >= Attack2end) {
			mFlagChangeAnima = true;
		}
		break;
	}
	pl->Move();
}

/*�X�V����*/
void CPlayerAttack::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*�A�j���[�V����*/
	pl->ChangeAnimation(F_PL_ATTACK, false, mAnimaSpeed);
	/*�U��*/
	AttackSpeed();//�U���ŏ����O�Ɉړ�������

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