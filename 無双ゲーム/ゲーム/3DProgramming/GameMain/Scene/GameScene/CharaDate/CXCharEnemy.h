#ifndef CXCHARENEMY
#define CXCHARENEMY

#include "CXCharPlayer.h"

/*�G�l�~�[�̃N���X*/
class CXCharEnemy : public CXCharPlayer{

	
public:
	CCollider *mpCBAttackBox; //�U���Ɉڍs����͈͐ݒ�
	CCollider *mpCBAttackInitBox; //�U���̏����Ɉڍs����͈͐ݒ�

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

	/*�W�����v�t���O*/
	void ColEnabledJump();

};
#endif
