#include "CStatePlayerAttack.h"
#include "../../CXCharPlayer.h"

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
void CStatePlayerAttack::Start()
{

}
/*�X�V����*/
void CStatePlayerAttack::Update()
{
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	/*�A�j���[�V����*/
	pl->ChangeAnimation(CTask::E_ATTACK, false, ANIMA_SPEED_ATTCK);


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