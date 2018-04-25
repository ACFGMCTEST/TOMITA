//タイトルのプログラミング
//担当者　高橋弘樹 && 冨田健斗

#ifndef SHOP_SCENE_HPP
#define SHOP_SCENE_HPP

#include "../Define/define.h"
#include "CShop.h"
#include "CShopCreating.h"
#include "../../Scene/CScene.h"



class CShopScene :public CScene{
private:
	CShop mShop;
	CShopCreating mShopCreating;//装備作成

	enum E_Status{
		E_SHOP,
		E_SHOP_CREATING,
	};
	E_Status eStatus;//場面の状態
	 
	~CShopScene();
	void Update();
public:
	CShopScene();
};
#endif