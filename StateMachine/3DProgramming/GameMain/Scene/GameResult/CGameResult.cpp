//�����O���@&& �y�c���l�@
#include"CGameResult.h"
#include "../../Graphic/CTexture.h"
#include "../../Key/CKey.h"
#include "../../../Define/Define.h"
#include "../../Key/CMouse.h"
#include "../GameScene/UI/CScoreBoard.h"
#include "../../Collision/CCollision2D.h"
#include <fstream> 
#include<stdio.h>
#include <Windows.h>


#define ZERO	 SetUv(mpNumber,   0,   0,  100, 100);
#define ONE		 SetUv(mpNumber, 100,   0,  200, 100);
#define TWO		 SetUv(mpNumber, 200,   0,  300, 100);
#define THREE	 SetUv(mpNumber, 300,   0,  400, 100);
#define FOUR	 SetUv(mpNumber, 400,   0,  500, 100);
#define FIVE	 SetUv(mpNumber, 500,   0,  600, 100);
#define SIX		 SetUv(mpNumber, 600,   0,  700, 100);
#define SEVEN	 SetUv(mpNumber, 700,   0,  800, 100);
#define EIGHT	 SetUv(mpNumber, 800,   0,  900, 100);
#define NINE	 SetUv(mpNumber, 900,   0, 1000, 100);

/*�T�C�Y*/
#define BG_SIZE -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y
#define TITLE_SIZE -400.0f, 280.0f, 400.0f, -280.0f
#define GAME_STATE_SIZE -120.0f, -80.0f, 120.0f, -140.0f
#define GAME_EXIT_SIZE - 120.0f, -160.0f, 120.0f, -220.0f

#define PNUM_SIZE -25.0f,25.0f,25.0f,-25.0f

#define NUM_POS3  CVector2( 140,  70)	//�x�[�X�}�l�[
#define NUM_POS2  CVector2(  80,  70)
#define NUM_POS1  CVector2(  20,  70)

#define MNUM_POS1 CVector2( 140, -30) //�{��
#define MNUM_POS2 CVector2(  80, -30)

#define TNUM_POS1 CVector2( 140, -130) //�g�[�^���}�l�[
#define TNUM_POS2 CVector2(  80, -130)
#define TNUM_POS3 CVector2(  20, -130)

#define PNUM_POS1 CVector2( 140, -250) //�|�P�b�g�}�l�[
#define PNUM_POS2 CVector2(  80, -250)
#define PNUM_POS3 CVector2(  20, -250)

#define ALPHA_HALF 0.5f
#define RESULT_FADE 0.02f


//TIPS�̐ݒ�
#define TIP_RECT -100.0f, 40, 100.0f, -40

#define TIP_POS0  CVector2( -210,  70)
#define TIP_POS1  CVector2( -210,  -30)	
#define TIP_POS2  CVector2( -210,  -130)	
#define TIP_POS3  CVector2( -210,  -250)	

#define TIP_TEX0		  0,  0,900,200 
#define TIP_TEX1		  0,201,900,400 
#define TIP_TEX2		  0,401,900,600 
#define TIP_TEX3		  0,601,900,800 

int CGameResult::mPrize = 0;

CGameResult::CGameResult() :mQuestMoney(0),mTotal(777){
}

CGameResult::~CGameResult(){
	if (mpTexture) {
		//�e�N�X�`�����g���Ă���΃C���X�^���X�폜
		delete mpTexture;
		mpTexture = nullptr;
	}

}

