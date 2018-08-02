#include "Windows.h"

#include "../Scene/GameScene/CharaDate/CSceneModel.h"
#include "glut.h"
#include "../Collision/CCollisionManager.h"
#include "CCamera.h"
#include "../Scene/GameScene/Map/CMap.h"
#include "../Key/CMouse.h"
#include "../Collision/CCollision2D.h"
#include "../Convenient/CConvenient.h"
#include "../Scene/GameScene/CGameScene.h"
#include "../Graphic/CLoadTexManager.h"
#include <math.h>


/*�J���������|�W�V����*/
#define FIAST_POS CVector3(0.0f,3.0f,0.0f)


#define ANGLE_SPEED 3.0f//�J�����X�s�[�h
#define SET_EYE	x, y+1.0f, z+10.0f //�ڐ��̐ݒ�
/*�ړ�����*/
#define MOVE_FORWARD CVector3(0.0f,0.0f,1.0f)


/*�J�����̐ݒ�l gluLookAt�Ŏg�p
Eye = ���_�̈ʒux,y,z;
pos = ���E�̒��S�ʒu�̎Q�Ɠ_���Wx,y,z
mUp = //���E�̏�����̃x�N�g��x,y,z
*/
#define CAMERA_LOOK mEye.x,mEye.y,mEye.z, mPos.x,mPos.y,mPos.z, mUp.x,mUp.y,mUp.z

/*�����蔻��̐ݒ�l*/
#define OBB_POS CVector3(0.0f, 1.0f, 0.0f) 
#define OBB_SPHERE_SIZE 3.0f
/*�J�����̈ʒu*/
#define CAMERA_OFFSET CVector3(0.0f, 1.0f, 4.0f) //�J�����ʒu�v���C���[����̑��Έʒu
//�L����
#define CHARA_POS(pos)	CVector3(pos.x,	pos.y + 3.0f, pos.z-1.0f)

/*�J�����}�E�X*/
#define ARRIVAL_TIME 0.1f//�҂�����
#define ANGLE_SPEED 3.0f//�J�����X�s�[�h
#define CAMERA_IF_DIVIDE  50//�J�����X�s�[�h�����p
#define CAMERA_DIVIDE  10//�J�����X�s�[�h�����p




//�J�����̏�����̏�����
CCamera::CCamera() : mUp(0.0f, 1.0f, 0.0f) ,mForward(FORWARD){
	//���_�ƒ����_�̐ݒ�
//	setPos(0.0f, 0.0f, 0.0f);
}

/*�L�����N�^�[�Ƀ|�W�V�����ړ�����*/
void CCamera::CharaPos(){
	///PosUpdate(mRot, CHARA_POS(CSceneModel::Player().mPosition));
}

/*����ɕ\������}�b�v�`����J�n���镔���Ɏg��*/
void CCamera::StartMiniMap() {
	/*
	gluPerspective( GL10 gl, float fovy, float aspect, float zNear, float zFar )
	gluPerspective�͎���p�A���s���̍ő�A�ŏ�������ݒ肵�܂��B
		gluPerspective�Őݒ肵���͈͊O�̃|���S���͊�{�I�ɕ`�悳��܂���B
		gl	�g�p����GL10�̃C���X�^���X���w�肵�܂��B
		fovy	�c�̎���p���h�x�h�P�ʂŐݒ肵�܂��B
		aspect	�c�ɑ΂��鉡�����̎���p�̔{����ݒ肵�܂��B
		zNear	��ԋ߂�Z�ʒu���w�肵�܂��B
		zFar	��ԉ���Z�ʒu���w�肵�܂��B
		aspect�͒ʏ� �X�N���[���� / �X�N���[������ �����܂�
	*/
#define CAMERA_INIT 75.0, (double)DISP_X / (double)DISP_Y, 1.0, 1000.0 
	gluPerspective(CAMERA_INIT);
	glPushMatrix();

	/*�J�����̐ݒ�*/
	glViewport(mMiniPos.x,mMiniPos.y,mMiniSize.x, mMiniSize.y);
	

	glLoadIdentity();
	gluLookAt(CAMERA_LOOK);
	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix.f);
	mCameraInverse = mMatrix.getInverse();
	mCameraInverse.m[3][0] = mCameraInverse.m[3][1] = mCameraInverse.m[3][2] = 0.0f;

	glDisable(GL_NORMALIZE);
	glDisable(GL_DEPTH_TEST);


}
/*�`�揈��*/
void CCamera::Render() {
	/*�QD�̕\��*/
	CRectangle2::Disp2D_Start();
	/*���̉��*/
	mMiniMapBG.Render();
	CRectangle2::Disp2D_Exit();
}

