#ifndef STATE_PLAYER_RUN_ATTACK_H
#define STATE_PLAYER_RUN_ATTACK_H

#include "../../../../../../StateMachine/CStateBase.h"
/*�v���C���[�̌��݂̏��(�U��)�N���X*/
class CPlayerRunAttack : public CStateBase{
public:
	CPlayerRunAttack();
	~CPlayerRunAttack();
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