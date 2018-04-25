#ifndef CSE_HPP
#define CSE_HPP
#include "CSound.h"

/*SE‘½‚­‚ÌŽæ‚èˆµ‚¤‚à‚Ì*/
class CSE
{
private:
	static CSE *mSE;
public:

	static CSE *GetInstance(); //GetInstance
	CSound mSEButton;//SEƒ{ƒ^ƒ“
	CSE();
	~CSE();

};

#endif