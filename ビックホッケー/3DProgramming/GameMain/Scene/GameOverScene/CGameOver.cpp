//�����O���@&& �y�c���l�@
#include"CGameOver.h"
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

CGameOver::~CGameOver(){
}

void CGameOver::Init(){
	//�w�i�̕`��ݒ�
	mBG.SetVertex(BG_SIZE); //�����ő傫���ύX
	mBG.SetColor(B_COLOR, mAlpha2);
	//mBG.SetUv(mpTexture, TEST_CG);
///////////////////////////////////////////////////////////////////
	//�Q�[���I�[�o�[�e�N�X�`���̓ǂݍ���
	mTexLogo.load(TGA_FILE"GameOver.tga");
	//�Q�[���I�[�o�[���S�̕`��ݒ�
	mGameOverLogo.SetVertex(TITLE_SIZE); //�����ő傫���ύX
	mGameOverLogo.SetColor(W_COLOR, mAlpha);
	mGameOverLogo.position = CVector2(0, DISP_2D_Y / 2);
	mGameOverLogo.SetUv(&mTexLogo, TEST_CG);
}

void CGameOver::Update(){
	if (CScoreBoard::mEnemyScore >= LIMIT_SCORE){
		CScoreBoard::mGameEnd = true;
		/*�t�F�[�h*/
		mGameOverLogo.Fade(FADE_SPEED, ALPHA_MAX);
		mBG.Fade(FADE_SPEED, ALPHA_MAX);

		/*�����łȂ��Ȃ�����*/
		if (mBG.triangle1.a >= ALPHA_MAX){
			/*�V�[���ڍs������t���O�𗧂Ă�*/
			CScoreBoard::GetInstance()->mFlagSceneChage = true;
		}
	}
};

void CGameOver::Render() {
	CRectangle2::Disp2D_Start();//2D�����J�n
	/*���̏ꏊ�ɕ`�揈��������*/


	mBG.Render();
	mGameOverLogo.Render();


	/*�`��I��*/
	CRectangle2::Disp2D_Exit();//2D�����I��
}