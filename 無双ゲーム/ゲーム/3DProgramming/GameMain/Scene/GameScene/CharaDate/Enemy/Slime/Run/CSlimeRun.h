#ifndef STATE_SLIME_RUN_H
#define STATE_SLIME_RUN_H

#include "../../../../../../../StateMachine/CStateBase.h"

/*プレイヤーの現在の状態(走る)クラス*/
class CSlimeRun : public CStateBase
{
private:
	void Move();//
public:
	CSlimeRun();
	~CSlimeRun();
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