#ifndef STATE_SLIME_DAMAGE_H
#define STATE_SLIME_DAMAGE_H

#include "../../../../../../../StateMachine/CStateBase.h"

/*�v���C���[�̌��݂̏��(�_���[�W)�N���X*/
class CSlimeDamage : public CStateBase
{
private:
	float mCount;//�J�E���g
public:
	CSlimeDamage();
	~CSlimeDamage();
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