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
#include <math.h>


/*カメラ初期ポジション*/
#define FIAST_POS CVector3(0.0f,3.0f,0.0f)


#define ANGLE_SPEED 3.0f//カメラスピード
#define SET_EYE	x, y+1.0f, z+10.0f //目線の設定
/*移動方向*/
#define MOVE_FORWARD CVector3(0.0f,0.0f,1.0f)
/*カメラの設定値 gluLookAtで使用
Eye = 視点の位置x,y,z;
pos = 視界の中心位置の参照点座標x,y,z
mUp = //視界の上方向のベクトルx,y,z
*/
#define CAMERA_LOOK mEye.x,mEye.y,mEye.z, mPos.x,mPos.y,mPos.z, mUp.x,mUp.y,mUp.z
/*あたり判定の設定値*/
#define OBB_POS CVector3(0.0f, 1.0f, 0.0f) 
#define OBB_SPHERE_SIZE 3.0f
/*カメラの位置*/
#define CAMERA_OFFSET CVector3(0.0f, 1.0f, 4.0f) //カメラ位置プレイヤーからの相対位置
//キャラ
#define CHARA_POS(pos)	CVector3(pos.x,	pos.y + 3.0f, pos.z-1.0f)

/*カメラマウス*/
#define ARRIVAL_TIME 0.1f//待ち時間
#define ANGLE_SPEED 3.0f//カメラスピード
#define CAMERA_IF_DIVIDE  50//カメラスピード調整用
#define CAMERA_DIVIDE  10//カメラスピード調整用


//カメラの上方向の初期化
CCamera::CCamera() : mUp(0.0f, 1.0f, 0.0f) ,mForward(FORWARD){
	//視点と注視点の設定
//	setPos(0.0f, 0.0f, 0.0f);
}

/*キャラクターにポジション移動する*/
void CCamera::CharaPos(){
	///PosUpdate(mRot, CHARA_POS(CSceneModel::Player().mPosition));
}

/*初期化処理*/
void CCamera::Init(){


	///*球の当たり判定設定*/
	//mpCBSphere = new CCollider(E_COL_SPHEPE);
	//mpCBSphere->mpParent = this;
	//mpCBSphere->SetShere(OBB_SPHERE_SIZE, OBB_POS, &mMatrix);
	///*当たり判定追加*/
	//CCollisionManager::GetInstance()->Add(CTask::E_TAG_CAMERA, mpCBSphere);
}
/* 視点と注視点の設定
void setPos(float x, float y, float z)
x:注視点のX座標 y:注視点のY座標 z:注視点のZ座標
規定の視点は注視点よりYへ+2、Zへ+4移動
*/
void CCamera::SetPos(float x, float y, float z) {
	//注視点の設定
	mPos = CVector3(x, y, z);
	//視点の設定
	mEye = CVector3(SET_EYE);
	//カメラ行列の設定
	gluLookAt(CAMERA_LOOK);
}
/*カメラ設定*/
void CCamera::MouseCamera(){
	/*カメラ設定マウス*/
	if (CMouse::GetInstance()->mPos.x != mSaveMousePos.x && mSaveMousePos.x  > CMouse::GetInstance()->mPos.x){//左
		mRot.y += (mSaveMousePos.x - CMouse::GetInstance()->mPos.x) / CAMERA_DIVIDE;

		CMouse::GetInstance()->SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//カーソルをウィンドウの中心にする

	}
	if (CMouse::GetInstance()->mPos.x != mSaveMousePos.x && mSaveMousePos.x < CMouse::GetInstance()->mPos.x){//右
		mRot.y += (mSaveMousePos.x - CMouse::GetInstance()->mPos.x) / CAMERA_DIVIDE;

		CMouse::GetInstance()->SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//カーソルをウィンドウの中心にする
	}

	/*中心からそれると真ん中に戻す処理*/
	if (CCollision2D::Collision2D(mColInitMouse, CMouse::GetInstance()->mRect)){
		/*時間が経つと真ん中に戻る*/
		if (CConvenient::Time(&mMouseInitCount, ARRIVAL_TIME) &&
			mSaveMousePos.x == CMouse::GetInstance()->mPos.x &&
			mSaveMousePos.y == CMouse::GetInstance()->mPos.y){ //0.1秒間動かなければ
			CMouse::GetInstance()->SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//カーソルをウィンドウの中心にする
			mMouseInitCount = 0;//0に戻す

		}
	}
	else
	{
		//CMouse::GetInstance()->SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//カーソルをウィンドウの中心にする
	}

	mSaveMousePos = CMouse::GetInstance()->mPos;//セーブする

}


