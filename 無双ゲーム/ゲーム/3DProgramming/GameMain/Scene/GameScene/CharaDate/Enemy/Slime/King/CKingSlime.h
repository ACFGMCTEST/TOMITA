#ifndef KING_SLIME_H
#define KING_SLIME_H

#include "../CSlime.h"
/*�X�e�[�^�X*/
#include "Attack\CKingSlimeAttack.h"
#include "Damage\CKingSlimeDamage.h"
#include "Idling\CKingSlimeIdling.h"
#include "Jump\CKingSlimeJump.h"
#include "Run\CKingSlimeRun.h"

/*�L���O�X���C���N���X*/
class CKingSlime : public CSlime
{
public:
	/*����������*/
	void Init(CModelX *model);

	CKingSlime();
	~CKingSlime();

	/*�X�V����*/
	void Update();
	/*�U���͈�*/
	bool AttackRange();

private:

};

#endif
