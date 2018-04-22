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


/*�}�b�v�ォ��̎��_*/
void CGameScene::RenderMiniMap() {


}
//�Q�[���J�ڂ̏���
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
		/*�G�X�P�[�v�L�[�Ń|�[�Y�Ɉڍs*/
		if (CKey::once(VK_ESCAPE))eTransition=E_PAUSE;

		CMouse::GetInstance()->mClipFlag = true; //��ʓ�

		if (firstaction == false){
			eTransition = E_COUNTDOWN;
		}

		break;
	case E_PAUSE:
		CMouse::GetInstance()->mClipFlag = false; //��ʊO
		/*�|�[�Y��ʕ\��*/
		mPause.Render();
		mPause.Update();

		if (mPause.mBackGame)eTransition = E_ACTIVE;
		mPause.mBackGame = false;
		

		break;
	default:
		break;
	}

}


//�J��Ԃ����s����鏈��
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

		/*�V�[���؂�ւ��t���O������*/
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
		/*�^�C�g���ɖ߂�*/
		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);
		break;
	}


}
