#ifndef MAIN_HPP
#define MAIN_HPP

#include "CharaDate/CSceneModel.h"
#include "Map/CMap.h"
#include "../CScene.h"
#include "Pause/CPause.h"
#include "Tutorial\CTutorial.h"

class CGameScene : public CScene{
private:
	CSceneModel mSceneModel;
public:

	/*èÛë‘*/
	enum E_STATE{
		E_INIT,
		E_MAIN,
		E_END
	};
	static E_STATE eState;


	CGameScene();
	~CGameScene();
	/*çXêV*/
	void Update();
};

#endif
