#ifndef STATE_MACHIN_H
#define STATE_MACHIN_H

#include "CStateBase.h"


// ��ԊǗ�
class CStateMachine
{
private:
	std::unordered_map<std::string, std::shared_ptr<CStateBase>> stateMap;
	std::shared_ptr<CStateBase> nowState;
public:
	CStateMachine() : nowState(),stateMap()
	{

	}
	/*�X�V����*/
	void Update();

	////// �o�^����
	//void Register(const std::string& name, const std::shared_ptr<CStateBase> state);
	//// �o�^����,�e�̐ݒ�
	void Register(const std::string& name, const std::shared_ptr<CStateBase> state, CTask *parent);

	// �ŏ�����n�߂��Ԃ�ݒ�
	void SetStartState(const std::string& registerName);

	// �o�^�������̂��폜����
	void Deregistration(const std::string& registerName);

	// ���ׂĂ̓o�^���폜����
	void AllDeregistration();

	// �X�e�[�g�O���狭���I�ɑJ�ڂ����s
	void ForceChange(const std::string& registerName);




};
#endif 
