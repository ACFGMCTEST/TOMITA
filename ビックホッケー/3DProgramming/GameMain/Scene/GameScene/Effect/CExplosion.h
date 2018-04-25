//�y�c���l
#ifndef EXPLOISON_HPP
#define EXPLOISON_HPP
#include <math.h>
#include "../../../Graphic/CRectangle.h"
#include "../../../../Base/CBase.h"
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
#define LIFE_TIME 40.0f
/*�i�ރX�s�[�h*/
#define VELOCITY 0.2f
/*�@���̍ő�l*/
#define NORMAL_MAX 1.0f
#define NORMAL_HALF 0.5f

class CExplosion :public  CBase{
public:
	class  CSpark : public CEffect2D{
	private:
		/*�����|�W�V�����ۑ�*/
		CVector4 mSavePos;//�����̃|�W�V�����ۑ�
	public:
		CMatrix44 *mpMatrix;//�}�g���b�N�X
		CSpark(){
			CEffect2D::Init(CEffect2D::E_SPARK);
		}
		/*����������*/
		void Init(CVector3 pos){
			mPos = CVector4(pos.x,pos.y,pos.x);
			mSavePos = CVector4(pos.x,pos.y,pos.z);
			
			/*�����_���ɉΉԂ��͂�����*/
			mPos.setRandomPositionSphere(RAND_INIT_NUM);
			mForward = CVector4(mPos.x, mPos.y, mPos.z);
		}


		/*�X�V����*/
		void Update(){
			mPos = mPos + mForward * VELOCITY;
			/*�r���{�[�h�ݒ�*/
			mpCamera = &MainCamera;
			mMatrix.identity();
			mMatrix.translate(mPos);
			
			CMatrix44 rot;
			/*�����ꏊ�����]�l���o��*/
			mRot.z = CVector2::Angle(CVector2(mPos.x, mPos.y), CVector2(mSavePos.x, mSavePos.y));
			mRot.z = mRot.z;
			/*��]�l���R�U�O�x�ȏ�ɂ��Ȃ��悤�ɂ���*/
			if (mRot.z >= ANGLE_360){
				mRot.z -= ANGLE_360;
			}
			////��]�s��̍쐬
			rot.rotationZ(mRot.z);
			mMatrix = mMatrix * mpCamera->mCameraInverse * rot;

	/*�@���v�Z�@��̎��s�������́@�ɂ����Ƃ��܂ōs��������Q�l�ɂ���*/
			float nx, ny, nz;//�@������
			/*0����90 OK*/
			if (0 <= mRot.z && mRot.z <= ANGLE_90){
				nx = 0.0f;
				ny = NORMAL_MAX;
				nz = 0.0f;
			}
			/*90����180 OK*/
			if (ANGLE_90 <= mRot.z && mRot.z <= ANGLE_180){
				nx = 0.0f;
				ny = -NORMAL_MAX;
				nz = 0.0f;
			}
			/*180����270 OK*/
			if (ANGLE_180 <= mRot.z && mRot.z <= ANGLE_270){
				nx = 0.0f;
				ny = -NORMAL_MAX;
				nz = 0.0f;
			}
			/*270����360*/
			if (ANGLE_270 <= mRot.z && mRot.z <= ANGLE_360){
				nx = 0.0f;
				ny = NORMAL_MAX;
				nz = 0.0f;
			}
			SetNormal(nx, ny, nz);

		}
		
	};

	CSpark mSpark[EXP_ARRAY];

	bool mEnabled;
	int mCount;

	CExplosion();


	/*����������
	rot = ��]�l
	m44 = �e�̃}�g���b�N�X
	*/
	void Init(CVector3 pos, CVector3 rot);
	/*�X�V����*/
	void Update();
	/*�`��*/
	void Render();
	/*�A�j���[�V�������I����*/
	void EnabledAnima();
	/*�A�j���[�V�������I�t��*/
	void DisableAnima();

};


#endif