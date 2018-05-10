#include "Windows.h"
#include "glut.h"
#include "CCamera.h"

//�J�����̏�����̏�����
CCamera::CCamera() : mUp(0.0f, 1.0f, 0.0f) {
	//���_�ƒ����_�̐ݒ�
//	setPos(0.0f, 0.0f, 0.0f);
}

/*����������*/
void CCamera::Init(){
	for (int i = 0; i < E_ARRAY; i++)
	{
		pos[i] = 0.0f;
		eye[i] = 0.0f;
	}
}
/* ���_�ƒ����_�̐ݒ�
void setPos(float x, float y, float z)
x:�����_��X���W y:�����_��Y���W z:�����_��Z���W
�K��̎��_�͒����_���Y��+2�AZ��+4�ړ�
*/
void CCamera::SetPos(float x, float y, float z) {
	//�����_�̐ݒ�
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	//���_�̐ݒ�
	eye[0] = pos[0];
	eye[1] = pos[1] + 1.0f;
	eye[2] = pos[2] + 10.0f;
	//�J�����s��̐ݒ�
	gluLookAt(eye[0], eye[1], eye[2], pos[0], pos[1], pos[2], 0.0f, 1.0f, 0.0f);
}

/* �X�V����
�L�[�ɂ�莋�_��ύX����
J�F���O����@K�F�O�ʂ���@L�F�E�O����
U�F����납��@I�F��납��@O�F�E��납��
*/
void CCamera::Update() {
	//�s��̃��[�h�����f���r���[�ɂ���
	glMatrixMode(GL_MODELVIEW);
	//���f���r���[�̍s���P�ʍs��ɂ���
	glLoadIdentity();
	//���_�̐ݒ�
	gluLookAt(eye[0], eye[1], eye[2], pos[0], pos[1], pos[2], mUp.x, mUp.y, mUp.z);
	glGetFloatv(GL_MODELVIEW_MATRIX, mCameraMatrix.f);
	mCameraInverse = mCameraMatrix.getInverse();
	mCameraInverse.m[3][0] = mCameraInverse.m[3][1] = mCameraInverse.m[3][2] = 0.0f;
	//CMatrix44 inverse;
	//inverse = mCameraMatrix.getInverse();
	//inverse = inverse * mCameraMatrix;
}
//
//void CCamera::update(CVector3 aeye, CVector3 pos, CVector3 up) {
//	//�s��̃��[�h�����f���r���[�ɂ���
//	glMatrixMode(GL_MODELVIEW);
//	//���f���r���[�̍s���P�ʍs��ɂ���
//	glLoadIdentity();
//	if (GetKeyState('J') & 0x8000) {
//		//J�L�[�̎��A���O���猩��
//		eye[0] -= 1.0f;
//		//		eye[1] = pos[1] + 2.0f;
//		//		eye[2] = pos[2] + 3.0f;
//	}
//	if (GetKeyState('K') & 0x8000) {
//		//K�L�[�̎��A�^���ʂ��猩��
//		//		eye[0] = pos[0];
//		//		eye[1] = pos[1] + 2.0f;
//		eye[2] += 1.0f;
//	}
//	if (GetKeyState('L') & 0x8000) {
//		//L�L�[�̎��A�E�O���猩��
//		eye[0] += 1.0f;
//		//		eye[1] = pos[1] + 2.0f;
//		//		eye[2] = pos[2] + 3.0f;
//	}
//	if (GetKeyState('I') & 0x8000) {
//		//I�L�[�̎��A�^��납�猩��
//		//eye[0] = pos[0];
//		//eye[1] = pos[1] + 2.0f;
//		eye[2] -= 1.0f;
//	}
//	//���_�̐ݒ�
//	gluLookAt(eye[0], eye[1], eye[2], pos.x, pos.y, pos.z, up.x, up.y, up.z);
//}
