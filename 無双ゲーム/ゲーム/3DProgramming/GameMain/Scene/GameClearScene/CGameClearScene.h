#ifndef GAMECLEARSCENE_HPP
#define GAMECLEARSCENE_HPP

#include "../Define/define.h"
#include "CGameClear.h"
#include "../../Scene/CScene.h"

/*�N���A�̑J�ڊǗ��N���X*/
class CGameClearScene:public CScene{
private:
	CGameClear mGameClear;

	~CGameClearScene();
	void Update();
public:
	CGameClearScene();
};
#endif