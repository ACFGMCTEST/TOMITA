#include "CHomeScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"

CHomeScene::CHomeScene():mHome(){
}

CHomeScene::~CHomeScene(){}

void CHomeScene::Update(){
	mHome.Update();//更新
	mHome.Render();//描画
	/*シーンCHANGE*/
	if (mHome.SceneFlag()){
		//CSceneManager::GetInstance()->ChangeScene(mHome.eScene);
		CSceneManager::GetInstance()->ChangeScene(E_GAMEMAIN);
	}

}