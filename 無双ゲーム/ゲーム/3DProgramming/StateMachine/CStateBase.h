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
#ifndef STATE_BASE_H
#define STATE_BASE_H



#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include "../GameMain/Task/CTask.h"

/*ステータスのベースクラス*/
class CStateBase
{
protected:
	// 遷移するかどうか
	bool mFlagNext;
	// 遷移先の登録名
	std::string mNextRegisterName;
	// アップデートの処理の中で状態遷移の条件を満たした場合
	// isNextをtrueにし、
	// nextRegisterNameに遷移先の登録名を代入する
	/*属性の親 castして使う アクセス用*/
	CTask *mpParent;
	
public:
	std::string mName;//自分の名前

	/*コンストラクタ*/
	CStateBase();
	/*デストラクタ*/
	~CStateBase();

	// アップデートの前に1度だけコール
	virtual void Start() = 0;
	// アップデート
	virtual void Update() = 0;
	//状態切り替え関数
	virtual void ChangeState() = 0;

	//自分の名前と一致しているか判断
	bool Name(std::string s) { return s == mName; }

	// 遷移時の処理
	// isNextをfalseに戻す処理はここで行うとよい
	void OnChangeEvent();

	// 遷移するかどうかの取得
	bool IsNext()const;

	// 遷移先の登録名の取得
	std::string NextRegisterName();

	/*親設定する*/
	void SetParent(CTask *p);
};

#endif

