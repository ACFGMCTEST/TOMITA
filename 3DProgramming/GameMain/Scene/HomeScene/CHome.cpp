//�����O�� && �y�c���l
#include"CHome.h"
#include "../Define\Define.h"
#include <fstream> 
#include <stdio.h>
#include "../GameMain\Key\CKey.h"
#include "../../Key/CMouse.h"
#include "../../Collision/CCollision2D.h"
/*�T�C�Y�}�N��*/
#define BG_SIZE -DISP_X,DISP_Y,DISP_X,-DISP_Y

#define MENU_SIZE   -150, 150, 150, -150

#define BIG_SIZE    -200, 200, 200, -200

#define TEST_SIZE	- 40, 400,  40, -400

#define MOVE_R		   0,   0, 100, 1000

#define MOVE_L		   0,   0,-100, 1000

#define HOME_ICON_CG  0, 0, 300, 300

#define CURSOR_CG 0,0,150,120

#define RE_MOVE_Y    -50

#define TEXT_BOX_SIZE -310.0f, 220.0f, 80.0f, -80.0f

#define UNITY_CHAN_SIZE   -223.0f, 346.5f, 223.0f, -346.5f
#define UNITY_CHAN_UV           0,      0,    446,     693
#define LOOP_SPEED		0.01f
CHome::~CHome(){
	if (mpTexture) {
		//�e�N�X�`�����g���Ă���΃C���X�^���X�폜
		delete mpTexture;
		mpTexture = 0;
	}
	if (mpMenu) {
		//�e�N�X�`�����g���Ă���΃C���X�^���X�폜
		delete mpMenu;
		mpMenu = 0;
	}
}

void CHome::Init(){

	mStatus = QUEST;
	alpha = 0.0f;
	alpha2 = 0.0f;

	//�w�i�̌Ăяo��
	mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpTexture->load(TGA_FILE"BG.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	mBG.SetVertex(BG_SIZE); //�����ő傫���ύX
	mBG.SetColor(WHITE_COLOR);
	mBG.SetUv(mpTexture, BG_SIZE);

	//�N�G�X�g�I���{�^���Ăяo��
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"questicon.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	mSelectButton.SetVertex(MENU_SIZE);
	mSelectButton.SetColor(WHITE_COLOR);
	mSelectButton.SetUv(mpMenu, HOME_ICON_CG);
	
	//�V���b�v�{�^���̌Ăяo��	
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"shopicon.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	mShopButton.SetVertex(MENU_SIZE);
	mShopButton.SetColor(WHITE_COLOR);
	mShopButton.SetUv(mpMenu, HOME_ICON_CG);

	//�A�C�e����ʂ̌Ăяo���B
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"itemicon.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	mItemButton.SetVertex(MENU_SIZE);
	mItemButton.SetColor(WHITE_COLOR);
	mItemButton.SetUv(mpMenu, HOME_ICON_CG);

	//�^�C�g���o�b�N��ʂ̌Ăяo��
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"exiticon.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	mTitleButton.SetVertex(MENU_SIZE);
	mTitleButton.SetColor(WHITE_COLOR);
	mTitleButton.SetUv(mpMenu, HOME_ICON_CG);

	//���j���[�̃|�W�V�������w�肷��B
	mSelectButton.position = CVector2(mMenuPos0            , 0);
	mShopButton  .position = CVector2(mMenuPos0 + mMenuPos1, 0);
	mItemButton  .position = CVector2(mMenuPos0 + mMenuPos2, 0);
	mTitleButton .position = CVector2(mMenuPos0 + mMenuPos3, 0);

	/*�J�[�\���l�p�쐬*/
	mpTexCursor = new CTexture();
	mpTexCursor->load(TGA_FILE"cursor.tga");
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(mpTexCursor, CURSOR_CG);

	 // E_GREEN_YELLOW,	//�΂��物
	 // E_YELLOW_RED,	//�������
	 // E_RED_PURPLE,	//�Ԃ��率
	 // E_PURPLE_BLUE,	//�������
	 // E_BLUE_CYAN,	//�����
	 // E_CYAN_GREEN,	//�΂����

	mSelectButton.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_RED_PURPLE);
	mShopButton.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_YELLOW_RED);
	mItemButton.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_GREEN_YELLOW);
	mTitleButton.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_BLUE_CYAN);
}


//���ڑS�̂̈ړ�����
void CHome::AllMove(bool zeroover){
	if ( zeroover){ mMenuPos0 += MOVE_SPEED; mMenuPos1 += MOVE_SPEED; mMenuPos2 += MOVE_SPEED; mMenuPos3 += MOVE_SPEED; }
	if (!zeroover){ mMenuPos0 -= MOVE_SPEED; mMenuPos1 -= MOVE_SPEED; mMenuPos2 -= MOVE_SPEED; mMenuPos3 -= MOVE_SPEED; }
}

