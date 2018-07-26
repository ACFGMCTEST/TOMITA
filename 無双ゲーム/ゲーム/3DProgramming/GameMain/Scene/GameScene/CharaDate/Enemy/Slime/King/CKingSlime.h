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
	/*描画処理*/
	void Render();
	/*攻撃範囲*/
	bool AttackRange();

	void CKingSlime::FallDamage(float height);
	/*カプセル内当たり判定*/
	void CKingSlime::CapsuleCol(CColCapsule *cc, CColBase* y);
	//m 自分　y 相手
	bool CKingSlime::Collision(CColBase* m, CColBase* y);
private:

};

#endif
