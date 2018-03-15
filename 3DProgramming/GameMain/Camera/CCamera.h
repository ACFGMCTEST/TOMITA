#pragma once
#include "../Matrix/CMatrix44.h"
#include "../Vector/CVector3.h"
#include "../Collision/CCollider.h"
#include "../Task/CTask.h"

/* カメラクラス（視点のクラス）
目の位置と目的の位置を保持し、
カメラ行列（ビュー変換行列）を設定する
*/
class CCamera : public CTask{
private:
	CVector3 mRot;//自分の方向
	CMatrix44 mMatrix;//行列
public:
	enum E_XYZ
	{
		E_X,
		E_Y,
		E_Z,
		E_ARRAY
	};
	//float pos[E_ARRAY];	//注視点 [0]:X座標 [1]:Y座標 [2]:Z座標
	//float eye[E_ARRAY];	//視点 [0]:X座標 [1]:Y座標 [2]:Z座標

	CVector3 mPos;//ポジション
	CVector3 mEye;//視点

	CVector3 mUp;	//カメラの上方向
	CMatrix44 mCameraMatrix;
	CMatrix44 mCameraInverse;
	CCollider *mpCBSphere;//当たり判定球体

	//カメラの上方向の初期化
	CCamera();

	/* 視点と注視点の設定
	void setPos(float x, float y, float z)
	x:注視点のX座標 y:注視点のY座標 z:注視点のZ座標
	規定の視点は注視点よりYへ+2、Zへ+4移動
	*/
	void SetPos(float x, float y, float z);

	/*初期化処理*/
	void Init();
	/* 更新処理
	キーにより視点を変更する
	J：左前から　K：前面から　L：右前から
	U：左後ろから　I：後ろから　O：右後ろから
	*/
	void Update();

	void Update(CVector3 eye, CVector3 pos, CVector3 up);
	/*指定された部分に移動する true で移動完了*/
	bool CameraMove(CVector3 pos);
	/*当たり判定戻す*/
	void CCamera::Collision(const COBB &box);
	
};

//カメラクラスのインスタンス
extern CCamera MainCamera;