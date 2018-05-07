#include "CStateMachine.h"

/*�X�V*/
void CStateMachine::Update()
{
	nowState->Update();
	if (nowState->IsNext())
	{
		// �J�ڎ��̏��������s
		nowState->OnChangeEvent();

		// �J�ڐ�̎擾
		auto it = stateMap.find(nowState->NextRegisterName());
		// ������Ȃ������ꍇ�A�������I��
		if (it == stateMap.end()) return;

		// stateMap�́u�L�[�v��������A�u�l�v��StateBase�̃|�C���^�̘A�z�z��imap)
		// find�֐��͈����Ŏw�肵���L�[�����݂��邩���m�F�ł���B
		// ���݂���ꍇ�́A���̃C�e���[�^��Ԃ��A
		// ���݂��Ȃ��ꍇ��end()�Ƃ����l�̃C�e���[�^��Ԃ��B

		// map�̃C�e���[�^��
		// ->first �Łu�L�[�v��
		// ->second �Łu�l�v���擾�ł���

		// map�ŕێ����Ă��鎟�̃X�e�[�g�̃|�C���^��nowState�ɂ���
		nowState = it->second;
		nowState->Start();
	}
}

// �o�^����
void CStateMachine::Register(const std::string& name, const std::shared_ptr<CStateBase> state)
{
	stateMap.insert(std::make_pair(name, state));
	std::cout << "StateMachine : " << name << "��o�^" << std::endl;
}

// �ŏ�����n�߂��Ԃ�ݒ�
void CStateMachine::SetStartState(const std::string& registerName)
{
	auto it = stateMap.find(registerName);
	if (it == stateMap.end()) return;

	std::cout << "StateMachine : " << it->first << "���X�^�[�g��Ԃɐݒ�" << std::endl;

	nowState = it->second;
	nowState->Start();

}

// �o�^�������̂��폜����
void CStateMachine::Deregistration(const std::string& registerName)
{
	auto it = stateMap.find(registerName);
	if (it == stateMap.end()) return;

	std::cout << "StateMachine : " << it->first << "��o�^���폜����" << std::endl;

	stateMap.erase(it);
}

// ���ׂĂ̓o�^���폜����
void CStateMachine::AllDeregistration()
{
	std::cout << "StateMachine : " << "���ׂĂ̓o�^���폜����" << std::endl;

	stateMap.clear();
}

// �X�e�[�g�O���狭���I�ɑJ�ڂ����s
void CStateMachine::ForceChange(const std::string& registerName) {
	// �J�ڎ��̏��������s
	nowState->OnChangeEvent();

	// �J�ڐ�̎擾
	auto it = stateMap.find(registerName);
	// ������Ȃ������ꍇ�A�������I��
	if (it == stateMap.end()) return;

	nowState = it->second;
	nowState->Start();
}
