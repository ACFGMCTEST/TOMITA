#include "GameScene\CGameScene.h"
#include "TitleScene\CTitleScene.h"
#include "HomeScene\CHomeScene.h"
#include "QuestScene\CQuestScene.h"
#include "ItemScene\CItemScene.h"
#include "../Key/CMouse.h"
#include"CSceneManager.h"

CSceneManager* CSceneManager::mSceneManager = 0;

CScene* mScene=0;

CSceneManager::CSceneManager():eStatus(E_INIT){
}
CSceneManager::~CSceneManager(){
}

//GetInstance
CSceneManager* CSceneManager::GetInstance(){
	if (mSceneManager == 0) {
		mSceneManager = new CSceneManager();
	}
	return mSceneManager;
}

//KILLˆ—
void CSceneManager::DeleteScene(){
	if (mScene)
		delete mScene;
	mScene = 0;
}

void CSceneManager::ChangeScene(eSceneNo SceneNo) {

	DeleteScene();		//KILL

	/*ƒV[ƒ“‘®«ŠÇ—*/
	CScene::State = SceneNo;

	switch (SceneNo)
	{
	case E_HOME:
		mScene = new CHomeScene;
		break;
	case E_STAGE_SELECT:
		mScene = new CQuestScene;
		break;
	case E_MODEL_CHANGE:
		mScene = new CItemScene;
		break;
	case E_GAMEMAIN:
		mScene = new CGameScene;
		break;
	default:
		break;
	}

}

void CSceneManager::SceneMain(){
	switch (eStatus)
	{
	case E_INIT:

		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_HOME);

		eStatus = E_LOOP;

		break;
	case E_LOOP:

		mScene->Update();

		break;
	}

}
