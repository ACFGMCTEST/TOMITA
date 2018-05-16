#ifndef COL_BASE_H
#define COL_BASE_H

#include "../../Vector/CVector3.h"
#include "../../Matrix/CMatrix44.h"
#include "../../Task/CTask.h"

/*当たり判定クラスベース*/
class CColBase : public CTask
{
public:
	CVector3 mParentNextPos;//親から調整したもの
	CVector3 mPos;		//中心座標
	float r, g, b, a;//色情報
	CVector3 mAdjust;	//衝突応答　調整値
	CTask *mpParent;	//親のタスク
	CMatrix44 *mpCombinedMatrix;	//フレームの合成行列
	CColBase() : mpParent(0), mpCombinedMatrix(0) {}

	/*色設定*/
	void SetColor(float cr, float cg, float cb, float ca){
		r = cr;
		g = cg;
		b = cb;
		a = ca;
	}
	/*描画処理*/
	virtual void Render() {};

};

#endif