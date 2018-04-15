#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../Matrix/CMatrix44.h"
#include "../Vector/CVector3.h"
#include "../Collision/CCollider.h"
#include "../Task/CTask.h"
#include "../Graphic/CRectangle2.h"

/* �J�����N���X�i���_�̃N���X�j
�ڂ̈ʒu�ƖړI�̈ʒu��ێ����A
�J�����s��i�r���[�ϊ��s��j��ݒ肷��
*/
class CCamera : public CTask{
private:
	CVector3 mRot;//�����̕���
	CVector3 mForward;//�ړ�����
	CMatrix44 mMatrix;//�s��

	CVector2 mSaveMousePos;//�}�E�X�̃|�W�V����
	CRectangle2 mColInitMouse;//�}�E�X�̏����ʒu

	float mMouseInitCount;//�J�����̏���������

public:
	/*�J�����̈ʒu*/
	static enum E_STATE{
		E_CHARA,
		E_PACK,
		E_GOAL,
	};
	E_STATE eState;//�X�e�[�^�X�Ǘ�
	enum E_XYZ
	{
		E_X,
		E_Y,
		E_Z,
		E_ARRAY
	};
	//float pos[E_ARRAY];	//�����_ [0]:X���W [1]:Y���W [2]:Z���W
	//float eye[E_ARRAY];	//���_ [0]:X���W [1]:Y���W [2]:Z���W

	CVector3 mPos;//�|�W�V����
	CVector3 mEye;//���_

	CVector3 mUp;	//�J�����̏����
	CMatrix44 mCameraMatrix;
	CMatrix44 mCameraInverse;
	CCollider *mpCBSphere;//�����蔻�苅��

	//�J�����̏�����̏�����
	CCamera();

	/* ���_�ƒ����_�̐ݒ�
	void setPos(float x, float y, float z)
	x:�����_��X���W y:�����_��Y���W z:�����_��Z���W
	�K��̎��_�͒����_���Y��+2�AZ��+4�ړ�
	*/
	void SetPos(float x, float y, float z);
	/*�}�E�X�J�����ݒ�*/
	void MouseCamera();
	/*����������*/
	void Init();
	/* �X�V����
	�L�[�ɂ�莋�_��ύX����
	J�F���O����@K�F�O�ʂ���@L�F�E�O����
	U�F����납��@I�F��납��@O�F�E��납��
	*/
	void Update();
	/*���L�[�ŃJ�����ړ�*/
	void CharaUpdate();
	/*�|�W�V�������w�肵���ꏊ�ɂ����Ă���*/
	void PosUpdate(CVector3 rot, CVector3 pos);
	/*�w�肳�ꂽ�����Ɉړ�����
	pos = �ړI�l
	speed = ����
	*/
	void Move(CVector3 pos, float speed);
	/*�����蔻��߂�*/
	void CCamera::Collision(const COBB &box);
	/*��]�l�̎Q��*/
	CVector3 Rot();
	/*�J�����̃X�e�[�^�X�ύX*/
	void StateChange(E_STATE state);
	
};

//�J�����N���X�̃C���X�^���X
extern CCamera MainCamera;

#endif