#ifndef STATE_SLIME_JUMP_H
#define STATE_SLIME_JUMP_H

#include "../../../../../../../StateMachine/CStateBase.h"

/*プレイヤーの現在の状態(攻撃)クラス*/
class CSlimeJump : public CStateBase
{
private:
	float mPrevPosY;//前のポジション
	bool mFlagFall;//落下中にフラグだ立つ
public:
	CSlimeJump();
	~CSlimeJump();
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