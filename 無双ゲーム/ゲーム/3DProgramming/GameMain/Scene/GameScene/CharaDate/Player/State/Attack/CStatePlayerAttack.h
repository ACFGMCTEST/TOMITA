#ifndef STATE_PLAYER_ATTACK_H
#define STATE_PLAYER_ATTACK_H
#include "../../../../../../../StateMachine/CStateBase.h"
/*�v���C���[�̌��݂̏��(�U��)�N���X*/
class CStatePlayerAttack : public CStateBase{
public:
	CStatePlayerAttack();
	~CStatePlayerAttack();
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