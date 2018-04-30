#include "Windows.h"
#include "CGameScene.h"
#include "../../Collision/CCollisionManager.h"
#include "../../Key/CKey.h"
#include "../../Key/CMouse.h"
#include "./../CSceneManager.h"
#include "../../../CCollider3.h"

CCamera MainCamera;

int CGameScene::Transition = E_ACTIVE;

CGameScene::CGameScene() : eState(E_INIT){
	Transition = E_ACTIVE;
	mPause.Init();
};

CGameScene::~CGameScene(){

}


//ゲーム遷移の処理
void CGameScene::TransitionManager(){

	switch (Transition)
	{
	case E_COUNTDOWN:

		if (CKey::once(VK_ESCAPE))Transition = E_ACTIVE;
		if (CKey::once(VK_RETURN))exit(0);
		if (CScoreBoard::mcFirstAction == false){
			firstaction = true;
			Transition = E_ACTIVE;
		}

		break;


	case E_ACTIVE:

		if (CKey::once(VK_ESCAPE))Transition=E_PAUSE;
		CMouse::mClipFlag = true; //画面内

		if (firstaction == false){
//			Transition = E_COUNTDOWN;
		}

		break;
	case E_PAUSE:
		CMouse::mClipFlag = false; //画面外

		mPause.Render();
		mPause.Update();

		if (mPause.mBackGame)Transition = E_ACTIVE; mPause.mBackGame = false;
		if (CKey::once(VK_RETURN))exit(0);//プログラムを終了させる

		break;
	default:
		break;
	}

}


//繰り返し実行される処理
void CGameScene::Update() {
	switch (eState)
	{
	case E_INIT:
		mMap.Init();
		CScoreBoard::GetInstance()->Init();
		mSceneModel.Init();
		MainCamera.Init();
		eState = E_MAIN;
		break;
		
	case E_MAIN:
		MainCamera.Update();

		mSceneModel.Update();
		mSceneModel.Render();

		mMap.Update(); 
		mMap.Render();

		mSceneModel.UpdateEffect();

		TransitionManager();

		CTaskManager::GetInstance()->AllUpdate();

		CScoreBoard::GetInstance()->Update();

//		CCollisionManager::GetInstance()->Update();
		CCollisionManager3::GetInstance()->Update();

		CTaskManager::GetInstance()->AllRender();

		CScoreBoard::GetInstance()->Render();

		/*シーン切り替えフラグが立つと*/
		if (CScoreBoard::GetInstance()->mFlagSceneChage ||
			CPause::mSceneChangeFlag){
			eState = E_END;
		}

		break;
	case E_END:
		CCollisionManager::GetInstance()->AllKill();
		CCollisionManager3::GetInstance()->AllKill();
		//		mSceneModel.mModelTaskManager.AllKill();
		CTaskManager::GetInstance()->AllKill();
//		mMap.mMapTaskManager.AllKill();
		mMap.mCsvMapData.~CCsv();
		eState = E_INIT;
		/*タイトルに戻る*/
		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);
		break;
	}


}
