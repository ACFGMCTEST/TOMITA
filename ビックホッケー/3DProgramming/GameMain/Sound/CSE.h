#ifndef CSE_HPP
#define CSE_HPP
#include "CSound.h"

/*SE�����̎�舵������*/
class CSE
{
private:
	static CSE *mSE;
public:

	static CSE *GetInstance(); //GetInstance
	CSound mSEButton;//SE�{�^��
	CSE();
	~CSE();

};

#endif