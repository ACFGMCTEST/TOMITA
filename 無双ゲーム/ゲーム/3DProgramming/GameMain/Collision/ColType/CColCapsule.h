#ifndef COL_CAPSULE_H
#define COL_CAPSULE_H
#include "CColBase.h"
#include "../CCollisionManager.h"
#include "../../Vector/CVector3.h"

class CColCapsule : public CColBase {
	void Update();
public:
	CVector3 mV[2];
	float mRadius;

	CColCapsule() : mRadius(0.0f) {
		mType = COL_CAPSULE;
		CCollisionManager::GetInstance()->Add(this);//‚ ‚½‚è”»’è’Ç‰Á
	}

	CColCapsule(CTask *parent, CVector3 v0, CVector3 v1, float radius, CMatrix44 *pcombinedMatrix);

	CColCapsule GetUpdate();

	void Render();

};


#endif
