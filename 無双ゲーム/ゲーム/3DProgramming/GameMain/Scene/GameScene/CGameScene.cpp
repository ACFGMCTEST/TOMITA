#include "Windows.h"
#include "CGameScene.h"
#include "../../Collision/CCollisionManager.h"
#include "../../Key/CKey.h"
#include "../../Key/CMouse.h"
#include "./../CSceneManager.h"
#include "../QuestScene/CQuest.h"
#include "../../Graphic/CBillBoard.h"
#include "Tutorial\CTutorial.h"
#include  "Result\CResult.h"

CCamera MainCamera;
CCamera MapCamera;

bool CGameScene::mPauseFlag = false;

CGameScene::E_STATE CGameScene::eState = CGameScene::E_INIT;

CGameScene::CGameScene(){
	eState = E_INIT;

};

CGameScene::~CGameScene(){

}

/*ミニマップ左上に表示するもの*/
void CGameScene::MiniMapRender() {
	
	MapCamera.SetPos();

	MapCamera.Render();

	//ミニマップ表示開始
	MapCamera.StartMiniMap();
	

	CMap::GetInstance()->MiniMapRender();
	CTaskManager::GetInstance()->AllMiniMapRender();
	//ミニマップ表示終了
	MapCamera.EndMiniMap();

	

}

//繰り返し実行される処理
void CGameScene::Update() {
	switch (eState)
	{
	case E_INIT:
		CMap::GetInstance()->Init();
		CSceneModel::GetInstance()->Init();
		CResult::GetInstance()->Init();
		CTutorial::GetInstance()->Init();

		eState = E_MAIN;
		break;
		
	case E_MAIN:

		MainCamera.Update();
		/*ポーズフラグが立つと*/
		if (!mPauseFlag) {
			CMap::GetInstance()->Update();
			CTaskManager::GetInstance()->AllUpdate();
			CCollisionManager::GetInstance()->Update();
			CResult::GetInstance()->Update();
		}
		/*描画*/
		CMap::GetInstance()->Render();
		CTaskManager::GetInstance()->AllRender();
		//ミニマップ表示
		MiniMapRender();
		CResult::GetInstance()->Render();
		//チュートリアルの更新　ここで止める処理など入れている
		CTutorial::GetInstance()->Update();
		CTutorial::GetInstance()->Render();

		break;
	case E_END:
		CCollisionManager::GetInstance()->AllKill();
		CTaskManager::GetInstance()->AllKill();
		
		eState = E_INIT;
		/*タイトルに戻る*/
		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_HOME);
		break;
	}


}
