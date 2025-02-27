#ifndef CCOLLISIONMANAGER_HPP
#define CCOLLISIONMANAGER_HPP
#include "../Task/CTaskManager.h"
#include "ColType\CColBase.h"

class CCollisionManager : public CTaskManager {
private:
	/*地形の当たり判定しない部分を決める*/
	bool FlagMap(const CColBase &task, const CColBase &map);

	static CCollisionManager *mCollisionManager;
	CCollisionManager();

public:

	static CCollisionManager *GetInstance(); //GetInstance

	~CCollisionManager();

	void Add(CColBase *col);//あたり判定追加処理

	void Update();
 
};

#endif