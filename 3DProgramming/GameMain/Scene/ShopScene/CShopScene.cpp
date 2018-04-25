//タイトルのプログラミング
//作成者　冨田健斗
#include "CShopScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"
CShopScene::CShopScene() : eStatus(E_SHOP){
	mShop.Init();

}
CShopScene::~CShopScene(){
}

void CShopScene::Update() {

	switch (eStatus)
	{

	case CShopScene::E_SHOP:

		mShop.Update();
		mShop.Render();

		//ホームボタンとの連結
		if (mShop.mBuyScene == false){

			if (CCollision2D::Collision2D(mShop.mCursor, mShop.mBackButton)){ //カーソルがあっている?
				if (CMouse::GetInstance()->mOneLeftFlag) {//マウス左クリック
					//B					CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_HOME);
					CSceneManager::GetInstance()->eStatus = CSceneManager::E_CHANGE;
					CScene::State = eSceneNo::E_HOME;
				}
			}
		}

		break;

	case CShopScene::E_SHOP_CREATING:


		break;
	default:
		break;
	}





}