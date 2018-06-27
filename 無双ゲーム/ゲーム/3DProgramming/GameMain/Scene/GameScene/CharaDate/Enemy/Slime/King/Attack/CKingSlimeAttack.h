#ifndef STATE_KING_SLIME_ATTACK_H
#define STATE_KING_SLIME_ATTACK_H
#include "../../Attack/CSlimeAttack.h"

/*プレイヤーの現在の状態(攻撃)クラス*/
class CKingSlimeAttack : public CSlimeAttack{
public:
	CKingSlimeAttack();
	~CKingSlimeAttack();
	void AttackSpeed();//アニメーションのスピード管理
};

#endif