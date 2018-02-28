//�����O�� && �y�c���l
#ifndef HOME_HPP
#define HOME_HPP
#include "../Base\CBase.h"
#include "../GameMain\Graphic\CRectangle2.h"
#include "../GameMain\Scene\CScene.h"

#define MOVE_SPEED 25

class CHome :public CScene{
public:
	CRectangle2 mBG;		    //�Q�[���^�C�g���i�w�i�j
	CRectangle2 mSelectButton;	//�Q�[���J�n
	CRectangle2 mOptionButton;  //�Q�[���I��
	CRectangle2 mShopButton;    //�V���b�v�{�^��
	CRectangle2 mItemButton;    //�V���b�v�{�^��
	CRectangle2 mTitleButton;   //�z�[���{�^��
	CRectangle2 mTextBox;	    //�e�L�X�g�{�b�N�X

	CRectangle2 mRightButton;
	CRectangle2 mLeftButton;

	CRectangle2 mCursor;//�J�[�\��

	CTexture	*mpTexture;
	CTexture	*mpTexCursor;
	CTexture	*mpMenu;

	float alpha;
	float alpha2;

	int mStatus;  //���j���[�ړ������̃X�e�[�^�X

	const float mcMenuX = 150;				     //�{�[�h�̃f�t�H���g�T�C�Y
	const float mcMenuY = 105;

	const float mcBoardSubX = 90;
	const float mcBoardSubY = 65;

	enum E_MENU
	{
		QUEST,//�N�G�X�g
		SHOP,//�V���b�v
		ITEM,//�A�C�e��
		TITLE,//�^�C�g��
	};
	bool mHiddenFlag = false;			//�B��Flag

	bool mMove=false;

	float mMenuPos0 = 0;		//menu�̃|�W�V����
	float mMenuPos1 = 400;
	float mMenuPos2 = 800;
	float mMenuPos3 = 1200;

	~CHome();
	CHome(){};
	void Init();
	void AllMove(bool zeroover);
	void Update();
	void Render();

};
#endif
