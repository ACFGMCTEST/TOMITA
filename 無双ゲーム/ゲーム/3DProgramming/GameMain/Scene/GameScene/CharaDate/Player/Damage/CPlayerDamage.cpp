#include "CPlayerDamage.h"
#include "../CPlayer.h"


//�ύX����֐�
void CPlayerDamage::ChangeState(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}


/*���߂ɌĂяo��*/
void CPlayerDamage::Start(){
	
}



/*�X�V����*/
void CPlayerDamage::Update(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*�A�C�h�����O�̏���*/
	pl->ChangeAnimation(CTask::E_DAMAGE, true, ANIMA_SPEED);

}

CPlayerDamage::CPlayerDamage()
{

}

CPlayerDamage::~CPlayerDamage()
{
}