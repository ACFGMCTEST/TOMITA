#ifndef BASE_H
#define BASE_H
#include "../GameMain/Vector/CVector4.h"
#include "../GameMain/Matrix/CMatrix44.h"
#include <cassert>
#include "../GameMain/Task/CTask.h"

/*３Dのベースになるクラス*/
class C3DBase : public CTask{
public:

	CVector3 mPos;
	CVector3 mRot;
	CMatrix44 mMatrix;
	CVector3 mNormal;
	CVector3 mForward;

	C3DBase *mpParent;

	C3DBase();

	void UpdateMatrix();


};

#endif