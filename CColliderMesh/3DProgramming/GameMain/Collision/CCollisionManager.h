#ifndef CCOLLISIONMANAGER_HPP
#define CCOLLISIONMANAGER_HPP
#include "CCollider.h"
#include "../Task/CTaskManager.h"
#include "CCollider.h"

/*すべての当たり判定管理*/
class CCollisionManager : public CTaskManager{
private:
	/*当たり判定*/
	//CCollider *mYouBox,*mIBox;
	//CColliderSphere *mYouSphere,*mISphere;

	bool ColIf(CTask *Task_You, CTask *Task_I);

	void Update(CTask *t);//更新処理

	void PlayerCollision(CTask *TaskYou, CTask *Player); //プレイヤーのあたりはんてい処理
	void EnemyCollision(CTask *TaskYou, CTask *Enemy); //エネミーのあたりはんてい処理A
	void PuckCollision(CTask *TaskYou, CTask *Puck); //パックの当たり判定

	void OnCollision(CTask *TaskYou, CTask *Task_I);    //あたり判定呼び出し処理


	static CCollisionManager *mCollisionManager;
	CCollisionManager();

public:

	static CCollisionManager *GetInstance(); //GetInstance
	~CCollisionManager();

	void Add(CTask::E_TAG tag, CCollider *col);//あたり判定追加処理

	void Update();
};

#endif