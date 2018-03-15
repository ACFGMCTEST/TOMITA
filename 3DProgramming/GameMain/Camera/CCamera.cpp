#include "Windows.h"
#include "glut.h"
#include "../Collision/CCollisionManager.h"
#include "CCamera.h"
#include <math.h>


#define SET_EYE	x, y+1.0f, z+10.0f //目線の設定

/*カメラの設定値 gluLookAtで使用
Eye = 視点の位置x,y,z;
pos = 視界の中心位置の参照点座標x,y,z
mUp = //視界の上方向のベクトルx,y,z
*/
#define CAMERA_LOOK mEye.x,mEye.y,mEye.z, mPos.x,mPos.y,mPos.z, mUp.x,mUp.y,mUp.z

/*あたり判定の設定値*/
#define OBB_POS CVector3(0.0f, 1.0f, 0.0f) 
#define OBB_SIZE new float[]{1.5f,0.5f, 1.5f} 
#define OBB_SPHERE_SIZE 1.0f

//カメラの上方向の初期化
CCamera::CCamera() : mUp(0.0f, 1.0f, 0.0f) {
	//視点と注視点の設定
//	setPos(0.0f, 0.0f, 0.0f);
}

/*初期化処理*/
void CCamera::Init(){
	/*for (int i = 0; i < E_ARRAY; i++)
	{
		pos[i] = 0.0f;
		eye[i] = 0.0f;
	}*/


	/*球の当たり判定設定*/
	mpCBSphere = new CCollider(E_COL_SPHEPE);
	mpCBSphere->mpParent = this;
	mpCBSphere->SetShere(OBB_SPHERE_SIZE, OBB_POS, &mMatrix);
	/*当たり判定追加*/
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_CAMERA, mpCBSphere);
}
/* 視点と注視点の設定
void setPos(float x, float y, float z)
x:注視点のX座標 y:注視点のY座標 z:注視点のZ座標
規定の視点は注視点よりYへ+2、Zへ+4移動
*/
void CCamera::SetPos(float x, float y, float z) {
	//注視点の設定
	/*pos[0] = x;
	pos[1] = y;
	pos[2] = z;*/
	mPos = CVector3(x, y, z);
	//視点の設定
	/*eye[0] = pos[0];
	eye[1] = pos[1] + 1.0f;
	eye[2] = pos[2] + 10.0f;*/
	mEye = CVector3(SET_EYE);
	//カメラ行列の設定
	//gluLookAt(eye[0], eye[1], eye[2], pos[0], pos[1], pos[2], 0.0f, 1.0f, 0.0f);
	gluLookAt(CAMERA_LOOK);
}

/* 更新処理
キーにより視点を変更する
J：左前から　K：前面から　L：右前から
U：左後ろから　I：後ろから　O：右後ろから
*/
void CCamera::Update() {
	mpCBSphere->mColSphere.mPos = mPos;
	//当たり判定更新
	mpCBSphere->Update();
	//行列のモードをモデルビューにする
	glMatrixMode(GL_MODELVIEW);
	//モデルビューの行列を単位行列にする
	glLoadIdentity();
	//視点の設定
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
//	//行列のモードをモデルビューにする
//	glMatrixMode(GL_MODELVIEW);
//	//モデルビューの行列を単位行列にする
//	glLoadIdentity();
//	if (GetKeyState('J') & 0x8000) {
//		//Jキーの時、左前から見る
//		eye[0] -= 1.0f;
//		//		eye[1] = pos[1] + 2.0f;
//		//		eye[2] = pos[2] + 3.0f;
//	}
//	if (GetKeyState('K') & 0x8000) {
//		//Kキーの時、真正面から見る
//		//		eye[0] = pos[0];
//		//		eye[1] = pos[1] + 2.0f;
//		eye[2] += 1.0f;
//	}
//	if (GetKeyState('L') & 0x8000) {
//		//Lキーの時、右前から見る
//		eye[0] += 1.0f;
//		//		eye[1] = pos[1] + 2.0f;
//		//		eye[2] = pos[2] + 3.0f;
//	}
//	if (GetKeyState('I') & 0x8000) {
//		//Iキーの時、真後ろから見る
//		//eye[0] = pos[0];
//		//eye[1] = pos[1] + 2.0f;
//		eye[2] -= 1.0f;
//	}
//	//視点の設定
//	gluLookAt(eye[0], eye[1], eye[2], pos.x, pos.y, pos.z, up.x, up.y, up.z);
//}

/*当たり判定呼び出し
元の場所に戻すための関数
*/
void CCamera::Collision(const COBB &box) {


	CVector3 savePos = mpCBSphere->mColSphere.mPos;//計算用

	float lengthX = mPos.x - savePos.x;  //球とポジションの距離
	float lengthY = mPos.y - savePos.y;  //球とポジションの距離
	float lengthZ = mPos.z - savePos.z;  //球とポジションの距離

	//BoxのX軸方向を求める
	CVector3 vx = box.mMatrixRotation * VEC_RIGHT;
	//BoxのY軸方向を求める
	CVector3 vy = box.mMatrixRotation * VEC_TOP;
	//BoxのZ軸方向を求める
	CVector3 vz = box.mMatrixRotation * VEC_FRONT;
	//四角形から球へのベクトルを求める
	CVector3 vectorBS = savePos - box.mPos;
	//四角形から球へ、四角形のX軸に対する長さとの差を求める
	float dx = mpCBSphere->mColSphere.mRadius + box.mLength[0] - fabs(vx.Dot(vectorBS));
	//四角形から球へ、四角形のY軸に対する長さとの差を求める
	float dy = mpCBSphere->mColSphere.mRadius + box.mLength[1] - fabs(vy.Dot(vectorBS));
	//四角形から球へ、四角形のZ軸に対する長さとの差を求める
	float dz = mpCBSphere->mColSphere.mRadius + box.mLength[2] - fabs(vz.Dot(vectorBS));


	//衝突しているか判定する
	if (dx > 0.0f && dy > 0.0f && dz > 0.0f) {
		if (dx > dy) {
			if (dy > dz) {
				//Z軸で戻す
				if (vz.Dot(vectorBS) > 0.0f) {
					mPos = savePos + vz * dz;
					//跳ね返り方向設定
					/*mRefrectVec*/
				}
				else {
					mPos= savePos - vz * dz;
				}
			}
			else {
				//Y軸で戻す
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

				//Z軸で戻す
				if (vz.Dot(vectorBS) > 0.0f) {
					mPos = savePos + vz * dz;
				}
				else {
					mPos = savePos - vz * dz;
				}
			}
			else {

				//X軸で戻す
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

	/*当たり判定更新*/
	mpCBSphere->Update();

}
