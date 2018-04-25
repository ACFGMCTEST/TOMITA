#pragma once
/*x方向*/
#define VEC_LEFT CVector3(-1.0f,0.0f,0.0f)
#define VEC_RIGHT CVector3(1.0f,0.0f,0.0f)
/*y方向*/
#define VEC_TOP CVector3(0.0f,1.0f,0.0f)
#define VEC_BOTTOM CVector3(0.0f,-1.0f,0.0f)
/*z方向*/
#define VEC_FRONT CVector3(0.0f,0.0f,1.0f)
#define VEC_BACK CVector3(0.0f,0.0f,-1.0f)
class CMatrix44;


class CVector3 {
public:
	union {
		float v[3];
		struct {
			float x, y, z;
		};
	};
	CVector3();
	CVector3(float x, float y, float z);
	//CMatrix44との掛け算
	const CVector3 operator * (const CMatrix44 &m) const;
	/* CVector3同士の演算
	*/
	const CVector3 operator + (const CVector3 &v) const;
	const bool operator == (const CVector3 &v) const;
	const bool operator != (const CVector3 &v) const;
	void operator += (const CVector3 &v);
	CVector3 operator - (const CVector3 &v) const;
	void operator -= (const CVector3 &v);
	const CVector3 operator * (const CVector3 &v) const;
	void operator *= (const CVector3 &v);
	const CVector3 operator / (const CVector3 &v) const;
	void operator /= (const CVector3 &v);
	const CVector3 operator * (float f) const;
	void operator *= (float f);
	const CVector3 operator / (float f) const;
	void operator /= (float f);
	/*内積を求める
	ただし、x,y,zのみ
	*/
	float Dot(const CVector3 &v) const ;
	static float Dot(const CVector3 &v, const CVector3 &v2);

	static CVector3 Cross(const CVector3 &v, const CVector3 &v2);
	/* ベクトルの大きさを返す
	ただし、x,y,zのみ
	*/
	float length();
	float Length() {
		return length();
	}
	/* 正規化したベクトルを返す
	ベクトルの正規化：大きさを1にする
	*/
	CVector3 normalize();
	CVector3 GetNormalize() {
		return normalize();
	}
	/* 指定されたベクトルの方向へ向ける為の回転角度を得る
	return:｜X軸の回転角度　Y軸の回転角度　０度｜
	*/
	CVector3 getRotationTowards(const CVector3 &dir);
	/* 指定された半径の球上の位置をランダムに設定する
	ベクトル｜0.0 0.0 1.0｜をX軸でランダムに回転させ、次に
	Y軸でランダムに回転させ、半径を掛けた値を設定する
	*/
	void setRandomPositionSphere(float radius);

	float LengthSq() { return length() * length(); }

	CVector3 Cross(const CVector3& v) const ;
	/*マトリックスポジション以降*/
	CVector3 Transeform(CMatrix44 &mat);

	/*中間値を出す*/
	CVector3 Median(const CVector3 &v)const;
};

