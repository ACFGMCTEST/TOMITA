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
	void Transform(CMatrix44 &mat) {
		CVector4 c = CVector4(mPos.x, mPos.y, mPos.z, 1);
		c = c*mat;
		mPos = CVector3(c.x, c.y, c.z);
	}
};
#endif