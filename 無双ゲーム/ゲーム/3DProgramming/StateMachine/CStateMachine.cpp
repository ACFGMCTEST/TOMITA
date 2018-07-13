#include "CStateMachine.h"
#include <assert.h>
/*�X�V*/
void CStateMachine::Update()
{

	nowState->Update();
	nowState->ChangeState();//��Ԑ؂�ւ�

	if (nowState->IsNext())
	{
		// �J�ڐ�̎擾
		auto it = stateMap.find(nowState->NextRegisterName());

		// �J�ڎ��̏��������s(����������)
		nowState->OnChangeEvent();
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

//// �o�^����
//void CStateMachine::Register(const std::string& name, const std::shared_ptr<CStateBase> state)
//{
//	stateMap.insert(std::make_pair(name, state));//�}�b�v�ɖ��O�Ƒ�����ǉ�
//#ifdef _DEBUG
//	std::cout << "StateMachine : " << name << "��o�^" << std::endl;//�f�o�b�N�p
//#endif
//}
//// �o�^����,�e�̐ݒ�
void CStateMachine::Register(const std::string& name, const std::shared_ptr<CStateBase> state, CTask *parent){
	state->SetParent(parent);//�e��ݒ肷��
	stateMap.insert(std::make_pair(name, state));//�}�b�v�ɖ��O�Ƒ�����ǉ�
#ifdef _DEBUG
	std::cout << "StateMachine : " << name << "��o�^" << std::endl;//�f�o�b�N�p
#endif
}

// �ŏ�����n�߂��Ԃ�ݒ�
void CStateMachine::SetStartState(const std::string& registerName)
{
	auto it = stateMap.find(registerName);
	if (it == stateMap.end()) return;
#ifdef _DEBUG
	std::cout << "StateMachine : " << it->first << "���X�^�[�g��Ԃɐݒ�" << std::endl;
#endif
	nowState = it->second;
	nowState->Start();

}

// �o�^�������̂��폜����
void CStateMachine::Deregistration(const std::string& registerName)
{
	auto it = stateMap.find(registerName);
	if (it == stateMap.end()) return;
#ifdef _DEBUG
	std::cout << "StateMachine : " << it->first << "��o�^���폜����" << std::endl;
#endif
	stateMap.erase(it);
}

// ���ׂĂ̓o�^���폜����
void CStateMachine::AllDeregistration()
{
#ifdef _DEBUG
	std::cout << "StateMachine : " << "���ׂĂ̓o�^���폜����" << std::endl;
#endif
	/*�T�C�Y������Ƃ�*/
	if (stateMap.size() != 0) {stateMap.clear();}
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
