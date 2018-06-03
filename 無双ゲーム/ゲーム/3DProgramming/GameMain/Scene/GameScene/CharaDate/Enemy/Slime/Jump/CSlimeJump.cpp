#include "CSlimeJump.h"
#include "../CSlime.h"

/*�W�����v�̃X�s�[�h*/
#define JUMP_SPEED 0.3f//�W�����v����X�s�[�h

//�ύX����֐�
void CSlimeJump::ChangeState(){
}
/*���߂ɌĂяo��*/
void CSlimeJump::Start()
{
}
/*�X�V����*/
void CSlimeJump::Update()
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
void CSlimeJump::OnChangeEvent()
{

}

CSlimeJump::CSlimeJump()
{
}

CSlimeJump::~CSlimeJump()
{
}