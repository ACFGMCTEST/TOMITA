//�����O���@&& �y�c���l�@
#include"CTitle.h"
#include "../../Graphic/CTexture.h"
#include "../../Key/CKey.h"
#include "../../../Define/Define.h"
#include "../../Key/CMouse.h"
#include <fstream> 
#include<stdio.h>
#include <Windows.h>
#include "../../Collision/CCollision2D.h"

/*�T�C�Y*/
#define BG_SIZE -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y
#define TITLE_SIZE -400.0f, 160.0f, 400.0f, -160.0f
#define LICENSE_SIZE 0.0f, 0.0f, 147.0f, -127.0f

#define GAME_STATE_SIZE -mScalingRectX, mScalingRectY, mScalingRectX, -mScalingRectY
#define GAME_EXIT_SIZE -mScalingRectX, mScalingRectY, mScalingRectX, -mScalingRectY

#define BUTTON_DEFAULT_SIZE -mButtonX, mButtonY, mButtonX, -mButtonY
/*�e�N�X�`���T�C�Y*/
#define TITLE_CG 0,0,1000,400
#define LICENSE_CG 0,0,147,127
#define START_CG 0,0,300,150
#define EXIT_CG 300,0,600,150
#define JAGGED_BALLOON_CG 0, 150, 600, 400

CTitle::~CTitle(){
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



void CTitle::Init(){
	mMaxSize = false;
	mScalingRectX = mButtonX;
	mScalingRectY = mButtonY;

	mAlpha = 0.0f;

	//�w�i�̌Ăяo��

	mpBg = new CTexture();
	mpBg->load(TGA_FILE"BG.tga");

	mBG.SetVertex(BG_SIZE); //�����ő傫���ύX
	mBG.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	mBG.SetUv(mpBg, BG_SIZE);

	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"Light_Frame.tga");

	//��ɂĂ�����񃉃C�Z���X

	mUnityChanLicense.SetVertex(LICENSE_SIZE); //�����ő傫���ύX
	mUnityChanLicense.SetColor(WHITE_COLOR);
	mUnityChanLicense.position = CVector2(250, -170);
	mUnityChanLicense.SetUv(mpTexture, LICENSE_CG);



	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"title.tga");

	//�^�C�g�����S�̌Ăяo��

	mTitleLogo.SetVertex(TITLE_SIZE); //�����ő傫���ύX
	mTitleLogo.SetColor(WHITE_COLOR);
	mTitleLogo.position = CVector2(0, 170);
	mTitleLogo.SetUv(mpTexture, TITLE_CG);


	//�^�C�g�����S�̌Ăяo��

	mShadow.SetVertex(TITLE_SIZE); //�����ő傫���ύX
	mShadow.SetColor(0.0f, 0.0f, 0.0f, 0.5f);
	mShadow.position = CVector2(20, 150);
	mShadow.SetUv(mpTexture, TITLE_CG);





	//�Q�[���J�n�̌Ăяo��
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"TitleSet.tga");	//�e�N�X�`���t�@�C���ǂݍ���


	mGameStart.SetVertex(GAME_STATE_SIZE);
	mGameStart.SetColor(WHITE_COLOR);
	mGameStart.position = CVector2(0, -80);
	mGameStart.SetUv(mpMenu, START_CG);

	////�Q�[���I���̌Ăяo��
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"TitleSet.tga");	//�e�N�X�`���t�@�C���ǂݍ���


	mGameExit.SetVertex(GAME_EXIT_SIZE);
	mGameExit.SetColor(WHITE_COLOR);
	mGameExit.position = CVector2(0, -220);
	mGameExit.SetUv(mpMenu, EXIT_CG);

	////�J�[�\���̌Ăяo��
	mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpTexture->load(TGA_FILE"cursor.tga");	//�e�N�X�`���t�@�C���ǂݍ���


	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(mpTexture, 0, 0, 150, 120);

	///*Gradation�֐�*/
	//mCursor.SetGradationLoop(CRectangle2::E_COLOR_CHANGE::E_RED_PURPLE);
}




void CTitle::Update(){

	/*�����蔻��*/
	if (CCollision2D::Collision2D(mCursor, mGameStart)){ //�J�[�\���������Ă���?
		mGameExit.SetVertex(BUTTON_DEFAULT_SIZE);
		mGameStart.SetVertex(GAME_STATE_SIZE);
		if (!mMaxSize){
			mScalingRectX += mChangeSize;
			mScalingRectY += mChangeSize;
			if (mScalingRectX >= mButtonX * mExpansionLimit)mMaxSize = true;
		}
		else if (mMaxSize){
			mScalingRectX -= mChangeSize;
			mScalingRectY -= mChangeSize;
			if (mScalingRectX <= mButtonX)mMaxSize = false;
		}
	}
	else
	if (CCollision2D::Collision2D(mCursor, mGameExit)){ //�J�[�\���������Ă���?
		mGameStart.SetVertex(BUTTON_DEFAULT_SIZE);
		mGameExit.SetVertex(GAME_STATE_SIZE);
		if (!mMaxSize){
			mScalingRectX += mChangeSize;
			mScalingRectY += mChangeSize;
			if (mScalingRectX >= mButtonX * mExpansionLimit)mMaxSize = true;
		}
		else if (mMaxSize){
			mScalingRectX -= mChangeSize;
			mScalingRectY -= mChangeSize;
			if (mScalingRectX <= mButtonX)mMaxSize = false;
		}
	}
	else
	{
		mScalingRectX = mButtonX;
		mScalingRectY = mButtonY;
		mGameStart.SetVertex(GAME_STATE_SIZE);
		mGameExit.SetVertex(GAME_STATE_SIZE);
	}

	mCursor.position = CMouse::mPos;

	//mCursor.GradationLoop(0.02f);
};

/*
�`�揈���݂̂��s���B
*/
void CTitle::Render() {

	CRectangle2::Disp2D_Start();//2D�����J�n

	/*���̏ꏊ�ɕ`�揈��������*/
	mBG.Render();
	mShadow.Render();
	mTitleLogo.Render();
	mGameStart.Render();
	mGameExit.Render();
	mUnityChanLicense.Render();
	mCursor.Render();
	/*�`��I��*/

	CRectangle2::Disp2D_Exit();//2D�����I��



}