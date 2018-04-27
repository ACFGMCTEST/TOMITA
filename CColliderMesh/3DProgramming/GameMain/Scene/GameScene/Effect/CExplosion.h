//冨田健斗
#ifndef EXPLOISON_HPP
#define EXPLOISON_HPP
#include <math.h>
#include "../../../Graphic/CRectangle.h"
#include "../../../../Base/CBase.h"
#include "../../../../Define/Define.h"
#include "../../../Camera/CCamera.h"
#include "CEffect2D.h"

#include "../../../Vector/CVector2.h"

/*テクスチャのサイズ*/
#define TEX_EFFECT_SIZE 0,0,270,270
/*頂点設定*/
#define EFFECT_SIZE_V0 -3.5f, 0.0f, -3.5f
#define EFFECT_SIZE_V1 -3.5f, 0.0f, 0.0f 
#define EFFECT_SIZE_V2 0.0f, 0.0f, 0.0f 
#define EFFECT_SIZE_V3 0.0f, 0.0f, -3.5f
#define EXP_ARRAY 100
/*火花の頂点指定*/
#define SPACK_SIZE_V0 1.0f, 1.0f, 0.0f 
#define SPACK_SIZE_V1 1.0f, -1.0f, 0.0f 
#define SPACK_SIZE_V2 -1.0f, -1.0f, 0.0f 
#define SPACK_SIZE_V3 -1.0f, 1.0f, 0.0f
/*色指定*/
#define Orange_Color 1.0f,0.6f,0.0f,1.0f

/*ランダム関数値*/
#define RAND_INIT_NUM 0.9f
/*消える時間*/
#define LIFE_TIME 40.0f
/*進むスピード*/
#define VELOCITY 0.2f
/*法線の最大値*/
#define NORMAL_MAX 1.0f
#define NORMAL_HALF 0.5f

class CExplosion :public  CBase{
public:
	class  CSpark : public CEffect2D{
	private:
		/*初期ポジション保存*/
		CVector4 mSavePos;//初期のポジション保存
	public:
		CMatrix44 *mpMatrix;//マトリックス
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
		/*初期化処理*/
		void Init(CVector3 pos){
			mPos = CVector4(pos.x,pos.y,pos.x);
			mSavePos = CVector4(pos.x,pos.y,pos.z);
			
			/*ランダムに火花がはじける*/
			mPos.setRandomPositionSphere(RAND_INIT_NUM);
			mForward = CVector4(mPos.x, mPos.y, mPos.z);
		}


		/*更新処理*/
		void Update(){
			mPos = mPos + mForward * VELOCITY;
			/*ビルボード設定*/
			mpCamera = &MainCamera;
			mMatrix.identity();
			mMatrix.translate(mPos);
			///*初期のポジションの方向に向ける*/
			//CVector3 normal = VEC_FRONT;
			//CVector4 cameraPos = CVector4(mpCamera->pos[0], mpCamera->pos[1], mpCamera->pos[2]);
			//normal = mForward.getRotationTowards(cameraPos + mPos * -1.0f);
			//CVector3 
			//printf("%f,%f,%f\n", mForward.x, mForward.y, mForward.z);

			CMatrix44 rot;
			/*初期場所から回転値を出す*/
			mRot.z = CVector2::Angle(CVector2(mPos.x, mPos.y), CVector2(mSavePos.x, mSavePos.y));
			mRot.z = mRot.z;
			/*回転値が３６０度以上にしないようにする*/
			if (mRot.z >= ANGLE_360){
				mRot.z -= ANGLE_360;
			}
			////回転行列の作成
			rot.rotationZ(mRot.z);
			mMatrix = mMatrix * mpCamera->mCameraInverse * rot;

		//	/*法線の計算*/
		//	normal_y = mRot.z / ANGLE_180;
		//	/*画像が180以上の時*/
		//	if (mRot.z > ANGLE_180){
		//		normal_y =   -NORMAL_MAX +(normal_y - NORMAL_MAX);
		//	}
		///*法線の絶対値を0.5以下にする*/
		//	/*法線がマイナスの場合の場合*/
		//	if (-NORMAL_HALF < normal_y  && normal_y < 0){
		//		normal_y -= NORMAL_HALF;
		//	}
		//	/*法線がプラスの場合の場合*/
		//	if (0 < normal_y  && normal_y < NORMAL_HALF){
		//		normal_y += NORMAL_HALF;
		//	}
	/*法線計算　上の失敗したもの　惜しいとこまで行ったから参考にする*/
			float nx, ny, nz;//法線たち
			/*0から90 OK*/
			if (0 <= mRot.z && mRot.z <= ANGLE_90){
				nx = 0.0f;
				ny = NORMAL_MAX;
				nz = 0.0f;
			}
			/*90から180 OK*/
			if (ANGLE_90 <= mRot.z && mRot.z <= ANGLE_180){
				nx = 0.0f;
				ny = -NORMAL_MAX;
				nz = 0.0f;
			}
			/*180から270 OK*/
			if (ANGLE_180 <= mRot.z && mRot.z <= ANGLE_270){
				nx = 0.0f;
				ny = -NORMAL_MAX;
				nz = 0.0f;
			}
			/*270から360*/
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


	/*初期化処理
	rot = 回転値
	m44 = 親のマトリックス
	*/
	void Init(CVector3 pos, CVector3 rot);
	/*更新処理*/
	void Update();
	/*描画*/
	void Render();
	/*アニメーションをオンに*/
	void EnabledAnima();
	/*アニメーションをオフに*/
	void DisableAnima();

};


#endif