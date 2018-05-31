#ifndef SLIME_H
#define SLIME_H
#include "../CEnemyBase.h"
/*当たり判定*/
#include "../../../../../Collision/ColType/CColSphere.h"
#include "../../../../../Collision/ColType/CColCapsule.h"

/*エネミーのクラス*/
class CSlime : public CEnemyBase{
private:
	static int mAllCount;//エネミーの数
	/*当たり判定*/
	CColCapsule *mpCaps;//カプセル胴体
	CColSphere  *mpSphere;//球体胴体
	
public:
	CSlime();
	~CSlime();
	/*初期化処理*/
	void Init(CModelX *model);

	/*更新*/
	void Update();
	/*描画*/
	void Render();
	/*索敵関数*/
	bool Search();
	/*球体判定*/
	void SphereCol(CColSphere *sphere, CColBase *y);
};
#endif
