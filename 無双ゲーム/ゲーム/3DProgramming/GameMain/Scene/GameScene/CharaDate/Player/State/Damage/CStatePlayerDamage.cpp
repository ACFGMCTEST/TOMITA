#include "CStatePlayerDamage.h"
#include "../../CXCharPlayer.h"


//�ύX����֐�
void CStatePlayerDamage::ChangeState(){
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}


/*���߂ɌĂяo��*/
void CStatePlayerDamage::Start(){
	
}



/*�X�V����*/
void CStatePlayerDamage::Update(){
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	/*�A�C�h�����O�̏���*/
	pl->ChangeAnimation(CTask::E_DAMAGE, true, ANIMA_SPEED);

}

CStatePlayerDamage::CStatePlayerDamage()
{

}

CStatePlayerDamage::~CStatePlayerDamage()
{
}