//�^�C�g���̃v���O���~���O
//�S���ҁ@�����O�� && �y�c���l

#ifndef GAMEOVERSCENE_HPP
#define GAMEOCERSCENE_HPP

#include "../Define/define.h"
#include "CGameOver.h"
#include "../../Scene/CScene.h"


class CGameOverScene :public CScene{
private:
	CGameOver mGameOver;

	~CGameOverScene();
	void Update();
public:
	CGameOverScene();
};
#endif