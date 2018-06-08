#include "CPlayerRun.h"
#include "../CPlayer.h"
/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED_RUN 100 

//�ύX����֐�
void CPlayerRun::ChangeState(){
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
void CPlayerRun::Start(){}
/*�X�V����*/
void CPlayerRun::Update(){
	CPlayer *pl;
	pl = dynamic_cast<CPlayer*>(mpParent);
	pl->ChangeAnimation(CPlayer::E_RUN, true, ANIMA_SPEED_RUN);
	SPEED_RUN_ACC(pl->mVelocity);//�v���C���[�ړ����x�v�Z
	pl->PlayerMoveRot();//�v���C���[���������߂�
	pl->State(PL_STATE_RUN);
}

CPlayerRun::CPlayerRun()
{
}

CPlayerRun::~CPlayerRun()
{
}