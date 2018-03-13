#ifndef MAIN_HPP
#define MAIN_HPP

#include "CharaDate/CSceneModel.h"
#include "Map/CMap.h"
#include "UI\CScoreBoard.h"
#include "../CScene.h"
#include"../CountDown/CCountDown.h"
#include "Pause/CPause.h"
#include "Tutorial\CTutorial.h"

class CGameScene : public CScene{
public:


	CTutorial mTutorial;
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
	/*状態*/
	enum E_STATE{
		E_INIT,
		E_TUTORIAL,//Tutorialシーン
		E_MAIN,
		E_END
	};
	E_STATE eState;
	bool pause = false;

	CGameScene();
	~CGameScene();

	void TransitionManager();
	//繰り返し実行される処理
	void Update();
	//ミニマップ

	/*マップ上からの視点*/
	void RenderMiniMap();
};

#endif
