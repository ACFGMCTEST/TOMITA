#include "Windows.h"
#include "CGameScene.h"
#include "../../Collision/CCollisionManager.h"
#include "../../Key/CKey.h"
#include "../../Key/CMouse.h"
#include "./../CSceneManager.h"
#include "../QuestScene/CQuest.h"

CCamera MainCamera;

CGameScene::E_TRANSTION CGameScene::eTransition = E_ACTIVE;

CGameScene::CGameScene() : eState(E_INIT){
	mBgm.Load(BGM_FILE);
	eTransition = E_ACTIVE;
	mPause.Init();
};

CGameScene::~CGameScene(){
	mBgm.Close();
}


/*マップ上からの視点*/
void CGameScene::RenderMiniMap() {


}
//ゲーム遷移の処理
void CGameScene::TransitionManager(){

	switch (eTransition)
	{
	case E_COUNTDOWN:


		if (CScoreBoard::mcFirstAction == false){
			firstaction = true;
			eTransition = E_ACTIVE;
		}

		break;


	case E_ACTIVE:
		/*エスケープキーでポーズに移行*/
		if (CKey::once(VK_ESCAPE))eTransition=E_PAUSE;

		CMouse::GetInstance()->mClipFlag = true; //画面内

		if (firstaction == false){
			eTransition = E_COUNTDOWN;
		}

		break;
	case E_PAUSE:
		CMouse::GetInstance()->mClipFlag = false; //画面外
		/*ポーズ画面表示*/
		mPause.Render();
		mPause.Update();

		if (mPause.mBackGame)eTransition = E_ACTIVE;
		mPause.mBackGame = false;
		

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
		mBgm.Repeat();
		eState = E_MAIN;
		break;
		
	case E_MAIN:
		MainCamera.Update();
		mSceneModel.Update();
		mMap.Update();

		mSceneModel.Render();
		mMap.Render();
		mSceneModel.UpdateEffect();

			

		CScoreBoard::GetInstance()->Update();

		CCollisionManager::GetInstance()->Update();

		CScoreBoard::GetInstance()->Render();

		TransitionManager();

		/*シーン切り替えフラグが立つと*/
		if (CScoreBoard::GetInstance()->mFlagSceneChage ||
			CPause::mSceneChangeFlag){
			eState = E_END;
		}


		break;
	case E_END:
		mBgm.Close();
		CCollisionManager::GetInstance()->AllKill();
		mSceneModel.mModelTaskManager.AllKill();
		mMap.mMapTaskManager.AllKill();
//		mMap.mCsvMapData.~CCsv();
		eState = E_INIT;
		/*タイトルに戻る*/
		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);
		break;
	}


}
