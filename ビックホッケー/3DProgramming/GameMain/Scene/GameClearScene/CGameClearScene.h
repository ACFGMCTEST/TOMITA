//タイトルのプログラミング
//担当者　高橋弘樹 && 冨田健斗

#ifndef GAMECLEARSCENE_HPP
#define GAMECLEARSCENE_HPP

#include "../Define/define.h"
#include "CGameClear.h"
#include "../../Scene/CScene.h"


class CGameClearScene:public CScene{
private:
	CGameClear mGameClear;

	~CGameClearScene();
	void Update();
public:
	CGameClearScene();
};
#endif