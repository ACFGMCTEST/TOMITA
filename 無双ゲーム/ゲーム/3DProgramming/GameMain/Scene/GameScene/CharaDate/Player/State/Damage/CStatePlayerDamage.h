#ifndef STATE_PLAYER_DAMAGE_H
#define STATE_PLAYER_DAMAGE_H

#include "../../../../../../../StateMachine/CStateBase.h"

/*�v���C���[�̌��݂̏��(�_���[�W)�N���X*/
class CStatePlayerDamage : public CStateBase
{
private:
public:
	CStatePlayerDamage();
	~CStatePlayerDamage();
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