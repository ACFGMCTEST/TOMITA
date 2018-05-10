
#include "../Scene/GameScene/CharaDate/CSceneModel.h"
#include "../../GameMain/Scene/CSceneManager.h"
#include "CCollisionManager.h"
#include "CCollision.h"

/*��]���t�����ɂ���*/
#define REVERSE_ROT(rot) CVector3(rot.x,rot.y +180,rot.z)

CCollisionManager* CCollisionManager::mCollisionManager = 0;

//GetInstance
CCollisionManager* CCollisionManager::GetInstance() {
	if (mCollisionManager == 0) {
		mCollisionManager = new CCollisionManager();
	}
	return mCollisionManager;
}


void CCollisionManager::Add(CTask::E_TAG tag, CCollider *col){
	col->eTag = tag;
	col->ePriority = (CTask::E_PRIORITY)tag;//�����蔻��p�̏��Ԃ�

	CTaskManager::Add(col);
}



/*�����蔻��t���O*/
bool CCollisionManager::ColIf(CTask *Task_You, CTask *Task_I){
	CCollider *col_you, *col_I;
	col_you = dynamic_cast<CCollider*>(Task_You);
	col_I = dynamic_cast<CCollider*>(Task_I);
	/*�A�^�����蔻�f(����)*/
	switch (Task_You->eColTag)
	{
		/*�{�b�N�X�̏ꍇ*/
	case CTask::E_COL_BOX:

		/*�����蔻�蔻�f(����)*/
		switch (Task_I->eColTag)
		{
			/*�{�b�N�X�̏ꍇ*/
		case CTask::E_COL_BOX:
			/*����̃{�b�N�X�Ǝ����̃{�b�N�X�𔻒f*/
			return (CCollision::CollisionOBB(col_you->mObb, col_I->mObb));
			break;
			/*���̏ꍇ*/
		case CTask::E_COL_SPHEPE:
			/*����̃{�b�N�X�Ǝ����̋��𔻒f*/
			return (CCollision::CollSphereBox(col_I->mColSphere, col_you->mObb));
			break;
		}

		break;
		/*���肪���̏ꍇ*/
	case CTask::E_COL_SPHEPE:
		CColSphere *you = &col_you->mColSphere;
		/*�����蔻�蔻�f(����)*/
		switch (Task_I->eColTag)
		{
			/*�{�b�N�X�̏ꍇ*/
		case CTask::E_COL_BOX:
			return (CCollision::CollSphereBox(*you, col_I->mObb));
			break;
			/*���̏ꍇ*/
		case CTask::E_COL_SPHEPE:
			return CCollision::CollisionShpere(*you, col_I->mColSphere);
			break;
		};
		break;
	}


	return false;
}


/*�X�V2�i��*/
void CCollisionManager::Update(CTask *t){
	CTask *task;
	task = mpRoot;
	/*�T������*/
	while (task != 0)
	{
		/*�������̈ȊO*/
		if (t != task && t != 0 && task != 0){
			switch (t->eTag)
			{
			case CTask::E_TAG_PLAYER:
				t->mpParent->Collision((CCollider2*)t, (CCollider2*)task);//task����,t�v���C���[
				break;
			case CTask::E_TAG_ENEMY:
			case CTask::E_TAG_ATTACK_INIT_RANGE:
			case CTask::E_TAG_ATTACK_RANGE:
			
				break;
			}
		}
		task = task->mpNext;
	}

}

/*�X�V����*/
void CCollisionManager::Update(){



	CTask *task;
	task = mpRoot;

	/*�T������*/
	while (task != 0)
	{
		task->Update();
		task = task->mpNext;
	}

	task = mpRoot;

	/*�T������*/
	while (task != 0)
	{
		if (task->eColTag != CTask::E_COL_TRIANGLE)
			Update(task);
		task = task->mpNext;
	}


#ifdef _DEBUG 
	//	AllRender();
#endif
}

CCollisionManager::CCollisionManager(){}


