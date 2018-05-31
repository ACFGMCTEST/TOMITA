#ifndef BASE_H
#define BASE_H
#include "../GameMain/Vector/CVector4.h"
#include "../GameMain/Matrix/CMatrix44.h"
#include <cassert>
#include "../GameMain/Task/CTask.h"

/*３Dのベースになるクラス*/
class C3DBase : public CTask{
public:

	C3DBase * mpParent;//親
	CMatrix44 mMatrix;//行列
	CVector3 mPos;//位置
	CVector3 mRot;//回転値
	CVector3 mNormal;//法線
	CVector3 mForward;//方向

	C3DBase();
	/*行列の更新*/
	void UpdateMatrix();


};

#endif