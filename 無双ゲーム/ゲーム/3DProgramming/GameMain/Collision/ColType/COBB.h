#ifndef COBB_H
#define COBB_H

#include "CColBase.h"


/*当たり判定クラス　OBB*/
class COBB : public CCollBase{
public:

	/*xyzマジックナンバー回避用*/
	enum E_VECTOR
	{
		E_X, E_Y, E_Z, E_ARRAY
	};
	CVector3 mAxis[E_ARRAY];	//各軸ベクトル
	float	 mLength[E_ARRAY];	//各軸の長さ 0 = x,	1 = y,	z = 2

	CVector3 mNormal = CVector3(0.0f, 0.0f, 0.0f);//初期値 向きを指定している パックの方向を決めています
	////回転値 向きの方向を決めて移動するなら使う
	CVector3 mRotation;
	////回転行列 
	CMatrix44 mMatrixRotation;

	//OBBに行列を反映
	void Transform(CMatrix44 &mat);

};
#endif