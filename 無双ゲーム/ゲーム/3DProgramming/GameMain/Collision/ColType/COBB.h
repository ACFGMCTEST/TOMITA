#ifndef COBB_H
#define COBB_H

#include "CColBase.h"


/*�����蔻��N���X�@OBB*/
class COBB : public CColBase{
private:
	/*�X�V����*/
	void Update();
public:

	/*xyz�}�W�b�N�i���o�[���p*/
	enum E_VECTOR
	{
		E_X, E_Y, E_Z, E_ARRAY
	};
	CVector3 mAxis[E_ARRAY];	//�e���x�N�g��
	float	 mLength[E_ARRAY];	//�e���̒��� 0 = x,	1 = y,	z = 2
	////��]�l �����̕��������߂Ĉړ�����Ȃ�g��
	CVector3 mRotation;
	////��]�s�� 
	CMatrix44 mMatrixRotation;


	/*�R���X�g���N�^*/
	COBB();
	/*�p�����[�^�ݒ�*/
	COBB(CVector3 &center, CVector3 &v, CMatrix44 *matrix);
	//OBB�ɍs��𔽉f
	void Transform(CMatrix44 &mat);
	/*�X�V�����Ăяo��*/
	COBB GetUpdate();
	/*�`��*/
	void Render();

};

#endif