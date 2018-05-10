#include "CState.h"
#include "GameMain\Key\CKey.h"

CStatePlayerIdle* CStatePlayerIdle::Instance() {
	static CStatePlayerIdle instance;
	return &instance;
}

void CStatePlayerIdle::Enter(CModelState *m) {
	CStatePlayer *p = dynamic_cast<CStatePlayer*>(m);
	p->ChangeAnimation(CTask::E_IDLE, true, ANIMA_SPEED);
}

void CStatePlayerIdle::Execute(CModelState *m) {
	CStatePlayer *p = dynamic_cast<CStatePlayer*>(m);
	CMatrix44 rot_y, pos;
	//回転行列の作成
	rot_y.rotationY(p->mRotation.y);

	//移動行列を計算する
	pos.translate(p->mPosition);
	//回転移動行列を求める
	p->mMatrix = pos * rot_y;

	//頂点データの更新
	m->Update(p->mMatrix);

	if (CKey::push('A')){//左に移動
		p->ChangeState(CStatePlayerRun::Instance());
	}
	else if (CKey::push('D')){//右に移動
		p->ChangeState(CStatePlayerRun::Instance());
	}
	else if (CKey::push('W')){//前に移動
		p->ChangeState(CStatePlayerRun::Instance());
	}
	else if (CKey::push('S')){
		p->ChangeState(CStatePlayerRun::Instance());
	}

}

void CStatePlayerIdle::Exit(CModelState *m) {

}

bool CStatePlayerIdle::Collision(CCollider3 *m, CCollider3 *y) {

	return false;
}

// Run ******************************************************************

CStatePlayerRun* CStatePlayerRun::Instance() {
	static CStatePlayerRun instance;
	return &instance;
}

void CStatePlayerRun::Enter(CModelState *m) {
	CStatePlayer *p = dynamic_cast<CStatePlayer*>(m);
	p->ChangeAnimation(CTask::E_RUN, true, ANIMA_SPEED_RUN);
}

void CStatePlayerRun::Execute(CModelState *m) {
	CStatePlayer *p = dynamic_cast<CStatePlayer*>(m);
	CMatrix44 rot_y, pos;
	//回転行列の作成
	rot_y.rotationY(p->mRotation.y);

	//移動行列を計算する
	pos.translate(p->mPosition);
	//回転移動行列を求める
	p->mMatrix = pos * rot_y;

	//頂点データの更新
	m->Update(p->mMatrix);

	if (CKey::push('A')){//左に移動
	}
	else if (CKey::push('D')){//右に移動
	}
	else if (CKey::push('W')){//前に移動
	}
	else if (CKey::push('S')){
	}
	else {
		p->ChangeState(CStatePlayerIdle::Instance());
	}

}

void CStatePlayerRun::Exit(CModelState *m) {

}

bool CStatePlayerRun::Collision(CCollider3 *m, CCollider3 *y) {

	return false;
}


