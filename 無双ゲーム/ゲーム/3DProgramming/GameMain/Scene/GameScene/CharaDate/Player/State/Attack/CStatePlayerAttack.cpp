#include "CStatePlayerAttack.h"
#include "../../CXCharPlayer.h"
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

//�ύX����֐�
void CStatePlayerAttack::ChangeState(){
	/*�W�����v����ꍇ*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = PL_STATE_JUMP;//�W�����v
	}
	/*�A�C�h�����O����*/
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime){
		mNextRegisterName = PL_STATE_IDLING;
	}

	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}

/*���߂ɌĂяo��*/
void CStatePlayerAttack::Start(){
	mAnimaSpeed = 0;//������
}

/*�U���̈ړ���������*/
void CStatePlayerAttack::AttackSpeed(){
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	/*�U���̑�����������*/
	if (FRAME_VEL_ATTACK1 <= pl->mAnimationTime && pl->mAnimationTime <= FRAME_VEL_ATTACK2){ //��������
		pl->mVelocity = VEL_ATTACK1;
		printf("�A�^�b�N1�ł�\n");
	}
	else if (FRAME_VEL_ATTACK2 <= pl->mAnimationTime && pl->mAnimationTime <= FRAME_VEL_ATTACK3){//������Ǝ~�܂�
		pl->mVelocity = VEL_ATTACK2;
		printf("�A�^�b�N2�ł�\n");
	}
	else{//��ԓ���
		pl->mVelocity = VEL_ATTACK3;
		printf("�A�^�b�N3�ł�\n");
	}

	printf("���݃t���[��%f\n", pl->mAnimationTime);
	pl->Move();
}
/*�X�V����*/
void CStatePlayerAttack::Update()
{
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	/*�A�j���[�V����*/
	pl->ChangeAnimation(CTask::E_ATTACK, false, ANIMA_SPEED_ATTCK);
	/*�U��*/
	AttackSpeed();//�U���ŏ����O�Ɉړ�������
	pl->State(PL_STATE_ATTACK);//�X�e�[�^�X������
}
//�J�ڎ��̏���
// isNext��false�ɖ߂������͂����ōs���Ƃ悢
void CStatePlayerAttack::OnChangeEvent()
{

}

CStatePlayerAttack::CStatePlayerAttack()
{
}

CStatePlayerAttack::~CStatePlayerAttack()
{
}