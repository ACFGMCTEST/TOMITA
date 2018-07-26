#include "CPlayerDied.h"
#include "../CPlayer.h"
#include "../../../Result/CResult.h"
/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED 60 

//�ύX����֐�
void CPlayerDied::ChangeState(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*�A�j���[�V�������I���ƃ��U���g��ʂ�\��*/
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime) {
		CResult::GetInstance()->Over();//�Q�[���I�[�o�[�t���O�𗧂Ă�
	}

	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}


/*���߂ɌĂяo��*/
void CPlayerDied::Start(){
	
}



/*�X�V����*/
void CPlayerDied::Update(){

	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	pl->ChangeAnimation(F_PL_DIED, false, ANIMA_SPEED);

	
}


CPlayerDied::CPlayerDied()
{

}

CPlayerDied::~CPlayerDied()
{
}