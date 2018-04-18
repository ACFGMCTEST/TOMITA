
#include "GameScene\CGameScene.h"
#include "TitleScene\CTitleScene.h"
#include "HomeScene\CHomeScene.h"
#include "QuestScene\CQuestScene.h"
#include "ShopScene\CShopScene.h"
#include "ItemScene\CItemScene.h"
#include "OptionsScene\COptionScene.h"
#include "../Key/CMouse.h"
#include"CSceneManager.h"
#include"GameClearScene\CGameClearScene.h"
#include"GameOverScene\CGameOverScene.h"

CSceneManager* CSceneManager::mSceneManager = 0;

CScene* mScene=0;


CSceneManager::CSceneManager():eStatus(E_INIT){
	

	mSEClear.Load(SE_CLEAR_FILE);//クリアー読み込み
	mSEOver.Load(SE_OVER_FILE);//オーバー読み込み

}
CSceneManager::~CSceneManager(){
	
	mSEClear.Close();
	mSEOver.Close();
}

//GetInstance
CSceneManager* CSceneManager::GetInstance(){
	if (mSceneManager == 0) {
		mSceneManager = new CSceneManager();
	}
	return mSceneManager;
}

//KILL処理
void CSceneManager::DeleteScene(){
	if (mScene)
		delete mScene;
	mScene = 0;
}

void CSceneManager::ChangeScene(eSceneNo SceneNo) {
	
	DeleteScene();		//KILL

	/*シーン属性管理*/
	CScene::State = SceneNo;

	switch (SceneNo)
	{
	case E_TITLE:

		mScene = new CTitleScene;
		break;
	case E_HOME:
		mScene = new CHomeScene;
		break;
	case E_QUEST:

		mScene = new CQuestScene;
		break;
	case E_SHOP:
		mScene = new CShopScene;
		break;
	case E_ITEM:

		mScene = new CItemScene;
		break;
	case E_OPTION:

		mScene = new COptionScene;
		break;
	case E_GAMEMAIN:
		mScene = new CGameScene;
		
		break;
	case E_GAMECLEAR:
		mSEClear.Play();//クリア音鳴らす
		mScene = new CGameClearScene;
		break;
	case E_GAMEOVER:
		mSEOver.Play();//オーバー音鳴らす
		mScene = new CGameOverScene;
		break;
	default:
		break;
	}

}

void CSceneManager::SceneMain(){
	switch (eStatus)
	{
	case E_INIT:
		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);

		eStatus = E_LOOP;

		break;
	case E_LOOP:

		
		mScene->Update();

		break;
	}

}
