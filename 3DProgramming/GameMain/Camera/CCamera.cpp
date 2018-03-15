#include "Windows.h"
#include "glut.h"
#include "../Collision/CCollisionManager.h"
#include "CCamera.h"
#include <math.h>


#define SET_EYE	x, y+1.0f, z+10.0f //�ڐ��̐ݒ�

/*�J�����̐ݒ�l gluLookAt�Ŏg�p
Eye = ���_�̈ʒux,y,z;
pos = ���E�̒��S�ʒu�̎Q�Ɠ_���Wx,y,z
mUp = //���E�̏�����̃x�N�g��x,y,z
*/
#define CAMERA_LOOK mEye.x,mEye.y,mEye.z, mPos.x,mPos.y,mPos.z, mUp.x,mUp.y,mUp.z

/*�����蔻��̐ݒ�l*/
#define OBB_POS CVector3(0.0f, 1.0f, 0.0f) 
#define OBB_SIZE new float[]{1.5f,0.5f, 1.5f} 
#define OBB_SPHERE_SIZE 1.0f

//�J�����̏�����̏�����
CCamera::CCamera() : mUp(0.0f, 1.0f, 0.0f) {
	//���_�ƒ����_�̐ݒ�
//	setPos(0.0f, 0.0f, 0.0f);
}

/*����������*/
void CCamera::Init(){
	/*for (int i = 0; i < E_ARRAY; i++)
	{
		pos[i] = 0.0f;
		eye[i] = 0.0f;
	}*/


	/*���̓����蔻��ݒ�*/
	mpCBSphere = new CCollider(E_COL_SPHEPE);
	mpCBSphere->mpParent = this;
	mpCBSphere->SetShere(OBB_SPHERE_SIZE, OBB_POS, &mMatrix);
	/*�����蔻��ǉ�*/
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_CAMERA, mpCBSphere);
}
/* ���_�ƒ����_�̐ݒ�
void setPos(float x, float y, float z)
x:�����_��X���W y:�����_��Y���W z:�����_��Z���W
�K��̎��_�͒����_���Y��+2�AZ��+4�ړ�
*/
void CCamera::SetPos(float x, float y, float z) {
	//�����_�̐ݒ�
	/*pos[0] = x;
	pos[1] = y;
	pos[2] = z;*/
	mPos = CVector3(x, y, z);
	//���_�̐ݒ�
	/*eye[0] = pos[0];
	eye[1] = pos[1] + 1.0f;
	eye[2] = pos[2] + 10.0f;*/
	mEye = CVector3(SET_EYE);
	//�J�����s��̐ݒ�
	//gluLookAt(eye[0], eye[1], eye[2], pos[0], pos[1], pos[2], 0.0f, 1.0f, 0.0f);
	gluLookAt(CAMERA_LOOK);
}

/* �X�V����
�L�[�ɂ�莋�_��ύX����
J�F���O����@K�F�O�ʂ���@L�F�E�O����
U�F����납��@I�F��납��@O�F�E��납��
*/
void CCamera::Update() {
	mpCBSphere->mColSphere.mPos = mPos;
	//�����蔻��X�V
	mpCBSphere->Update();
	//�s��̃��[�h�����f���r���[�ɂ���
	glMatrixMode(GL_MODELVIEW);
	//���f���r���[�̍s���P�ʍs��ɂ���
	glLoadIdentity();
	//���_�̐ݒ�
	//gluLookAt(eye[0], eye[1], eye[2], pos[0], pos[1], pos[2], mUp.x, mUp.y, mUp.z);
	gluLookAt(CAMERA_LOOK);
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

/*�����蔻��Ăяo��
���̏ꏊ�ɖ߂����߂̊֐�
*/
void CCamera::Collision(const COBB &box) {


	CVector3 savePos = mpCBSphere->mColSphere.mPos;//�v�Z�p

	float lengthX = mPos.x - savePos.x;  //���ƃ|�W�V�����̋���
	float lengthY = mPos.y - savePos.y;  //���ƃ|�W�V�����̋���
	float lengthZ = mPos.z - savePos.z;  //���ƃ|�W�V�����̋���

	//Box��X�����������߂�
	CVector3 vx = box.mMatrixRotation * VEC_RIGHT;
	//Box��Y�����������߂�
	CVector3 vy = box.mMatrixRotation * VEC_TOP;
	//Box��Z�����������߂�
	CVector3 vz = box.mMatrixRotation * VEC_FRONT;
	//�l�p�`���狅�ւ̃x�N�g�������߂�
	CVector3 vectorBS = savePos - box.mPos;
	//�l�p�`���狅�ցA�l�p�`��X���ɑ΂��钷���Ƃ̍������߂�
	float dx = mpCBSphere->mColSphere.mRadius + box.mLength[0] - fabs(vx.Dot(vectorBS));
	//�l�p�`���狅�ցA�l�p�`��Y���ɑ΂��钷���Ƃ̍������߂�
	float dy = mpCBSphere->mColSphere.mRadius + box.mLength[1] - fabs(vy.Dot(vectorBS));
	//�l�p�`���狅�ցA�l�p�`��Z���ɑ΂��钷���Ƃ̍������߂�
	float dz = mpCBSphere->mColSphere.mRadius + box.mLength[2] - fabs(vz.Dot(vectorBS));


	//�Փ˂��Ă��邩���肷��
	if (dx > 0.0f && dy > 0.0f && dz > 0.0f) {
		if (dx > dy) {
			if (dy > dz) {
				//Z���Ŗ߂�
				if (vz.Dot(vectorBS) > 0.0f) {
					mPos = savePos + vz * dz;
					//���˕Ԃ�����ݒ�
					/*mRefrectVec*/
				}
				else {
					mPos= savePos - vz * dz;
				}
			}
			else {
				//Y���Ŗ߂�
				if (vy.Dot(vectorBS) > 0.0f) {
					mPos = savePos + vy * dy;
				}
				else {
					mPos = savePos - vy * dy;
				}
			}
		}
		else{
			if (dx > dz) {

				//Z���Ŗ߂�
				if (vz.Dot(vectorBS) > 0.0f) {
					mPos = savePos + vz * dz;
				}
				else {
					mPos = savePos - vz * dz;
				}
			}
			else {

				//X���Ŗ߂�
				if (vx.Dot(vectorBS) > 0.0f) {
					mPos = savePos + vx * dx;
				}
				else {
					mPos = savePos - vx * dx;
				}
			}
		}
	}
	mPos.x += lengthX;
	mPos.y += lengthY;
	mPos.z += lengthZ;

	/*�����蔻��X�V*/
	mpCBSphere->Update();

}
