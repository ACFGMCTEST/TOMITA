#ifndef STATE_KING_SLIME_RUN_H
#define STATE_KING_SLIME_RUN_H
#include "../../Run/CSlimeRun.h"

/*プレイヤーの現在の状態(走る)クラス*/
class CKingSlimeRun : public CSlimeRun
{
public:
	CKingSlimeRun();
	~CKingSlimeRun();
	/*ステータス変更関数*/
	void ChangeState();
};

#endif