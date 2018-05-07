#include "CStateBase.h"

/*ƒRƒ“ƒXƒgƒ‰ƒNƒ^*/
CStateBase::CStateBase() :mFlagNext(false){};


// ‘JˆÚ‚·‚é‚©‚Ç‚¤‚©‚Ìæ“¾
bool  CStateBase::IsNext()const
{
	return mFlagNext;
}

// ‘JˆÚæ‚Ì“o˜^–¼‚Ìæ“¾
std::string CStateBase::NextRegisterName() 
{
	return mNextRegisterName;
}