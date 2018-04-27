/*
‚ ‚½‚è”»’è‚ÌƒvƒƒOƒ‰ƒ€
’S“–Ò@•y“cŒ’“l
*/
#ifndef COLLISION2D_HPP
#define COLLISION2D_HPP
#include "../Graphic/CRectangle2.h"
#include "../Vector/CVector2.h"

class CCollision2D {
public:
	/*base1‚ªUŒ‚”ÍˆÍ(lŠp) base2‚ªUŒ‚‚ğó‚¯‚é‚Ù‚¤ range‚ªUŒ‚”ÍˆÍ(²)*/
	static bool Collision2D(const CRectangle2 rect1, const CRectangle2 rect2);
};

#endif