void CHome::Update(){
	//�J�[�\���|�W�V����
	mCursor.position = CMouse::GetInstance()->mPos;
	//���j���[�̃T�C�Y���펞�A�b�v�f�[�g����(�ϓ����邽��)
	mSelectButton.SetVertex(MENU_SIZE);
	mShopButton.SetVertex(MENU_SIZE);
	mItemButton.SetVertex(MENU_SIZE);
	mTitleButton.SetVertex(MENU_SIZE);
	//�J���[���A�b�v�f�[�g����
	if (mStatus != QUEST) mSelectButton.SetColor(WHITE_COLOR);
	if (mStatus != SHOP)mShopButton.SetColor(WHITE_COLOR);
	if (mStatus != ITEM)mItemButton.SetColor(WHITE_COLOR);
	if (mStatus != TITLE)mTitleButton.SetColor(WHITE_COLOR);

	//�|�W�V�����̍X�V�BY�͂O�Ƃ���
	mSelectButton.position = CVector2(mMenuPos0, 0);
	mShopButton.position   = CVector2(mMenuPos1, 0);
	mItemButton.position   = CVector2(mMenuPos2, 0);
	mTitleButton.position  = CVector2(mMenuPos3, 0);

//���C�g�{�^�����t�g�{�^���̑J�ڏ���
	switch (mStatus)
	{
	case QUEST:
		//���j���[�̃T�C�Y��傫������B
		mSelectButton.SetVertex(BIG_SIZE);
		mSelectButton.GradationLoop(LOOP_SPEED);
		//�������ɉ�����
		mSelectButton.position = CVector2(mMenuPos0, RE_MOVE_Y);
		//�X�e�[�^�X��ύX����
		//�}�E�X�J�[�\���������Ă��邩
		if (CCollision2D::Collision2D(mCursor, mShopButton)){
			mShopButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag){ mMove = true; mStatus = SHOP; }}
		     if (mMenuPos0 < 0)    { AllMove(true); } //�|�W�V������0���傫������������������move���w�肷��
		else if (mMenuPos0 > 0)    { AllMove(false); }
		     if (mMenuPos0 != 0.0f){ mMove = false; }//���j���[���ړ�����ƃN���b�N��L����

		break;
	case SHOP:
		mShopButton.SetVertex(BIG_SIZE);
		mShopButton.GradationLoop(LOOP_SPEED);
		mShopButton.position = CVector2(mMenuPos1, RE_MOVE_Y);
		if (CCollision2D::Collision2D(mCursor, mItemButton))  {
			mItemButton.SetColor(GRAY_COLOR);
		if (CMouse::GetInstance()->mOneLeftFlag){ mMove = true; mStatus = ITEM; } }

		if (CCollision2D::Collision2D(mCursor, mSelectButton)){
			mSelectButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag){ mMove = true; mStatus = QUEST; }}

		     if (mMenuPos1 < 0)    { AllMove(true);  }
		else if (mMenuPos1 > 0)    { AllMove(false); }
		     if (mMenuPos1 != 0.0f){ mMove = false; }

		break;
	case ITEM:
		mItemButton.SetVertex(BIG_SIZE);
		mItemButton.GradationLoop(LOOP_SPEED);
		mItemButton.position = CVector2(mMenuPos2, RE_MOVE_Y);
		if (CCollision2D::Collision2D(mCursor, mTitleButton)){
			mTitleButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag){ mMove = true; mStatus = TITLE; }}
		if (CCollision2D::Collision2D(mCursor, mShopButton )){ 
			mShopButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag){ mMove = true; mStatus = SHOP; }}
		     if (mMenuPos2 < 0)     { AllMove(true); }
		else if (mMenuPos2> 0)      { AllMove(false);}
		     if (mMenuPos2 != 0.0f) { mMove = false; }
		
		break;
	case TITLE:
		mTitleButton.SetVertex(BIG_SIZE);
		mTitleButton.GradationLoop(LOOP_SPEED);
		mTitleButton.position = CVector2(mMenuPos3, RE_MOVE_Y);
		if (CCollision2D::Collision2D(mCursor, mItemButton)){
			mItemButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag) { mMove = true; mStatus = ITEM; }}
		     if (mMenuPos3 < 0)    { AllMove(true); }
		else if (mMenuPos3 > 0)    { AllMove(false); }
	     	 if (mMenuPos3 != 0.0f){ mMove = false; }
		
		break;
	}

};

/*
�`�揈���݂̂��s���B
*/
void CHome::Render() {
	CRectangle2::Disp2D_Start();//�`��͂���
	mBG.Render();	
	mSelectButton.Render();
	mShopButton.Render();
	mItemButton.Render();
	mTitleButton.Render();

	mCursor.Render();
	CRectangle2::Disp2D_Exit();//�`��I���
}