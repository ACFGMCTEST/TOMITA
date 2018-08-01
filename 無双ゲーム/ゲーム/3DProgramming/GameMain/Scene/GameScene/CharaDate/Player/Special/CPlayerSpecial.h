#ifndef STATE_PLAYER_SPECIAL_H
#define STATE_PLAYER_SPECIAL_H
#include "../../../Effect/CEffect2D.h"
#include "../../../Effect/CEffect3D.h"

#include "../../../../../../StateMachine/CStateBase.h"

/*�v���C���[�̌��݂̏��(�U��)�N���X*/
class CPlayerSpecial : public CStateBase{
private:
	CEffect2D *mpEffect;//�G�t�F�N�g
	CEffect3D *mpEffect3D;//�Rd�̃G�t�F�N�g
public:
	CPlayerSpecial();
	~CPlayerSpecial();
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