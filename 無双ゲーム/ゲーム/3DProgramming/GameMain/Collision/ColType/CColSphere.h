#ifndef COL_SPHERE_H
#define COL_SPHERE_H

#include "CColBase.h"

/*当たり判定クラス　球*/
class CColSphere :public CColBase
{
private:
	CVector3 mInitPos;//初めのpos値
	/*更新処理*/
	void Update();
public:
	float mRadius;//半径
	////回転行列 
	CMatrix44 mMatrixRotation;
	CColSphere(){};
	/*当たり判定追加*/
	void ColAdd();
	/*球のパラメータ設定*/
	CColSphere(CTask *parent, CVector3 pos, float radius, CMatrix44 *m);
	/*球のパラメータ設定 マネージャーで管理しない場合*/
	CColSphere(float radius, CVector3 pos, CMatrix44 *m);

	//OBBに行列を反映
	void Transform(CMatrix44 &mat);
	/*更新処理呼び出し*/
	CColSphere GetUpdate();
	/*描画*/
	void Render();

};
#endif