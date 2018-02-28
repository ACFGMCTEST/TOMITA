//�^�C�g���̃v���O���~���O
//�S���ҁ@�����O�� && �y�c���l

#ifndef SHOP_SCENE_HPP
#define SHOP_SCENE_HPP

#include "../Define/define.h"
#include "CShop.h"
#include "CShopCreating.h"
#include "../../Scene/CScene.h"



class CShopScene :public CScene{
private:
	CShop mShop;
	CShopCreating mShopCreating;//�����쐬

	enum E_Status{
		E_SHOP,
		E_SHOP_CREATING,
	};
	E_Status eStatus;//��ʂ̏��
	 
	~CShopScene();
	void Update();
public:
	CShopScene();
};
#endif