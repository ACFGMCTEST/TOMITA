#include "CVector2.h"

#define _USE_MATH_DEFINES	//���w���C�u������M_PI��L���ɂ���
#include <math.h>
/* �f�t�H���g�R���X�g���N�^
x,y�Ƃ���0.0f�ŏ���������
*/
CVector2::CVector2()
: x(0.0f), y(0.0f) {}

/* ����x��y�̒l�ŏ����ݒ肷��
CVector2(float x, float y)
[in] x	x�̒l
[in] y	y�̒l
*/
CVector2::CVector2(float x, float y)
	: x(x), y(y) {}

/*�@+=���Z�q �̃I�[�o�[���C�h
void operator+=(const CVector2 &v) { x += v.x; y += v.y; }

void: �߂�l�Ȃ�
operator+=�F x���m�Ay���m�����Z����
CVector2 &v�F�����Bv��x��x�ցAv��y��y�։��Z����

vector2 += v �̏ꍇ�Avector2.x��v.x�Avector2.y��v.y�����Z�����
*/
void CVector2::operator+=(const CVector2 &v) { x += v.x; y += v.y; }

/*�@*���Z�q�̃I�[�o�[���C�h
const CVector2 operator*(float f) const { return CVector2(x * f, y * f); };

const: �ύX�s�Ƃ����Ӗ��B���̖߂�l�͕ύX�s�Ƃ������ƁB
CVector2�F �߂�l�̌^
operator*�Fx,y�Ƃ��ɁAf�̒l���|����
float f: �����Bf�̒l�ŁAx��y�̒l���|���Z����

vector2 * 2.0f �̏ꍇ�Avector2��x��2.0f�{�Avector2��y��2.0f�{����CVector2�^�̒l��߂�
*/
const CVector2 CVector2::operator*(float f) const { return CVector2(x * f, y * f); }

/*�@*=���Z�q �̃I�[�o�[���C�h
void operator*=(const CVector2 &v) { x += v.x; y += v.y; }

void: �߂�l�Ȃ�
operator*=�F x���m�Ay���m����Z����
CVector2 &v�F�����Bv��x��x�Av��y��y����Z����

vector2 *= v �̏ꍇ�Avector2.x��v.x�Avector2.y��v.y����Z�����
*/
void CVector2::operator*=(const CVector2 &v) { x *= v.x; y *= v.y; }

const CVector2 CVector2::operator - (const CVector2 &v) const {
	return CVector2(x - v.x, y - v.y);
};

float CVector2::Dot(const CVector2 &v1, const CVector2 &v2) {
	return v1.x*v2.x + v1.y*v2.y;
}

/*
���_����p�x�����߂�֐�
*/
float CVector2::Angle(CVector2 vec1, CVector2 vec2){
	float r = atan2(vec1.y - vec2.y, vec1.x - vec2.x);
	if (r < 0) {
		r = r + 2 * M_PI;
	}
	return floor(r * 360 / (2 * M_PI));
}