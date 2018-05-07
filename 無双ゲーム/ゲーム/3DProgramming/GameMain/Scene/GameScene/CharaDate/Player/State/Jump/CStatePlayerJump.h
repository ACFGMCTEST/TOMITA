#ifndef STATE_PLAYER_JUMP_H
#define STATE_PLAYER_JUMP_H
#include "../CStatePlayerBase.h"

/*プレイヤーの現在の状態(攻撃)クラス*/
class CStatePlayerJump : public CStatePlayerBase
{
public:
	CStatePlayerJump();
	~CStatePlayerJump();
	/*初めに呼び出し*/
	void Start();
	/*更新処理*/
	void Update();
	//遷移時の処理
	// isNextをfalseに戻す処理はここで行うとよい
	void OnChangeEvent();
};

#endif