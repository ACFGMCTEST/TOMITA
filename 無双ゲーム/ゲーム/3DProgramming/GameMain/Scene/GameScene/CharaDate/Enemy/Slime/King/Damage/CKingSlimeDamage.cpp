#include "CKingSlimeDamage.h"
#include "../CKingSlime.h"
#include "../../../../../Result/CResult.h"
//変更する関数
void CKingSlimeDamage::ChangeState() {
	CSlimeDamage::ChangeState();

	
	CKingSlime *sli = dynamic_cast<CKingSlime*>(mpParent);
	/*体力がなくなると*/
	if (sli->HP() <= 0) {
		CResult::GetInstance()->Clear();
	}
}

CKingSlimeDamage::CKingSlimeDamage() {}
CKingSlimeDamage::~CKingSlimeDamage() {}