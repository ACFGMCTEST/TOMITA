//�����O��
#include"COption.h"
#include"../../Key/CKey.h"
#include"../../Key/CMouse.h"
#include <fstream> 
#include<stdio.h>

#define DISP_2D_Y 768 //�c��

#define BACK_GROUND     -400.0f, 300.0f, 400.0f, -300.0f
///////////////////////////////////////
//BGM
#define BGM_BOX	-300.0f, 220.0f,    0.0f, 30.0f
#define BGM_MIN	-20.0f,  40.0f, 20.0f,   -40.0f
#define BGM_MAX -20.0f,  40.0f, 20.0f,   -40.0f
///////////////////////////////////////
//SE
#define SE_BOX	-300.0f, 20.0f,	  0.0f,   -170.0f
#define SE_MIN	-20.0f,  40.0f, 20.0f,   -40.0f
#define SE_MAX	-20.0f,  40.0f, 20.0f,   -40.0f
///////////////////////////////////////
//���̑�
#define GAGE_ICON	      -20.0f,  40.0f, 20.0f,   -40.0f
#define BACK_BUTTON		-320.0f, -180.0f, -220.0f, -240.0f

#define FIRST_X	100			//�A�C�R���̏������l
#define FIRST_Y	180		//�A�C�R���̏������l
#define RECT_WIDE 3

#define ITEM_MENU	  TGA_FILE"itembutton.tga"
#define BACK	  TGA_FILE"backbutton.tga"


/*tex�t�F�C��*/
#define CURSOR_CG 0,0,150,120


COption::COption() :rectnum(0){
	rectx = FIRST_X;
	recty = FIRST_Y;
}

COption::~COption(){
	if (mpTexture) {
		//�e�N�X�`�����g���Ă���΃C���X�^���X�폜
		delete mpTexture;
		mpTexture = 0;
	}
	if (mpMenu) {
		//�e�N�X�`�����g���Ă���΃C���X�^���X�폜
		delete mpMenu;
		mpMenu = 0;
	}
}

