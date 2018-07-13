#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../Matrix/CMatrix44.h"
#include "../Vector/CVector3.h"
#include "../Task/CTask.h"
#include "../Graphic/CRectangle2.h"


/* �J�����N���X�i���_�̃N���X�j
�ڂ̈ʒu�ƖړI�̈ʒu��ێ����A
�J�����s��i�r���[�ϊ��s��j��ݒ肷��
*/
class CCamera{
private:
	CMatrix44 mMatrix;//�s��
	CRectangle2 mColInitMouse;//�}�E�X�̏����ʒu


	CRectangle2 mMiniMapBG;//�~�j�}�b�v�̔w�i

	CVector3 mForward;//�ړ�����

	CVector3 mRot;//�����̕���
	CVector3 mEye;//���_
	CVector3 mUp;	//�J�����̏����

	CVector2 mSaveMousePos;//�}�E�X�̃|�W�V����
	float mMouseInitCount;//�J�����̏���������
public:
	//�~�j�}�b�v�p
	CVector2 mMiniSize;//�T�C�Y
	CVector2 mMiniPos;//�|�W�V����
														  

	CVector3 mPos;//�|�W�V����
	CMatrix44 mCameraInverse;

	//�J�����̏�����̏�����
	CCamera();

	/* ���_�ƒ����_�̐ݒ�
	void setPos(float x, float y, float z)
	x:�����_��X���W y:�����_��Y���W z:�����_��Z���W
	*/
	void SetPos();
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
	
	/*��]�l�̎Q��*/
	CVector3 Rot();
	
	/*����ɕ\������}�b�v*/
	void StartMiniMap();
	/*�E��ɕ\������}�b�v*/
	void EndMiniMap();

	/*�L�����N�^�[�Ƀ|�W�V�����ړ�����*/
	void CharaPos();

	/*�`�揈��*/
	void Render();
};

//�J�����N���X�̃C���X�^���X
extern CCamera MainCamera;
//�J�����N���X�̃C���X�^���X
extern CCamera MapCamera;


#endif