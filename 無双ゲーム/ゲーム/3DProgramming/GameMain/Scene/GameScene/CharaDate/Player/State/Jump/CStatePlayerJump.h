#ifndef STATE_PLAYER_JUMP_H
#define STATE_PLAYER_JUMP_H
#include "../CStatePlayerBase.h"

/*�v���C���[�̌��݂̏��(�U��)�N���X*/
class CStatePlayerJump : public CStatePlayerBase
{
public:
	CStatePlayerJump();
	~CStatePlayerJump();
	/*���߂ɌĂяo��*/
	void Start();
	/*�X�V����*/
	void Update();
	//�J�ڎ��̏���
	// isNext��false�ɖ߂������͂����ōs���Ƃ悢
	void OnChangeEvent();
};

#endif