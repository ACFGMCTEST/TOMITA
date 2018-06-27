#include "CPlayerRun.h"
#include "../CPlayer.h"
/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED_RUN 60

//�ύX����֐�
void CPlayerRun::ChangeState(){
	/*�A�C�h�����O����ꍇ*/
	if ( !(CKey::push('W') || CKey::push('A') || CKey::push('S') || CKey::push('D') ) ){
		mNextRegisterName = F_PL_IDLING;
	}/*�������ꍇ*/
	else if (CKey::push(KEY_AVOID)) {
		mNextRegisterName = F_PL_AVOID;//����Ɉڍs
	}/*�W�����v����ꍇ*/
	else if (CKey::once(KEY_JUMP)){
		mNextRegisterName = F_PL_JUMP;//�W�����v
	}
	/*�U������ꍇ*/
	else if (CKey::once(KEY_ATTACK)){
		mNextRegisterName = F_PL_ATTACK;//�U��
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
	pl->ChangeAnimation(F_PL_RUN, true, ANIMA_SPEED_RUN);
	SPEED_RUN_ACC(pl->mVelocity);//�v���C���[�ړ����x�v�Z
	pl->PlayerMoveRot();//�v���C���[���������߂�
	pl->State(F_PL_RUN);
}

CPlayerRun::CPlayerRun()
{
}

CPlayerRun::~CPlayerRun()
{
}