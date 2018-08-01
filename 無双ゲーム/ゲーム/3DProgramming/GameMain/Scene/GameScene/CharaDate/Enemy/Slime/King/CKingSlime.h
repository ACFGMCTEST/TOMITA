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
	/*�`�揈��*/
	void Render();
	/*�U���͈�*/
	bool AttackRange();

	void CKingSlime::FallDamage(float height);
	/*�J�v�Z���������蔻��*/
	void CKingSlime::CapsuleCol(CColCapsule *cc, CColBase* y);
	//m �����@y ����
	bool CKingSlime::Collision(CColBase* m, CColBase* y);
private:

};

#endif
