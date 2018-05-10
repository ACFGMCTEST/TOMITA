
#include "../Scene/GameScene/CharaDate/CSceneModel.h"
#include "../../GameMain/Scene/CSceneManager.h"
#include "CCollisionManager.h"
#include "CCollision.h"

/*回転を逆向きにする*/
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
	col->ePriority = (CTask::E_PRIORITY)tag;//当たり判定用の順番に

	CTaskManager::Add(col);
}



/*当たり判定フラグ*/
bool CCollisionManager::ColIf(CTask *Task_You, CTask *Task_I){
	CCollider *col_you, *col_I;
	col_you = dynamic_cast<CCollider*>(Task_You);
	col_I = dynamic_cast<CCollider*>(Task_I);
	/*アタリ判定判断(相手)*/
	switch (Task_You->eColTag)
	{
		/*ボックスの場合*/
	case CTask::E_COL_BOX:

		/*当たり判定判断(自分)*/
		switch (Task_I->eColTag)
		{
			/*ボックスの場合*/
		case CTask::E_COL_BOX:
			/*相手のボックスと自分のボックスを判断*/
			return (CCollision::CollisionOBB(col_you->mObb, col_I->mObb));
			break;
			/*球の場合*/
		case CTask::E_COL_SPHEPE:
			/*相手のボックスと自分の球を判断*/
			return (CCollision::CollSphereBox(col_I->mColSphere, col_you->mObb));
			break;
		}

		break;
		/*相手が球の場合*/
	case CTask::E_COL_SPHEPE:
		CColSphere *you = &col_you->mColSphere;
		/*当たり判定判断(自分)*/
		switch (Task_I->eColTag)
		{
			/*ボックスの場合*/
		case CTask::E_COL_BOX:
			return (CCollision::CollSphereBox(*you, col_I->mObb));
			break;
			/*球の場合*/
		case CTask::E_COL_SPHEPE:
			return CCollision::CollisionShpere(*you, col_I->mColSphere);
			break;
		};
		break;
	}


	return false;
}


/*更新2段目*/
void CCollisionManager::Update(CTask *t){
	CTask *task;
	task = mpRoot;
	/*探索処理*/
	while (task != 0)
	{
		/*同じもの以外*/
		if (t != task && t != 0 && task != 0){
			switch (t->eTag)
			{
			case CTask::E_TAG_PLAYER:
				t->mpParent->Collision((CCollider2*)t, (CCollider2*)task);//task何か,tプレイヤー
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

/*更新処理*/
void CCollisionManager::Update(){



	CTask *task;
	task = mpRoot;

	/*探索処理*/
	while (task != 0)
	{
		task->Update();
		task = task->mpNext;
	}

	task = mpRoot;

	/*探索処理*/
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


