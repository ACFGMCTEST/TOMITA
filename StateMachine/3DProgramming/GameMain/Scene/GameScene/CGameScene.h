#ifndef MAIN_HPP
#define MAIN_HPP

#include "CharaDate/CSceneModel.h"
#include "Map/CMap.h"
#include "UI\CScoreBoard.h"
#include "../CScene.h"
#include"../CountDown/CCountDown.h"
#include "Pause/CPause.h"

class CGameScene : public CScene{
public:

	CPause mPause;
	CSceneModel mSceneModel;
	CMap mMap;
	
	bool firstaction=false;

	static int Transition;

	enum eTransition{
		E_COUNTDOWN,
		E_ACTIVE,
		E_PAUSE,
	};
	/*���*/
	enum E_STATE{
		E_INIT,
		E_MAIN,
		E_END
	};
	E_STATE eState;
	bool pause = false;

	CGameScene();
	~CGameScene();

	void TransitionManager();
	//�J��Ԃ����s����鏈��
	void Update();

};

#endif
