//-------------------------------------------------
// ��ԊǗ��N���X
// 
// StateMachine : ��Ԃ̊Ǘ�����
// StateBase : ��Ԃ̊��N���X
// StateSwitch : ��Ԃ�؂�ւ���N���X
//--------------------------------------------------

// �k�상��
// �����������ł���͈͂ł�StateSwitch���s�v�Ɏv����̂ŏȂ��Ă݂܂����B
// StateMachine�N���X����StateBase�̔h���N���X�𒼐ڎQ�Ƃ���悤�ɂ��Ă��܂��B
// �܂��A�e�X�e�[�g����J�ڐ�����R�Ɍ��߂���悤�ɂ��Ă��܂��B
#ifndef STATE_BASE_H
#define STATE_BASE_H


/*�L���^�N�^�[�̏��*/
#define PL_STATE_ATTACK "playerAttack"
#define PL_STATE_IDLING "playerIdling"
#define PL_STATE_RUN "playerRun"
#define PL_STATE_JUMP "playerJump"
#define PL_STATE_RUN_ATTACK "playerRunAttack"
#define PL_STATE_DAMAGE "playerDamage"
#define PL_STATE_AVOID "playerAvoid"
/*�G�l�~�[�̏�ԑJ��*/
/*�X���C��*/
#define SLI_STATE_ATTACK	"slimeAttack"
#define SLI_STATE_IDLING	"slimeIdling"
#define SLI_STATE_RUN		"slimeRun"
#define SLI_STATE_JUMP		"slimeJump"
#define SLI_STATE_DAMAGE	"slimeDamage"
#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include "../GameMain/Task/CTask.h"

/*�X�e�[�^�X�̃x�[�X�N���X*/
class CStateBase
{
protected:

	// �J�ڂ��邩�ǂ���
	bool mFlagNext;
	// �J�ڐ�̓o�^��
	std::string mNextRegisterName;
	// �A�b�v�f�[�g�̏����̒��ŏ�ԑJ�ڂ̏����𖞂������ꍇ
	// isNext��true�ɂ��A
	// nextRegisterName�ɑJ�ڐ�̓o�^����������
	/*�����̐e cast���Ďg�� �A�N�Z�X�p*/
	CTask *mpParent;
	

public:

	/*�R���X�g���N�^*/
	CStateBase();
	/*�f�X�g���N�^*/
	~CStateBase();

	// �A�b�v�f�[�g�̑O��1�x�����R�[��
	virtual void Start() = 0;
	// �A�b�v�f�[�g
	virtual void Update() = 0;
	//��Ԑ؂�ւ��֐�
	virtual void ChangeState() = 0;


	// �J�ڎ��̏���
	// isNext��false�ɖ߂������͂����ōs���Ƃ悢
	void OnChangeEvent();

	// �J�ڂ��邩�ǂ����̎擾
	bool IsNext()const;

	// �J�ڐ�̓o�^���̎擾
	std::string NextRegisterName();

	/*�e�ݒ肷��*/
	void SetParent(CTask *p);
};

#endif

