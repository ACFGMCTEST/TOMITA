#include "CVector2.h"

#define _USE_MATH_DEFINES	//数学ライブラリのM_PIを有効にする
#include <math.h>
/* デフォルトコンストラクタ
x,yともに0.0fで初期化する
*/
CVector2::CVector2()
: x(0.0f), y(0.0f) {}

/* 引数xとyの値で初期設定する
CVector2(float x, float y)
[in] x	xの値
[in] y	yの値
*/
CVector2::CVector2(float x, float y)
	: x(x), y(y) {}

/*　+=演算子 のオーバーライド
void operator+=(const CVector2 &v) { x += v.x; y += v.y; }

void: 戻り値なし
operator+=： x同士、y同士を加算する
CVector2 &v：引数。vのxをxへ、vのyをyへ加算する

vector2 += v の場合、vector2.xにv.x、vector2.yにv.yが加算される
*/
void CVector2::operator+=(const CVector2 &v) { x += v.x; y += v.y; }

/*　*演算子のオーバーライド
const CVector2 operator*(float f) const { return CVector2(x * f, y * f); };

const: 変更不可という意味。この戻り値は変更不可ということ。
CVector2： 戻り値の型
operator*：x,yともに、fの値を掛ける
float f: 引数。fの値で、xとyの値を掛け算する

vector2 * 2.0f の場合、vector2のxを2.0f倍、vector2のyを2.0f倍したCVector2型の値を戻す
*/
const CVector2 CVector2::operator*(float f) const { return CVector2(x * f, y * f); }

/*　*=演算子 のオーバーライド
void operator*=(const CVector2 &v) { x += v.x; y += v.y; }

void: 戻り値なし
operator*=： x同士、y同士を乗算する
CVector2 &v：引数。vのxとx、vのyとyを乗算する

vector2 *= v の場合、vector2.xにv.x、vector2.yにv.yが乗算される
*/
void CVector2::operator*=(const CVector2 &v) { x *= v.x; y *= v.y; }

const CVector2 CVector2::operator - (const CVector2 &v) const {
	return CVector2(x - v.x, y - v.y);
};

float CVector2::Dot(const CVector2 &v1, const CVector2 &v2) {
	return v1.x*v2.x + v1.y*v2.y;
}

/*
頂点から角度を求める関数
*/
float CVector2::Angle(CVector2 vec1, CVector2 vec2){
	float r = atan2(vec1.y - vec2.y, vec1.x - vec2.x);
	if (r < 0) {
		r = r + 2 * M_PI;
	}
	return floor(r * 360 / (2 * M_PI));
}