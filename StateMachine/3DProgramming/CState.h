#ifndef CSTATE_H
#define CSTATE_H

#include "CCollider3.h"
#include "GameMain\Graphic\CModelX.h"

class CModelState;

//各状態の具現化をするクラスの基底クラス
class CState {
public:
	virtual ~CState() {}

	virtual void Enter(CModelState*) = 0;	//最初に1回
	virtual void Execute(CModelState*) = 0;	//実行中
	virtual void Exit(CModelState*) = 0;	//終わりに1回
	virtual bool Collision(CCollider3*, CCollider3*)=0;
};

//インスタンス化するクラスの基底クラス
class CModelState : public CModelXS {
	CState *mpState;
public:
	CModelState() : mpState(0) {}
	~CModelState() {}

	CVector3 mPosition;
	CVector3 mRotation;
	CMatrix44 mMatrix;

	void ChangeState(CState *state) {
		if (mpState)
			mpState->Exit(this);	//終わりに1回
		mpState = state;		//状態変更
		mpState->Enter(this);	//最初に1回
	}

	void Update() {
		mpState->Execute(this);	//実行中
	}

	void Update(CMatrix44 &m) {
		CModelXS::Update(m);
	}

	bool Collision(CCollider3 *m, CCollider3 *y) {
		return mpState->Collision(m, y);
	}
};

//待機
class CStatePlayerIdle : public CState {
	CStatePlayerIdle(){}
public:
	~CStatePlayerIdle(){}
	static CStatePlayerIdle* Instance();
	void Enter(CModelState *m);
	void Execute(CModelState *m);
	void Exit(CModelState *m);
	bool Collision(CCollider3 *m, CCollider3 *y);
};
//走る
class CStatePlayerRun : public CState {
	CStatePlayerRun(){}
public:
	~CStatePlayerRun(){}
	static CStatePlayerRun* Instance();
	void Enter(CModelState *m);
	void Execute(CModelState *m);
	void Exit(CModelState *m);
	bool Collision(CCollider3 *m, CCollider3 *y);

};

//インスタンス化するクラス
class CStatePlayer : public CModelState {
public:
	CStatePlayer() {}
	CStatePlayer(CModelX *m) {
		Init(m);
		//初期ステータスはプレイヤー待機モーション
		ChangeState(CStatePlayerIdle::Instance());
		//カプセル　キャラクタ全体
		new CCollider3Capsule(this, CVector3(0.0f, 1.5f, 0.0f), CVector3(0.0f, -0.9f, 0.0f), 0.5f
			, &mpCombinedMatrix[m->FindFrame("metarig_hips")->mIndex]);
	}
	CStatePlayer(CModelX *m, CVector3 &pos)
		: CStatePlayer(m)
	{
		mPosition = pos;
	}
};

#endif
