#ifndef SLIME_H
#define SLIME_H
#include "../CEnemyBase.h"

/*エネミーのクラス*/
class CSlime : public CEnemyBase{
private:
public:
	CSlime();
	/*初期化処理*/
	void Init(CModelX *model);
	/*更新*/
	void Update();
	/*描画*/
	void Render();
};
#endif
