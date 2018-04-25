#ifndef COBB_H
#define COBB_H

#include "CColBase.h"


/*�����蔻��N���X�@OBB*/
class COBB : public CCollBase{
public:

	/*xyz�}�W�b�N�i���o�[���p*/
	enum E_VECTOR
	{
		E_X, E_Y, E_Z, E_ARRAY
	};
	CVector3 mAxis[E_ARRAY];	//�e���x�N�g��
	float	 mLength[E_ARRAY];	//�e���̒��� 0 = x,	1 = y,	z = 2

	CVector3 mNormal = CVector3(0.0f, 0.0f, 0.0f);//�����l �������w�肵�Ă��� �p�b�N�̕��������߂Ă��܂�
	////��]�l �����̕��������߂Ĉړ�����Ȃ�g��
	CVector3 mRotation;
	////��]�s�� 
	CMatrix44 mMatrixRotation;

	//OBB�ɍs��𔽉f
	void Transform(CMatrix44 &mat);

};
#endif