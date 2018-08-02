#include "../CGameScene.h"
#include "CResult.h"
#include "../../../Convenient/CConvenient.h"
/*�T�C�Y*/
#define BG_SIZE -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y
#define LOGO_POS CVector2(0.0f,100.0f) //�|�W�V����

CResult* CResult::mResult = 0;
//GetInstance
CResult* CResult::GetInstance() {
	if (mResult == 0) {
		mResult = new CResult();
	}
	return mResult;
}

CResult::~CResult(){

}
/*�e�N�X�`���̃T�C�Y*/
#define TEX_SIZE_X 340
#define TEX_SIZE_Y 50
void CResult::Init(){
	mRenderFlag = false;
	mCount = 0.0f;
	//���S�e�N�X�`��
	mTexLogo.Load(TGA_FILE"Result\\Result.tga");
	
	//�w�i�̌Ăяo��
	mBG.SetVertex(BG_SIZE); //�����ő傫���ύX	
	mBG.SetColor(0.0f, 0.0f, 0.0f, 0.0f);//�F���u���b�N�ɂ���
	mBG.SetUv(&mTexBG, TEST_CG);



	//�N���A���S�̌Ăяo��
	mLogo.SetVertex(RECT_SIZE(1.0f, TEX_SIZE_X, TEX_SIZE_Y)); //�����ő傫���ύX
	mLogo.SetColor(NO_A_WHITE_COLOR, 0.0f);
	mLogo.SetUv(&mTexLogo, 0.0f, TEX_SIZE_Y, TEX_SIZE_X, TEX_SIZE_Y * 2);//�e�N�X�`���@over��
	mLogo.mPosition = LOGO_POS;

}

//Clear�����Ƃ��Ă�
void CResult::Clear() {
	mBG.SetColor(NO_A_WHITE_COLOR, 0.0f);
	mLogo.SetUv(&mTexLogo, 0.0f, 0.0f, TEX_SIZE_X, TEX_SIZE_Y);
	mRenderFlag = true;
}
//���S�����Ƃ��Ă�
void CResult::Over() {
	mBG.SetColor(0.0f, 0.0f, 0.0f, 0.0f);
	mRenderFlag = true;
}

#define FADE_SPEED 0.01f
#define FADE_BG_SPEED 0.005f
#define FADE_TIME 4.0f //�t�F�[�h���n�܂鎞��
void CResult::Update(){
	/*�`�悷���ԂȂ�*/
	if (mRenderFlag) {
		/*���Ԃ������Ă��Ȃ��ꍇ*/
		if (!CConvenient::Time(&mCount, FADE_TIME)) {
			mLogo.Fade(FADE_SPEED, 1.0f);
		}
		else {
			mBG.Fade(FADE_BG_SPEED, 1.0f);
			mLogo.FadeOut(FADE_BG_SPEED, 0.0f);
			if(mLogo.mTriangle1.a == 0.0f)CGameScene::eState = CGameScene::E_END;
		}
	}

};

/*
�`�揈���݂̂��s���B
*/
void CResult::Render() {
	if (mRenderFlag) {
		
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//�F�͒u�������ă}�b�s���O

		CRectangle2::Disp2D_Start();//2D�����J�n

		/*���̏ꏊ�ɕ`�揈��������*/
		mBG.Render();
		mLogo.Render();
		/*�`��I��*/

		CRectangle2::Disp2D_Exit();//2D�����I��

	}
}