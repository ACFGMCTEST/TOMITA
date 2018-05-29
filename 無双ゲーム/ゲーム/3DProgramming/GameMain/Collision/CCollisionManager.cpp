
#include "../Scene/GameScene/CharaDate/CSceneModel.h"
#include "../../GameMain/Scene/CSceneManager.h"
#include "CCollisionManager.h"
#include "CCollision.h"
#include "ColType\CColCapsule.h"
#include "ColType\CColSphere.h"
/*コンストラクタ*/
CCollisionManager::CCollisionManager() {}
CCollisionManager* CCollisionManager::mCollisionManager = 0;

//GetInstance
CCollisionManager* CCollisionManager::GetInstance() {
	if (mCollisionManager == 0) {
		mCollisionManager = new CCollisionManager();
	}
	return mCollisionManager;
}
/*追加処理*/
void CCollisionManager::Add(CColBase *t){
	/*何も設定していないとき*/
	if (mpRoot == 0){
		/*頭の設定*/
		mpRoot = t;
		mpRoot->mpPrev = 0;
		mpRoot->mpNext = 0;
		/*尻尾の設定*/
		mpTail = 0;
	}
	/*2番目の処理*/
	else if (mpTail == 0){
		/*現在のものが小さい場合*/
		if (mpRoot->mType < t->mType){
			/*尻尾の設定*/
			mpTail = t;
			mpTail->mpPrev = mpRoot;
			mpTail->mpNext = 0;
			/*頭の設定*/
			mpRoot->mpPrev = 0;
			mpRoot->mpNext = mpTail;

		}
		/*現在のものが大きい場合*/
		else{
			/*尻尾の設定*/
			mpTail = mpRoot;
			mpTail->mpPrev = t;
			mpTail->mpNext = 0;
			/*頭の設定*/
			mpRoot = t;
			mpRoot->mpPrev = 0;
			mpRoot->mpNext = mpTail;
		}
	}
	/*3番目以上*/
	else if (mpRoot->mpNext != 0 && mpTail->mpPrev != 0){
		CTask temp;
		CTask *moveTask = &temp;//探すタスク
		moveTask->mpNext = mpRoot;

		/*追加する場所を探す*/
		while (moveTask != mpTail)
		{
			moveTask = moveTask->mpNext;


			/*最初*/
			if (mpRoot->mType > t->mType){
				/*追加するもの設定*/
				t->mpPrev = 0;
				t->mpNext = mpRoot;
				/*頭のタスク設定*/
				mpRoot = t;
				/*探すタスク設定*/
				moveTask->mpPrev = t;
				if (moveTask->mpNext == 0){
					mpTail = moveTask;
				}

				break;
			}
			/*最後*/
			else if (moveTask == mpTail){
				/*しっぽ設定*/
				t->mpPrev = mpTail;
				mpTail->mpNext = t;
				mpTail = t;
				mpTail->mpNext = 0;
				break;
			}
			/*中間*/
			else if (moveTask->mType <= t->mType &&
				t->mType <= moveTask->mpNext->mType){
				/*追加するもの設定*/
				t->mpNext = moveTask->mpNext;
				t->mpPrev = moveTask;
				/*外側のタスク設定*/
				moveTask->mpNext->mpPrev = t;
				moveTask->mpNext = t;

				break;
			}

		}
	}
	//CTaskManager::Add(col);
}

/*地形の当たり判定しない部分を決める*/
bool CCollisionManager::FlagMap(const CColBase &task,const CColBase &map){
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(task.mpParent);
	/*三角形のポリゴンの場合マップ*/
	if (map.mType == CTask::COL_TRIANGLE){
		/*マップでない方の位置から判定するマップのポリゴン数の幅を決める*/
		int taskNum;//プレイヤーの座標から番号を特定する
		int mapPrev;//
		int mapTail;
		/*if (){
			return true;
		}*/
		//printf("ポジション%f,%f,%f\n", pl->mPosition.x, pl->mPosition.y, pl->mPosition.z);
		//return false;
		//return true;
	}
	else{
		return true;
	}
}

/*更新処理*/
void CCollisionManager::Update(){

	CColBase *task;
	task = (CColBase*)mpRoot;

	/*探索処理*/
	while (task != 0)
	{
		//自身のコライダタイプを識別
		switch (task->mType) {
		case CColBase::COL_CAPSULE:
			//変化しないコライダは衝突判定しない
			if (task->mpCombinedMatrix) {
				//コライダをコピーして更新
				CColCapsule cc = (*(CColCapsule*)task).GetUpdate();
				//コライダを先頭から衝突判定していく
				CColBase *n = (CColBase*)mpRoot;
				while (n != NULL) {
					//親のタスクで衝突判定させる
					if (task->mpParent && task != n) {
						task->mpParent->Collision(&cc, n);
					}
					n = (CColBase*)n->mpNext;
				}
			}
			break;
		case CColBase::COL_BOX:
			break;
		case CColBase::COL_SPHEPE:
			//変化しないコライダは衝突判定しない
			if (task->mpCombinedMatrix) {
				//コライダをコピーして更新
				CColSphere cc = (*(CColSphere*)task).GetUpdate();
				//コライダを先頭から衝突判定していく
				CColBase *n = (CColBase*)mpRoot;
				while (n != NULL) {
					//親のタスクで衝突判定させる
					if (task->mpParent && task != n) {
						task->mpParent->Collision(&cc, n);
					}
					n = (CColBase*)n->mpNext;
				}
			}
			break;
		}
		task = (CColBase*)task->mpNext;
	}

#ifdef _DEBUG 
	AllRender();
#endif
}

CCollisionManager::~CCollisionManager(){
	AllKill();
}
