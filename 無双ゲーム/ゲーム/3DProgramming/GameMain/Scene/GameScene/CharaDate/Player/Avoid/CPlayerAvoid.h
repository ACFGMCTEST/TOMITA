#ifndef STATE_PLAYER_AVOID_H
#define STATE_PLAYER_AVOID_H

#include "../../../../../../StateMachine/CStateBase.h"
/*�v���C���[�̌��݂̏��(�U��)�N���X*/
class CPlayerAvoid : public CStateBase{
public:
	CPlayerAvoid();
	~CPlayerAvoid();
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