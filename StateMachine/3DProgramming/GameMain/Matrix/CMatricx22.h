#pragma once

#include "../Vector/CVector2.h"
#define _USE_MATH_DEFINES
#include <math.h>

class CMatricx22{
public:
	float m[2][2];

	CMatricx22(){
		loadidentity();
	}

	void loadidentity(){
		m[0][0] = m[1][1] = 1.0f;
		m[0][1] = m[1][0] = 0.0f;
	}

	void setrotation(float degree){
		float rad = degree * M_PI / 180.0f;
		m[0][0] = m[1][1] = cosf(rad);
		m[0][1] = -sinf(rad);
		m[1][0] = sinf(rad);
	}

	const CVector2 operator*(const CVector2& v)const {
		return CVector2(m[0][0] * v.x + m[0][1] * v.y, m[1][0] * v.x + m[1][1] * v.y);
	}

	void setscale(float sx, float sy){
		m[0][0] = sx;
		m[0][1] = m[1][0] = 0.0f;
		m[1][1] = sy;
	}
};