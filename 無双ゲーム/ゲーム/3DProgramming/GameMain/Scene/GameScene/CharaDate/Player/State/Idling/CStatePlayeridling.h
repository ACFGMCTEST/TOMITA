#ifndef STATE_PLAYER_IDLING_H
#define STATE_PLAYER_IDLING_H
#include "../CStatePlayerBase.h"
/*�v���C���[�̌��݂̏��(�ҋ@)�N���X*/
class CStatePlayerIdling : public CStatePlayerBase
{
public:



	CStatePlayerIdling();
	~CStatePlayerIdling();
	/*���߂ɌĂяo��*/
	void Start();
	/*�X�V����*/
	void Update();
	//�J�ڎ��̏���
	// isNext��false�ɖ߂������͂����ōs���Ƃ悢
	void OnChangeEvent();

};


#endif