#ifndef STATE_SLIME_RUN_H
#define STATE_SLIME_RUN_H

#include "../../../../../../../StateMachine/CStateBase.h"

/*�v���C���[�̌��݂̏��(����)�N���X*/
class CSlimeRun : public CStateBase
{
private:
	void Move();//
public:
	CSlimeRun();
	~CSlimeRun();
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