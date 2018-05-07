#ifndef CCOLLISIONMANAGER_HPP
#define CCOLLISIONMANAGER_HPP
#include "CCollider.h"
#include "../Task/CTaskManager.h"
#include "CCollider.h"

/*‚·‚×‚Ä‚Ì“–‚½‚è”»’èŠÇ—*/
class CCollisionManager : public CTaskManager{
private:

	/*“–‚½‚è”»’ètag”»’f*/
	bool ColIf(CTask *Task_You, CTask *Task_I);

	void Update(CTask *t);//XVˆ—



	static CCollisionManager *mCollisionManager;
	CCollisionManager();

public:

	static CCollisionManager *GetInstance(); //GetInstance
	~CCollisionManager();

	void Add(CTask::E_TAG tag, CCollider *col);//‚ ‚½‚è”»’è’Ç‰Áˆ—

	void Update();
};

#endif