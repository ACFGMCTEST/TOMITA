#include "CColTriangle.h"
#include "../CCollisionManager.h"

/*コンストラクタ newする*/
CColTriangle::CColTriangle() {
	mType = COL_TRIANGLE;
	CCollisionManager::GetInstance()->Add(this);//あたり判定追加
}
/*コンストラクタ　頂点数代入*/
CColTriangle::CColTriangle(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2)
: CColTriangle()
{
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

/*更新*/
void CColTriangle::Update() {
	if (mpCombinedMatrix) {
		mV[0] = mV[0] * *mpCombinedMatrix;
		mV[1] = mV[1] * *mpCombinedMatrix;
		mV[2] = mV[2] * *mpCombinedMatrix;
	}
}

/*当たり判定をとるときのみ更新する*/
CColTriangle CColTriangle::GetUpdate() {
	CColTriangle ct = *this;
	ct.Update();
	return ct;
}

