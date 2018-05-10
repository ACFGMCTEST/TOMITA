#include "CBase.h"

void CBase::BaseInit(){
	mpParent = 0;
	mEnabled = true;
	mHp = HP_TANK;
	mColRot = 0.0f;

	mRadius = 0.0f;
	const_cast<ESTATE>(mState) = NORMAL;
	mNum = 0;
	mSumNum += 1;
	mNum += mSumNum;
}

CBase::CBase() :mState(NORMAL){
	BaseInit();
}

bool CBase::mFlagEnemyFight = false;
int CBase::mSumNum = 0;

void CBase::UpdateMatrix(){
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