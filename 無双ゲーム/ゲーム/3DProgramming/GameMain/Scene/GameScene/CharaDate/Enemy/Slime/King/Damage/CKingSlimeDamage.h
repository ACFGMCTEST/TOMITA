#ifndef STATE_KING_SLIME_DAMAGE_H
#define STATE_KING_SLIME_DAMAGE_H

#include "../../Damage/CSlimeDamage.h"

/*K�X���C���̌��݂̏��(�_���[�W)�N���X*/
class CKingSlimeDamage : public CSlimeDamage
{
public:
	CKingSlimeDamage();
	~CKingSlimeDamage();

	//�ύX����֐�
	void ChangeState();
};


#endif