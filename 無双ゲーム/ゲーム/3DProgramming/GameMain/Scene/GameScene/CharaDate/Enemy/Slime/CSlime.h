#ifndef SLIME_H
#define SLIME_H
#include "../CEnemyBase.h"
/*当たり判定*/
#include "../../../../../Collision/ColType/CColSphere.h"
#include "../../../../../Collision/ColType/CColCapsule.h"

/*エネミーのクラス*/
class CSlime : public CEnemyBase{
protected:
	/*当たり判定*/
	CColCapsule * mpCaps;//カプセル胴体
	CColSphere  *mpSphere;//球体胴体
private:
	static int mAllCount;//エネミーの数
public:
	enum E_STATE {
		E_IDLING,		//立ち
		E_RUN,			//走る
		E_DAMAGE,		//ダメージ
		E_ATTACK,		//アタック
		E_STATE_ARRAY//ステータスの上限
	};

	CSlime();
	~CSlime();
	/*削除*/
	void Delete();
	/*初期化処理*/
	void Init(CModelX *model);

	/*更新*/
	void Update();
	/*描画*/
	void Render();
	/*索敵関数*/
	bool Search();
	/*攻撃範囲*/
	bool AttackRange();
	/*球体判定*/
	void SphereCol(CColSphere *sphere, CColBase *y);
};
#endif
