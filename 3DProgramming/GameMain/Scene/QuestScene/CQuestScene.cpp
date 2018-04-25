#include "CQuestScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"
#include "../GameResult/CGameResult.h"


CQuestScene::CQuestScene()
//	: mpQuest(0)
{
//	mpQuest = new CQuest();
	mpQuest.Init();//初期化
	
}

CQuestScene::~CQuestScene(){

	//if (mpQuest) {
	//	delete mpQuest;
	//	mpQuest = 0;
	//}

}

void CQuestScene::Update(){
	mpQuest.Update();//更新
	mpQuest.Render();//描画



	/*ここからシーン移行処理*/

	//クエスト00をクリックしたとき
	if (CCollision2D::Collision2D(mpQuest.mCursor, mpQuest.mQuestName00)){
		if (CMouse::GetInstance()->mOneLeftFlag){//マウス左クリック
			CQuest::eChoice = CQuest::E_QUEST00;//クエスト00を選択した
			CGameResult::mPrize = CGameResult::E_Quest0;
			/*ゲームメインに移行*/
			//B			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_GAMEMAIN);
			CSceneManager::GetInstance()->eStatus = CSceneManager::E_CHANGE;
			CScene::State = eSceneNo::E_GAMEMAIN;
		}
	}
	//クエスト01をクリックしたとき
	if (CCollision2D::Collision2D(mpQuest.mCursor, mpQuest.mQuestName01)){
		if (CMouse::GetInstance()->mOneLeftFlag){//マウス左クリック
			CQuest::eChoice = CQuest::E_QUEST01;//クエスト01を選択した
			CGameResult::mPrize = CGameResult::E_Quest1;
			/*ゲームメインに移行*/
			//B			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_GAMEMAIN);
			CSceneManager::GetInstance()->eStatus = CSceneManager::E_CHANGE;
			CScene::State = eSceneNo::E_GAMEMAIN;
		}
	}
	//クエスト02をクリックしたとき
	if (CCollision2D::Collision2D(mpQuest.mCursor, mpQuest.mQuestName02)){
		if (CMouse::GetInstance()->mOneLeftFlag){//マウス左クリック
			CQuest::eChoice = CQuest::E_QUEST02;//クエスト02を選択した
			CGameResult::mPrize = CGameResult::E_Quest2;
			/*ゲームメインに移行*/
			//B			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_GAMEMAIN);
			CSceneManager::GetInstance()->eStatus = CSceneManager::E_CHANGE;
			CScene::State = eSceneNo::E_GAMEMAIN;
		}
	}



	//ホームボタンとの連結
	if (CCollision2D::Collision2D(mpQuest.mCursor, mpQuest.mBackButton)){ //カーソルがあっている?
		if (CMouse::GetInstance()->mOneLeftFlag) {//マウス左クリック
			//B			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_HOME);
			CSceneManager::GetInstance()->eStatus = CSceneManager::E_CHANGE;
			CScene::State = eSceneNo::E_HOME;
		}
	}


}