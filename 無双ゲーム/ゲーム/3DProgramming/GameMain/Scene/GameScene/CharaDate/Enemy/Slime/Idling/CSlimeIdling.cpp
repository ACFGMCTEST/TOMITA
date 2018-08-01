#include "CSlimeIdling.h"
#include "../CSlime.h"

/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED 60 * 4

//�ύX����֐�
void CSlimeIdling::ChangeState(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);

	/*�����t���O�����Ă�*/
	if ( sli->Search()){
		mNextRegisterName = F_SLI_RUN;//����
	}

	/*�_���[�W���󂯂Ă���Ȃ�*/
	if (sli->mFlagDamage || sli->HP() == 0) {
		mNextRegisterName = F_SLI_DAMAGE;//�_���[�W
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
	sli->ChangeAnimation(F_SLI_IDLING,F_SLI_KING_IDLING, true, ANIMA_SPEED);
}

CSlimeIdling::CSlimeIdling()
{

}

CSlimeIdling::~CSlimeIdling()
{
}