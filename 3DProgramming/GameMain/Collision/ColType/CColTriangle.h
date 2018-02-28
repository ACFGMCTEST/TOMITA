#ifndef COL_TRIANGLE_H
#define COL_TRIANGLE_H

#include "CColBase.h"


/*当たり判定クラス 三角面*/
class CColTriangle : CCollBase{
public:
	CVector3 v0, v1, v2;//三角形の頂点

};

#endif