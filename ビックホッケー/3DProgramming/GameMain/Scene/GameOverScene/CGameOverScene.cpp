//�^�C�g���̃v���O���~���O
//�쐬�ҁ@�y�c���l
#include "CGameOverScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"

CGameOverScene::CGameOverScene(){
	mGameOver.Init();
}

CGameOverScene::~CGameOverScene(){
}

void CGameOverScene::Update() {
	
	mGameOver.Update();
	mGameOver.Render();


}