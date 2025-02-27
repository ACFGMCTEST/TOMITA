/*
あたり判定のプログラム
担当者　冨田健斗
*/
#ifndef COLLISION2D_HPP
#define COLLISION2D_HPP
#include "../Graphic/CRectangle2.h"
#include "../Vector/CVector2.h"

class CCollision2D {
public:
	/*base1が攻撃範囲(四角) base2が攻撃を受けるほう rangeが攻撃範囲(軸)*/
	static bool Collision2D(const CRectangle2 rect1, const CRectangle2 rect2);
};

#endif