
#ifndef LOAD_TEX_MANAGER_HPP
#define LOAD_TEX_MANAGER_HPP
#include "CTexture.h"


class  CLoadTexManager
{
private:
	static CLoadTexManager *mLoadTexManager;
	CLoadTexManager();
	~CLoadTexManager();

public:
	static CLoadTexManager *GetInstance(); //GetInstance
	/*�r���{�[�h�̃��[�h*/
	CTexture *mpSpark;//�Ή�
private:

};

#endif