//-------------------------------------------------
// 状態管理クラス
// 
// StateMachine : 状態の管理部分
// StateBase : 状態の基底クラス
// StateSwitch : 状態を切り替えるクラス
//--------------------------------------------------

// 北川メモ
// 自分が理解できる範囲ではStateSwitchが不要に思えるので省いてみました。
// StateMachineクラスからStateBaseの派生クラスを直接参照するようにしています。
// また、各ステートから遷移先を自由に決められるようにしています。


#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

#ifndef STATE_BASE_H
#define STATE_BASE_H

/*ステータスのベースクラス*/
class CStateBase
{
public:

	/*コンストラクタ*/
	CStateBase();

	// アップデートの前に1度だけコール
	virtual void Start() = 0;

	// アップデート
	virtual void Update() = 0;

	// 遷移時の処理
	// isNextをfalseに戻す処理はここで行うとよい
	virtual void OnChangeEvent() = 0;

	// 遷移するかどうかの取得
	bool IsNext()const;

	// 遷移先の登録名の取得
	std::string NextRegisterName();
protected:
	// 遷移するかどうか
	bool mFlagNext;
	// 遷移先の登録名
	std::string mNextRegisterName;
	// アップデートの処理の中で状態遷移の条件を満たした場合
	// isNextをtrueにし、
	// nextRegisterNameに遷移先の登録名を代入する
};

#endif

