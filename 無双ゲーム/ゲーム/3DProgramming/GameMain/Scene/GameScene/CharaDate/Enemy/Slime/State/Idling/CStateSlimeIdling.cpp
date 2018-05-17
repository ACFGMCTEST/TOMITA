#include "CStateSlimeIdling.h"
#include "../../CSlime.h"


//�ύX����֐�
void CStateSlimeIdling::ChangeState(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*�����t���O�����Ă�*/
	if (sli->Search()){
		mNextRegisterName = SLI_STATE_RUN;//����
	}
	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}


/*���߂ɌĂяo��*/
void CStateSlimeIdling::Start(){
	
}



/*�X�V����*/
void CStateSlimeIdling::Update(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*�A�C�h�����O�̏���*/
	sli->ChangeAnimation(CTask::E_IDLING, true, ANIMA_SPEED);

}

CStateSlimeIdling::CStateSlimeIdling()
{

}

CStateSlimeIdling::~CStateSlimeIdling()
{
}