//�����O��
#include "CShop.h"
#include"../../../Define/Define.h"
#include "../../Key/CKey.h"
#include <fstream> 
#include<stdio.h>
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"

#define POCKET_MONEY_TEX		  0,601,900,800 
#define POCKET_MONEY_RECT -100.0f, 40, 100.0f, -40
/*tex�t�F�C��*/
#define CURSOR_CG 0,0,150,120

bool CShop::mBuyScene = false;
bool CShop::mSoldOut[WEAPON_TYPE];

CShop::~CShop(){
	if (mpNum) {
		//�e�N�X�`�����g���Ă���΃C���X�^���X�폜
		delete mpNum;
		mpNum = 0;
	}
	if (mpWeaponName) {
		//�e�N�X�`�����g���Ă���΃C���X�^���X�폜
		delete mpWeaponName;
		mpWeaponName = 0;
	}
	if (mpTexture) {
		//�e�N�X�`�����g���Ă���΃C���X�^���X�폜
		delete mpTexture;
		mpTexture = 0;
	}

	if (mpDollar) {
		//�e�N�X�`�����g���Ă���΃C���X�^���X�폜
		delete mpDollar;
		mpDollar = 0;
	}
	
	if (mpBuyButton) {
		//�e�N�X�`�����g���Ă���΃C���X�^���X�폜
		delete mpBuyButton;
		mpBuyButton = 0;
	}
}

CShop::CShop() :mWeapnNo(WEAPON0){}

