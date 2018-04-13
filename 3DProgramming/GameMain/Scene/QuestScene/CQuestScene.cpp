#include "CQuestScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"
#include "../GameResult/CGameResult.h"


CQuestScene::CQuestScene(){
	mQuest.Init();//初期化
	
}

CQuestScene::~CQuestScene(){}

void CQuestScene::Update(){
	mQuest.Update();//更新
	mQuest.Render();//描画



	/*ここからシーン移行処理*/

	//クエスト00をクリックしたとき
	if (CCollision2D::Collision2D(mQuest.mCursor, mQuest.mQuestName00)){
		if (CMouse::GetInstance()->mOneLeftFlag){//マウス左クリック
			CQuest::eChoice = CQuest::E_QUEST00;//クエスト00を選択した
			CGameResult::mPrize = CGameResult::E_Quest0;
			/*ゲームメインに移行*/
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_GAMEMAIN);
		}
	}
	//クエスト01をクリックしたとき
	if (CCollision2D::Collision2D(mQuest.mCursor, mQuest.mQuestName01)){
		if (CMouse::GetInstance()->mOneLeftFlag){//マウス左クリック
			CQuest::eChoice = CQuest::E_QUEST01;//クエスト01を選択した
			CGameResult::mPrize = CGameResult::E_Quest1;
			/*ゲームメインに移行*/
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_GAMEMAIN);
		}
	}
	//クエスト02をクリックしたとき
	if (CCollision2D::Collision2D(mQuest.mCursor, mQuest.mQuestName02)){
		if (CMouse::GetInstance()->mOneLeftFlag){//マウス左クリック
			CQuest::eChoice = CQuest::E_QUEST02;//クエスト02を選択した
			CGameResult::mPrize = CGameResult::E_Quest2;
			/*ゲームメインに移行*/
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_GAMEMAIN);
		}
	}
	////クエスト03をクリックしたとき
	//if (CCollision2D::Collision2D(mQuest.mCursor, mQuest.mQuestName03)){
	//	if (CMouse::GetInstance()->mOneLeftFlag){//マウス左クリック
	//		CQuest::eChoice = CQuest::E_QUEST03;//クエスト03を選択した
	//		CGameResult::mPrize = CGameResult::E_Quest3;
	//		/*ゲームメインに移行*/
	//		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_GAMEMAIN);
	//	}
	//}



	//ホームボタンとの連結
	if (CCollision2D::Collision2D(mQuest.mCursor, mQuest.mBackButton)){ //カーソルがあっている?
		if (CMouse::GetInstance()->mOneLeftFlag)//マウス左クリック
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_HOME);
	}


}