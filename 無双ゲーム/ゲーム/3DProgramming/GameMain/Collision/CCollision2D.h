/*
�����蔻��̃v���O����
�S���ҁ@�y�c���l
*/
#ifndef COLLISION2D_HPP
#define COLLISION2D_HPP
#include "../Graphic/CRectangle2.h"
#include "../Vector/CVector2.h"

class CCollision2D {
public:
	/*base1���U���͈�(�l�p) base2���U�����󂯂�ق� range���U���͈�(��)*/
	static bool Collision2D(const CRectangle2 rect1, const CRectangle2 rect2);
};

#endif