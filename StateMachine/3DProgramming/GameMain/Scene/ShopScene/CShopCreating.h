//�����O��
#ifndef SHOP_CREATING_HPP
#define SHOP_CREATING_HPP
#include "../../Graphic/CRectangle2.h"

class CShopCreating{
public:
	CRectangle2 mBackGround;		//�w�i

	CRectangle2 mWeaponName00;		//����̖��O00

	CRectangle2 mWeaponName01;		//

	CRectangle2 mWeaponName02;	    //

	CRectangle2 mWeaponName03;

	CRectangle2 mBackButton;	    //�߂�{�^��

	CRectangle2 mWeaponDetails;    //����ڍ�

	CRectangle2 mHelp;          	//�쐬���܂����H

	CRectangle2 mYes;			//�͂�

	CRectangle2 mNo;				//������


	CRectangle2 mCursor;//�J�[�\��

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
