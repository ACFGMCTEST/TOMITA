#ifndef COBB_H
#define COBB_H

#include "CColBase.h"


/*当たり判定クラス　OBB*/
class COBB : public CColBase{
private:
	/*更新処理*/
	void Update();
public:

	/*xyzマジックナンバー回避用*/
	enum E_VECTOR
	{
		E_X, E_Y, E_Z, E_ARRAY
	};
	CVector3 mAxis[E_ARRAY];	//各軸ベクトル
	float	 mLength[E_ARRAY];	//各軸の長さ 0 = x,	1 = y,	z = 2
	////回転値 向きの方向を決めて移動するなら使う
	CVector3 mRotation;
	////回転行列 
	CMatrix44 mMatrixRotation;


	/*コンストラクタ*/
	COBB();
	/*パラメータ設定*/
	COBB(CVector3 &center, CVector3 &v, CMatrix44 *matrix);
	//OBBに行列を反映
	void Transform(CMatrix44 &mat);
	/*更新処理呼び出し*/
	COBB GetUpdate();
	/*描画*/
	void Render();

};

#endif