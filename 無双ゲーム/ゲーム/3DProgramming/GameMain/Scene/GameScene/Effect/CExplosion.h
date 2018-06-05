//�y�c���l
#ifndef EXPLOISON_HPP
#define EXPLOISON_HPP
#include <math.h>
#include "../../../Graphic/CRectangle.h"
#include "../../../../3DBase/C3DBase.h"
#include "../../../../Define/Define.h"
#include "../../../Camera/CCamera.h"
#include "CEffect2D.h"

#include "../../../Vector/CVector2.h"

/*�e�N�X�`���̃T�C�Y*/
#define TEX_EFFECT_SIZE 0,0,270,270
/*���_�ݒ�*/
#define EFFECT_SIZE_V0 -3.5f, 0.0f, -3.5f
#define EFFECT_SIZE_V1 -3.5f, 0.0f, 0.0f 
#define EFFECT_SIZE_V2 0.0f, 0.0f, 0.0f 
#define EFFECT_SIZE_V3 0.0f, 0.0f, -3.5f
#define EXP_ARRAY 100
/*�ΉԂ̒��_�w��*/
#define SPACK_SIZE_V0 1.0f, 1.0f, 0.0f 
#define SPACK_SIZE_V1 1.0f, -1.0f, 0.0f 
#define SPACK_SIZE_V2 -1.0f, -1.0f, 0.0f 
#define SPACK_SIZE_V3 -1.0f, 1.0f, 0.0f
/*�F�w��*/
#define Orange_Color 1.0f,0.6f,0.0f,1.0f

/*�����_���֐��l*/
#define RAND_INIT_NUM 0.9f
/*�����鎞��*/
#define LIFE_TIME 30.0f
/*�i�ރX�s�[�h*/
#define VELOCITY 0.17f
/*�@���̍ő�l*/
#define NORMAL_MAX 1.0f
#define NORMAL_HALF 0.5f

class CExplosion :public CTask{
private:
	class  CSpark : public CEffect2D {
	private:
		/*�����|�W�V�����ۑ�*/
		CVector4 mSavePos;//�����̃|�W�V�����ۑ�
		CVector3 *mpPos;//�ʒu
	public:
		CSpark() :CEffect2D() {}
		/*����������*/
		void Init(CTexture *tex, float x, float y, STexVer texVer) {
			CEffect2D::Init(tex, x, y, texVer);
			/*�����_���ɉΉԂ��͂�����*/
			mPos.setRandomPositionSphere(RAND_INIT_NUM);
			mForward = CVector4(mPos.x, mPos.y, mPos.z);
		}
		/*�����Ȃ��o�[�W����(�l���ݒ肳��Ă���ꍇ�͂�����)*/
		void Init() {
			CEffect2D::Init();
			/*�����_���ɉΉԂ��͂�����*/
			mPos.setRandomPositionSphere(RAND_INIT_NUM);
			mForward = CVector4(mPos.x, mPos.y, mPos.z);
		}

		/*�X�V����*/
		void Update() {
			mPos = mPos + mForward * VELOCITY;
			CEffect2D::Update();
			//		/*�r���{�[�h�ݒ�*/
			//		mpCamera = &MainCamera;
			//		mMatrix.identity();
			//		mMatrix.translate(mPos);
			////		
			//		CMatrix44 rot;
			//		/*�����ꏊ�����]�l���o��*/
			//		mRot.z = CVector2::Angle(CVector2(mPos.x, mPos.y), CVector2(mSavePos.x, mSavePos.y));
			//		/*��]�l���R�U�O�x�ȏ�ɂ��Ȃ��悤�ɂ���*/
			//		if (mRot.z >= ANGLE_360){
			//			mRot.z -= ANGLE_360;
			//		}
			//		////��]�s��̍쐬
			//		rot.rotationZ(mRot.z);
			//		mMatrix = mMatrix * mpCamera->mCameraInverse * rot;

			///*�@���v�Z�@��̎��s�������́@�ɂ����Ƃ��܂ōs��������Q�l�ɂ���*/
			//		float nx, ny, nz;//�@������
			//		/*0����90 OK*/
			//		if (0 <= mRot.z && mRot.z <= ANGLE_90){
			//			nx = 0.0f;
			//			ny = NORMAL_MAX;
			//			nz = 0.0f;
			//		}
			//		/*90����180 OK*/
			//		if (ANGLE_90 <= mRot.z && mRot.z <= ANGLE_180){
			//			nx = 0.0f;
			//			ny = -NORMAL_MAX;
			//			nz = 0.0f;
			//		}
			//		/*180����270 OK*/
			//		if (ANGLE_180 <= mRot.z && mRot.z <= ANGLE_270){
			//			nx = 0.0f;
			//			ny = -NORMAL_MAX;
			//			nz = 0.0f;
			//		}
			//		/*270����360*/
			//		if (ANGLE_270 <= mRot.z && mRot.z <= ANGLE_360){
			//			nx = 0.0f;
			//			ny = NORMAL_MAX;
			//			nz = 0.0f;
			//		}
			//		SetNormal(nx, ny, nz);

			//
		}
	};

	CSpark mSpark[EXP_ARRAY];
	bool mEnabled;
	int mCount;
public:
	
	CExplosion();


	/*����������
	rot = ��]�l
	m44 = �e�̃}�g���b�N�X
	*/
	void Init(CTexture *tex, float x, float y, STexVer texVer);
	/*�ݒ肳��Ă���ꍇ*/
	void Init();
	/*�X�V����*/
	void Update();
	/*�`��*/
	void Render();
	/*�A�j���[�V�����Z�b�g*/
	void SetAnima(int size, float width);
	/*�A�j���[�V�������I����*/
	void StartAnima(float speed, CVector3 pos);
	/*�A�j���[�V�������I�t��*/
	void DisableAnima();
	/*�������I���������f*/
	bool ExpEnd();
};


#endif