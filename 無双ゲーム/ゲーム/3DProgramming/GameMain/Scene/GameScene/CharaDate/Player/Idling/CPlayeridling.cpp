#include "CPlayeridling.h"
#include "../CPlayer.h"


//�ύX����֐�
void CPlayerIdling::ChangeState(){
	/*�����L�[���͂����ꍇ�@����*/
	if (CKey::push('A') || CKey::push('D') || CKey::push('S') || CKey::push('W')){
		mNextRegisterName = PL_STATE_RUN;//�����ԂɈڍs
	}
	/*�W�����v����ꍇ*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = PL_STATE_JUMP;//�W�����v
	}
	/*�U������ꍇ*/
	if (CKey::once(KEY_ATTACK)){
		mNextRegisterName = PL_STATE_ATTACK;//�U��
	}
	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}

/*���߂ɌĂяo��*/
void CPlayerIdling::Start(){
	CPlayer *pl;
	pl = dynamic_cast<CPlayer*>(mpParent);
	pl->mVelocity = 0;//�����Ȃ��ɂ���
}
/*�X�V����*/
void CPlayerIdling::Update(){
	CPlayer *pl;
	pl = dynamic_cast<CPlayer*>(mpParent);
	/*�A�C�h�����O�̏���*/
	pl->ChangeAnimation(CPlayer::E_IDLING, true, ANIMA_SPEED);
	pl->State(PL_STATE_IDLING);//�X�e�[�^�X������
}

CPlayerIdling::CPlayerIdling()
{

}

CPlayerIdling::~CPlayerIdling()
{
}