#include "CPlayerJump.h"
#include "../CPlayer.h"
/*�W�����v�̃X�s�[�h*/
#define JUMP_SPEED 0.3f//�W�����v����X�s�[�h
/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED_JUMP 30

//�ύX����֐�
void CPlayerJump::ChangeState(){
	/*�A�C�h�����O����ꍇ*�@�n�ʂɂ����Ƃ�*/
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	if (!pl->mFlagJump){
		mNextRegisterName = PL_STATE_IDLING;//�A�C�h�����O����
	}
	/*�U������ꍇ*/
	if (CKey::once(KEY_ATTACK)){
		mNextRegisterName = PL_STATE_ATTACK;//�U��
	}
	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}
/*���߂ɌĂяo��*/
void CPlayerJump::Start()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	pl->mFlagJump = true;//�v���C���[���W�����v������
	mFlagFall = false;
}
/*�X�V����*/
void CPlayerJump::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*�A�j���[�V����*/
	pl->ChangeAnimation(CPlayer::E_JUMP, true, ANIMA_SPEED_JUMP);

	/*�W�����v*/
	pl->Move();//�ړ��֐�.��(x,z)�̈ړ�
	mPrevPosY = pl->mPosition.y;//���݂̃|�W�V�����L��
	float jumpVilocity = JUMP_SPEED - GRAVITY(pl->mGravitTime);//��������
	/*�W�����v��0���傫���ꍇ*/
	pl->mPosition.y += jumpVilocity;
	/*�������łȂ��ꍇ*/
	if (!mFlagFall){
		pl->mFlagJump = true;//�n�ʂ����ԂƂ��̔��蒲���p
		/*�������̏ꍇ*/
		float graSpeed = GRAVITY(pl->mGravitTime);
		if (JUMP_SPEED <= graSpeed*2){
			mFlagFall = true;
		}
	}
	pl->State(PL_STATE_JUMP);


}
//�J�ڎ��̏���
// isNext��false�ɖ߂������͂����ōs���Ƃ悢
void CPlayerJump::OnChangeEvent()
{

}

CPlayerJump::CPlayerJump()
{
}

CPlayerJump::~CPlayerJump()
{
}