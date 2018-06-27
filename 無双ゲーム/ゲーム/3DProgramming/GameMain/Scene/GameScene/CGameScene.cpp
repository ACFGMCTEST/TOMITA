#include "Windows.h"
#include "CGameScene.h"
#include "../../Collision/CCollisionManager.h"
#include "../../Key/CKey.h"
#include "../../Key/CMouse.h"
#include "./../CSceneManager.h"
#include "../QuestScene/CQuest.h"
#include "../../Graphic/CBillBoard.h"
#include  "Result\CResult.h"

CCamera MainCamera;



CGameScene::E_STATE CGameScene::eState = CGameScene::E_INIT;

CGameScene::CGameScene(){
	eState = E_INIT;
};

CGameScene::~CGameScene(){

}

//繰り返し実行される処理
void CGameScene::Update() {
	switch (eState)
	{
	case E_INIT:
		CMap::GetInstance()->Init();
		mSceneModel.Init();
		CResult::GetInstance()->Init();
		MainCamera.Init();
		eState = E_MAIN;
		break;
		
	case E_MAIN:

		MainCamera.Update();
		CMap::GetInstance()->Update();
		CMap::GetInstance()->Render();
		mSceneModel.Update();
		CCollisionManager::GetInstance()->Update();
		mSceneModel.Render();

		CResult::GetInstance()->Update();
		CResult::GetInstance()->Render();


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