void CGameResult::Init(){
	mNumCount = 0;
	mPocketMoneySave = mItem.mMoney;

	//�w�i�̌Ăяo��

	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"Cle_ar.tga");

	mBG.SetVertex(BG_SIZE); //�����ő傫���ύX
	mBG.SetColor(W_COLOR, mAlpha);
	mBG.SetUv(mpTexture, TEST_CG);

	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"Clear.tga");

	//�^�C�g�����S�̌Ăяo��

	mResult.SetVertex(TITLE_SIZE); //�����ő傫���ύX
	mResult.SetColor(W_COLOR, mAlpha);
	mResult.position = CVector2(0.0f, DISP_2D_Y / 2);
	mResult.SetUv(mpTexture, TEST_CG);


	/////////���ƂȂ���z�i�N�G�X�g�ŗL���z�j////////////////////////////////////////////////////////////////////
	//3���ڂ̕\��
	mpNumber = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNumber->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mBaseMoney[2].SetVertex(NUM_SIZE);
	mBaseMoney[2].SetColor(GR_COLOR, mAlpha);
	mBaseMoney[2].position = NUM_POS3;
	mBaseMoney[2].ZERO;

	//2���ڂ̕\��
	mpNumber = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNumber->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mBaseMoney[1].SetVertex(NUM_SIZE);
	mBaseMoney[1].SetColor(GR_COLOR, mAlpha);
	mBaseMoney[1].position = NUM_POS2;
	mBaseMoney[1].ZERO;

	//1���ڂ̕\��
	mpNumber = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNumber->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mBaseMoney[0].SetVertex(NUM_SIZE);
	mBaseMoney[0].SetColor(GR_COLOR, mAlpha);
	mBaseMoney[0].position = NUM_POS1;
	mBaseMoney[0].ZERO;


	//////���v���z�\���̏����ݒ�////////////////////////////////////////////////////////////////////////////////////////
	//3���ڂ̕\��
	mpNumber = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNumber->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mTotalMoney[2].SetVertex(NUM_SIZE);
	mTotalMoney[2].SetColor(BLE_COLOR, mAlpha);
	mTotalMoney[2].position = TNUM_POS3;
	mTotalMoney[2].ZERO;

	//2���ڂ̕\��
	mpNumber = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNumber->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mTotalMoney[1].SetVertex(NUM_SIZE);
	mTotalMoney[1].SetColor(BLE_COLOR, mAlpha);
	mTotalMoney[1].position = TNUM_POS2;
	mTotalMoney[1].ZERO;

	//1���ڂ̕\��
	mpNumber = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNumber->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mTotalMoney[0].SetVertex(NUM_SIZE);
	mTotalMoney[0].SetColor(BLE_COLOR, mAlpha);
	mTotalMoney[0].position = TNUM_POS1;
	mTotalMoney[0].ZERO;

	////////////�{���̕\��//////////////////////////////////////////////////////////////////////////////////
	//3���ڂ̕\��
	mpNumber = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNumber->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mMagnification[2].SetVertex(NUM_SIZE);
	mMagnification[2].SetColor(RE_COLOR, mAlpha);
	mMagnification[2].position = MNUM_POS1;
	mMagnification[2].ZERO;

	//2���ڂ̕\��
	mpNumber = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNumber->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mMagnification[1].SetVertex(NUM_SIZE);
	mMagnification[1].SetColor(RE_COLOR, mAlpha);
	mMagnification[1].position = MNUM_POS2;
	mMagnification[1].ZERO;

	//1���ڂ̕\��
	mpNumber = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNumber->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mMagnification[0].SetVertex(NUM_SIZE);
	mMagnification[0].SetColor(RE_COLOR, mAlpha);
	mMagnification[0].position = MNUM_POS1;
	mMagnification[0].ZERO;

	for (int i = 0; i < TIPS; i++)
	{
		//Result�`�b�v�X
		mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpTexture->load(TGA_FILE"ResultTips.tga");	//�e�N�X�`���t�@�C���ǂݍ���
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		mTips[i].SetVertex(TIP_RECT);
		mTips[i].SetColor(W_COLOR, mAlpha);
	}


	////////////�������̕\��//////////////////////////////////////////////////////////////////////////////////
	//3���ڂ̕\��
	mpNumber = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNumber->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mPocketMoney[2].SetVertex(PNUM_SIZE);
	mPocketMoney[2].SetColor(B_COLOR, mAlpha);
	mPocketMoney[2].position = PNUM_POS3;
	mPocketMoney[2].ZERO;

	//2���ڂ̕\��
	mpNumber = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNumber->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mPocketMoney[1].SetVertex(PNUM_SIZE);
	mPocketMoney[1].SetColor(B_COLOR, mAlpha);
	mPocketMoney[1].position = PNUM_POS2;
	mPocketMoney[1].ZERO;

	//1���ڂ̕\��
	mpNumber = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpNumber->load(TGA_FILE"Number.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mPocketMoney[0].SetVertex(PNUM_SIZE);
	mPocketMoney[0].SetColor(B_COLOR, mAlpha);
	mPocketMoney[0].position = PNUM_POS1;
	mPocketMoney[0].ZERO;



	mTips[0].position = TIP_POS0;
	mTips[1].position = TIP_POS1;
	mTips[2].position = TIP_POS2;
	mTips[3].position = TIP_POS3;
	mTips[0].SetUv(mpTexture, TIP_TEX0);
	mTips[1].SetUv(mpTexture, TIP_TEX1);
	mTips[2].SetUv(mpTexture, TIP_TEX2);
	mTips[3].SetUv(mpTexture, TIP_TEX3);


	/*�J�[�\���l�p�쐬*/
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor (WHITE_COLOR);

}

