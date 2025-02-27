#ifndef STATE_PLAYER_IDLING_H
#define STATE_PLAYER_IDLING_H

#include "../../../../../../StateMachine/CStateBase.h"

/*プレイヤーの現在の状態(待機)クラス*/
class CPlayerIdling : public CStateBase
{
public:
	CPlayerIdling();
	~CPlayerIdling();
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