#ifndef KING_SLIME_H
#define KING_SLIME_H

#include "../CSlime.h"
/*ステータス*/
#include "Attack\CKingSlimeAttack.h"
#include "Damage\CKingSlimeDamage.h"
#include "Idling\CKingSlimeIdling.h"
#include "Jump\CKingSlimeJump.h"
#include "Run\CKingSlimeRun.h"

/*キングスライムクラス*/
class CKingSlime : public CSlime
{
public:
	/*初期化処理*/
	void Init(CModelX *model);

	CKingSlime();
	~CKingSlime();

	/*更新処理*/
	void Update();
	/*攻撃範囲*/
	bool AttackRange();

private:

};

#endif
