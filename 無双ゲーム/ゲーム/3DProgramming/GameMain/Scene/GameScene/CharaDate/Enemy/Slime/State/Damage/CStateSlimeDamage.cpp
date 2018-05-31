#include "CStateSlimeDamage.h"
#include "../../CSlime.h"


//�ύX����֐�
void CStateSlimeDamage::ChangeState(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*�A�j���[�V�������I����*/
	if (sli->mAnimationTime >
		sli->mpModel->mAnimationSet[sli->mAnimationIndex]->mMaxTime) {
		mNextRegisterName = SLI_STATE_IDLING;//�A�C�h�����O�ɖ߂�
	}
	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}


/*���߂ɌĂяo��*/
void CStateSlimeDamage::Start(){
	
}



/*�X�V����*/
void CStateSlimeDamage::Update(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*�A�C�h�����O�̏���*/
	sli->ChangeAnimation(CTask::E_DAMAGE, true, ANIMA_SPEED);
	sli->BlowOff();//�������
}

CStateSlimeDamage::CStateSlimeDamage()
{

}

CStateSlimeDamage::~CStateSlimeDamage()
{
}