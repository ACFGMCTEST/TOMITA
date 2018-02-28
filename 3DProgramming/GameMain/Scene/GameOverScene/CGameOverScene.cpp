//タイトルのプログラミング
//作成者　冨田健斗
#include "CGameOverScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"

CGameOverScene::CGameOverScene(){
//	SE_Enter.load(SOUNDFILE"SE_ENTER.mp3");
	mGameOver.Init();
}

CGameOverScene::~CGameOverScene(){
//	SE_Enter.close();
}

void CGameOverScene::Update() {
	
	mGameOver.Update();
	mGameOver.Render();


}