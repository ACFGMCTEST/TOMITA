#include "CSlimeDamage.h"
#include "../CSlime.h"

const float AnimaSpeed = 10;//�A�j���[�V�����̃X�s�[�h

//�ύX����֐�
void CSlimeDamage::ChangeState(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*�A�j���[�V�������I����*/
	if (sli->mAnimationTime > 
		sli->mpModel->mAnimationSet[sli->mAnimationIndex]->mMaxTime) {
		mNextRegisterName = SLI_STATE_IDLING;//�A�C�h�����O�ɖ߂�
		sli->mFlagDamage = false;
	}
	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}


/*���߂ɌĂяo��*/
void CSlimeDamage::Start(){
	
}



/*�X�V����*/
void CSlimeDamage::Update(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*�A�C�h�����O�̏���*/
	sli->ChangeAnimation(CSlime::E_DAMAGE, false, AnimaSpeed);
	sli->BlowOff();//�������

}

CSlimeDamage::CSlimeDamage()
{

}

CSlimeDamage::~CSlimeDamage()
{
}