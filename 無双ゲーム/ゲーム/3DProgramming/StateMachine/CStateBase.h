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


#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

#ifndef STATE_BASE_H
#define STATE_BASE_H

/*�X�e�[�^�X�̃x�[�X�N���X*/
class CStateBase
{
public:

	/*�R���X�g���N�^*/
	CStateBase();

	// �A�b�v�f�[�g�̑O��1�x�����R�[��
	virtual void Start() = 0;

	// �A�b�v�f�[�g
	virtual void Update() = 0;

	// �J�ڎ��̏���
	// isNext��false�ɖ߂������͂����ōs���Ƃ悢
	virtual void OnChangeEvent() = 0;

	// �J�ڂ��邩�ǂ����̎擾
	bool IsNext()const;

	// �J�ڐ�̓o�^���̎擾
	std::string NextRegisterName();
protected:
	// �J�ڂ��邩�ǂ���
	bool mFlagNext;
	// �J�ڐ�̓o�^��
	std::string mNextRegisterName;
	// �A�b�v�f�[�g�̏����̒��ŏ�ԑJ�ڂ̏����𖞂������ꍇ
	// isNext��true�ɂ��A
	// nextRegisterName�ɑJ�ڐ�̓o�^����������
};

#endif

