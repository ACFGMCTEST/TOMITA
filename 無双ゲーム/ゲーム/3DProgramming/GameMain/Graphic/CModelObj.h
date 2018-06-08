#ifndef CMODELOBJ_H
#define CMODELOBJ_H

#include "../Vector\CVector3.h"
#include "CTriangle.h"
#include <vector>

class CModelObj {
private:
	std::vector<CVector3> mVectorV;
	std::vector<CVector3> mVectorN;
	std::vector<CVector2> mVectorTex;
	std::vector<CTriangle> mTriangle;
	bool  mFlagTex;//テクスチャがあるか判断
public:
	float mLeft, mRight, mTop, mBottom;
	CModelObj() :mLeft(0.0f),mRight(0.0f),mTop(0.0f),mBottom(0.0f), mFlagTex(false){}
	void LoadFile(char* filename);//読み込み
	void Render();//描画
	void AddCollisionManager();//当たり判定追加

};

#endif
