#pragma once
#include "../Matrix/CMatrix44.h"
#include "../Vector/CVector3.h"

/* �J�����N���X�i���_�̃N���X�j
�ڂ̈ʒu�ƖړI�̈ʒu��ێ����A
�J�����s��i�r���[�ϊ��s��j��ݒ肷��
*/
class CCamera {
public:
	enum E_XYZ
	{
		E_X,
		E_Y,
		E_Z,
		E_ARRAY
	};
	float pos[E_ARRAY];	//�����_ [0]:X���W [1]:Y���W [2]:Z���W
	float eye[E_ARRAY];	//���_ [0]:X���W [1]:Y���W [2]:Z���W
	CVector3 mUp;	//�J�����̏����
	CMatrix44 mCameraMatrix;
	CMatrix44 mCameraInverse;

	//�J�����̏�����̏�����
	CCamera();

	/* ���_�ƒ����_�̐ݒ�
	void setPos(float x, float y, float z)
	x:�����_��X���W y:�����_��Y���W z:�����_��Z���W
	�K��̎��_�͒����_���Y��+2�AZ��+4�ړ�
	*/
	void SetPos(float x, float y, float z);

	/*����������*/
	void Init();
	/* �X�V����
	�L�[�ɂ�莋�_��ύX����
	J�F���O����@K�F�O�ʂ���@L�F�E�O����
	U�F����납��@I�F��납��@O�F�E��납��
	*/
	void Update();

	void Update(CVector3 eye, CVector3 pos, CVector3 up);
};

//�J�����N���X�̃C���X�^���X
extern CCamera MainCamera;
