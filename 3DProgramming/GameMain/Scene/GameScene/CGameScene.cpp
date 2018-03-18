#include "Windows.h"
#include "CGameScene.h"
#include "../../Collision/CCollisionManager.h"
#include "../../Key/CKey.h"
#include "../../Key/CMouse.h"
#include "./../CSceneManager.h"
#include "../QuestScene/CQuest.h"

CCamera MainCamera;

int CGameScene::Transition = E_ACTIVE;

CGameScene::CGameScene() : eState(E_INIT){
	Transition = E_ACTIVE;
	mPause.Init();
};

CGameScene::~CGameScene(){

}


/*マップ上からの視点*/
void CGameScene::RenderMiniMap() {

	//gluPerspective(75.0, (double)DISP_X / (double)DISP_Y, 1.0, 1000.0);
	//glPushMatrix();
	//glViewport(600, 450, 200, 150); //画面の描画エリアの指定
	//glLoadIdentity();
	//gluLookAt(0, 80, -10, 0, 0, 0, 0, 1, 0);

	//glDisable(GL_NORMALIZE);
	//glDisable(GL_DEPTH_TEST);
	///*描画*/
	//mSceneModel.Render();
	//mMap.Render();
	//mSceneModel.UpdateEffect();


	//glPopMatrix();
	//glViewport(0, 0, DISP_X, DISP_Y); //画面の描画エリアの指定

	//glEnable(GL_NORMALIZE);
	//glEnable(GL_DEPTH_TEST);
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
			Transition = E_COUNTDOWN;
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

		/*状態によりTutorialを表示*/
		if(CQuest::eChoice == CQuest::E_QUEST00){
			eState = E_TUTORIAL;
		}
		else{
			eState = E_MAIN;
		}
		break;
		
		/*Tutorialの状態*/
	case E_TUTORIAL:
		MainCamera.Update();
		mSceneModel.Update();
		mSceneModel.Render();
		mMap.Update();
		mMap.Render();
		mSceneModel.UpdateEffect();
		TransitionManager();

		CScoreBoard::GetInstance()->Update();
		CCollisionManager::GetInstance()->Update();
		CScoreBoard::GetInstance()->Render();



		/*シーン切り替えフラグが立つと*/
		if (CScoreBoard::GetInstance()->mFlagSceneChage ||
			CPause::mSceneChangeFlag){
			eState = E_END;
		}

		break;
	case E_MAIN:
		MainCamera.Update();
		mSceneModel.Update();
		mMap.Update();

		mSceneModel.Render();
		mMap.Render();
		mSceneModel.UpdateEffect();

		TransitionManager();
			

		CScoreBoard::GetInstance()->Update();

		CCollisionManager::GetInstance()->Update();

		CScoreBoard::GetInstance()->Render();

		/*シーン切り替えフラグが立つと*/
		if (CScoreBoard::GetInstance()->mFlagSceneChage ||
			CPause::mSceneChangeFlag){
			eState = E_END;
		}


		break;
	case E_END:
		CCollisionManager::GetInstance()->AllKill();
		mSceneModel.mModelTaskManager.AllKill();
		mMap.mMapTaskManager.AllKill();
		mMap.mCsvMapData.~CCsv();
		eState = E_INIT;
		/*タイトルに戻る*/
		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);
		break;
	}


}
