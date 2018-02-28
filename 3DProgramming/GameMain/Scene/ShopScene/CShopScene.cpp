//タイトルのプログラミング
//作成者　冨田健斗
#include "CShopScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"
//CScene eSceneNo Shop

CShopScene::CShopScene() : eStatus(E_SHOP){
	//	SE_Enter.load(SOUNDFILE"SE_ENTER.mp3");
	mShop.Init();

}
CShopScene::~CShopScene(){
	//	SE_Enter.close();
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
				if (CMouse::mOneLeftFlag)//マウス左クリック
					CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_HOME);
			}
		}

		break;

	case CShopScene::E_SHOP_CREATING:
//

		break;
	default:
		break;
	}





}