/*�E��ɕ\������}�b�v�`����I������Ƃ��Ɏg��*/
void CCamera::EndMiniMap() {
	glPopMatrix();
	glViewport(0, 0, DISP_X, DISP_Y); //��ʂ̕`��G���A�̎w��

	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
}
/*����������*/
void CCamera::Init(){

	mRot = CVector3();
	///*���̓����蔻��ݒ�*/
	//mpCBSphere = new CCollider(E_COL_SPHEPE);
	//mpCBSphere->mpParent = this;
	//mpCBSphere->SetShere(OBB_SPHERE_SIZE, OBB_POS, &mMatrix);
	///*�����蔻��ǉ�*/
	//CCollisionManager::GetInstance()->Add(CTask::E_TAG_CAMERA, mpCBSphere);
}

/* ���_�ƒ����_�̐ݒ�
void setPos(float x, float y, float z)
x:�����_��X���W y:�����_��Y���W z:�����_��Z���W
*/
const float doub = 2.1f;//�{��
const float ajust = 1.97f;//�{��2�{�����ǃL�c�L�c�ɉ�ʕ\���Ȃ̂Œ���
const float BGDoub = 1.08f;//�~�j�}�b�v�pBG�̑傫���{��
const CVector3 eye = CVector3(0.0f, 100.0f, 0.0f);//+ �g��
const CVector3 up = CVector3(0.0f, 1.0f, -1.0f);
void CCamera::SetPos() {
	mEye = CSceneModel::mpPlayer->mPosition;
	mEye += eye;
	mPos = CSceneModel::mpPlayer->mPosition;
	mUp  = up;

	//��ʂ̕`��G���A�̎w��
	mMiniSize = CVector2(DISP_2D_X / doub, DISP_2D_Y / doub);//�T�C�Y
	mMiniPos = CVector2(DISP_2D_X *ajust - mMiniSize.x, DISP_2D_Y * ajust - mMiniSize.y);
	//mMiniPos = CVector2(0.0f,0.0f);
	/*�~�j�}�b�vBG�̐ݒ�*/
	mMiniMapBG.SetVerPos(mMiniSize, mMiniPos);
	mMiniMapBG.SetVer(mMiniSize * BGDoub);
#define TEX_SIZE 0.0f,0.0f,500.0f,500.0f
	mMiniMapBG.SetUv(CLoadTexManager::GetInstance()->
		mpMiniMap[CLoadTexManager::MAP_FRAME], TEX_SIZE);
}
/*�J�����ݒ�*/
void CCamera::MouseCamera(){
	/*�J�����ݒ�}�E�X*/
	if (CMouse::GetInstance()->mPos.x != mSaveMousePos.x && mSaveMousePos.x  > CMouse::GetInstance()->mPos.x){//��
		mRot.y += (mSaveMousePos.x - CMouse::GetInstance()->mPos.x) / CAMERA_DIVIDE;

		CMouse::GetInstance()->SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//�J�[�\�����E�B���h�E�̒��S�ɂ���

	}
	if (CMouse::GetInstance()->mPos.x != mSaveMousePos.x && mSaveMousePos.x < CMouse::GetInstance()->mPos.x){//�E
		mRot.y += (mSaveMousePos.x - CMouse::GetInstance()->mPos.x) / CAMERA_DIVIDE;

		CMouse::GetInstance()->SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//�J�[�\�����E�B���h�E�̒��S�ɂ���
	}

	/*���S���炻���Ɛ^�񒆂ɖ߂�����*/
	if (CCollision2D::Collision2D(mColInitMouse, CMouse::GetInstance()->mRect)){
		/*���Ԃ��o�Ɛ^�񒆂ɖ߂�*/
		if (CConvenient::Time(&mMouseInitCount, ARRIVAL_TIME) &&
			mSaveMousePos.x == CMouse::GetInstance()->mPos.x &&
			mSaveMousePos.y == CMouse::GetInstance()->mPos.y){ //0.1�b�ԓ����Ȃ����
			CMouse::GetInstance()->SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//�J�[�\�����E�B���h�E�̒��S�ɂ���
			mMouseInitCount = 0;//0�ɖ߂�

		}
	}
	else
	{
		//CMouse::GetInstance()->SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//�J�[�\�����E�B���h�E�̒��S�ɂ���
	}

	mSaveMousePos = CMouse::GetInstance()->mPos;//�Z�[�u����

}


