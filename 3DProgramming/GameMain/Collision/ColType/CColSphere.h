#ifndef COL_SPHERE_H
#define COL_SPHERE_H

#include "CColBase.h"

/*�����蔻��N���X�@��*/
class CColSphere :public CCollBase
{
public:
	float mRadius;//���a

	//OBB�ɍs��𔽉f
	void Transeform(CMatrix44 &mat);
};
#endif