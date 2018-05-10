#include "CStatePlayeridling.h"
#include "../../CXCharPlayer.h"


//�ύX����֐�
void CStatePlayerIdling::ChangeState(){
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
void CStatePlayerIdling::Start(){
	CXCharPlayer *pl;
	pl = dynamic_cast<CXCharPlayer*>(mpParent);
	pl->mVelocity = 0;//�����Ȃ��ɂ���
}
/*�X�V����*/
void CStatePlayerIdling::Update(){
	CXCharPlayer *pl;
	pl = dynamic_cast<CXCharPlayer*>(mpParent);
	/*�A�C�h�����O�̏���*/
	pl->ChangeAnimation(CTask::E_IDLING, true, ANIMA_SPEED);

}

CStatePlayerIdling::CStatePlayerIdling()
{

}

CStatePlayerIdling::~CStatePlayerIdling()
{
}