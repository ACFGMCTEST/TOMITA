#ifndef STATE_SLIME_ATTACK_H
#define STATE_SLIME_ATTACK_H
#include "../../../../../../../StateMachine/CStateBase.h"
/*�v���C���[�̌��݂̏��(�U��)�N���X*/
class CSlimeAttack : public CStateBase{
private:
	float mAnimaSpeed;//�A�j���[�V�����X�s�[�h
	float mTimeCount;//���Ԍv���p
	/*�U���̈ړ���������*/
	void AttackSpeed();
public:
	CSlimeAttack();
	~CSlimeAttack();
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