void COption::Init(){

	alpha = 0.0f;
	alpha2 = 0.0f;




	//�w�i�̌Ăяo��
	mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpTexture->load(TGA_FILE"testback_.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*gluOrtho2D(-320.0f, 320.0f, -340.0f, 340.0f);*/
	mBackGround.SetVertex(BACK_GROUND); //�����ő傫���ύX
	mBackGround.SetColor(RED_COLOR);
	mBackGround.SetUv(mpTexture, 0, 0, 1024, 768);

//////////////////////////////////////////////////////////////////////////////////
	//BGM
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"start_menu_.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mBgmBox.SetVertex(BGM_BOX);
	mBgmBox.SetColor(GREEN_COLOR);
	mBgmBox.SetUv(mpMenu, 0, 0, 250, 46);
	//mSelectOutfit.position();

	//SE
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"start_menu_.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mSeBox.SetVertex(SE_BOX);
	mSeBox.SetColor(YELLOW_COLOR);
	mSeBox.SetUv(mpMenu, 0, 46, 250, 89);


/////////////////////////////////////////////////////////////////////////////////////////
	//BGM_MAX
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"start_menu_.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mBgmMax.SetVertex(BGM_MAX);
	mBgmMax.SetColor(NOTHING_COLOR);
	mBgmMax.SetUv(mpMenu, 0, 46, 250, 89);

	//BGM_MIN
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"start_menu_.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mBgmMin.SetVertex(BGM_MIN);
	mBgmMin.SetColor(NOTHING_COLOR);
	mBgmMin.SetUv(mpMenu, 0, 46, 250, 89);

///////////////////////////////////////////////////////////////////////////////////////

	//SE_MAX
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"start_menu_.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mSeMax.SetVertex(SE_MAX);
	mSeMax.SetColor(NOTHING_COLOR);
	mSeMax.SetUv(mpMenu, 0, 46, 250, 89);

	//SE_MIN
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"start_menu_.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mSeMin.SetVertex(SE_MIN);
	mSeMin.SetColor(NOTHING_COLOR);
	mSeMin.SetUv(mpMenu, 0, 46, 250, 89);



///////////////////////////////////////////////////////////////////////////////////////////



	////�߂�{�^���̌Ăяo��
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(BACK);	//�e�N�X�`���t�@�C���ǂݍ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-320.0f, 320.0f, -240.0f, 240.0f);
	mBackButton.SetVertex(BACK_RECT);
	mBackButton.SetColor(1.0f, 1.0f, 0.0f, 0.5f);
	mBackButton.SetUv(mpMenu, TEST_CG);



///////////////////////////////////////////////////////////////////////////////////////////
	int rectcnt = BGM_GAGE;

	for (int i = 0; i < BGM_GAGE; i++){
		printf("%d\n", i);

		rectcnt--;
		//BGM�Q�[�W
		mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpMenu->load("not_image");	//�e�N�X�`���t�@�C���ǂݍ���
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		mBgmGage[i].SetVertex(GAGE_ICON);
		mBgmGage[i].SetColor (PINK_COLOR);
		mBgmGage[i].position = CVector2(rectx, recty);
		mBgmGage[i].SetUv    (mpMenu, TEST_CG);


		//SE�Q�[�W
		mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpMenu->load("not_image");	//�e�N�X�`���t�@�C���ǂݍ���
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		mSeGage[i].SetVertex(GAGE_ICON);
		mSeGage[i].SetColor (WHITE_COLOR);
		mSeGage[i].position = CVector2(rectx,-100);
		mSeGage[i].SetUv    (mpMenu, TEST_CG);

		rectx += 50.0f;
		if (rectcnt == 0){ rectx = FIRST_X;  rectcnt = RECT_WIDE; };

	}

	


	/*�J�[�\���l�p�쐬*/
	mpTexCursor = new CTexture();
	mpTexCursor->load(TGA_FILE"cursor.tga");
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(mpTexCursor, CURSOR_CG);

	status = 0;//�f�t�H���g��0

}




void COption::Update(){


	mBackButton.SetColor(WHITE_COLOR);		   //���F

	mCursor.position = CMouse::mPos;

	//���j���[��ʂł̑I���B�Q���ڂ����Ȃ�����status�ړ��������ł��

	if (CKey::once(UP_KEY)){
		//cursorchange.play();
		//mCursor.SetVertex(-180.0f, -90.0f, -140.0f, -130.0f);
		/*	status = 0;*/
	}

	if (CKey::once(DOWN_KEY)){
		/*	cursorchange.play();
		mCursor.SetVertex(-180.0f, -170.0f, -140.0f, -210.0f);*/
		/*status = 1;*/
	}

	//����
	if (CKey::push(ENTER_KEY))
	{
		//�쐬���܂����H�Ƃ͂��@��������\������

		/*mHelp.Render();
		mYes.Render();
		mNo.Render();*/



	}

	switch (status)
	{
	case 0:
		//mGameStart.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		//mGameExit.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		if (CKey::push(ENTER_KEY))
		{
			//SE�Đ�
			//returnkey.play();

			//BGM���X�g�b�v����
			//Itembgm.stop();

			//CSceneManager::GetInstance()->ChangeScene(SceneNo::GAME_MAIN);	//�Q�[����ʂɈڍs���܂��B

		}
		break;
	case 1:
		//mGameStart.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		//mGameExit.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

		if (CKey::push(ENTER_KEY))
		{
			//SE�̍Đ�
			/*	returnkey.play();*/

			exit(0);	//�Q�[�����I�����܂��B

		}

		break;
	}


};

/*
�`�揈���݂̂��s���B
*/
void COption::Render() {
	CRectangle2::Disp2D_Start();//�`��J�n
	mBackGround.Render();
	mBgmBox.Render();
	mSeBox.Render();

	mBgmMin.Render();
	mBgmMax.Render();

	mSeMin.Render();
	mSeMax.Render();


	for (int i = 0; i <= BGM_GAGE; i++) {

		mBgmGage[i].Render();
	};
	for (int i = 0; i <= SE_GAGE; i++) {

		mSeGage[i].Render();
	};

	mBackButton.Render();

	mCursor.Render();
	CRectangle2::Disp2D_Exit();//�`��I��




	/*mSelectOutfitDetails.	Render();*/
	//odifit.Render();
	//thdifit.Render();
	//twdifit.Render();




}