//高橋弘樹
#ifndef SHOP_CREATING_HPP
#define SHOP_CREATING_HPP
#include "../../Graphic/CRectangle2.h"

class CShopCreating{
public:
	CRectangle2 mBackGround;		//背景

	CRectangle2 mWeaponName00;		//武器の名前00

	CRectangle2 mWeaponName01;		//

	CRectangle2 mWeaponName02;	    //

	CRectangle2 mWeaponName03;

	CRectangle2 mBackButton;	    //戻るボタン

	CRectangle2 mWeaponDetails;    //武器詳細

	CRectangle2 mHelp;          	//作成しますか？

	CRectangle2 mYes;			//はい

	CRectangle2 mNo;				//いいえ


	CRectangle2 mCursor;//カーソル

	CTexture	*mpTexture;
	CTexture	*mpMenu;
	//CSound ShopCreatingbgm;

	//CSound returnkey;
	//CSound cursorchange;


	enum E_Status{
		E_WEAPON,
		E_ARMOR
	};

	static int status;

	float alpha;
	float alpha2;


	~CShopCreating();
	CShopCreating(){};
	void Init();
	void Update();
	void Render();

};
#endif
