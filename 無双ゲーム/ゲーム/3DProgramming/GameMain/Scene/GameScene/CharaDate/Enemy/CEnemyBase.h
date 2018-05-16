#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "../Player/CXCharPlayer.h"

/*エネミーのクラス*/
class CEnemyBase : public CXCharPlayer{
protected:
	/*ステータス管理*/
	std::unique_ptr<CStateMachine> mStateMachine;//ステータス管理
public:
	
	CEnemyBase();

	/*初期化処理*/
	void Init(CModelX *model);
	/*AIの動き関数*/
	void AIMove();
	/*更新*/
	void Update();
	/*攻撃準備 当たり判定部分で呼ぶ*/
	void AttackInit();

};
#endif
