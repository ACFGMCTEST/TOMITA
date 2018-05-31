#ifndef STATE_PLAYER_DAMAGE_H
#define STATE_PLAYER_DAMAGE_H

#include "../../../../../../../StateMachine/CStateBase.h"

/*プレイヤーの現在の状態(ダメージ)クラス*/
class CStatePlayerDamage : public CStateBase
{
private:
public:
	CStatePlayerDamage();
	~CStatePlayerDamage();
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