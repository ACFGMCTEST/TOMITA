#include "CSlimeDamage.h"
#include "../CSlime.h"
#include "../../../../../../Convenient/CConvenient.h"

const float AnimaSpeed = 100;//�A�j���[�V�����̃X�s�[�h
const float BlowOffTime = 0.1f;//������Ԏ���
//�ύX����֐�
void CSlimeDamage::ChangeState() {
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*���Ԃ�����HP��0�ɂȂ��*/
	if (CConvenient::Time(&mCount, BlowOffTime) && sli->HP() > 0) {
		mNextRegisterName = F_SLI_IDLING;//�A�C�h�����O�ɖ߂�
		sli->mFlagDamage = false;
	}
	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}


/*���߂ɌĂяo��*/
void CSlimeDamage::Start() {
	mCount = 0;
}



/*�X�V����*/
void CSlimeDamage::Update() {
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	if (sli->HP() <= 0) {
		sli->mFlagBlowDamage = false;
		sli->ChangeAnimation(
			F_SLI_DAMAGE,F_SLI_KING_DAMAGE, false, AnimaSpeed);//�A�j���[�V����
		/* �_���[�W���[�V�������I���� �f���[�g����*/
		if (sli->mAnimationTime >
			sli->mpModel->mAnimationSet[sli->mAnimationIndex]->mMaxTime) {
			sli->Delete();
		}
	}
	else {
		sli->mFlagBlowDamage = true;
		sli->BlowOff();
	}



}

CSlimeDamage::CSlimeDamage()
{

}

CSlimeDamage::~CSlimeDamage()
{
}