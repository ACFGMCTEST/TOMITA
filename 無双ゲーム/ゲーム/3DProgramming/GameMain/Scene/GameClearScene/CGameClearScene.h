#ifndef GAMECLEARSCENE_HPP
#define GAMECLEARSCENE_HPP

#include "../Define/define.h"
#include "CGameClear.h"
#include "../../Scene/CScene.h"

/*クリアの遷移管理クラス*/
class CGameClearScene:public CScene{
private:
	CGameClear mGameClear;

	~CGameClearScene();
	void Update();
public:
	CGameClearScene();
};
#endif