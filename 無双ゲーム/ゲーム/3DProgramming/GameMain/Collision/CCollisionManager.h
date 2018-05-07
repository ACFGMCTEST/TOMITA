#ifndef CCOLLISIONMANAGER_HPP
#define CCOLLISIONMANAGER_HPP
#include "CCollider.h"
#include "../Task/CTaskManager.h"
#include "CCollider.h"

/*���ׂĂ̓����蔻��Ǘ�*/
class CCollisionManager : public CTaskManager{
private:

	/*�����蔻��tag���f*/
	bool ColIf(CTask *Task_You, CTask *Task_I);

	void Update(CTask *t);//�X�V����



	static CCollisionManager *mCollisionManager;
	CCollisionManager();

public:

	static CCollisionManager *GetInstance(); //GetInstance
	~CCollisionManager();

	void Add(CTask::E_TAG tag, CCollider *col);//�����蔻��ǉ�����

	void Update();
};

#endif