#ifndef STATE_PLAYER_BASE_H
#define STATE_PLAYER_BASE_H

#include "../../../../../../StateMachine/CStateBase.h"

/*プレイヤーステータスのベースクラス*/
class CStatePlayerBase : public CStateBase
{
public:
	/*キャラクターのステータス*/
	const std::string mStateAttack = "PlayerAttack";//攻撃
	const std::string mStateIdling = "PlayerIdling";//アイドル
	const std::string mStateRun    = "PlayerRun";	//走る
	const std::string mStateJump   = "PlayerJump";	//ジャンプ

};


#endif