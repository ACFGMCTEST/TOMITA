#ifndef STATE_PLAYER_DIED_H
#define STATE_PLAYER_DIED_H

#include "../../../../../../StateMachine/CStateBase.h"


/*�v���C���[�̌��݂̏��(���S)�N���X*/
class CPlayerDied : public CStateBase
{
private:
public:
	CPlayerDied();
	~CPlayerDied();
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