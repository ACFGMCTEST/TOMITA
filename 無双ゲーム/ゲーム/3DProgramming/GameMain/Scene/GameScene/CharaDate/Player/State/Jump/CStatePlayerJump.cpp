#include "CStatePlayerJump.h"
#include "../../CXCharPlayer.h"
/*�W�����v�̃X�s�[�h*/
#define JUMP_SPEED 0.3f//�W�����v����X�s�[�h

//�ύX����֐�
void CStatePlayerJump::ChangeState(){
	/*�A�C�h�����O����ꍇ*�@�n�ʂɂ����Ƃ�*/
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
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
void CStatePlayerJump::Start()
{
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	pl->mFlagJump = true;//�v���C���[���W�����v������
	mFlagFall = false;
}
/*�X�V����*/
void CStatePlayerJump::Update()
{
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	/*�A�j���[�V����*/
	pl->ChangeAnimation(CTask::E_JUMP, true, ANIMA_SPEED_JUMP);

	/*�W�����v*/
	pl->Move();//�ړ��֐�.��(x,z)�̈ړ�

	mPrevPosY = pl->mPosition.y;//���݂̃|�W�V�����L��
	float jumpVilocity = JUMP_SPEED - GRAVITY(pl->mGravitTime);//��������
	printf("%f\n", jumpVilocity);
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
	


}
//�J�ڎ��̏���
// isNext��false�ɖ߂������͂����ōs���Ƃ悢
void CStatePlayerJump::OnChangeEvent()
{

}

CStatePlayerJump::CStatePlayerJump()
{
}

CStatePlayerJump::~CStatePlayerJump()
{
}