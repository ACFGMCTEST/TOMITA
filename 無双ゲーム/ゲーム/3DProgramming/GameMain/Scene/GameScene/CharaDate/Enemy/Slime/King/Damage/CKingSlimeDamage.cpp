#include "CKingSlimeDamage.h"
#include "../CKingSlime.h"
#include "../../../../../Result/CResult.h"
//ïœçXÇ∑ÇÈä÷êî
void CKingSlimeDamage::ChangeState() {
	CSlimeDamage::ChangeState();

	
	CKingSlime *sli = dynamic_cast<CKingSlime*>(mpParent);
	/*ëÃóÕÇ™Ç»Ç≠Ç»ÇÈÇ∆*/
	if (sli->HP() <= 0) {
		CResult::GetInstance()->Clear();
	}
}

CKingSlimeDamage::CKingSlimeDamage() {}
CKingSlimeDamage::~CKingSlimeDamage() {}