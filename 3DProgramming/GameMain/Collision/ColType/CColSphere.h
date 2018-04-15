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
	void Transeform(CMatrix44 &mat);
};
#endif