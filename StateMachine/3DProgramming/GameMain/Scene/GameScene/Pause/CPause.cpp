//�����O���@&& �y�c���l�@
#include"CPause.h"
#include "../../../Graphic/CTexture.h"
#include "../../../Key/CKey.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CMouse.h"
#include "../../GameScene/UI/CScoreBoard.h"
#include "../../../Collision/CCollision2D.h"
#include <fstream> 
#include<stdio.h>
#include <Windows.h>

/*�T�C�Y*/
#define BG_SIZE -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y
#define TITLE_SIZE -200.0f, 80.0f, 200.0f, -80.0f
#define BUTTON_SIZE -189.0f, 72.0f, 189.0f, -72.0f
#define GAME_STATE_SIZE -120.0f, -80.0f, 120.0f, -140.0f
#define GAME_EXIT_SIZE - 120.0f, -160.0f, 120.0f, -220.0f
#define PAUSE_LOGO	  0,0,400,160
#define PAUSE_MENU_LOGO	  0,0,420,160
/*tex�t�F�C��*/
#define CURSOR_CG 0,0,150,120


bool CPause::mSceneChangeFlag = false;//�V�[�����ς��t���O
bool CPause::mGoTitle = false;
bool CPause::mBackGame = false;

CPause::~CPause(){
	if (mpTexture) {
		//�e�N�X�`�����g���Ă���΃C���X�^���X�폜
		delete mpTexture;
		mpTexture = 0;
	}

}

void CPause::Init(){
	mSceneChangeFlag = false;
	mGoTitle = false;
	mBackGame = false;
	//�w�i�̌Ăяo��

	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"Cle_ar.tga");

	mBG.SetVertex(BG_SIZE); //�����ő傫���ύX
	mBG.SetColor(B_COLOR, 0.5f);
	mBG.SetUv(mpTexture, TEST_CG);


	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"Pause.tga");

	//�|�[�Y���S�̌Ăяo��
	
	mPauseLogo.SetVertex(TITLE_SIZE); //�����ő傫���ύX
	mPauseLogo.SetColor(W_COLOR, 1.0f);
	mPauseLogo.position = CVector2(0, DISP_2D_Y / 2);
	mPauseLogo.SetUv(mpTexture, PAUSE_LOGO);



	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"Resume.tga");

	//�Q�[���֖߂�̌Ăяo��

	mBack.SetVertex(BUTTON_SIZE); //�����ő傫���ύX
	mBack.SetColor(W_COLOR, 1.0f);
	mBack.position = CVector2(0, -50);
	mBack.SetUv(mpTexture, PAUSE_MENU_LOGO);




	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"Quit.tga");

	//�^�C�g���֖߂�̌Ăяo��

	mTitleBack.SetVertex(BUTTON_SIZE); //�����ő傫���ύX
	mTitleBack.SetColor(W_COLOR, 1.0f);
	mTitleBack.position = CVector2(0, -180);
	mTitleBack.SetUv(mpTexture, PAUSE_MENU_LOGO);


	/*�J�[�\���l�p�쐬*/
	mpTexCursor = new CTexture();
	mpTexCursor->load(TGA_FILE"cursor.tga");
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(mpTexCursor, CURSOR_CG);


}




void CPause::Update(){

	//�Q�[���֖߂�
	if (CCollision2D::Collision2D(mCursor, mBack)){ //�J�[�\���������Ă���?
		mBack.SetColor(GRAY_COLOR);
		if (CMouse::mOneLeftFlag)//�}�E�X���N���b�N
		mBackGame = true;
	}
	else{
		mBack.SetColor(W_COLOR, 1.0f);
	}
	//�^�C�g���ֈړ�
	if (CCollision2D::Collision2D(mCursor, mTitleBack)){ //�J�[�\���������Ă���?
		mTitleBack.SetColor(GRAY_COLOR);
		if (CMouse::mOneLeftFlag){//�}�E�X���N���b�N
			//CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);
			mSceneChangeFlag = true;
		}
	}
	else{
		mTitleBack.SetColor(W_COLOR, 1.0f);
	}
	mCursor.position = CMouse::mPos;
};

/*
�`�揈���݂̂��s���B
*/
void CPause::Render() {

	CRectangle2::Disp2D_Start();//2D�����J�n

	/*���̏ꏊ�ɕ`�揈��������*/
	mBG.Render();
	mPauseLogo.Render();
	mTitleBack.Render();
	mBack.Render();
	mCursor.Render();

	/*�`��I��*/

	CRectangle2::Disp2D_Exit();//2D�����I��

}