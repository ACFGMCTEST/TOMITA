#include "Windows.h"
#include "CGameScene.h"
#include "../../Collision/CCollisionManager.h"
#include "../../Collision/CCollider3.h"
#include "../../Key/CKey.h"
#include "../../Key/CMouse.h"
#include "./../CSceneManager.h"
#include "../QuestScene/CQuest.h"

CCamera MainCamera;

CGameScene::CGameScene() : eState(E_INIT){
};

CGameScene::~CGameScene(){

}



//�J��Ԃ����s����鏈��
void CGameScene::Update() {
	switch (eState)
	{
	case E_INIT:
		mSceneModel.Init();
		MainCamera.Init();
		mMap.Init();
		eState = E_MAIN;
		break;
		
	case E_MAIN:
		mMap.Update();
		mMap.Render();

		MainCamera.Update();
		mSceneModel.Update();
		
		mSceneModel.Render();
		
		CCollisionManager::GetInstance()->Update();
		CCollisionManager3::GetInstance()->Update();

		break;
	case E_END:
		CCollisionManager::GetInstance()->AllKill();
		CCollisionManager3::GetInstance()->AllKill();
		mSceneModel.ModelAllKill();
		
		eState = E_INIT;
		/*�^�C�g���ɖ߂�*/
		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);
		break;
	}


}