//�����ݒ���s��
void CShop::Init(){

	//����͔���؂�ɂ��Ă������ɂ���čw���ɂ͏���������Ǝv�킹��
	mSoldOut[WEAPON2] = true;
	mSoldOut[WEAPON3] = true;

	mWeapnAtk[WEAPON0] = WEAPON_ATK0;//����U����
	mWeapnAtk[WEAPON1] = WEAPON_ATK1;
	mWeapnAtk[WEAPON2] = WEAPON_ATK2;
	mWeapnAtk[WEAPON3] = WEAPON_ATK3;

	mPrice   [WEAPON0] = WEAPON_PRICE0;//����U����
	mPrice   [WEAPON1] = WEAPON_PRICE1;
	mPrice   [WEAPON2] = WEAPON_PRICE2;
	mPrice   [WEAPON3] = WEAPON_PRICE3;

	//�w�i�̌Ăяo��
	mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpTexture->load(TGA_FILE"BG.tga");	//�e�N�X�`���t�@�C���ǂݍ���

	mBackGround.SetVertex(BG_SIZE); //�����ő傫���ύX
	mBackGround.SetColor(WHITE_COLOR);
	mBackGround.SetUv(mpTexture, 0, 0, 1024, 768);

	//�{�[�h�̌Ăяo��
	mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpTexture->load(TGA_FILE"Board0.tga");	//�e�N�X�`���t�@�C���ǂݍ���

	mBoard[WEAPON0].SetVertex(-mcBoardX, mcBoardY, mcBoardX, -mcBoardY); //�����ő傫���ύX
	mBoard[WEAPON0].SetColor(WHITE_COLOR);
	mBoard[WEAPON0].position = CVector2(0, 90);
	mBoard[WEAPON0].SetUv(mpTexture, 0, 0, 600, 494);

	mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpTexture->load(TGA_FILE"Board1.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	mBoard[WEAPON1].SetVertex(-mcBoardX, mcBoardY, mcBoardX, -mcBoardY); //�����ő傫���ύX
	mBoard[WEAPON1].SetColor(WHITE_COLOR);
	mBoard[WEAPON1].position = CVector2(0, 90);
	mBoard[WEAPON1].SetUv(mpTexture, 0, 0, 600, 494);
	mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpTexture->load(TGA_FILE"Board2.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	mBoard[WEAPON2].SetVertex(-mcBoardX, mcBoardY, mcBoardX, -mcBoardY); //�����ő傫���ύX
	mBoard[WEAPON2].SetColor(WHITE_COLOR);
	mBoard[WEAPON2].position = CVector2(0, 90);
	mBoard[WEAPON2].SetUv(mpTexture, 0, 0, 600, 494);
	mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpTexture->load(TGA_FILE"Board3.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	mBoard[WEAPON3].SetVertex(-mcBoardX, mcBoardY, mcBoardX, -mcBoardY); //�����ő傫���ύX
	mBoard[WEAPON3].SetColor(WHITE_COLOR);
	mBoard[WEAPON3].position = CVector2(0, 90);
	mBoard[WEAPON3].SetUv(mpTexture, 0, 0, 600, 494);



	//SoldOut�̊�{�ݒ���{�[�h�Ɠ����ɂ���
	for (int i = 0; i < WEAPON_TYPE; i++){
		mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpTexture->load(TGA_FILE"soldout.tga");	//�e�N�X�`���t�@�C���ǂݍ���
		mSoldOutTex[i].SetVertex(-mcBoardX, mcBoardY, mcBoardX, -mcBoardY);
		mSoldOutTex[i].SetColor(WHITE_COLOR);
		mSoldOutTex[i].position = CVector2(0, 90);
		mSoldOutTex[i].SetUv(mpTexture, 0, 0, 600, 494);
	}

	float WeaponNameX = NAME_X;
	float WeaponNameY = NAME_Y;

	int WeaponNameTexY1 = NAME_TEX_Y1;
	int WeaponNameTexY2 = NAME_TEX_Y2;

		//������

		mpNum = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpNum->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
		mPocketMoney[2].SetVertex(ATK_NUM_RECT);
		mPocketMoney[2].SetColor(WHITE_COLOR);
		mPocketMoney[2].position = P_POS3;
		mPocketMoney[2].ZERO;

		mpNum = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpNum->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
		mPocketMoney[1].SetVertex(ATK_NUM_RECT);
		mPocketMoney[1].SetColor(WHITE_COLOR);
		mPocketMoney[1].position = P_POS2;
		mPocketMoney[1].ZERO;

		mpNum = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpNum->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
		mPocketMoney[0].SetVertex(ATK_NUM_RECT);
		mPocketMoney[0].SetColor(WHITE_COLOR);
		mPocketMoney[0].position = P_POS1;
		mPocketMoney[0].ZERO;
	

		//�I�𒆂̉��i�ݒ�
		mpNum = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpNum->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
		mPriceSave[2].SetVertex(ATK_NUM_RECT);
		mPriceSave[2].SetColor(WHITE_COLOR);
		mPriceSave[2].position = PS_POS3;
		mPriceSave[2].ZERO;

		mpNum = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpNum->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
		mPriceSave[1].SetVertex(ATK_NUM_RECT);
		mPriceSave[1].SetColor(WHITE_COLOR);
		mPriceSave[1].position = PS_POS2;
		mPriceSave[1].ZERO;

		mpNum = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpNum->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
		mPriceSave[0].SetVertex(ATK_NUM_RECT);
		mPriceSave[0].SetColor(WHITE_COLOR);
		mPriceSave[0].position = PS_POS1;
		mPriceSave[0].ZERO;


	for (int i = 0; i < WEAPON_TYPE; i++){
		
		//����l�[��
		mpWeaponName = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpWeaponName->load(TGA_FILE"WeaponName.tga");	//�e�N�X�`���t�@�C���ǂݍ���
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		mWeaponName[i].SetVertex(WEAPON_NAME_RECT);
		mWeaponName[i].SetColor(WHITE_COLOR);
		mWeaponName[i].position = CVector2(WEAPON_NAME_POS);
		mWeaponName[i].SetUv(mpWeaponName, WEAPON_NAME_TEX);	
		//////////////////////////////////////////////////////////////////////////////////////

		mpDollar = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpDollar->load(TGA_FILE"Dollar.tga");	//�e�N�X�`���t�@�C���ǂݍ���
		mDollar[i].SetVertex(DOLLAR_RECT);
		mDollar[i].SetColor(WHITE_COLOR);
		mDollar[i].position = CVector2(DOLLAR_POS);
		mDollar[i].DOLLAR;
	
		//���i�����ݒ�
		mpNum = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpNum->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
		mPrice3[i].SetVertex(NUM_RECT);
		mPrice3[i].SetColor(WHITE_COLOR);
		mPrice3[i].position = CVector2(PRICE_3_POS);
		mPrice3[i].ZERO;
		mpNum = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpNum->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
		mPrice2[i].SetVertex(NUM_RECT);
		mPrice2[i].SetColor(WHITE_COLOR);
		mPrice2[i].position = CVector2(PRICE_2_POS);
		mPrice2[i].ZERO;
		mpNum = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpNum->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
		mPrice1[i].SetVertex(NUM_RECT);
		mPrice1[i].SetColor(WHITE_COLOR);
		mPrice1[i].position = CVector2(PRICE_1_POS);
		mPrice1[i].ZERO;
		//////////////////////////////////////////////////////////////////////////////////////
		
		WeaponNameX += NAME_FIRST_SET_MOVE;
		WeaponNameTexY1 += NAME_FIRST_SET_MOVE;
		WeaponNameTexY2 += NAME_FIRST_SET_MOVE;

	}
	//����U����
	mpNum = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNum->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	mWeaponAtk3.SetVertex(ATK_NUM_RECT);
	mWeaponAtk3.SetColor(BLACK_COLOR);
	mWeaponAtk3.position = CVector2(ATK_NUM3_POS);
	mWeaponAtk3.ZERO;
	mpNum = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNum->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	mWeaponAtk2.SetVertex(ATK_NUM_RECT);
	mWeaponAtk2.SetColor(BLACK_COLOR);
	mWeaponAtk2.position = CVector2(ATK_NUM2_POS);
	mWeaponAtk2.ZERO;
	mpNum = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNum->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	mWeaponAtk1.SetVertex(ATK_NUM_RECT);
	mWeaponAtk1.SetColor(BLACK_COLOR);
	mWeaponAtk1.position = CVector2(ATK_NUM1_POS);
	mWeaponAtk1.ZERO;

	//������TEXT
	mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpTexture->load(TGA_FILE"ResultTips.tga");	//�e�N�X�`���t�@�C���ǂݍ���

	mPocketMoneyText.SetVertex(POCKET_MONEY_RECT);
	mPocketMoneyText.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	mPocketMoneyText.SetUv(mpTexture, POCKET_MONEY_TEX);
	mPocketMoneyText.position = MONEY_TEXT_POS;

	////�߂�{�^���̌Ăяo��
	mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpTexture->load(TGA_FILE"backbutton.tga");	//�e�N�X�`���t�@�C���ǂݍ���

	mBackButton.SetVertex(BACK_RECT);
	mBackButton.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	mBackButton.SetUv(mpTexture, BACK_CG);
	mBackButton.position = BACK_POS;



	/*�J�[�\���l�p�쐬*/
	mpTexCursor = new CTexture();
	mpTexCursor->load(TGA_FILE"cursor.tga");
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(mpTexCursor, CURSOR_CG);



	
	//���i�e�N�X�`����\���Ă���
	Number(mPrice[WEAPON0], mPrice1[WEAPON0], mPrice2[WEAPON0], mPrice3[WEAPON0]); 
	Number(mPrice[WEAPON1], mPrice1[WEAPON1], mPrice2[WEAPON1], mPrice3[WEAPON1]);
	Number(mPrice[WEAPON2], mPrice1[WEAPON2], mPrice2[WEAPON2], mPrice3[WEAPON2]);
	Number(mPrice[WEAPON3], mPrice1[WEAPON3], mPrice2[WEAPON3], mPrice3[WEAPON3]);

	//�|�W�V�����̏����ݒ�
	mBoard[WEAPON0].position = CVector2(mWeaponPos0, 90);
	mBoard[WEAPON1].position = CVector2(mWeaponPos0 + mWeaponPos1, 90);
	mBoard[WEAPON2].position = CVector2(mWeaponPos0 + mWeaponPos2, 90);
	mBoard[WEAPON3].position = CVector2(mWeaponPos0 + mWeaponPos3, 90);


	////////�w���m�F��ʂ̐ݒ�//////////////////////////////////////////////////////////////////////////
	//�w���{�^��
	mpBuyButton = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpBuyButton->load(TGA_FILE"buynow.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	mBuy.SetVertex(BUY_BOX_RECT);
	mBuy.SetColor(WHITE_COLOR);
	mBuy.position = CVector2(180, -70);
	mBuy.SetUv(mpBuyButton, BUY_BOX_TEX);

	mBuyShadow = mBuy;
	mBuyShadow.SetColor(SKELETON_BLACK_COLOR);
	mBuyShadow.position = CVector2(183, -75);

	//�C�G�X�{�^��
	mpBuyButton = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpBuyButton->load(TGA_FILE"YesNo.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	mYes.SetVertex(YES_NO_RECT);
	mYes.SetColor(WHITE_COLOR);
	mYes.position = CVector2(-120, -100);
	mYes.SetUv(mpBuyButton, YES_TEX);

	//�m�[�{�^��
	mpBuyButton = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpBuyButton->load(TGA_FILE"YesNo.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	mNo.SetVertex(YES_NO_RECT);
	mNo.SetColor(WHITE_COLOR);
	mNo.position = CVector2(120, -100);
	mNo.SetUv(mpBuyButton, NO_TEX);



	//�������̔w�i�̌Ăяo��
	mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpTexture->load(TGA_FILE"BG.tga");	//�e�N�X�`���t�@�C���ǂݍ���

	mSmoke.SetVertex(BUY_WINDOW_SIZE); //�����ő傫���ύX
	mSmoke.SetColor(SKELETON_BLACK_COLOR);
	mSmoke.SetUv(mpTexture, 0, 0, 10, 10);


	status = 0;//�f�t�H���g��0
}

//�����̃e�N�X�`���ݒ���s��
void CShop::Number(int score, CRectangle2 &odifit, CRectangle2 &twdifit, CRectangle2 &thdifit){		//�����̏���
	//�X�R�A��100�Ŋ��邱�Ƃ�3���ڂ��擾
	int difit3 = score / 100;
	//�X�R�A�� 10�Ŋ��邱�Ƃ�2���ڂ��擾
	int difit2 = (score - (difit3 * 100)) / 10;
	//�X�R�A��  1�Ŋ��邱�Ƃ�1���ڂ��擾
	int difit1 = score - ((difit3 * 100) + (difit2 * 10));
	//�R�P�^��
	//�ǂ̐��������ʂƂ��ďo�����ŏ�����ς���
	if (difit3 <= 0){thdifit. ZERO;}
	if (difit3 == 1){thdifit.  ONE;}
	if (difit3 == 2){thdifit.  TWO;}
	if (difit3 == 3){thdifit.THREE;}
	if (difit3 == 4){thdifit. FOUR;}
	if (difit3 == 5){thdifit. FIVE;}
	if (difit3 == 6){thdifit.  SIX;}
	if (difit3 == 7){thdifit.SEVEN;}
	if (difit3 == 8){thdifit.EIGHT;}
	if (difit3 == 9){thdifit. NINE;}
	//2�P�^��
	//�ǂ̐��������ʂƂ��ďo�����ŏ�����ς���
	if (difit2 <= 0){twdifit. ZERO;}
	if (difit2 == 1){twdifit.  ONE;}
	if (difit2 == 2){twdifit.  TWO;}
	if (difit2 == 3){twdifit.THREE;}
	if (difit2 == 4){twdifit. FOUR;}
	if (difit2 == 5){twdifit. FIVE;}
	if (difit2 == 6){twdifit.  SIX;}
	if (difit2 == 7){twdifit.SEVEN;}
	if (difit2 == 8){twdifit.EIGHT;}
	if (difit2 == 9){twdifit. NINE;}
	//1�P�^��
	//�ǂ̐��������ʂƂ��ďo�����ŏ�����ς���
	if (difit1 <= 0){odifit. ZERO;}
	if (difit1 == 1){odifit.  ONE;}
	if (difit1 == 2){odifit.  TWO;}
	if (difit1 == 3){odifit.THREE;}
	if (difit1 == 4){odifit. FOUR;}
	if (difit1 == 5){odifit. FIVE;}
	if (difit1 == 6){odifit.  SIX;}
	if (difit1 == 7){odifit.SEVEN;}
	if (difit1 == 8){odifit.EIGHT;}
	if (difit1 == 9){odifit. NINE;}
}

//���ڑS�̂̈ړ�����
void CShop::AllMove(bool zeroover){
	if ( zeroover){mWeaponPos0 += MOVE_SPEED;mWeaponPos1 += MOVE_SPEED;mWeaponPos2 += MOVE_SPEED;mWeaponPos3 += MOVE_SPEED;}
	if (!zeroover){mWeaponPos0 -= MOVE_SPEED;mWeaponPos1 -= MOVE_SPEED;mWeaponPos2 -= MOVE_SPEED;mWeaponPos3 -= MOVE_SPEED;}
}

//�X�V�������s��
void CShop::Update(){
	if (CKey::push('W')){
		mItem.mMoney += 100;
	}

	//��ɏ����l�ł̍X�V���s���������
	mWeaponName[WEAPON0].SetColor(WHITE_COLOR);
	mWeaponName[WEAPON1].SetColor(WHITE_COLOR);
	mWeaponName[WEAPON2].SetColor(WHITE_COLOR);
	mWeaponName[WEAPON3].SetColor(WHITE_COLOR);
	mBackButton.SetColor(WHITE_COLOR);
	mBuy.SetColor(WHITE_COLOR);
	mBuy.position = CVector2(180, -70);
	if (mBuyScene)mBuy.position = CVector2(183, -75);
	//�\�[���h�A�E�g�̃|�W�V�������{�[�h�Ɠ����ʒu�ɂ���
	for  (int i = 0; i < WEAPON_TYPE; i++)
	{
		mSoldOutTex[i].position = mBoard[i].position;
	}
	//backButton�ƐڐG�������ɔ��ʂł���悤�ɐF��ς���
	if (CCollision2D::Collision2D(mCursor, mBackButton)){ mBackButton.SetColor(GRAY_COLOR); }
	//�\�[���h�A�E�g�t���O�������Ă��鎞�͐ԐF�ŕ\������
	if (mSoldOut[WEAPON0])mBoard[WEAPON0].SetColor(DARK_GRAY_COLOR);
	if (mSoldOut[WEAPON1])mBoard[WEAPON1].SetColor(DARK_GRAY_COLOR);
	if (mSoldOut[WEAPON2])mBoard[WEAPON2].SetColor(DARK_GRAY_COLOR);
	if (mSoldOut[WEAPON3])mBoard[WEAPON3].SetColor(DARK_GRAY_COLOR);

	//������菊�����𑝂₹��z
	if (CKey::push('W')){ mItem.mMoney += 10.0f; }


	//�������̃i���o�[�e�N�X�`���X�V
	Number(mItem.mMoney, mPocketMoney[0], mPocketMoney[1], mPocketMoney[2]);
	//�I�𒆂̉��i�̃e�N�X�`���ύX
	Number(mPriceSelect, mPriceSave[0], mPriceSave[1], mPriceSave[2]);

	//����U���͂̍X�V
	mWeaponAtk1.SetVertex(ATK_NUM_RECT);
	mWeaponAtk2.SetVertex(ATK_NUM_RECT);
	mWeaponAtk3.SetVertex(ATK_NUM_RECT);
	mBuy.SetVertex(BUY_BOX_RECT);
	mBuyShadow.SetVertex(BUY_BOX_RECT);
	//�B���l�p�`�̏���
	if (mHiddenFlag&&mMoveY>0){ mMoveY =0; }
	else if (!mHiddenFlag&&mMoveY < mcDefaultHidden){ mMoveY++; }
	//����{�[�h�̍X�V
	mBoard[WEAPON0].position = CVector2(mWeaponPos0, BOARD_Y);
	mBoard[WEAPON1].position = CVector2(mWeaponPos1, BOARD_Y);
	mBoard[WEAPON2].position = CVector2(mWeaponPos2, BOARD_Y);
	mBoard[WEAPON3].position = CVector2(mWeaponPos3, BOARD_Y);
	//����ڍׂ̕\���ׂ̈̏���
	if (!mBuyScene){//�w���m�F��ʂłȂ���Ώ������s��
		if (CCollision2D::Collision2D(mCursor, mWeaponName[WEAPON0]) ||
			CCollision2D::Collision2D(mCursor, mBoard[WEAPON0])){ //�J�[�\���������Ă���?
			mWeaponName[WEAPON0].SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag)//�}�E�X���N���b�N
				mWeapnNo = WEAPON0;
			mHiddenFlag = true;
		}
		if (CCollision2D::Collision2D(mCursor, mWeaponName[WEAPON1]) ||
			CCollision2D::Collision2D(mCursor, mBoard[WEAPON1])){ //�J�[�\���������Ă���?
			mWeaponName[WEAPON1].SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag)//�}�E�X���N���b�N
				mWeapnNo = WEAPON1;
			mHiddenFlag = true;
		}
		if (CCollision2D::Collision2D(mCursor, mWeaponName[WEAPON2]) ||
			CCollision2D::Collision2D(mCursor, mBoard[WEAPON2])){ //�J�[�\���������Ă���?
			mWeaponName[WEAPON2].SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag)//�}�E�X���N���b�N
				mWeapnNo = WEAPON2;
			mHiddenFlag = true;
		}
		if (CCollision2D::Collision2D(mCursor, mWeaponName[WEAPON3]) ||
			CCollision2D::Collision2D(mCursor, mBoard[WEAPON3])){ //�J�[�\���������Ă���?
			mWeaponName[WEAPON3].SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag)//�}�E�X���N���b�N
				mWeapnNo = WEAPON3;
			mHiddenFlag = true;
		}
		
		//�w���{�^�����������Ƃ��̏���
		if (CCollision2D::Collision2D(mCursor, mBuy)){ //�J�[�\���������Ă���
			mBuy.SetColor(DARK_GRAY_COLOR);
			//�\�[���h�A�E�g�ɂȂ�ƍw���{�^���𖳌��ɂ���
			for (int i = 0; i <WEAPON_TYPE; i++)
			{
				if (mWeapnNo == i&&!mSoldOut[i] && !mSoldOut[i]){
					if (CMouse::GetInstance()->mOneLeftFlag){ mBuyScene = true;/*�w����^��*/ 
					}/*�}�E�X���N���b�N*/ 
				}
			}
		}
	}
	else{
		//�C�G�X�{�^�����������Ƃ��̏���
		if (CCollision2D::Collision2D(mCursor, mYes)){ //�J�[�\���������Ă���?
			if (CMouse::GetInstance()->mOneLeftFlag){ 
				//WEAPON0��I�����Ă���//����؂�ɂȂ��Ă��Ȃ��ꍇ
				if (mWeapnNo == WEAPON0){
					//���������w�����镐��̉��i�𒴂��Ă���ꍇ
					if (mPrice[WEAPON0] < mItem.mMoney)
					{
						mItem.mMoney -= mPrice[WEAPON0];
						
						//�w�����̏��� ����؂ꏈ����
						
						//�{�[�h��Ԃɂ��Ĕ���؂������
						mBoard[WEAPON0].SetColor(RED_COLOR);
						mSoldOut[WEAPON0] = true;
						//�w����ʂ����
						mBuyScene = false;
					}
				}
				//WEAPON1��I�����Ă���
				else if (mWeapnNo == WEAPON1&&!mSoldOut[WEAPON1]){
					//���������w�����镐��̉��i�𒴂��Ă���ꍇ
					if (mPrice[WEAPON1] < mItem.mMoney)
					{ 
						mItem.mMoney -= mPrice[WEAPON1];
						mBoard[WEAPON1].SetColor(RED_COLOR);
						mSoldOut[WEAPON1] = true;
						mBuyScene = false;
					}
				}
				//WEAPON2��I�����Ă���
				else if (mWeapnNo == WEAPON2&&!mSoldOut[WEAPON2]){
					//���������w�����镐��̉��i�𒴂��Ă���ꍇ
					if (mPrice[WEAPON2] < mItem.mMoney)
					{ 
						mItem.mMoney -= mPrice[WEAPON2];
						mBoard[WEAPON2].SetColor(RED_COLOR);
						mSoldOut[WEAPON2] = true;
						mBuyScene = false;
					}
				}
				//WEAPON3��I�����Ă���
				else if (mWeapnNo == WEAPON3&&!mSoldOut[WEAPON3]){
					//���������w�����镐��̉��i�𒴂��Ă���ꍇ
					if (mPrice[WEAPON3] < mItem.mMoney)
					{
						mItem.mMoney -= mPrice[WEAPON3];
						mBoard[WEAPON3].SetColor(RED_COLOR);
						mSoldOut[WEAPON3] = true;
						mBuyScene = false;
					}
				}
				else{ mBuyScene = false; }
			}//�}�E�X���N���b�N
		}
		//�m�[�{�^�����������Ƃ��̏���
		if (CCollision2D::Collision2D(mCursor, mNo)){ //�J�[�\���������Ă���?
			if (CMouse::GetInstance()->mOneLeftFlag){ mBuyScene = false;/*�w����^��*/ }//�}�E�X���N���b�N
		}
	}

	//�I����������ɂ���ă|�W�V������ϓ�������B
	switch (mWeapnNo)
	{
	case WEAPON0:
		//�\�[���h�A�E�g�̎��͍w���{�^����s����������
		if (mSoldOut[WEAPON0])mBuy.SetColor(DARK_GRAY_COLOR);
		//���i�ݒ�𕐊했�ɍX�V����
		mPriceSelect = mPrice[WEAPON0];
		//�����e�N�X�`��
		Number(mWeapnAtk[WEAPON0], mWeaponAtk1, mWeaponAtk2, mWeaponAtk3);
		//�B���t���O�ƈړ��t���O���Ǘ����Ĉړ��������s��
		if (mWeaponPos0 == 0)mHiddenFlag = false;
		if (mWeaponPos0 < 0/*�|�W�V�����O*/) { AllMove(true); }
		else if (mWeaponPos0 > 0) { AllMove(false); }
	    break;

	case WEAPON1:
		if (mSoldOut[WEAPON1])mBuy.SetColor(DARK_GRAY_COLOR);
		mPriceSelect = mPrice[WEAPON1];
		Number(mWeapnAtk[WEAPON1], mWeaponAtk1, mWeaponAtk2, mWeaponAtk3);
		if (mWeaponPos1 == 0)mHiddenFlag = false;
		if (mWeaponPos1 < 0) { AllMove(true); }
		else if (mWeaponPos1 > 0) { AllMove(false); }
		break;

	case WEAPON2 :
		if (mSoldOut[WEAPON2])mBuy.SetColor(DARK_GRAY_COLOR);
		mPriceSelect = mPrice[WEAPON2];
		Number(mWeapnAtk[WEAPON2], mWeaponAtk1, mWeaponAtk2, mWeaponAtk3);
		if (mWeaponPos2 == 0)mHiddenFlag = false;
		if (mWeaponPos2 < 0) { AllMove(true); }
		else if (mWeaponPos2 > 0) { AllMove(false); }
		break;

	case WEAPON3:
		if (mSoldOut[WEAPON3])mBuy.SetColor(DARK_GRAY_COLOR);
		mPriceSelect = mPrice[WEAPON3];
		Number(mWeapnAtk[WEAPON3], mWeaponAtk1, mWeaponAtk2, mWeaponAtk3);
		if (mWeaponPos3 == 0)mHiddenFlag = false;
		if (mWeaponPos3 < 0) { AllMove(true); }
		else if (mWeaponPos3 > 0) { AllMove(false); }
		break;

	default:
		break;
	}
	mBoard[WEAPON0].SetVertex(-mBoardX, mBoardY, mBoardX, -mBoardY); //�����ő傫���ύX
	mCursor.position = CMouse::GetInstance()->mPos;	//�J�[�\���̃|�W�V����
	//�{�[�h�̈ړ�����
	if (mBoardX >= mcBoardX + mcBoardSubX){mBoardX -= mcBoardSubX;}
	if (mBoardY >= mcBoardY + mcBoardSubY){mBoardY -= mcBoardSubY;}
};

//�`�悷��
void CShop::Render() {

	CRectangle2::Disp2D_Start();//�`��J�n
	mBackGround.Render();
	mBackButton.Render();
	for (int i = 0; i < WEAPON_TYPE; i++) { 
		mBoard[i].Render();
		mWeaponName[i].Render();
		mDollar[i]    .Render();
		mPrice3[i]    .Render();
		mPrice2[i]    .Render();
		mPrice1[i]    .Render();
	};
	for (int i = 0; i < DIGIT; i++)
	{
		mPocketMoney[i].Render();
	}
	mBuyShadow.Render();
	mBuy.Render();
	mWeaponAtk3.Render();
	mWeaponAtk2.Render();
	mWeaponAtk1.Render();
	mPocketMoneyText.Render();
	for (int i = 0; i < WEAPON_TYPE; i++) {
		if (mSoldOut[i]){
			mSoldOutTex[i].Render();
		}
	}
	if (mBuyScene){
		mSmoke.Render();
		for (int i = 0; i < DIGIT; i++)
		{
			mPriceSave[i].Render();
		}
		mYes.Render();
		mNo.Render();
	}
	mCursor.Render();
	CRectangle2::Disp2D_Exit();//�`��I��
}
/*












�@�@              �@�� .�^�j)�@�@�@�@�@�@�@�^
	 �@       �@�@���]����k(_             <�@�@�L�����ł��B
	          �@.�f,g�M.�턥��Y�R�@�@�@    �_
		   �@�^ * �@ ����������
		   . L���m�P�@�@�@�M���������
			�@ �@ �@ �@ �@ �@ ���@�����e�
						  �@�@ ���������ҭ�C
							 �@ ���������]�㭁C
					             �������������
			              �@�@�@�@�� .����������
							     �@������������������
							       ������������������������
				�@ �@ �@ �@ �@ �@ ��.������������������������ �C
		   �@ �@ �@ �@ �@ �@ �@ �@ �����������������������������]�.,,,,,�Q___ ,��k�
				    �@ �@ �@ �@ �@ �����������������������������M'''''''''''''''''''''�T �B�L
				 �@�@ �@ �@   �@ �@ ,����������������������������
							  �@ �@ /������@ �@.�M�N�N�f.T�L����Rt�����]!
					  �@ �@ �@ �@ �^���C �@! �@ �@ �@ �@ !. �����@ �_���� ,
			   �@�@ �@ �@ �@ �@ ,�X�C�@ |�����@ �@ �@�@�@�f���'. �@ �@.�M�@,�����C
					  �@  �@ �@{��� �@�@|��!�@�@�@�@ �@ �@�@�S��ʁ@�@�@�@ �M�S����,
						   �@�@ �_ �R �@ }�@/�@�@ �@ �@ �@ �@ �@̈́�ʁ@ �@ �@�@ �M'���
						   �@�@�@ �_�_ٲ �@ �@ �@ �@ �@ �@.�@Ɂ@,��@�@�@�@ �@ �@ �R�@											
							        �R,�_ �@ �@ �@ �@ �@�@�@./ /�@�@�@�@ �@ �@ �@�@�@'.�.
							�@�@�@�@ �n__�M��. �@ �@ �@ �@ / / �@ �@ �@ �@ �@�@�@�@�@ '.�@�
			    �@ �@ �@ �@ �@ �@ �@ / f�L�@�_ʁ@�@�@�@�@ / /�@�@�@�@�@�@�@�@�@�@�@�@�@} �n
					 �@ �@ �@�@ �@ �^.���@��@ �M�f�@�@�@.�^ Ɂ@ �@ �@ �@ �@ �@�@�@�@�@�@�__ .,�f
						      �@ �� ���@�@�@ �@ �@ �@ �� ���@�@�@�@�@�@�@�@�@�@�@�@�@�@{_ �C


*/