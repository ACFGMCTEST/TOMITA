#include"CGameOver.h"
#include "../../Graphic/CTexture.h"
#include "../../Key/CKey.h"
#include "../../../Define/Define.h"
#include "../../Key/CMouse.h"
#include <fstream> 
#include<stdio.h>
#include <Windows.h>

/*�T�C�Y*/
#define BG_SIZE -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y
#define TITLE_SIZE -200.0f, 80.0f, 200.0f, -80.0f
#define GAME_STATE_SIZE -120.0f, -80.0f, 120.0f, -140.0f
#define GAME_EXIT_SIZE - 120.0f, -160.0f, 120.0f, -220.0f

CGameOver::~CGameOver(){

}

void CGameOver::Init(){
	CTexture t;//�t�B���^�[�p
	//�w�i�̕`��ݒ�
	mBG.SetVertex(BG_SIZE); //�����ő傫���ύX
	mBG.SetColor(NO_A_WHITE_COLOR, mAlpha2);
	mBG.SetUv(&t, TEST_CG);
///////////////////////////////////////////////////////////////////
	//�Q�[���I�[�o�[�e�N�X�`���̓ǂݍ���
	mTexOverLogo.load(TGA_FILE"GameOver.tga");
	//�Q�[���I�[�o�[���S�̕`��ݒ�
	mGameOverLogo.SetVertex(TITLE_SIZE); //�����ő傫���ύX
	mGameOverLogo.SetColor(NO_A_WHITE_COLOR, mAlpha);
	mGameOverLogo.mPosition = CVector2(0, DISP_2D_Y / 2);
	mGameOverLogo.SetUv(&mTexOverLogo, TEST_CG);
}

void CGameOver::Update(){

};

void CGameOver::Render() {
	CRectangle2::Disp2D_Start();//2D�����J�n
	/*���̏ꏊ�ɕ`�揈��������*/


	mBG.Render();
	mGameOverLogo.Render();


	/*�`��I��*/
	CRectangle2::Disp2D_Exit();//2D�����I��
}