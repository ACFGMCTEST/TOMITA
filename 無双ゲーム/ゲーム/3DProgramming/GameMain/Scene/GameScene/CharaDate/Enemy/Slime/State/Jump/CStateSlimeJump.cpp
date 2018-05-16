#include "CStateSlimeJump.h"
#include "../../CSlime.h"

/*�W�����v�̃X�s�[�h*/
#define JUMP_SPEED 0.3f//�W�����v����X�s�[�h

//�ύX����֐�
void CStateSlimeJump::ChangeState(){
}
/*���߂ɌĂяo��*/
void CStateSlimeJump::Start()
{
}
/*�X�V����*/
void CStateSlimeJump::Update()
{
	CSlime *sl = dynamic_cast<CSlime*>(mpParent);
	/*�A�j���[�V����*/
	sl->ChangeAnimation(CTask::E_JUMP, true, ANIMA_SPEED_JUMP);

	/*�W�����v*/
	sl->Move();//�ړ��֐�.��(x,z)�̈ړ�

	mPrevPosY = sl->mPosition.y;//���݂̃|�W�V�����L��
	float jumpVilocity = JUMP_SPEED - GRAVITY(sl->mGravitTime);//��������
	/*�W�����v��0���傫���ꍇ*/
	sl->mPosition.y += jumpVilocity;

	/*�������łȂ��ꍇ*/
	if (!mFlagFall){
		sl->mFlagJump = true;//�n�ʂ����ԂƂ��̔��蒲���p
		/*�������̏ꍇ*/
		float graSpeed = GRAVITY(sl->mGravitTime);
		if (JUMP_SPEED <= graSpeed*2){
			mFlagFall = true;
		}
	}
	


}
//�J�ڎ��̏���
// isNext��false�ɖ߂������͂����ōs���Ƃ悢
void CStateSlimeJump::OnChangeEvent()
{

}

CStateSlimeJump::CStateSlimeJump()
{
}

CStateSlimeJump::~CStateSlimeJump()
{
}