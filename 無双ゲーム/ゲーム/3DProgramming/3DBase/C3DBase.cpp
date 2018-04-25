#include "C3DBase.h"


C3DBase::C3DBase() : mpParent(nullptr){
}

void C3DBase::UpdateMatrix(){
	CMatrix44 trans, roty, rotx,rotz;
	trans.translate(mPos);
	roty.rotationY(mRot.y);
	rotx.rotationX(mRot.x);
	rotz.rotationZ(mRot.z);

	if (mpParent){
		mMatrix = mpParent->mMatrix * trans * roty * rotx * rotz;
	}
	else{
		mMatrix = trans * roty *rotx * rotz;
	}
}