#ifndef STATE_PLAYER_SPECIAL_H
#define STATE_PLAYER_SPECIAL_H
#include "../../../Effect/CEffect2D.h"
#include "../../../Effect/CEffect3D.h"

#include "../../../../../../StateMachine/CStateBase.h"

/*プレイヤーの現在の状態(攻撃)クラス*/
class CPlayerSpecial : public CStateBase{
private:
	CEffect2D *mpEffect;//エフェクト
	CEffect3D *mpEffect3D;//３dのエフェクト
public:
	CPlayerSpecial();
	~CPlayerSpecial();
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