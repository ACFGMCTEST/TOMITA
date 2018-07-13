#include "CStateMachine.h"
#include <assert.h>
/*更新*/
void CStateMachine::Update()
{

	nowState->Update();
	nowState->ChangeState();//状態切り替え

	if (nowState->IsNext())
	{
		// 遷移先の取得
		auto it = stateMap.find(nowState->NextRegisterName());

		// 遷移時の処理を実行(初期化処理)
		nowState->OnChangeEvent();
		// 見つからなかった場合、処理を終了
		if (it == stateMap.end()) return;

		// stateMapは「キー」が文字列、「値」がStateBaseのポインタの連想配列（map)
		// find関数は引数で指定したキーが存在するかを確認できる。
		// 存在する場合は、そのイテレータを返し、
		// 存在しない場合はend()という値のイテレータを返す。

		// mapのイテレータは
		// ->first で「キー」を
		// ->second で「値」を取得できる

		// mapで保持している次のステートのポインタをnowStateにうつす
		nowState = it->second;
		nowState->Start();
	}
}

//// 登録する
//void CStateMachine::Register(const std::string& name, const std::shared_ptr<CStateBase> state)
//{
//	stateMap.insert(std::make_pair(name, state));//マップに名前と属性を追加
//#ifdef _DEBUG
//	std::cout << "StateMachine : " << name << "を登録" << std::endl;//デバック用
//#endif
//}
//// 登録する,親の設定
void CStateMachine::Register(const std::string& name, const std::shared_ptr<CStateBase> state, CTask *parent){
	state->SetParent(parent);//親を設定する
	stateMap.insert(std::make_pair(name, state));//マップに名前と属性を追加
#ifdef _DEBUG
	std::cout << "StateMachine : " << name << "を登録" << std::endl;//デバック用
#endif
}

// 最初から始める状態を設定
void CStateMachine::SetStartState(const std::string& registerName)
{
	auto it = stateMap.find(registerName);
	if (it == stateMap.end()) return;
#ifdef _DEBUG
	std::cout << "StateMachine : " << it->first << "をスタート状態に設定" << std::endl;
#endif
	nowState = it->second;
	nowState->Start();

}

// 登録したものを削除する
void CStateMachine::Deregistration(const std::string& registerName)
{
	auto it = stateMap.find(registerName);
	if (it == stateMap.end()) return;
#ifdef _DEBUG
	std::cout << "StateMachine : " << it->first << "を登録を削除する" << std::endl;
#endif
	stateMap.erase(it);
}

// すべての登録を削除する
void CStateMachine::AllDeregistration()
{
#ifdef _DEBUG
	std::cout << "StateMachine : " << "すべての登録を削除する" << std::endl;
#endif
	/*サイズがあるとき*/
	if (stateMap.size() != 0) {stateMap.clear();}
}

// ステート外から強制的に遷移を実行
void CStateMachine::ForceChange(const std::string& registerName) {
	// 遷移時の処理を実行
	nowState->OnChangeEvent();

	// 遷移先の取得
	auto it = stateMap.find(registerName);
	// 見つからなかった場合、処理を終了
	if (it == stateMap.end()) return;

	nowState = it->second;
	nowState->Start();
}
