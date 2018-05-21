#include "CColTriangle.h"
#include "../CCollisionManager.h"

int CColTriangle::mAllCount = 0;

/*コンストラクタ newする*/
CColTriangle::CColTriangle(bool addFlag) {

	mType = COL_TRIANGLE;
	/*追加するフラグが立つと追加する*/
	if (addFlag){
		CCollisionManager::GetInstance()->Add(this);//あたり判定追加
	}
}
/*デストラクタ*/
CColTriangle::~CColTriangle(){
	mAllCount--;
}


/*コンストラクタ　頂点数代入*/
CColTriangle::CColTriangle(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2) :
CColTriangle(true)
{
	mAllCount++;//カウントする
	mNumber = mAllCount;//自分の生成番号決める
	mPos = CVector3::TriangleCenter(v0, v1, v2);
	/*自分のポジションから当たり判定する*/

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

