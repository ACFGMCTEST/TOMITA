#include "CHomeScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"

CHomeScene::CHomeScene(){
	mHome.Init();//初期化
}

CHomeScene::~CHomeScene(){}

void CHomeScene::Update(){
	mHome.Update();//更新
	mHome.Render();//描画
	
	//printf("%d  %d\n", mHome.mStatus,mHome.mMove);

	/*ここからシーン移行処理*/
	/*あたり判定*/
	if (CCollision2D::Collision2D(mHome.mCursor, mHome.mSelectButton) && mHome.mStatus == mHome.QUEST&&mHome.mMove==false){ //カーソルがあっている?
		if (CMouse::GetInstance()->mOneLeftFlag){//マウス左クリック
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_QUEST);
			return;
		}
	}
	/*あたり判定*/
	if (CCollision2D::Collision2D(mHome.mCursor, mHome.mShopButton) && mHome.mStatus == mHome.SHOP&&mHome.mMove == false){ //カーソルがあっている?
		if (CMouse::GetInstance()->mOneLeftFlag){//マウス左クリック
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_SHOP);
			return;

		}
	}

	/*あたり判定*/
	if (CCollision2D::Collision2D(mHome.mCursor, mHome.mItemButton) && mHome.mStatus == mHome.ITEM&&mHome.mMove == false){ //カーソルがあっている?
		if (CMouse::GetInstance()->mOneLeftFlag){//マウス左クリック
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_ITEM);
			return;

		}
	}

	/*あたり判定*/
	if (CCollision2D::Collision2D(mHome.mCursor, mHome.mTitleButton) && mHome.mStatus == mHome.TITLE&&mHome.mMove == false){ //カーソルがあっている?
		if (CMouse::GetInstance()->mOneLeftFlag){//マウス左クリック
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);
			return;

		}
	}



}