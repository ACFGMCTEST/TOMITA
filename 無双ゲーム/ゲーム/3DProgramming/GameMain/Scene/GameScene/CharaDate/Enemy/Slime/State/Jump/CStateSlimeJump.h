#ifndef STATE_PLAYER_JUMP_H
#define STATE_PLAYER_JUMP_H
#include "../../../../../../../../StateMachine/CStateBase.h"

/*�v���C���[�̌��݂̏��(�U��)�N���X*/
class CStateSlimeJump : public CStateBase
{
private:
	float mPrevPosY;//�O�̃|�W�V����
	bool mFlagFall;//�������Ƀt���O������
public:
	CStateSlimeJump();
	~CStateSlimeJump();
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