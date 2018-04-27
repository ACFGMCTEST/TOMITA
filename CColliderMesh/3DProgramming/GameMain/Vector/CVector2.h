#pragma once

/* 2�����̃x�N�g���N���X���쐬���� */
class CVector2 {
public:
	float x;	//X���ւ̑傫��
	float y;	//Y���ւ̑傫��

	CVector2();	//�f�t�H���g�R���X�g���N�^
	CVector2(float x, float y);	//�R���X�g���N�^

	/*�@+=���Z�q�̃I�[�o�[���C�h
	CVector2 += CVector2�@�̐錾
	*/
	void operator+=(const CVector2 &v);

	/*�@*���Z�q�̃I�[�o�[���C�h
	CVector2 * float�@�̐錾
	*/
	const CVector2 operator*(float f) const;

	/*�@*=���Z�q�̃I�[�o�[���C�h
	CVector2 *= CVector2�@�̐錾
	*/
	void operator*=(const CVector2 &v);
	const CVector2 operator-(const CVector2 &v) const;
	static float Dot(const CVector2 &v1, const CVector2 &v2);
	const CVector2 CVector2::operator + (const CVector2 &v) const {
		return CVector2(x + v.x, y + v.y);
	};


	/*
	���_����p�x�����߂�֐�
	*/
	static float Angle(CVector2 vec1, CVector2 vec2);

};
//typedef CVector2 CVector2;

