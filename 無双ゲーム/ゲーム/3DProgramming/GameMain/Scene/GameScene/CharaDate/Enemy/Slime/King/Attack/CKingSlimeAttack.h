#ifndef STATE_KING_SLIME_ATTACK_H
#define STATE_KING_SLIME_ATTACK_H
#include "../../Attack/CSlimeAttack.h"

/*�v���C���[�̌��݂̏��(�U��)�N���X*/
class CKingSlimeAttack : public CSlimeAttack{
public:
	CKingSlimeAttack();
	~CKingSlimeAttack();
	void AttackSpeed();//�A�j���[�V�����̃X�s�[�h�Ǘ�
};

#endif