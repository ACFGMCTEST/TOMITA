#ifndef COL_BASE_H
#define COL_BASE_H

#include "../../Vector/CVector3.h"
#include "../../Matrix/CMatrix44.h"
#include "../../Task/CTask.h"

/*当たり判定クラスベース*/
class CCollBase
{
public:
	CVector3 mPos;		//中心座標
	float r, g, b, a;//色情報
	/*色設定*/
	void SetColor(float cr, float cg, float cb, float ca){
		r = cr;
		g = cg;
		b = cb;
		a = ca;
	}
};

#endif