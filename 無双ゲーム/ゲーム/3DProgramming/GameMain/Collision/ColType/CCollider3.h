#ifndef CCOLLIDER3_H
#define CCOLLIDER3_H

#include "../Task/CTaskManager.h"
#include "../Vector/CVector3.h"
#include "../Matrix/CMatrix44.h"

/*
コライダ　第3世代
*/

class CCollider3 : public CTask {
public:
	enum EType {
		COL_TRIANGLE,	//三角形コライダ
		COL_CAPSULE		//カプセルコライダ
	};
	EType mType;
	CVector3 mAdjust;	//衝突応答　調整値
	CTask *mpParent;	//親のタスク
	CMatrix44 *mpCombinedMatrix;	//フレームの合成行列
	CCollider3() : mpParent(0), mpCombinedMatrix(0) {}
};

class CCollisionManager3 : public CTaskManager {
private:

	static CCollisionManager3 *mCollisionManager;
	CCollisionManager3();

public:

	static CCollisionManager3 *GetInstance(); //GetInstance
	~CCollisionManager3();

	void Add(CCollider3 *col);//あたり判定追加処理

	void Update();
};

//三角形コライダクラス
class CCollider3Triangle : public CCollider3 {
	//更新　頂点を合成行列で掛ける
	void Update();
public:
	CVector3 mV[3];

	CCollider3Triangle() {
		mType = COL_TRIANGLE;
		CCollisionManager3::GetInstance()->Add(this);//あたり判定追加
	}

	CCollider3Triangle(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2)
		: CCollider3Triangle()
	{
		mV[0] = v0;
		mV[1] = v1;
		mV[2] = v2;
	}
	//頂点を合成行列で掛けたコライダを取得する
	CCollider3Triangle GetUpdate();
};

class CCollider3Capsule : public CCollider3 {
	void Update();
public:
	CVector3 mV[2];
	float mRadius;

	CCollider3Capsule() : mRadius(0.0f) {
		mType = COL_CAPSULE;
		CCollisionManager3::GetInstance()->Add(this);//あたり判定追加
	}

	CCollider3Capsule(CTask *parent, CVector3 v0, CVector3 v1, float radius, CMatrix44 *pcombinedMatrix);

	CCollider3Capsule GetUpdate();

	void Render();

};


#endif
