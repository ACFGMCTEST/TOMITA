#ifndef STATE_MACHIN_H
#define STATE_MACHIN_H

#include "CStateBase.h"


// 状態管理
class CStateMachine
{
private:
	std::unordered_map<std::string, std::shared_ptr<CStateBase>> stateMap;
	std::shared_ptr<CStateBase> nowState;
public:
	CStateMachine() : nowState(),stateMap()
	{

	}
	/*更新処理*/
	void Update();

	////// 登録する
	//void Register(const std::string& name, const std::shared_ptr<CStateBase> state);
	//// 登録する,親の設定
	void Register(const std::string& name, const std::shared_ptr<CStateBase> state, CTask *parent);

	// 最初から始める状態を設定
	void SetStartState(const std::string& registerName);

	// 登録したものを削除する
	void Deregistration(const std::string& registerName);

	// すべての登録を削除する
	void AllDeregistration();

	// ステート外から強制的に遷移を実行
	void ForceChange(const std::string& registerName);

	/*ステータスフラグ*/
	bool StateFlag(std::string s) {return nowState->mName == s; }


};
#endif 
