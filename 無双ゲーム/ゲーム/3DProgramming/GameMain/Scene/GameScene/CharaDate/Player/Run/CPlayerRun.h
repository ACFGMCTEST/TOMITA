#ifndef STATE_PLAYER_RUN_H
#define STATE_PLAYER_RUN_H

#include  "../../../../../../StateMachine/CStateBase.h"

/*�v���C���[�̌��݂̏��(����)�N���X*/
class CPlayerRun : public CStateBase
{
private:
public:
	CPlayerRun();
	~CPlayerRun();
	/*���߂ɌĂяo��*/
	void Start();
	/*�X�V����*/
	void Update();
	//�J�ڎ��̏���
	// isNext��false�ɖ߂������͂����ōs���Ƃ悢
	void OnChangeEvent();
	//�ύX����֐�
	void ChangeState();

};

#endif