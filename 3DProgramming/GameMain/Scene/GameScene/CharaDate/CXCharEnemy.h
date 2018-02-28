/*
�S���� �y�c���l

�G�l�~�[�̃N���X
*/

#ifndef CXCHARENEMY
#define CXCHARENEMY

#include "CXCharPlayer.h"
#include "../Puck/CXPuck.h"

class CXCharEnemy : public CXCharPlayer{
private:
	float mRotPuckTime;//�p�b�N�̕����ɉ�]����^�C�~���O���Ԍv���p
	
public:
	CCollider *mpCBAttackBox; //�U���Ɉڍs����͈͐ݒ�
	CCollider *mpCBAttackInitBox; //�U���̏����Ɉڍs����͈͐ݒ�
	static int mEnemyCountMax;//���݂̍ő�l

	/*AI�̉�]���f�p*/
	enum E_AIROT_STATE{
		E_ROT_FAST_POS,
		E_ROT_PUCK,
		E_ROT_GOAL,
	};
	E_AIROT_STATE eAIRotState;
	/*E_AIROT_STATE�̃X�e�[�^�X�Ǘ�*/
	void AIRotStateUpdate();
	CXCharEnemy();

	void Init(CModelX *model);
	/*�����蔻�菉����*/
	void ColInit();

	void AIMove();/*AI�̓����֐�*/
	void Update();/*�X�V*/
	/*�U������ �����蔻�蕔���ŌĂ�*/
	void AttackInit();
	/*�U��*/
	void Attack(CCollider &col);
	/*�S�[���ɑł��������߂�֐�*/
	CVector3 GoalShot();
	/*�W�����v�t���O*/
	void ColEnabledJump();

};
#endif
