//�^�C�g���̃v���O���~���O
//�S���ҁ@�����O�� && �y�c���l

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