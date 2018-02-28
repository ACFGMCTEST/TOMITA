#include "CCollision2D.h"

#include <math.h>


bool CCollision2D::Collision2D(const CRectangle2 rect1, const CRectangle2 rect2){

	float w_xl1 = rect1.triangle1.x1 + rect1.position.x;
	float w_xr1 = rect1.triangle1.x3 + rect1.position.x;
	float w_yt1 = rect1.triangle1.y1 + rect1.position.y;
	float w_yb1 = rect1.triangle1.y3 + rect1.position.y;
	float w_xl2 = rect2.triangle1.x1 + rect2.position.x;
	float w_xr2 = rect2.triangle1.x3 + rect2.position.x;
	float w_yt2 = rect2.triangle1.y1 + rect2.position.y;
	float w_yb2 = rect2.triangle1.y3 + rect2.position.y;


	if (w_xl1 < w_xr2 && w_xr1 > w_xl2 &&	w_yt1 > w_yb2 && w_yb1 < w_yt2 ){
		return true;
	}

	return false;
}