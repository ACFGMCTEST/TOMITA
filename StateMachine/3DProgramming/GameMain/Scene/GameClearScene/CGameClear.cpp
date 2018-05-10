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


CGameClear::~CGameClear(){
	if (mpTexture) {
		//�e�N�X�`�����g���Ă���΃C���X�^���X�폜
		delete mpTexture;
		mpTexture = nullptr;
	}

}

void CGameClear::Init(){
	mEnd = END_TIME;
	//�w�i�̌Ăяo��

	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"Cle_ar.tga");

	mBG.SetVertex(BG_SIZE); //�����ő傫���ύX
	mBG.SetColor(W_COLOR,0.0f);
	mBG.SetUv(mpTexture, TEST_CG);



	mpTexture = new CTexture();
	mpTexture->load(TGA_FILE"Clear.tga");

	//�N���A���S�̌Ăяo��
	
	mClearLogo.SetVertex(TITLE_SIZE); //�����ő傫���ύX
	mClearLogo.SetColor(W_COLOR, mAlpha);
	mClearLogo.position = CVector2(0.0f, 200);
	mClearLogo.SetUv(mpTexture, TEST_CG);


}




void CGameClear::Update(){
	if (CScoreBoard::mPlayerScore >= LIMIT_SCORE){
		CScoreBoard::mGameEnd = true;
		//if (mAlpha <= ALPHA_MAX)mAlpha += 0.01f;
		///*�t�F�[�h*/
		//if (mAlpha2 <= 0.5f){ mAlpha2 += 0.01f; }	
		//mClearLogo.SetColor(W_COLOR, mAlpha);
		//mBG.SetColor(B_COLOR, mAlpha2);

		/*�t�F�[�h*/
		mClearLogo.Fade(FADE_SPEED, ALPHA_MAX);
		mBG.Fade(FADE_SPEED, ALPHA_MAX);
		mEnd -= 0.01f;
		
		/*�����łȂ��Ȃ�����*/
		//if (mBG.triangle1.a >= ALPHA_MAX){
		if (mEnd <= 0){
			/*�V�[���ڍs������t���O�𗧂Ă�*/

			CScoreBoard::mResult = true;
			//CScoreBoard::GetInstance()->mFlagSceneChage = true;
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