#include "CPlayerAvoid.h"
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
/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED 20
/*����X�s�[�h*/
#define AVOID_SPEED SPEED_RUN  * 1.4f
//�ύX����֐�
void CPlayerAvoid::ChangeState(){
	/*�W�����v����ꍇ*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = F_PL_JUMP;//�W�����v
	}
	/*�A�C�h�����O����*/
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	if (pl->mAnimationTime > 
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime){
		mNextRegisterName = F_PL_IDLING;
	}

	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}
/*���߂ɌĂяo��*/
void CPlayerAvoid::Start(){
	
}
/*�X�V����*/
void CPlayerAvoid::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*�A�j���[�V����*/
	pl->ChangeAnimation(F_PL_AVOID, false, ANIMA_SPEED);
	pl->mVelocity = AVOID_SPEED;
	pl->Move();
	pl->State(F_PL_AVOID);
}
//�J�ڎ��̏���
// isNext��false�ɖ߂������͂����ōs���Ƃ悢
void CPlayerAvoid::OnChangeEvent()
{

}

CPlayerAvoid::CPlayerAvoid()
{
}

CPlayerAvoid::~CPlayerAvoid()
{
}