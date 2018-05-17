#ifndef SLIME_H
#define SLIME_H
#include "../CEnemyBase.h"

/*エネミーのクラス*/
class CSlime : public CEnemyBase{
private:
	static int mAllCount;//エネミーの数
public:
	int mNumber;//自分の製造番号
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
};
#endif
