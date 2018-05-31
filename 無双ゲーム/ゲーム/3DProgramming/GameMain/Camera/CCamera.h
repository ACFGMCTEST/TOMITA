#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../Matrix/CMatrix44.h"
#include "../Vector/CVector3.h"
#include "../Task/CTask.h"
#include "../Graphic/CRectangle2.h"


/* カメラクラス（視点のクラス）
目の位置と目的の位置を保持し、
カメラ行列（ビュー変換行列）を設定する
*/
class CCamera : public CTask{
private:
	CMatrix44 mMatrix;//行列
	CRectangle2 mColInitMouse;//マウスの初期位置
	CVector3 mForward;//移動方向
	CVector3 mRot;//自分の方向
	CVector3 mPos;//ポジション
	CVector3 mEye;//視点
	CVector3 mUp;	//カメラの上方向
	CVector2 mSaveMousePos;//マウスのポジション
	float mMouseInitCount;//カメラの初期化時間
public:
	CMatrix44 mCameraInverse;

	//カメラの上方向の初期化
	CCamera();

	/* 視点と注視点の設定
	void setPos(float x, float y, float z)
	x:注視点のX座標 y:注視点のY座標 z:注視点のZ座標
	規定の視点は注視点よりYへ+2、Zへ+4移動
	*/
	void SetPos(float x, float y, float z);
	/*マウスカメラ設定*/
	void MouseCamera();
	/*初期化処理*/
	void Init();
	/* 更新処理
	キーにより視点を変更する
	J：左前から　K：前面から　L：右前から
	U：左後ろから　I：後ろから　O：右後ろから
	*/
	void Update();
	/*矢印キーでカメラ移動*/
	void CharaUpdate();
	/*ポジションを指定した場所にもっていく*/
	void PosUpdate(CVector3 rot, CVector3 pos);
	/*指定された部分に移動する
	pos = 目的値
	speed = 速さ
	*/
	void Move(CVector3 pos, float speed);
	
	/*回転値の参照*/
	CVector3 Rot();
	

	/*キャラクターにポジション移動する*/
	void CharaPos();
};

//カメラクラスのインスタンス
extern CCamera MainCamera;


#endif