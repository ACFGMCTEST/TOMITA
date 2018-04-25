#include "Windows.h"
#include "CGameScene.h"
#include "../../Collision/CCollisionManager.h"
#include "../../Key/CKey.h"
#include "../../Key/CMouse.h"
#include "./../CSceneManager.h"
#include "../QuestScene/CQuest.h"

CCamera MainCamera;

CGameScene::CGameScene() : eState(E_INIT),mSceneModel(){
};

CGameScene::~CGameScene(){

}



//繰り返し実行される処理
void CGameScene::Update() {
	switch (eState)
	{
	case E_INIT:
		MainCamera.Init();

		eState = E_MAIN;
		break;
		
	case E_MAIN:
		MainCamera.Update();
		mSceneModel.Update();
		
		mSceneModel.Render();
		
		mSceneModel.UpdateEffect();
		
		CCollisionManager::GetInstance()->Update();

		break;
	case E_END:
		CCollisionManager::GetInstance()->AllKill();
		mSceneModel.ModelAllKill();
		
		eState = E_INIT;
		/*タイトルに戻る*/
		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);
		break;
	}


}
