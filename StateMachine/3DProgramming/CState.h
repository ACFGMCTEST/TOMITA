#ifndef CSTATE_H
#define CSTATE_H

#include "CCollider3.h"
#include "GameMain\Graphic\CModelX.h"

class CModelState;

//�e��Ԃ̋��������N���X�̊��N���X
class CState {
public:
	virtual ~CState() {}

	virtual void Enter(CModelState*) = 0;	//�ŏ���1��
	virtual void Execute(CModelState*) = 0;	//���s��
	virtual void Exit(CModelState*) = 0;	//�I����1��
	virtual bool Collision(CCollider3*, CCollider3*)=0;
};

//�C���X�^���X������N���X�̊��N���X
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
			mpState->Exit(this);	//�I����1��
		mpState = state;		//��ԕύX
		mpState->Enter(this);	//�ŏ���1��
	}

	void Update() {
		mpState->Execute(this);	//���s��
	}

	void Update(CMatrix44 &m) {
		CModelXS::Update(m);
	}

	bool Collision(CCollider3 *m, CCollider3 *y) {
		return mpState->Collision(m, y);
	}
};

//�ҋ@
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
//����
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

//�C���X�^���X������N���X
class CStatePlayer : public CModelState {
public:
	CStatePlayer() {}
	CStatePlayer(CModelX *m) {
		Init(m);
		//�����X�e�[�^�X�̓v���C���[�ҋ@���[�V����
		ChangeState(CStatePlayerIdle::Instance());
		//�J�v�Z���@�L�����N�^�S��
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
