#ifndef STATE_PLAYER_DAMAGE_H
#define STATE_PLAYER_DAMAGE_H

#include "../../../../../../StateMachine/CStateBase.h"


/*�v���C���[�̌��݂̏��(�_���[�W)�N���X*/
class CPlayerDamage : public CStateBase
{
private:
public:
	CPlayerDamage();
	~CPlayerDamage();
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