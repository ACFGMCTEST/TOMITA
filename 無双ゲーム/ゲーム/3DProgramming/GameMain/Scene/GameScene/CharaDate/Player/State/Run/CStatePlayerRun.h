#ifndef STATE_PLAYER_RUN_H
#define STATE_PLAYER_RUN_H
#include "../CStatePlayerBase.h"
/*�v���C���[�̌��݂̏��(�ҋ@)�N���X*/
class CStatePlayerRun : public CStatePlayerBase
{
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

};

#endif