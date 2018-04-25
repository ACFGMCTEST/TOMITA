#ifndef MAIN_HPP
#define MAIN_HPP

#include "CharaDate/CSceneModel.h"
#include "Map/CMap.h"
#include "UI\CScoreBoard.h"
#include "../CScene.h"
#include"../CountDown/CCountDown.h"
#include "Pause/CPause.h"
#include "Tutorial\CTutorial.h"
#include "../../Sound/CSound.h"

class CGameScene : public CScene{
public:


	CPause mPause;
	CSceneModel mSceneModel;
	CMap mMap;
	CSound mBgm;//BGM
	
	bool firstaction=false;

	/*画面偏移*/
	enum E_TRANSTION{
		E_COUNTDOWN, //カウントダウン
		E_ACTIVE,//
		E_PAUSE,//ポーズ中
	};
	static E_TRANSTION eTransition;

	/*状態*/
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
	//繰り返し実行される処理
	void Update();
	//ミニマップ

	/*マップ上からの視点*/
	void RenderMiniMap();
};

#endif
