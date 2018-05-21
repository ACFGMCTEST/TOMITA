#ifndef CCOLLISIONMANAGER_HPP
#define CCOLLISIONMANAGER_HPP
#include "../Task/CTaskManager.h"
#include "ColType\CColBase.h"

class CCollisionManager : public CTaskManager {
private:
	/*�n�`�̓����蔻�肵�Ȃ����������߂�*/
	bool FlagMap(const CColBase &task, const CColBase &map);

	static CCollisionManager *mCollisionManager;
	CCollisionManager();

public:

	static CCollisionManager *GetInstance(); //GetInstance

	~CCollisionManager();

	void Add(CColBase *col);//�����蔻��ǉ�����

	void Update();
 
};

#endif