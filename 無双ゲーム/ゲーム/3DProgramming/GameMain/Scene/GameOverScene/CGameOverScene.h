#ifndef GAMEOVERSCENE_HPP
#define GAMEOCERSCENE_HPP

#include "../Define/define.h"
#include "CGameOver.h"
#include "../../Scene/CScene.h"

//ゲームオーバーの遷移クラス
class CGameOverScene :public CScene{
private:
	CGameOver mGameOver;

	~CGameOverScene();
	void Update();
public:
	CGameOverScene();
};
#endif