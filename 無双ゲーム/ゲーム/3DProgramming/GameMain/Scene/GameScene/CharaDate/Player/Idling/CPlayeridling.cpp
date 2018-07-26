#include "CPlayeridling.h"
#include "../CPlayer.h"

/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED 60 * 2

//�ύX����֐�
void CPlayerIdling::ChangeState(){
	/*�����L�[���͂����ꍇ�@����*/
	if (CKey::push('A') || CKey::push('D') || CKey::push('S') || CKey::push('W')){
		mNextRegisterName = F_PL_RUN;//�����ԂɈڍs
	}
	/*�������ꍇ*/
	else if (CKey::push(KEY_AVOID)) {
		mNextRegisterName = F_PL_AVOID;//����Ɉڍs
	}
	/*�W�����v����ꍇ*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = F_PL_JUMP;//�W�����v
	}
	/*�U������ꍇ*/
	if (CKey::once(KEY_ATTACK)){
		mNextRegisterName = F_PL_ATTACK;//�U��
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
	pl->ChangeAnimation(F_PL_IDLING, true, ANIMA_SPEED);

}

CPlayerIdling::CPlayerIdling()
{

}

CPlayerIdling::~CPlayerIdling()
{
}