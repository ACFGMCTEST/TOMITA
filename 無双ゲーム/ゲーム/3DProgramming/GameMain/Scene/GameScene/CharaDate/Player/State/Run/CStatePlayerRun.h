#ifndef STATE_PLAYER_RUN_H
#define STATE_PLAYER_RUN_H

#include "../../../../../../../StateMachine/CStateBase.h"

/*�v���C���[�̌��݂̏��(����)�N���X*/
class CStatePlayerRun : public CStateBase
{
private:
	void Move();//
public:
	CStatePlayerRun();
	~CStatePlayerRun();
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