#ifndef CCOLLIDERBOX_H
#define CCOLLIDERBOX_H
#include "../Task/CTask.h"
//#include "CCollision.h"
#include "ColType/COBB.h"
#include "ColType/CColSphere.h"

/*当たり判定クラス
eColTagを指定し形を決めている
*/
class CCollider :public CTask
{
private:
	/*当たり判定*/
	CVector3 *mpPos;//ポジション同期用

	/*当たり判定(ボックス用)*/
	CVector3 mParentNextPos;//ボックスの親からの位置
public:
	/*当たり判定　ボックス*/
	COBB mObb;
	/*当たり判定 球*/
	CColSphere mColSphere;

	//フレームの合成行列
	CMatrix44 *mpCombinedMatrix;

	CCollider() : mpCombinedMatrix(0) {}

	CCollider(CTask::E_COL_TAG tag) : mpCombinedMatrix(0) {
			eColTag = tag;
	}

	//OBBのボックスパラメータ設定
	void SetBoxOBB(CVector3 &center, float length[], CMatrix44 *m);

	/*球のパラメータ設定*/
	void SetShere(float radius, CVector3 pos, CMatrix44 *m);

	/*壁のパラメーター設定 壁の向きとポジション*/
	void SetWall(CVector3 normal, CVector3 *pos);

	/*サイズアップ*/
	void SizeUP(float f);

	/*Obbを回転させる*/
	void SetObbRot(const CVector3 rot);
	/*Obbを大きくさせる*/
	void SetObbSize(float length[]);

	/*色設定*/
	void SetColor(float cr, float cg, float cb, float ca);
	void Update();
	void Render();
	void Render(COBB *obb);
};

class CCollider2 : public CCollider
{
private:

protected:
	/*当たり判定(ボックス用)*/
	CVector3 mPositionFromParent;//ボックスの親からの位置
	//親からの位置の行列
	CMatrix44 mMatrixFromParent;
	//ワールド座標変換行列
	CMatrix44 mMatrix;
public:
	//線分01、三角形012、OBB012 カプセル01
	CVector3 mV[2][3];
	//半径0、軸の長さ012
	float mF[3];

	//フレームの合成行列
	CMatrix44 *mpCombinedMatrix;


	CCollider2() {}
	CCollider2(CTask::E_COL_TAG tag) : mpCombinedMatrix(0) {
		eColTag = tag;
	}

	void Update() {
		if (mpCombinedMatrix) {
			mMatrix = mMatrixFromParent * *mpCombinedMatrix;
		}
	}

	virtual void Render() {};

};


class CCollider3 : public CTask {
public:
	enum EType {
		COL_TRIANGLE,
		COL_CAPSULE
	};
	EType mType;
	CVector3 mAdjust;
	CTask *mpParent;
	CMatrix44 *mpCombinedMatrix;
	CCollider3() : mpParent(0), mpCombinedMatrix(0) {}
	bool Collision(CCollider3 *col);
};

class CCollider3Triangle : public CCollider3 {
public:
	CVector3 mV[3];

	CCollider3Triangle() {
		mType = COL_TRIANGLE;
	}

	CCollider3Triangle(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2) {
		mV[0] = v0;
		mV[1] = v1;
		mV[2] = v2;
	}

	void Update();

	CCollider3Triangle GetUpdate();
};

class CCollider3Capsule : public CCollider3 {
public:
	CVector3 mV[2];
	float mRadius;

	CCollider3Capsule() : mRadius(0.0f) {
		mType = COL_CAPSULE;
	}

	CCollider3Capsule(const CVector3 &p0, const CVector3 &p1, const float r) {
		mV[0] = p0;
		mV[1] = p1;
		mRadius = r;
	}

	void Update();

	CCollider3Capsule GetUpdate();

	void Init(CTask *parent, CVector3 v0, CVector3 v1, float radius, CMatrix44 *pcombinedMatrix);

	void Render();

};


#endif
