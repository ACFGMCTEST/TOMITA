/*
担当者 冨田健斗

エネミーのクラス
*/

#ifndef CXCHARENEMY
#define CXCHARENEMY

#include "CXCharPlayer.h"
#include "../Puck/CXPuck.h"

class CXCharEnemy : public CXCharPlayer{
private:
	float mRotPuckTime;//パックの方向に回転するタイミング時間計測用
	
public:
	CCollider *mpCBAttackBox; //攻撃に移行する範囲設定
	CCollider *mpCBAttackInitBox; //攻撃の準備に移行する範囲設定
	static int mEnemyCountMax;//現在の最大値

	/*AIの回転判断用*/
	enum E_AIROT_STATE{
		E_ROT_FAST_POS,
		E_ROT_PUCK,
		E_ROT_GOAL,
	};
	E_AIROT_STATE eAIRotState;
	/*E_AIROT_STATEのステータス管理*/
	void AIRotStateUpdate();
	CXCharEnemy();

	void Init(CModelX *model);
	/*あたり判定初期化*/
	void ColInit();

	void AIMove();/*AIの動き関数*/
	void Update();/*更新*/
	/*攻撃準備 当たり判定部分で呼ぶ*/
	void AttackInit();
	/*攻撃*/
	void Attack(CCollider &col);
	/*ゴールに打つ方向を決める関数*/
	CVector3 GoalShot();
	/*ジャンプフラグ*/
	void ColEnabledJump();

};
#endif
