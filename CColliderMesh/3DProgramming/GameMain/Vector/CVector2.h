#pragma once

/* 2次元のベクトルクラスを作成する */
class CVector2 {
public:
	float x;	//X軸への大きさ
	float y;	//Y軸への大きさ

	CVector2();	//デフォルトコンストラクタ
	CVector2(float x, float y);	//コンストラクタ

	/*　+=演算子のオーバーライド
	CVector2 += CVector2　の宣言
	*/
	void operator+=(const CVector2 &v);

	/*　*演算子のオーバーライド
	CVector2 * float　の宣言
	*/
	const CVector2 operator*(float f) const;

	/*　*=演算子のオーバーライド
	CVector2 *= CVector2　の宣言
	*/
	void operator*=(const CVector2 &v);
	const CVector2 operator-(const CVector2 &v) const;
	static float Dot(const CVector2 &v1, const CVector2 &v2);
	const CVector2 CVector2::operator + (const CVector2 &v) const {
		return CVector2(x + v.x, y + v.y);
	};


	/*
	頂点から角度を求める関数
	*/
	static float Angle(CVector2 vec1, CVector2 vec2);

};
//typedef CVector2 CVector2;

