#ifndef STATE_KING_SLIME_RUN_H
#define STATE_KING_SLIME_RUN_H
#include "../../Run/CSlimeRun.h"

/*�v���C���[�̌��݂̏��(����)�N���X*/
class CKingSlimeRun : public CSlimeRun
{
public:
	CKingSlimeRun();
	~CKingSlimeRun();
	/*�X�e�[�^�X�ύX�֐�*/
	void ChangeState();
};

#endif