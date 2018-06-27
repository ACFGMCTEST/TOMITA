#ifndef STATE_PLAYER_DIED_H
#define STATE_PLAYER_DIED_H

#include "../../../../../../StateMachine/CStateBase.h"


/*プレイヤーの現在の状態(死亡)クラス*/
class CPlayerDied : public CStateBase
{
private:
public:
	CPlayerDied();
	~CPlayerDied();
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