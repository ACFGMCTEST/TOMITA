#include "CPlayerRunAttack.h"
#include "../CPlayer.h"
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
void CPlayerRunAttack::ChangeState(){
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
void CPlayerRunAttack::Start(){
	
}
/*�X�V����*/
void CPlayerRunAttack::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*�A�j���[�V����*/
	pl->ChangeAnimation(CTask::E_RUN_ATTACK, false, ANIMA_SPEED_RUN_ATTCK);
	pl->Move();
	pl->State(PL_STATE_RUN_ATTACK);
}
//�J�ڎ��̏���
// isNext��false�ɖ߂������͂����ōs���Ƃ悢
void CPlayerRunAttack::OnChangeEvent()
{

}

CPlayerRunAttack::CPlayerRunAttack()
{
}

CPlayerRunAttack::~CPlayerRunAttack()
{
}