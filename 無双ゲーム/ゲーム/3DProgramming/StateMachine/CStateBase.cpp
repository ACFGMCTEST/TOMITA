#include "CStateBase.h"

/*�R���X�g���N�^*/
CStateBase::CStateBase() :mFlagNext(false){};


// �J�ڂ��邩�ǂ����̎擾
bool  CStateBase::IsNext()const
{
	return mFlagNext;
}

// �J�ڐ�̓o�^���̎擾
std::string CStateBase::NextRegisterName() 
{
	return mNextRegisterName;
}