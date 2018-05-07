#ifndef COL_SPHERE_H
#define COL_SPHERE_H

#include "CColBase.h"

/*当たり判定クラス　球*/
class CColSphere :public CCollBase
{
public:
	float mRadius;//半径
	////回転行列 
	CMatrix44 mMatrixRotation;


	//OBBに行列を反映
	void Transform(CMatrix44 &mat) {
		CVector4 c = CVector4(mPos.x, mPos.y, mPos.z, 1);
		c = c*mat;
		mPos = CVector3(c.x, c.y, c.z);
	}
};
#endif