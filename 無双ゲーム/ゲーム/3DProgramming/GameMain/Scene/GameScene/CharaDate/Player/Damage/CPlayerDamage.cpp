#include "CPlayerDamage.h"
#include "../CPlayer.h"

/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED 30 

//�ύX����֐�
void CPlayerDamage::ChangeState(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*�A�C�h�����O����*/
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime) {
		mNextRegisterName = F_PL_IDLING;
	}
	/*hp���Ȃ��Ȃ��*/
	if (pl->HP() <= 0) {
		mNextRegisterName = F_PL_DIED;
	}

	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}


/*���߂ɌĂяo��*/
void CPlayerDamage::Start(){
	
}



/*�X�V����*/
void CPlayerDamage::Update(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	pl->ChangeAnimation(F_PL_DAMAGE, false, ANIMA_SPEED);

	/*���[�V�������łȂ��Ƃ��̓m�b�N�o�b�N*/
	if (pl->mAnimationTime <=
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime) {
		pl->BlowOff();
	}
}


CPlayerDamage::CPlayerDamage()
{

}

CPlayerDamage::~CPlayerDamage()
{
}