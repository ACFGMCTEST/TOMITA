#include "CSE.h"

CSE *CSE::mSE = 0;

CSE::CSE()
{
	mSEButton.Load(SE_BUTTON_FILE);
}

CSE::~CSE()
{
	mSEButton.Close();
}

//GetInstance
CSE* CSE::GetInstance() {
	if (mSE == 0) {
		mSE = new CSE();
	}
	return mSE;
}
