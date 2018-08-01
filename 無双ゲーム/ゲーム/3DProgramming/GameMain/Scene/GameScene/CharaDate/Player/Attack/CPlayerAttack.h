#ifndef STATE_PLAYER_ATTACK_H
#define STATE_PLAYER_ATTACK_H

#include "../../../../../../StateMachine/CStateBase.h"

/*�v���C���[�̌��݂̏��(�U��)�N���X*/
class CPlayerAttack : public CStateBase{
private:
	float mAnimaSpeed;//�A�j���[�V�����X�s�[�h
	float mTimeKey;//�L�[���͑҂�
	bool mFlagChangeAnima;//�A�j���[�V�����̓����̔��f
	/*�U���̈ړ���������*/
	void AttackSpeed();
	/*�U�����[�V�����t���[��*/
	enum EAttackFrame {
		Attack1sta = 0,//�U���ꔭ�ڂ̂͂���
		Attack1end = 20,//�U���ꔭ�ڏI��
		Attack2sta = 50,//�U���Q���ڎn�܂�
		Attack2end = 80,//�U���Q���ڏI���
	};
	EAttackFrame eAttackFrame;
public:
	CPlayerAttack();
	~CPlayerAttack();
	
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