#include "CKingSlimeRun.h"
#include "../CKingSlime.h"

void CKingSlimeRun::ChangeState() {
	CKingSlime *sli = dynamic_cast<CKingSlime*>(mpParent);
	/*çUåÇÇÃÉtÉâÉOÇ™ÇΩÇ¬Ç∆*/
	if (sli->AttackRange()) {
		mNextRegisterName = F_SLI_ATTACK;//çUåÇ
	}
	CSlimeRun::ChangeState();
}
CKingSlimeRun::CKingSlimeRun() {}
CKingSlimeRun::~CKingSlimeRun() {}