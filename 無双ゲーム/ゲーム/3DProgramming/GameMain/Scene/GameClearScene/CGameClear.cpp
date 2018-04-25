#include"CGameClear.h"
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


CGameClear::~CGameClear(){

}

void CGameClear::Init(){
	//�w�i�̌Ăяo��
	mBG.SetVertex(BG_SIZE); //�����ő傫���ύX
	mBG.SetColor(NO_A_WHITE_COLOR, 0.0f);
	mBG.SetUv(&mTexBG, TEST_CG);


	//�N���A���S�̌Ăяo��
	mClearLogo.SetVertex(TITLE_SIZE); //�����ő傫���ύX
	mClearLogo.SetColor(NO_A_WHITE_COLOR, 0.0f);
	mClearLogo.mPosition = CVector2(0.0f, 200);
	mClearLogo.SetUv(&mTexClearLogo, TEST_CG);


}




void CGameClear::Update(){

};

/*
�`�揈���݂̂��s���B
*/
void CGameClear::Render() {

	CRectangle2::Disp2D_Start();//2D�����J�n

	/*���̏ꏊ�ɕ`�揈��������*/
	mBG.Render();
	mClearLogo.Render();
	/*�`��I��*/

	CRectangle2::Disp2D_Exit();//2D�����I��

}