#include "Windows.h"
#include "glut.h"
#include "CCamera.h"

//カメラの上方向の初期化
CCamera::CCamera() : mUp(0.0f, 1.0f, 0.0f) {
	//視点と注視点の設定
//	setPos(0.0f, 0.0f, 0.0f);
}

/*初期化処理*/
void CCamera::Init(){
	for (int i = 0; i < E_ARRAY; i++)
	{
		pos[i] = 0.0f;
		eye[i] = 0.0f;
	}
}
/* 視点と注視点の設定
void setPos(float x, float y, float z)
x:注視点のX座標 y:注視点のY座標 z:注視点のZ座標
規定の視点は注視点よりYへ+2、Zへ+4移動
*/
void CCamera::SetPos(float x, float y, float z) {
	//注視点の設定
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	//視点の設定
	eye[0] = pos[0];
	eye[1] = pos[1] + 1.0f;
	eye[2] = pos[2] + 10.0f;
	//カメラ行列の設定
	gluLookAt(eye[0], eye[1], eye[2], pos[0], pos[1], pos[2], 0.0f, 1.0f, 0.0f);
}

/* 更新処理
キーにより視点を変更する
J：左前から　K：前面から　L：右前から
U：左後ろから　I：後ろから　O：右後ろから
*/
void CCamera::Update() {
	//行列のモードをモデルビューにする
	glMatrixMode(GL_MODELVIEW);
	//モデルビューの行列を単位行列にする
	glLoadIdentity();
	//視点の設定
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
