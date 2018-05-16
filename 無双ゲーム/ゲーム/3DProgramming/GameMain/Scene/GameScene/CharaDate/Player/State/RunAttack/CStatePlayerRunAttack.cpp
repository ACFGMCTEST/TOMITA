#include "CStatePlayerRunAttack.h"
#include "../../CXCharPlayer.h"
/*�X�s�[�h�̃t���[������velocity��ύX����*/
/*�t���[��*/
#define FRAME_VEL_ATTACK1 0
#define FRAME_VEL_ATTACK2 30
#define FRAME_VEL_ATTACK3 40
/*�X�s�[�h*/
#define VEL_ATTACK1 0.05f
#define VEL_ATTACK2 0
#define VEL_ATTACK3 0.07f

//�ύX����֐�
void CStatePlayerRunAttack::ChangeState(){
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
void CStatePlayerRunAttack::Start(){
	
}
/*�X�V����*/
void CStatePlayerRunAttack::Update()
{
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	/*�A�j���[�V����*/
	pl->ChangeAnimation(CTask::E_RUN_ATTACK, false, ANIMA_SPEED_RUN_ATTCK);
	pl->Move();
}
//�J�ڎ��̏���
// isNext��false�ɖ߂������͂����ōs���Ƃ悢
void CStatePlayerRunAttack::OnChangeEvent()
{

}

CStatePlayerRunAttack::CStatePlayerRunAttack()
{
}

CStatePlayerRunAttack::~CStatePlayerRunAttack()
{
}