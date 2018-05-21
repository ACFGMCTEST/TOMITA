#ifndef CCOLLISIONMANAGER_HPP
#define CCOLLISIONMANAGER_HPP
#include "../Task/CTaskManager.h"
#include "ColType\CColBase.h"

class CCollisionManager : public CTaskManager {
private:
	/*’nŒ`‚Ì“–‚½‚è”»’è‚µ‚È‚¢•”•ª‚ğŒˆ‚ß‚é*/
	bool FlagMap(const CColBase &task, const CColBase &map);

	static CCollisionManager *mCollisionManager;
	CCollisionManager();

public:

	static CCollisionManager *GetInstance(); //GetInstance

	~CCollisionManager();

	void Add(CColBase *col);//‚ ‚½‚è”»’è’Ç‰Áˆ—

	void Update();
 
};

#endif