/*ポジションを指定した場所にもっていく*/
void CCamera::PosUpdate(CVector3 rot, CVector3 pos){

	int mRotPercent = rot.y;
	//カメラ位置プレイヤーからの相対位置
	CVector3 cp = CAMERA_OFFSET;
	//カメラの回転行列
	CMatrix44 mat;
	//キャラクターの位置からカメラ位置を計算
	CVector3 SavePos = pos;
	/*３人称*/
	cp.z *= -1;
	mRotPercent %= ANGLE_360;
	CVector3 matrixRot = mRot;
	mRot.y = mRotPercent;//３６０にする
	mat.rotationX(matrixRot.x);
	mat.rotationY(matrixRot.y);
	//カメラを回転させる
	cp = cp * mat;
	cp += SavePos;
	//カメラの視点(eye)と注意点(pos)を設定
	
	//カメラ位置代入
	mPos = SavePos;

	//mMatrix.MatrixTransform(mRot, mPos);
	
	//カメラ視点代入
	mEye = cp;


}

/*矢印キーでカメラ移動*/
void CCamera::CharaUpdate(){
	/*カメラ設定*/
	if (CKey::push(VK_LEFT)) {//左
		mRot.y += ANGLE_SPEED;
	}
	if (CKey::push(VK_RIGHT)) {//右
		mRot.y -= ANGLE_SPEED;
	}

	/*ローテーションがマイナスの場合*/
	if (mRot.y < 0){
		mRot.y = ANGLE_360 + mRot.y;
	}

	mRot.y = abs(mRot.y);


}
/*回転値の参照*/
CVector3 CCamera::Rot(){
	return mRot;
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
	//gluLookAt(eye[0], eye[1], eye[2], pos[0], pos[1], pos[2], mUp.x, mUp.y, mUp.z);
	gluLookAt(CAMERA_LOOK);
	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix.f);
	mCameraInverse = mMatrix.getInverse();
	mCameraInverse.m[3][0] = mCameraInverse.m[3][1] = mCameraInverse.m[3][2] = 0.0f;

	/*キャラクタスイッチに使う*/
	CVector3 pos = CHARA_POS(CSceneModel::mpPlayer->mPosition);
	/*キャラクターに合わせる*/
	CharaUpdate();
	/*カメラの移動*/
	//Move(pos, CSceneModel::mpPlayer->mVelocity);
	PosUpdate(mRot, pos);
	

}

/*指定された部分に移動する
pos = 目的値
speed = 速さ
*/
void CCamera::Move(CVector3 pos, float speed){

	/*範囲内の場合移動しない*/
	if (pos.x - speed < mPos.x && mPos.x < pos.x + speed &&
		pos.y - speed < mPos.y && mPos.y < pos.y + speed &&
		pos.z - speed < mPos.z && mPos.z < pos.z + speed){
		return;
	}
	else{
		//進行方向初期化
		mForward = CVector3(FORWARD);
		//回転値計算
		CVector3 SaveRot = mForward.getRotationTowards(pos + mPos * -1.0f);

		CMatrix44 rot_y, matrix;

		//回転行列の作成
		rot_y.rotationY(SaveRot.y);

		mForward = mForward * rot_y;
		//移動させる
		mPos.y = pos.y;
		mPos += mForward * speed;

		PosUpdate(mRot, mPos);
	}
}