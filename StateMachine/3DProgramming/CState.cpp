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
	//��]�s��̍쐬
	rot_y.rotationY(p->mRotation.y);

	//�ړ��s����v�Z����
	pos.translate(p->mPosition);
	//��]�ړ��s������߂�
	p->mMatrix = pos * rot_y;

	//���_�f�[�^�̍X�V
	m->Update(p->mMatrix);

	if (CKey::push('A')){//���Ɉړ�
		p->ChangeState(CStatePlayerRun::Instance());
	}
	else if (CKey::push('D')){//�E�Ɉړ�
		p->ChangeState(CStatePlayerRun::Instance());
	}
	else if (CKey::push('W')){//�O�Ɉړ�
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
	//��]�s��̍쐬
	rot_y.rotationY(p->mRotation.y);

	//�ړ��s����v�Z����
	pos.translate(p->mPosition);
	//��]�ړ��s������߂�
	p->mMatrix = pos * rot_y;

	//���_�f�[�^�̍X�V
	m->Update(p->mMatrix);

	if (CKey::push('A')){//���Ɉړ�
	}
	else if (CKey::push('D')){//�E�Ɉړ�
	}
	else if (CKey::push('W')){//�O�Ɉړ�
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