/*�|�W�V�������w�肵���ꏊ�ɂ����Ă���*/
void CCamera::PosUpdate(CVector3 rot, CVector3 pos){

	int mRotPercent = rot.y;
	//�J�����ʒu�v���C���[����̑��Έʒu
	CVector3 cp = CAMERA_OFFSET;
	//�J�����̉�]�s��
	CMatrix44 mat;
	//�L�����N�^�[�̈ʒu����J�����ʒu���v�Z
	CVector3 SavePos = pos;
	/*�R�l��*/
	cp.z *= -1;
	mRotPercent %= ANGLE_360;
	CVector3 matrixRot = mRot;
	mRot.y = mRotPercent;//�R�U�O�ɂ���
	mat.rotationX(matrixRot.x);
	mat.rotationY(matrixRot.y);
	//�J��������]������
	cp = cp * mat;
	cp += SavePos;
	//�J�����̎��_(eye)�ƒ��ӓ_(pos)��ݒ�
	
	//�J�����ʒu���
	mPos = SavePos;

	//mMatrix.MatrixTransform(mRot, mPos);
	
	//�J�������_���
	mEye = cp;


}
#define LIMIT_Y 30 //�J�����̏㉺�������~�b�g
/*���L�[�ŃJ�����ړ�*/
void CCamera::CharaUpdate(){
	/*�J�����ݒ�*/
	if (CKey::push(VK_LEFT)) {//��
		mRot.y += ANGLE_SPEED;
	}
	if (CKey::push(VK_RIGHT)) {//�E
		mRot.y -= ANGLE_SPEED;
	}
	if (CKey::push(VK_UP) && mRot.x >= -LIMIT_Y) {//��
		mRot.x -= ANGLE_SPEED;
	}
	if (CKey::push(VK_DOWN) && mRot.x <= LIMIT_Y) {//�E
		mRot.x += ANGLE_SPEED;
	}

	/*���[�e�[�V�������}�C�i�X�̏ꍇ*/
	if (mRot.y < 0){
		mRot.y = ANGLE_360 + mRot.y;
	}

	mRot.y = abs(mRot.y);


}
/*��]�l�̎Q��*/
CVector3 CCamera::Rot(){
	return mRot;
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
	gluLookAt(CAMERA_LOOK);
	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix.f);
	mCameraInverse = mMatrix.getInverse();
	mCameraInverse.m[3][0] = mCameraInverse.m[3][1] = mCameraInverse.m[3][2] = 0.0f;

	/*�L�����N�^�X�C�b�`�Ɏg��*/
	CVector3 pos = CHARA_POS(CSceneModel::mpPlayer->mPosition);
	/*�L�����N�^�[�ɍ��킹��*/
	CharaUpdate();
	/*�J�����̈ړ�*/
	//Move(pos, CSceneModel::mpPlayer->mVelocity);
	PosUpdate(mRot, pos);
	

}

/*�w�肳�ꂽ�����Ɉړ�����
pos = �ړI�l
speed = ����
*/
void CCamera::Move(CVector3 pos, float speed){

	/*�͈͓��̏ꍇ�ړ����Ȃ�*/
	if (pos.x - speed < mPos.x && mPos.x < pos.x + speed &&
		pos.y - speed < mPos.y && mPos.y < pos.y + speed &&
		pos.z - speed < mPos.z && mPos.z < pos.z + speed){
		return;
	}
	else{
		//�i�s����������
		mForward = CVector3(FORWARD);
		//��]�l�v�Z
		CVector3 SaveRot = mForward.getRotationTowards(pos + mPos * -1.0f);

		CMatrix44 rot_y, matrix;

		//��]�s��̍쐬
		rot_y.rotationY(SaveRot.y);

		mForward = mForward * rot_y;
		//�ړ�������
		mPos.y = pos.y;
		mPos += mForward * speed;

		PosUpdate(mRot, mPos);
	}
}