#ifndef STATE_PLAYER_ATTACK_H
#define STATE_PLAYER_ATTACK_H

#include "../../../../../../StateMachine/CStateBase.h"

/*プレイヤーの現在の状態(攻撃)クラス*/
class CPlayerAttack : public CStateBase{
private:
	float mAnimaSpeed;//アニメーションスピード
	float mTimeKey;//キー入力待ち
	bool mFlagChangeAnima;//アニメーションの動くの判断
	/*攻撃の移動速さ調整*/
	void AttackSpeed();
	/*攻撃モーションフレーム*/
	enum EAttackFrame {
		Attack1sta = 0,//攻撃一発目のはじめ
		Attack1end = 20,//攻撃一発目終了
		Attack2sta = 50,//攻撃２発目始まり
		Attack2end = 80,//攻撃２発目終わり
	};
	EAttackFrame eAttackFrame;
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