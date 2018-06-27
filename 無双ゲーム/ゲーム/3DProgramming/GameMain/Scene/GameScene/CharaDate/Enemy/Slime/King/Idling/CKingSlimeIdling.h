#ifndef STATE_KING_SLIME_IDLING_H
#define STATE_KING_SLIME_IDLING_H

#include "../../Idling/CSlimeIdling.h"

/*Kスライムの現在の状態(待機)クラス*/
class CKingSlimeIdling : public CSlimeIdling
{
public:
	CKingSlimeIdling();
	~CKingSlimeIdling();
};


#endif