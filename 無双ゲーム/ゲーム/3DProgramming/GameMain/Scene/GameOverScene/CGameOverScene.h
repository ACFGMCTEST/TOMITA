#ifndef GAMEOVERSCENE_HPP
#define GAMEOCERSCENE_HPP

#include "../Define/define.h"
#include "CGameOver.h"
#include "../../Scene/CScene.h"

//�Q�[���I�[�o�[�̑J�ڃN���X
class CGameOverScene :public CScene{
private:
	CGameOver mGameOver;

	~CGameOverScene();
	void Update();
public:
	CGameOverScene();
};
#endif