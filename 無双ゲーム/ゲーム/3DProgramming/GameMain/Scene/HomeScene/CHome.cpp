#include"CHome.h"
#include "../Define\Define.h"
#include <fstream> 
#include <stdio.h>
#include "../GameMain\Key\CKey.h"
#include "../../Key/CMouse.h"
#include "../../Collision/CCollision2D.h"
//�e�N�X�`���T�C�Y
#define TEX_TITLE_X			410
#define TEX_TITLE_Y			100

//�|���S���T�C�Y
#define TITLE_LOGO_SIZE		RECT_SIZE(0.7f,TEX_TITLE_X,TEX_TITLE_Y) 
#define RECT_BUTTON_SIZE	RECT_SIZE(0.7f,TEX_BUTTON_X,TEX_BUTTON_Y)
#define STAGE_CURSOR_SIZE	RECT_SIZE(0.3f,TEX_STAGE_CURSOR_X,TEX_STAGE_CURSOR_Y)
/*�|���S���̃|�W�V����*/
#define TITLE_POS			BUTTON_POS(0,0.2f)
#define SELECT_POS			BUTTON_POS(0.06f,-0.2f)
#define MODEL_CHANGE_POS	BUTTON_POS(0.06f,-0.4f)
/*�e�N�X�`���ꏊ*/
#define TEX_TITLE_FILE			TGA_FILE"Title\\TitleLogo.tga"
#define TEX_SELECT_FILE			TGA_FILE"Home\\StageSelect.tga"
#define TEX_MODEL_CHANGE_FILE	TGA_FILE"Home\\ModelChange.tga"
/*���o�̐��l �g��k���֐�*/
#define SCALLING_NUM 1.2f,2.0f
/*���o�̐��l �F�̓_�ŗp*/
#define FLASHING_NUM 0.01f,1.0f,0.7f

