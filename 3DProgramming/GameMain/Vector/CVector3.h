#pragma once
/*x����*/
#define VEC_LEFT CVector3(-1.0f,0.0f,0.0f)
#define VEC_RIGHT CVector3(1.0f,0.0f,0.0f)
/*y����*/
#define VEC_TOP CVector3(0.0f,1.0f,0.0f)
#define VEC_BOTTOM CVector3(0.0f,-1.0f,0.0f)
/*z����*/
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
	//CMatrix44�Ƃ̊|���Z
	const CVector3 operator * (const CMatrix44 &m) const;
	/* CVector3���m�̉��Z
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
	/*���ς����߂�
	�������Ax,y,z�̂�
	*/
	float Dot(const CVector3 &v) const ;
	static float Dot(const CVector3 &v, const CVector3 &v2);

	static CVector3 Cross(const CVector3 &v, const CVector3 &v2);
	/* �x�N�g���̑傫����Ԃ�
	�������Ax,y,z�̂�
	*/
	float length();
	float Length() {
		return length();
	}
	/* ���K�������x�N�g����Ԃ�
	�x�N�g���̐��K���F�傫����1�ɂ���
	*/
	CVector3 normalize();
	CVector3 GetNormalize() {
		return normalize();
	}
	/* �w�肳�ꂽ�x�N�g���̕����֌�����ׂ̉�]�p�x�𓾂�
	return:�bX���̉�]�p�x�@Y���̉�]�p�x�@�O�x�b
	*/
	CVector3 getRotationTowards(const CVector3 &dir);
	/* �w�肳�ꂽ���a�̋���̈ʒu�������_���ɐݒ肷��
	�x�N�g���b0.0 0.0 1.0�b��X���Ń����_���ɉ�]�����A����
	Y���Ń����_���ɉ�]�����A���a���|�����l��ݒ肷��
	*/
	void setRandomPositionSphere(float radius);

	float LengthSq() { return length() * length(); }

	CVector3 Cross(const CVector3& v) const ;
	/*�}�g���b�N�X�|�W�V�����ȍ~*/
	CVector3 Transeform(CMatrix44 &mat);

	/*���Ԓl���o��*/
	CVector3 Median(const CVector3 &v)const;
};

