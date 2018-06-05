#ifndef STATE_SLIME_DAMAGE_H
#define STATE_SLIME_DAMAGE_H

#include "../../../../../../../StateMachine/CStateBase.h"

/*プレイヤーの現在の状態(ダメージ)クラス*/
class CSlimeDamage : public CStateBase
{
private:
	float mCount;//カウント
public:
	CSlimeDamage();
	~CSlimeDamage();
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