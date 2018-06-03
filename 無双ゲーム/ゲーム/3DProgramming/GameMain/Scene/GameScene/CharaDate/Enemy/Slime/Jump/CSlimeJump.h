#ifndef STATE_SLIME_JUMP_H
#define STATE_SLIME_JUMP_H

#include "../../../../../../../StateMachine/CStateBase.h"

/*�v���C���[�̌��݂̏��(�U��)�N���X*/
class CSlimeJump : public CStateBase
{
private:
	float mPrevPosY;//�O�̃|�W�V����
	bool mFlagFall;//�������Ƀt���O������
public:
	CSlimeJump();
	~CSlimeJump();
	/*���߂ɌĂяo��*/
	void Start();
	/*�X�V����*/
	void Update();
	//�J�ڎ��̏���
	// isNext��false�ɖ߂������͂����ōs���Ƃ悢
	void OnChangeEvent();
	//�ύX����֐�
	void ChangeState();
};

#endif