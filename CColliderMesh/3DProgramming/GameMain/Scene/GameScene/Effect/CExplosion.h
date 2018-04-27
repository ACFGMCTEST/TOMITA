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
			//CVector3 v0(EFFECT_SIZE_V0);
			//CVector3 v1(EFFECT_SIZE_V1);
			//CVector3 v2(EFFECT_SIZE_V2);
			//CVector3 v3(EFFECT_SIZE_V3);

			//mRect.SetVertex(v0, v1, v2, v3);
			//mRect.SetDiffuse(WHITE_COLOR);
			//mRect.SetNormal(0.0f, 1.0f, 0.0f);
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
			///*�����̃|�W�V�����̕����Ɍ�����*/
			//CVector3 normal = VEC_FRONT;
			//CVector4 cameraPos = CVector4(mpCamera->pos[0], mpCamera->pos[1], mpCamera->pos[2]);
			//normal = mForward.getRotationTowards(cameraPos + mPos * -1.0f);
			//CVector3 
			//printf("%f,%f,%f\n", mForward.x, mForward.y, mForward.z);

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

		//	/*�@���̌v�Z*/
		//	normal_y = mRot.z / ANGLE_180;
		//	/*�摜��180�ȏ�̎�*/
		//	if (mRot.z > ANGLE_180){
		//		normal_y =   -NORMAL_MAX +(normal_y - NORMAL_MAX);
		//	}
		///*�@���̐�Βl��0.5�ȉ��ɂ���*/
		//	/*�@�����}�C�i�X�̏ꍇ�̏ꍇ*/
		//	if (-NORMAL_HALF < normal_y  && normal_y < 0){
		//		normal_y -= NORMAL_HALF;
		//	}
		//	/*�@�����v���X�̏ꍇ�̏ꍇ*/
		//	if (0 < normal_y  && normal_y < NORMAL_HALF){
		//		normal_y += NORMAL_HALF;
		//	}
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