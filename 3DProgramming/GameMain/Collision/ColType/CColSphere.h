#ifndef COL_SPHERE_H
#define COL_SPHERE_H

#include "CColBase.h"

/*�����蔻��N���X�@��*/
class CColSphere :public CCollBase
{
public:
	float mRadius;//���a
	////��]�s�� 
	CMatrix44 mMatrixRotation;


	//OBB�ɍs��𔽉f
	void Transeform(CMatrix44 &mat);
};
#endif