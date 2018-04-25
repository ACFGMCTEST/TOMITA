#ifndef BASE_H
#define BASE_H
#include "../GameMain/Vector/CVector4.h"
#include "../GameMain/Matrix/CMatrix44.h"
#include <cassert>
#include "../GameMain/Task/CTask.h"
/*ƒ^ƒ“ƒN‚ÌHP*/
#define HP_TANK 2.5f
/*‰×•¨‚ÌHP*/
#define HP_BAGGAGE 2.0f


class CBase : public CTask{
public:

	CVector4 mPos;
	CVector4 mRot;
	CMatrix44 mMatrix;
	CVector4 mNormal;
	CVector4 mForward;

	CBase *mpParent;

	CBase();

	void UpdateMatrix();

	void BaseInit();

	virtual void Update(){};
	virtual void Render(){};
	
};

#endif