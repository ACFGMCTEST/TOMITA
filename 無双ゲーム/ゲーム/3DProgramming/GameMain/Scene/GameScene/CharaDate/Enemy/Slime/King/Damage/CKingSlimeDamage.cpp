#include "CKingSlimeDamage.h"
#include "../CKingSlime.h"
#include "../../../../../Result/CResult.h"
//�ύX����֐�
void CKingSlimeDamage::ChangeState() {
	CSlimeDamage::ChangeState();

	
	CKingSlime *sli = dynamic_cast<CKingSlime*>(mpParent);
	/*�̗͂��Ȃ��Ȃ��*/
	if (sli->HP() <= 0) {
		CResult::GetInstance()->Clear();
	}
}

CKingSlimeDamage::CKingSlimeDamage() {}
CKingSlimeDamage::~CKingSlimeDamage() {}