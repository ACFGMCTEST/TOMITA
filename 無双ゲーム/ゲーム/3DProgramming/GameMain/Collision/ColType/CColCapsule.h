#ifndef COL_CAPSULE_H
#define COL_CAPSULE_H
#include "CColBase.h"
#include "../CCollisionManager.h"
#include "../../Vector/CVector3.h"

class CColCapsule : public CColBase {
private:
	/*更新*/
	void Update();
public:
	CVector3 mV[2];
	float mRadius;
	/*コンストラクタ*/
	CColCapsule(){};
	/*コンストラクタ　引数:当たり判定追加しないか判断*/
	CColCapsule(bool addFlag);
	/*パラメータ設定*/
	CColCapsule(CTask *parent, CVector3 v0, CVector3 v1, float radius, CMatrix44 *pcombinedMatrix);
	/*更新処理呼び出し*/
	CColCapsule GetUpdate();
	/*描画処理*/
	void Render();

};


#endif
