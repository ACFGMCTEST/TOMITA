#ifndef STATE_PLAYER_IDLING_H
#define STATE_PLAYER_IDLING_H

#include "../../../../../../../StateMachine/CStateBase.h"
/*�v���C���[�̌��݂̏��(�ҋ@)�N���X*/
class CStatePlayerIdling : public CStateBase
{
public:
	CStatePlayerIdling();
	~CStatePlayerIdling();
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