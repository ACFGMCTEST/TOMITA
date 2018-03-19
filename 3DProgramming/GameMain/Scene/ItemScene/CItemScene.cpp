#include "CItemScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"

CItemScene::CItemScene(){
	mItem.Init();//初期化
}

CItemScene::~CItemScene(){}

void CItemScene::Update(){
	mItem.Update();//更新
	mItem.Render();//描画

	///*ここからシーン移行処理*/

	/*あたり判定*/
	if (CCollision2D::Collision2D(mItem.mCursor, mItem.mBackButton)){ //カーソルがあっている?
		if (CMouse::GetInstance()->mLeftFlag){//マウス左クリック
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_HOME);
		}
	}
	///*あたり判定*/
	//if (CCollision2D::Collision2D(mItem.mCursor, mItem.mShopButton)){ //カーソルがあっている?
	//	if (CMouse::GetInstance()->mLeftFlag){//マウス左クリック
	//		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_SHOP);
	//	}
	//}

}