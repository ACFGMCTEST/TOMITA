#include "CKingSlimeRun.h"
#include "../CKingSlime.h"

void CKingSlimeRun::ChangeState() {
	CKingSlime *sli = dynamic_cast<CKingSlime*>(mpParent);
	/*�U���̃t���O������*/
	if (sli->AttackRange()) {
		mNextRegisterName = F_SLI_ATTACK;//�U��
	}
	CSlimeRun::ChangeState();
}
CKingSlimeRun::CKingSlimeRun() {}
CKingSlimeRun::~CKingSlimeRun() {}