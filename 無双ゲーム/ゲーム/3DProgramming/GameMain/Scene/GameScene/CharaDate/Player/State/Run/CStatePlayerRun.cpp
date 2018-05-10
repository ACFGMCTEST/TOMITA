#include "CStatePlayerRun.h"
#include "../../CXCharPlayer.h"

//�ύX����֐�
void CStatePlayerRun::ChangeState(){
	/*�A�C�h�����O����ꍇ*/
	if (CKey::push('W') || CKey::push('A') || CKey::push('S') || CKey::push('D')){}
	else{
		mNextRegisterName = PL_STATE_IDLING;
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
void CStatePlayerRun::Start(){}
/*�X�V����*/
void CStatePlayerRun::Update(){
	CXCharPlayer *pl;
	pl = dynamic_cast<CXCharPlayer*>(mpParent);
	pl->ChangeAnimation(CTask::E_RUN, true, ANIMA_SPEED_RUN);
	SPEED_RUN_ACC(pl->mVelocity);//�v���C���[�ړ����x�v�Z
	pl->PlayerMoveRot();//�v���C���[���������߂�
}

CStatePlayerRun::CStatePlayerRun()
{
}

CStatePlayerRun::~CStatePlayerRun()
{
}