void CGameResult::Number(int score, CRectangle2 &odifit, CRectangle2 &twdifit, CRectangle2 &thdifit){		//�����̏���

	//�X�R�A��100�Ŋ��邱�Ƃ�3���ڂ��擾
	difit3 = score / 100;
	//�X�R�A�� 10�Ŋ��邱�Ƃ�2���ڂ��擾
	difit2 = (score - (difit3 * 100)) / 10;
	//�X�R�A��  1�Ŋ��邱�Ƃ�1���ڂ��擾
	difit1 = score - ((difit3 * 100) + (difit2 * 10));

	//�R�P�^��
	//�ǂ̐��������ʂƂ��ďo�����ŏ�����ς���
	//�O�`�X
	if (difit3 <= 0){
		thdifit.ZERO;
	}
	if (difit3 == 1){
		thdifit.ONE;
	}
	if (difit3 == 2){
		thdifit.TWO;
	}
	if (difit3 == 3){
		thdifit.THREE;
	}
	if (difit3 == 4){
		thdifit.FOUR;
	}
	if (difit3 == 5){
		thdifit.FIVE;
	}
	if (difit3 == 6){
		thdifit.SIX;
	}
	if (difit3 == 7){
		thdifit.SEVEN;
	}
	if (difit3 == 8){
		thdifit.EIGHT;
	}
	if (difit3 == 9){
		thdifit.NINE;
	}



	//2�P�^��
	//�ǂ̐��������ʂƂ��ďo�����ŏ�����ς���
	//�O�`�X
	if (difit2 <= 0){
		twdifit.ZERO;
	}
	if (difit2 == 1){
		twdifit.ONE;
	}
	if (difit2 == 2){
		twdifit.TWO;
	}
	if (difit2 == 3){
		twdifit.THREE;
	}
	if (difit2 == 4){
		twdifit.FOUR;
	}
	if (difit2 == 5){
		twdifit.FIVE;
	}
	if (difit2 == 6){
		twdifit.SIX;
	}
	if (difit2 == 7){
		twdifit.SEVEN;
	}
	if (difit2 == 8){
		twdifit.EIGHT;
	}
	if (difit2 == 9){
		twdifit.NINE;
	}


	//1�P�^��
	//�ǂ̐��������ʂƂ��ďo�����ŏ�����ς���
	//�O�`�X
	if (difit1 <= 0){
		odifit.ZERO;
	}
	if (difit1 == 1){
		odifit.ONE;
	}
	if (difit1 == 2){
		odifit.TWO;
	}
	if (difit1 == 3){
		odifit.THREE;
	}
	if (difit1 == 4){
		odifit.FOUR;
	}
	if (difit1 == 5){
		odifit.FIVE;
	}
	if (difit1 == 6){
		odifit.SIX;
	}
	if (difit1 == 7){
		odifit.SEVEN;
	}
	if (difit1 == 8){
		odifit.EIGHT;
	}
	if (difit1 == 9){
		odifit.NINE;
	}

}


