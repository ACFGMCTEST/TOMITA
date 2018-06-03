#ifndef STATE_PLAYER_ATTACK_H
#define STATE_PLAYER_ATTACK_H

#include "../../../../../../StateMachine/CStateBase.h"

/*プレイヤーの現在の状態(攻撃)クラス*/
class CPlayerAttack : public CStateBase{
private:
	float mAnimaSpeed;//アニメーションスピード
	float mTimeCount;//時間計測用
	/*攻撃の移動速さ調整*/
	void AttackSpeed();
public:
	CPlayerAttack();
	~CPlayerAttack();
	/*初めに呼び出し*/
	void Start();
	/*更新処理*/
	void Update();
	//遷移時の処理
	// isNextをfalseに戻す処理はここで行うとよい
	void OnChangeEvent();
	//変更する関数
	void ChangeState();


};

#endif