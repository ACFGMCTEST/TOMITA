#include "CSlimeIdling.h"
#include "../CSlime.h"

/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED 60 * 4

//�ύX����֐�
void CSlimeIdling::ChangeState(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);

	/*�����t���O�����Ă�*/
	if ( sli->Search()){
		mNextRegisterName = SLI_STATE_RUN;//����
	}

	/*�_���[�W���󂯂Ă���Ȃ�*/
	if (sli->mFlagDamage) {
		mNextRegisterName = SLI_STATE_DAMAGE;//�_���[�W
	}
	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}


/*���߂ɌĂяo��*/
void CSlimeIdling::Start(){
	
}



/*�X�V����*/
void CSlimeIdling::Update(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*�A�C�h�����O�̏���*/
	sli->ChangeAnimation(CSlime::E_IDLING, true, ANIMA_SPEED);
	sli->State(SLI_STATE_IDLING);

}

CSlimeIdling::CSlimeIdling()
{

}

CSlimeIdling::~CSlimeIdling()
{
}