void CGameResult::Update(){

	switch (mPrize)
	{
	case E_Quest0:
		mQuestMoney = PRIZE0;
		break;

	case E_Quest1:
		mQuestMoney = PRIZE1;
		break;

	case E_Quest2:
		mQuestMoney = PRIZE2;
		break;

	case E_Quest3:
		mQuestMoney = PRIZE3;
		break;

	default:
		break;
	}


	mDifference = (CScoreBoard::mPlayerScore/10) - (CScoreBoard::mEnemyScore/10);

	mTotal = mQuestMoney*mDifference;

	

	//if (CKey::push('J')){
	//	mPocketMoneySave += 0.01f;
	//}

	//mItem.mMoney = mPocketMoneySave;

	Number(mTotal, mTotalMoney[0], mTotalMoney[1], mTotalMoney[2]);

	Number(mQuestMoney, mBaseMoney [0], mBaseMoney [1], mBaseMoney [2]);

	Number(mDifference, mMagnification[0], mMagnification[1], mMagnification[2]);

	Number(mItem.mMoney, mPocketMoney[0], mPocketMoney[1], mPocketMoney[2]);


	if (CScoreBoard::mPlayerScore >= LIMIT_SCORE){
		//CScoreBoard::mGameEnd = true;
		//if (mAlpha <= ALPHA_MAX)mAlpha += 0.01f;
		///*�t�F�[�h*/
		//if (mAlpha2 <= 0.5f){ mAlpha2 += 0.01f; }	
		//mClearLogo.SetColor(W_COLOR, mAlpha);
		//mBG.SetColor(B_COLOR, mAlpha2);

		/*�t�F�[�h*/
		mBG.Fade(RESULT_FADE, ALPHA_HALF);
		mResult.Fade(RESULT_FADE, ALPHA_MAX);
		for (int i = 0; i < 3; i++)
		{
			mTotalMoney[i].Fade(RESULT_FADE, ALPHA_MAX);
			mPocketMoney[i].Fade(RESULT_FADE, ALPHA_MAX);
		}
		for (int i = 0; i < TIPS; i++)
		{
			mTips[i].Fade(RESULT_FADE, ALPHA_MAX);
		}
		for (int i = 1; i < 3; i++)
		{
			mBaseMoney[i].Fade(RESULT_FADE, ALPHA_MAX);
		}
		mMagnification[0].Fade(RESULT_FADE, ALPHA_MAX);

		if (mNumCount < mTotal){
				//printf("%d\n", );
				mNumCount += 0.1f;
				mPocketMoneySave += 0.1f;
				mNumCount += 0.1f;
				mPocketMoneySave += 0.1f;
				mItem.mMoney = mPocketMoneySave;
		}
		//��ʂ��N���b�N����ƃV�[�����ڍs����
		else if (CCollision2D::Collision2D(mCursor, mBG)){ //�J�[�\���������Ă���?
			if (CMouse::mOneLeftFlag)//�}�E�X���N���b�N
			{
		    CScoreBoard::mResult = false;
			CScoreBoard::GetInstance()->mFlagSceneChage = true;
			}
		}

	}

	mCursor.position = CMouse::mPos;

};

/*
�`�揈���݂̂��s���B
*/
void CGameResult::Render() {

	CRectangle2::Disp2D_Start();//2D�����J�n

	/*���̏ꏊ�ɕ`�揈��������*/
	//mBG.Render();
	//mResult.Render();

	for (int i = 0; i < DIGIT; i++)
	{
		mTips[i].Render();
		mBaseMoney[i]    .Render();
		mTotalMoney[i]   .Render();
		mPocketMoney[i]  .Render();
	}
	for (int i = 0; i < TIPS; i++)
	{
		mTips[i].Render();
	}
	for (int i = 0; i < DIGIT-1; i++)
	{
		mMagnification[i].Render();
	}


	//mBaseMoney[2].Render();
	//mBaseMoney[1].Render();
	//mBaseMoney[0].Render();

	//mTotalMoney[2].Render();
	//mTotalMoney[1].Render();
	//mTotalMoney[0].Render();

	//mMagnification[0].Render();
	//mMagnification[1].Render();


	/*�`��I��*/
	CRectangle2::Disp2D_Exit();//2D�����I��

}