CHome::~CHome(){

}
CHome::CHome() :CTitle(){

	eScene = eSceneNo::E_HOME;
	/*�^�C�g���F�w��*/
	mTitleLogo.SetColor(NO_A_WHITE_COLOR,0.0f);
	/*�Z���N�g�|���S���ݒ�*/
	mSelectButton.SetColor(NO_A_WHITE_COLOR, 0.0f);
	mSelectButton.SetVertex(RECT_BUTTON_SIZE);
	mSelectButton.mPosition = SELECT_POS;
	/*���f���`�F���W�|���S���ݒ�*/
	mModelChangeButton.SetColor(NO_A_WHITE_COLOR, 0.0f);
	mModelChangeButton.SetVertex(RECT_BUTTON_SIZE);
	mModelChangeButton.mPosition = MODEL_CHANGE_POS;
	/*�Z���N�g��Button�|���S���ݒ�*/
	mSelectCursor.SetColor(NO_A_WHITE_COLOR, 0.0f);
	mSelectCursor.SetVertex(STAGE_CURSOR_SIZE);
	mSelectCursor.mPosition = 
		CVector2(*mSelectButton.mpLeft - *mSelectCursor.mpRight + mSelectButton.mPosition.x
		,mSelectButton.mPosition.y);

	/*�Z���N�g�e�N�X�`���ݒ�*/
	mTexSelectButton.Load(TEX_SELECT_FILE);
	mSelectButton.SetUv(&mTexSelectButton, 0, 0, TEX_BUTTON_X, TEX_BUTTON_Y);
	/*�Z���N�g�e�N�X�`���ݒ�*/
	mTexModelChangeButton.Load(TEX_MODEL_CHANGE_FILE);
	mModelChangeButton.SetUv(&mTexModelChangeButton, 0, 0,TEX_BUTTON_X, TEX_BUTTON_Y);	
	/*�Z���N�g�e�N�X�`���ݒ�*/
	mTexStageCursor.Load(TEX_STAGE_CURSOR_FILE);
	mSelectCursor.SetUv(&mTexStageCursor, 0, 0, TEX_STAGE_CURSOR_X, TEX_STAGE_CURSOR_Y);

}
/*�I��������*/
void CHome::SelectInit() {
	/*���f���`�F���W������*/
	mModelChangeButton.SetColor(NO_A_WHITE_COLOR, 1.0f);//�F�߂�
	mModelChangeButton.SetVertex(RECT_BUTTON_SIZE);//�T�C�Y�߂�
	mModelChangeButton.mPosition = MODEL_CHANGE_POS;//�|�W�V�����߂�

	mSelectButton.SetColor(NO_A_WHITE_COLOR, 1.0f);//�J���[�߂�
	mSelectButton.SetVertex(RECT_BUTTON_SIZE);//�T�C�Y�߂�
	mSelectButton.mPosition = SELECT_POS;//�|�W�V�����߂�
}
/*�I������*/
void CHome::Select(){

	/*�Z���N�g��I�񂾏ꍇ*/
	if (eScene == E_HOME) {
		if (mSelectCursor.mPosition.y == mSelectButton.mPosition.y) {
			/*���o*/
			mSelectButton.RectScalingLeftPos(SCALLING_NUM);//�g��
			mSelectButton.FlashingColor(FLASHING_NUM);//�F�_��
		}
		else 
			if (mSelectCursor.mPosition.y == mModelChangeButton.mPosition.y) {
				/*���o����*/
				mModelChangeButton.RectScalingLeftPos(SCALLING_NUM);//�g��
				mModelChangeButton.FlashingColor(FLASHING_NUM);//�F�_��
			}
	}

	/*Cursor�̈ړ�����*/
	/*���f���`�F���W�I�񂾎�*/
	if (CKey::once(DOWN_KEY)){
		mSelectCursor.mPosition.y = mModelChangeButton.mPosition.y;

	}
	/*�X�e�[�W�Z���N�g�I�񂾎�*/
	if (CKey::once(UP_KEY)){
		mSelectCursor.mPosition.y = mSelectButton.mPosition.y;
	
	}

}
/*���肳�ꂽ�ꍇ(�L�[��)*/
void CHome::SelectDecisionKey() {
	/*�L�[�o�[�W����*/
	/*�I�����������f ���f���`�F���W�̏ꍇ*/
	if (CKey::once(VK_RETURN)) {
		if (mSelectCursor.mPosition.y == mModelChangeButton.mPosition.y) {
			eScene = E_MODEL_CHANGE;
			return;
		}
		else /*�I�����������f �X�e�[�W�Z���N�g�̏ꍇ*/
			if (mSelectCursor.mPosition.y == mSelectButton.mPosition.y) {
				eScene = E_STAGE_SELECT;
				return;
			}
	}
}
/*���肳�ꂽ�ꍇ(�}�E�X��)*/
void CHome::SelectDecisionMouse() {
	/*�}�E�X�o�[�W����*/
	if (CCollision2D::Collision2D(mModelChangeButton, mCursor)) {
		mSelectCursor.mPosition.y = mModelChangeButton.mPosition.y;
		mModelChangeButton.RectScalingLeftPos(SCALLING_NUM);//�g��
		if (CMouse::GetInstance()->mOneLeftFlag) {
			eScene = E_MODEL_CHANGE;
		}
		return;
	}
	/*�I�����������f �X�e�[�W�Z���N�g�̏ꍇ*/
	if (CCollision2D::Collision2D(mSelectButton, mCursor) ) {
		mSelectCursor.mPosition.y = mSelectButton.mPosition.y;
		mSelectButton.RectScalingLeftPos(SCALLING_NUM);//�g��

		if (CMouse::GetInstance()->mOneLeftFlag) {
			eScene = E_STAGE_SELECT;//�Z���N�g��
		}

		return;
	}
}
/*���肳�ꂽ�ꍇ*/
void CHome::SelectDecision(){
	/*�I�������Ƃ��̊֐�*/
	Select();
	SelectDecisionKey();
	SelectDecisionMouse();
}
/*�V�[���J�� ���f*/
bool CHome::SceneFlag(){
	/*�t�F�[�h�A�E�g������������*/
	if (mModelChangeButton.mTriangle1.a == 0 || 
		mSelectButton.mTriangle1.a == 0){
		return true;
	}
	return false;
	
}

/*�X�V����*/
void CHome::Update() {
	/*BG��Scroll����*/
	CTitle::Scroll();
	
	/*���肳��Ă������f*/
	SelectDecision();


	/*�t�F�[�h����*/
	/*�t���O�����ƃt�F�C�h�A�E�g���Ă���*/

	if (eScene == E_MODEL_CHANGE)mModelChangeButton.FadeOut(FADE_SPEED, 0.0f);
	if (eScene == E_STAGE_SELECT) mSelectButton.FadeOut(FADE_SPEED, 0.0f);
	if(eScene != E_HOME)mSelectCursor.FadeOut(FADE_SPEED, 0.0f);

	/*���o����t�F�[�h�œo��*/
	if (eScene == E_HOME && mSelectButton.mTriangle1.a != 1) {
		AllFade();
	}
};
/*���߂̃t�F�[�h����*/
void CHome::AllFade() {
	mTitleLogo.Fade(FADE_SPEED, 1.0f);
	mSelectButton.Fade(FADE_SPEED, 1.0f);
	mModelChangeButton.Fade(FADE_SPEED, 1.0f);
	mSelectCursor.Fade(FADE_SPEED, 1.0f);
}
/*
�`�揈���݂̂��s���B
*/
void CHome::Render() {
	CRectangle2::Disp2D_Start();//�`��͂���


	mBG.Render();	
	mTitleLogo.Render();
	mSelectButton.Render();
	mModelChangeButton.Render();
	mSelectCursor.Render();
	mCursor.Render();


	
	CRectangle2::Disp2D_Exit();//�`��I���
}