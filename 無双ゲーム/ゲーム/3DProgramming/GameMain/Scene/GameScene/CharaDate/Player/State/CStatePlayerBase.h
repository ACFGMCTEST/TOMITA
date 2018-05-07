#ifndef STATE_PLAYER_BASE_H
#define STATE_PLAYER_BASE_H

#include "../../../../../../StateMachine/CStateBase.h"

/*�v���C���[�X�e�[�^�X�̃x�[�X�N���X*/
class CStatePlayerBase : public CStateBase
{
public:
	/*�L�����N�^�[�̃X�e�[�^�X*/
	const std::string mStateAttack = "PlayerAttack";//�U��
	const std::string mStateIdling = "PlayerIdling";//�A�C�h��
	const std::string mStateRun    = "PlayerRun";	//����
	const std::string mStateJump   = "PlayerJump";	//�W�����v

};


#endif