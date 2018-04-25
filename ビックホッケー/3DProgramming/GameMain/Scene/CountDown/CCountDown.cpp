//�����O���@&& �y�c���l�@
#include"CCountDown.h"
#include "../../Graphic/CTexture.h"
#include "../../Key/CKey.h"
#include "../../../Define/Define.h"
#include "../../Key/CMouse.h"
#include "../GameScene/UI/CScoreBoard.h"
#include <fstream> 
#include<stdio.h>
#include <Windows.h>

/*�T�C�Y*/
#define TITLE_SIZE -200.0f, 80.0f, 200.0f, -80.0f
#define GAME_STATE_SIZE -120.0f, -80.0f, 120.0f, -140.0f
#define GAME_EXIT_SIZE - 120.0f, -160.0f, 120.0f, -220.0f

#define ZERO		SetUv(mpTexture,   0,   0,  100, 100);
#define ONE			SetUv(mpTexture, 100,   0,  200, 100);
#define TWO			SetUv(mpTexture, 200,   0,  300, 100);
#define THREE		SetUv(mpTexture, 300,   0,  400, 100);
#define FOUR		SetUv(mpTexture, 400,   0,  500, 100);
#define FIVE		SetUv(mpTexture, 500,   0,  600, 100);
#define SIX			SetUv(mpTexture, 600,   0,  700, 100);
#define SEVEN		SetUv(mpTexture, 700,   0,  800, 100);
#define EIGHT		SetUv(mpTexture, 800,   0,  900, 100);
#define NINE		SetUv(mpTexture, 900,   0, 1000, 100);

#define COUNT_ONE	SetUv(mpTexture, 800,   0, 1200, 400 );
#define COUNT_TWO	SetUv(mpTexture, 400,   0,  800, 400);
#define COUNT_THREE SetUv(mpTexture,   0,   0,  400, 400);

#define READY	 SetUv(mpReady, 2,   2, 398, 198);
#define GO	     SetUv(mpReady, 400,   0, 800, 200);

CCountDown::~CCountDown(){
	if (mpTexture) {
		//�e�N�X�`�����g���Ă���΃C���X�^���X�폜
		delete mpTexture;
		mpTexture = 0;
	}
	if (mpReady) {
		//�e�N�X�`�����g���Ă���΃C���X�^���X�폜
		delete mpReady;
		mpReady = 0;
	}

}


void CCountDown::Init(){
	//�J�E���g�_�E���ǂݍ���
	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"CountDown.tga");

	mNumberBox.SetVertex(TITLE_SIZE); //�����ő傫���ύX
	mNumberBox.SetColor(W_COLOR, 1.0f);
	mNumberBox.position = CVector2(0, DISP_2D_Y / 2);
	mNumberBox.COUNT_THREE;

	//printf("Ready\n");
	mpReady = new CTexture();
	mpReady->load(TGA_FILE"Ready.tga");

	mReadyBox.SetVertex(TITLE_SIZE); //�����ő傫���ύX
	mReadyBox.SetColor(W_COLOR, 0.0f);
	mReadyBox.position = CVector2(0, DISP_2D_Y / 2);
	mReadyBox.READY;
	/*�J�E���g*/
	mCount = cmCountInit;
	mAlpha = 0.0f;

}


void CCountDown::Update(){
	mCount -= 1.0f;

	if (mCount > FPS*4){

		mNumberBox.COUNT_THREE;
	}else

	if (mCount > FPS*3){
		mNumberBox.COUNT_TWO;
	}else

	if (mCount > FPS*2){
		mNumberBox.COUNT_ONE;
	}
	
	else
	
	if (mCount > FPS){
		mNumberBox.SetColor(W_COLOR, 0.0f);
		mReadyBox.SetColor(W_COLOR, 1.0f);

	}else
	if (mCount < FPS){

		mReadyBox.GO;
	}
	if (mCount < 0){ CScoreBoard::mcFirstAction = false; }

};

/*
�`�揈���݂̂��s���B
*/
void CCountDown::Render() {
	CRectangle2::Disp2D_Start();//2D�����J�n
	/*���̏ꏊ�ɕ`�揈��������*/
	
	mNumberBox.Render();
	mReadyBox.Render();
	/*�`��I��*/
	CRectangle2::Disp2D_Exit();//2D�����I��
}