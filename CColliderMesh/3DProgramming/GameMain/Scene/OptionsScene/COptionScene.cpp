#include "COptionScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"

COptionScene::COptionScene(){
	mOption.Init();//初期化
}

COptionScene::~COptionScene(){}

void COptionScene::Update(){
	mOption.Update();//更新
	mOption.Render();//描画

	///*ここからシーン移行処理*/

	/*あたり判定*/
	if (CCollision2D::Collision2D(mOption.mCursor, mOption.mBackButton)){ //カーソルがあっている?
		if (CMouse::mLeftFlag){//マウス左クリック
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_HOME);
		}
	}
	///*あたり判定*/
	//if (CCollision2D::Collision2D(mItem.mCursor, mItem.mShopButton)){ //カーソルがあっている?
	//	if (CMouse::mLeftFlag){//マウス左クリック
	//		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_SHOP);
	//	}
	//}

}