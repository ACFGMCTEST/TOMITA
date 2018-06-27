#ifndef STATE_KING_SLIME_DAMAGE_H
#define STATE_KING_SLIME_DAMAGE_H

#include "../../Damage/CSlimeDamage.h"

/*Kスライムの現在の状態(ダメージ)クラス*/
class CKingSlimeDamage : public CSlimeDamage
{
public:
	CKingSlimeDamage();
	~CKingSlimeDamage();

	//変更する関数
	void ChangeState();
};


#endif