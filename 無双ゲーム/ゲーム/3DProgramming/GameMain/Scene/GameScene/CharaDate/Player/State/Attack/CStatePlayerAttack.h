#ifndef STATE_PLAYER_ATTACK_H
#define STATE_PLAYER_ATTACK_H
#include "../CStatePlayerBase.h"

/*�v���C���[�̌��݂̏��(�U��)�N���X*/
class CStatePlayerAttack : public CStatePlayerBase
{
public:



	CStatePlayerAttack();
	~CStatePlayerAttack();
	/*���߂ɌĂяo��*/
	void Start();
	/*�X�V����*/
	void Update();
	//�J�ڎ��̏���
	// isNext��false�ɖ߂������͂����ōs���Ƃ悢
	void OnChangeEvent();

};

#endif