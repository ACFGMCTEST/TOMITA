//�����O���@&& �y�c���l�@
#include"CGameClear.h"
#include "../../Graphic/CTexture.h"
#include "../../Key/CKey.h"
#include "../../../Define/Define.h"
#include "../../Key/CMouse.h"
#include "../GameScene/UI/CScoreBoard.h"
#include <fstream> 
#include<stdio.h>
#include <Windows.h>

/*�T�C�Y*/
#define BG_SIZE -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y
#define TITLE_SIZE -200.0f, 80.0f, 200.0f, -80.0f
#define GAME_STATE_SIZE -120.0f, -80.0f, 120.0f, -140.0f
#define GAME_EXIT_SIZE - 120.0f, -160.0f, 120.0f, -220.0f
/*�e�N�X�`���ꏊ*/

CGameClear::~CGameClear(){

}

void CGameClear::Init(){
	//�w�i�̌Ăяo��
	mBG.SetVertex(BG_SIZE); //�����ő傫���ύX
	mBG.SetColor(W_COLOR,0.0f);
	//mBG.SetUv(&mTexBG, TEST_CG);


	//�N���A���S�̌Ăяo��
	mTexClearLogo.load(TGA_FILE"Clear.tga");
	mClearLogo.SetVertex(TITLE_SIZE); //�����ő傫���ύX
	mClearLogo.SetColor(W_COLOR, 0.0f);
	mClearLogo.position = CVector2(0.0f, 200);
	mClearLogo.SetUv(&mTexClearLogo, TEST_CG);


}




void CGameClear::Update(){
	if (CScoreBoard::mPlayerScore >= LIMIT_SCORE){
		CScoreBoard::mGameEnd = true;

		/*�t�F�[�h*/
		mClearLogo.Fade(FADE_SPEED, ALPHA_MAX);
		mBG.Fade(FADE_SPEED, ALPHA_MAX);
		
		/*�����łȂ��Ȃ�����*/
		if (mBG.triangle1.a >= ALPHA_MAX){
			/*�V�[���ڍs������t���O�𗧂Ă�*/
			CGameResult::mFlagResult = true;
		}

	}
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