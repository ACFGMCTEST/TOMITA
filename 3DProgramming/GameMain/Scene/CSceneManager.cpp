
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
	mBgm.Load(BGM_FILE);//BGM�ǂݍ���

}
CSceneManager::~CSceneManager(){
	mBgm.Close();
}

//GetInstance
CSceneManager* CSceneManager::GetInstance(){
	if (mSceneManager == 0) {
		mSceneManager = new CSceneManager();
	}
	return mSceneManager;
}

//KILL����
void CSceneManager::DeleteScene(){
	if (mScene)
		delete mScene;
	mScene = 0;
}

void CSceneManager::ChangeScene(eSceneNo SceneNo) {
	
	DeleteScene();		//KILL

	mBgm.Repeat();
	/*�V�[�������Ǘ�*/
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

		mScene = new CGameClearScene;
		break;
	case E_GAMEOVER:

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
