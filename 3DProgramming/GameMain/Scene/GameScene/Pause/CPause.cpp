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
/*�|�W�V����*/
#define POS_PAUZE CVector2(0, DISP_2D_Y / 2)
#define POS_BACK_BUTTON CVector2(0, -30)
#define POS_GUIDE_BUTTON CVector2(0, -130)
#define POS_TITLE_BACK_BUTTON CVector2(0, -230)
/*�T�C�Y*/
#define BG_SIZE -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y
#define TITLE_SIZE -200.0f, 80.0f, 200.0f, -80.0f
#define BUTTON_PERCENT 3
#define BUTTON_SIZE -400/BUTTON_PERCENT, 160.0f/BUTTON_PERCENT, 400.0f/BUTTON_PERCENT, -160.0f/BUTTON_PERCENT
#define GAME_STATE_SIZE -120.0f, -80.0f, 120.0f, -140.0f
#define GAME_EXIT_SIZE - 120.0f, -160.0f, 120.0f, -220.0f

/*tex�t�F�C��*/
#define FILTER_CG 0,0,10,10
#define PAUSE_LOGO_CG	  0,0,400,160
#define PAUSE_MENU_LOGO_CG	  0,0,420,160
#define CURSOR_CG 0,0,150,120
#define OPERA_CG 0,0,750,400
/*tga�ꏊ*/
#define TEX_FILTER			TGA_FILE"Pause\\filter.tga"
#define TEX_PAUZE			TGA_FILE"Pause\\pause.tga"
#define TEX_RESUME			TGA_FILE"Pause\\resume.tga"
#define TEX_QUIT			TGA_FILE"Pause\\quit.tga"
#define TEX_GUIDE			TGA_FILE"Pause\\guide.tga"
#define TEX_CURSOR			TGA_FILE"cursor.tga"
#define TEX_OPERA			TGA_FILE"Tutorial/allOperation.tga" 

bool CPause::mSceneChangeFlag = false;//�V�[�����ς��t���O
bool CPause::mGoTitle = false;
bool CPause::mBackGame = false;
/*�R���X�g���N�^*/
CPause::CPause():mOperationFlag(false){

}
/*�f�X�g���N�^*/
CPause::~CPause(){

}

void CPause::Init(){
	mSceneChangeFlag = false;
	mGoTitle = false;
	mBackGame = false;
	mOperationFlag = false;
	//�w�i�̌Ăяo��
	mTexFilter.load(TEX_FILTER);
	mBG.SetVertex(BG_SIZE); //�����ő傫���ύX
	mBG.SetColor(B_COLOR, 0.5f);
	mBG.SetUv(&mTexFilter, FILTER_CG);
	//�|�[�Y���S�̌Ăяo��
	mTexPauze.load(TEX_PAUZE);
	mPauseLogo.SetVertex(TITLE_SIZE); //�����ő傫���ύX
	mPauseLogo.SetColor(W_COLOR, 1.0f);
	mPauseLogo.position = POS_PAUZE;
	mPauseLogo.SetUv(&mTexPauze, PAUSE_LOGO_CG);
	//�Q�[���֖߂�̌Ăяo��
	mTexResume.load(TEX_RESUME);
	mBackButton.SetVertex(BUTTON_SIZE); //�����ő傫���ύX
	mBackButton.SetColor(W_COLOR, 1.0f);
	mBackButton.position = POS_BACK_BUTTON;
	mBackButton.SetUv(&mTexResume, PAUSE_MENU_LOGO_CG);
	//�^�C�g���֖߂�̌Ăяo��
	mTexQuit.load(TEX_QUIT);
	mTitleBackButton.SetVertex(BUTTON_SIZE); //�����ő傫���ύX
	mTitleBackButton.SetColor(W_COLOR, 1.0f);
	mTitleBackButton.position = POS_TITLE_BACK_BUTTON;
	mTitleBackButton.SetUv(&mTexQuit, PAUSE_MENU_LOGO_CG);
	/*����{�^���쐬*/
	mTexGuideButton.load(TEX_GUIDE);
	mGuideButton.SetVertex(BUTTON_SIZE);
	mGuideButton.position = POS_GUIDE_BUTTON;
	mGuideButton.SetUv(&mTexGuideButton, PAUSE_MENU_LOGO_CG);
	/*�J�[�\���l�p�쐬*/
	mTexCursor.load(TEX_CURSOR);
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(&mTexCursor, CURSOR_CG);
	/*��������쐬*/
	mTexOperation.load(TEX_OPERA);
	mOperation.SetVertex(BG_SIZE);
	mOperation.SetUv(&mTexOperation, OPERA_CG);


}




void CPause::Update(){
	/*Operation���o�Ă���ꍇ*/
	if (mOperationFlag){
		/*�E�N���b�N���������ꍇ || �G���^�[�{�^�����������ꍇ*/
		if (CMouse::GetInstance()->mOneLeftFlag || CKey::once(VK_RETURN)){
			mOperationFlag = false;
		}
	}
	else{
		//�Q�[���֖߂�
		if (CCollision2D::Collision2D(mCursor, mBackButton)){ //�J�[�\���������Ă���?
			mBackButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag)//�}�E�X���N���b�N
				mBackGame = true;
		}
		else{
			mBackButton.SetColor(W_COLOR, 1.0f);
		}
		//�^�C�g���ֈړ�
		if (CCollision2D::Collision2D(mCursor, mTitleBackButton)){ //�J�[�\���������Ă���?
			mTitleBackButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag){//�}�E�X���N���b�N
				//CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);
				mSceneChangeFlag = true;
			}
		}
		else{
			mTitleBackButton.SetColor(W_COLOR, 1.0f);
		}
		//�������
		if (CCollision2D::Collision2D(mCursor, mGuideButton)){ //�J�[�\���������Ă���?
			mGuideButton.SetColor(GRAY_COLOR);
			if (CMouse::GetInstance()->mOneLeftFlag){//�}�E�X���N���b�N
				//CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);
				mOperationFlag = true;
			}
		}
		else{
			mGuideButton.SetColor(W_COLOR, 1.0f);
		}
	}

	mCursor.position = CMouse::GetInstance()->mPos;
};

/*
�`�揈���݂̂��s���B
*/
void CPause::Render() {

	CRectangle2::Disp2D_Start();//2D�����J�n

	/*���̏ꏊ�ɕ`�揈��������*/
	mBG.Render();
	mPauseLogo.Render();
	mTitleBackButton.Render();
	mGuideButton.Render();
	mBackButton.Render();
	if (mOperationFlag)mOperation.Render();//�t���O���Ă��Ă���Ƃ��̂�
	mCursor.Render();


	/*�`��I��*/

	CRectangle2::Disp2D_Exit();//2D�����I��

}