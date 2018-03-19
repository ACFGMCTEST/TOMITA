//�����O��
#include "CShopCreating.h"
#include"../../Key/CKey.h"
#include "../../../Define/Define.h"
#include "../../Key/CMouse.h"

#define WEAPON_NAME "weaponname.tga"
#define ARMOR_NAME "armorname.tga"


int CShopCreating::status = E_WEAPON;

CShopCreating::~CShopCreating(){
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



void CShopCreating::Init(){

	alpha = 0.0f;
	alpha2 = 0.0f;

	printf("����ɂ���\n");
	printf("%d\n", status);

	switch (status)
	{
	case E_WEAPON:
		printf("Weapon�ł�");
		//���햼�O�̌Ăяo��
		mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpMenu->load(WEAPON_NAME);	//�e�N�X�`���t�@�C���ǂݍ���


		mWeaponName00.SetVertex(-200.0f, 200.0f, 20.0f, 130.0f);
		mWeaponName00.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		mWeaponName00.SetUv(mpMenu, TEST_CG);

		//���햼�O�̌Ăяo��
		mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpMenu->load(WEAPON_NAME);	//�e�N�X�`���t�@�C���ǂݍ���


		mWeaponName01.SetVertex(-200.0f, 110.0f, 20.0f, 40.0f);
		mWeaponName01.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		mWeaponName01.SetUv(mpMenu, TEST_CG);

		////���햼�O�̌Ăяo��
		mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpMenu->load(WEAPON_NAME);	//�e�N�X�`���t�@�C���ǂݍ���


		mWeaponName02.SetVertex(-200.0f, 20.0f, 20.0f, -50.0f);
		mWeaponName02.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		mWeaponName02.SetUv(mpMenu, TEST_CG);


		////���햼�O�̌Ăяo��
		mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpMenu->load(WEAPON_NAME);	//�e�N�X�`���t�@�C���ǂݍ���


		mWeaponName03.SetVertex(-200.0f, -70.0f, 20.0f, -140.0f);
		mWeaponName03.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		mWeaponName03.SetUv(mpMenu, TEST_CG);

		////�����o���̌Ăяo��
		mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpMenu->load(WEAPON_NAME);	//�e�N�X�`���t�@�C���ǂݍ���

		mWeaponDetails.SetVertex(50.0f, 220.0f, 310.0f, -220.0f);
		mWeaponDetails.SetColor(1.0f, 1.0f, 1.0f, 0.0f);
		mWeaponDetails.SetUv(mpMenu, TEST_CG);

		break;

   case E_ARMOR:
		printf("Armor�ł�");
		//���햼�O�̌Ăяo��
		mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpMenu->load(ARMOR_NAME);	//�e�N�X�`���t�@�C���ǂݍ���


		mWeaponName00.SetVertex(-200.0f, 200.0f, 20.0f, 130.0f);
		mWeaponName00.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		mWeaponName00.SetUv(mpMenu, TEST_CG);

		//���햼�O�̌Ăяo��
		mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpMenu->load(ARMOR_NAME);	//�e�N�X�`���t�@�C���ǂݍ���


		mWeaponName01.SetVertex(-200.0f, 110.0f, 20.0f, 40.0f);
		mWeaponName01.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		mWeaponName01.SetUv(mpMenu, TEST_CG);

		////���햼�O�̌Ăяo��
		mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpMenu->load(ARMOR_NAME);	//�e�N�X�`���t�@�C���ǂݍ���


		mWeaponName02.SetVertex(-200.0f, 20.0f, 20.0f, -50.0f);
		mWeaponName02.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		mWeaponName02.SetUv(mpMenu, TEST_CG);


		////���햼�O�̌Ăяo��
		mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpMenu->load(ARMOR_NAME);	//�e�N�X�`���t�@�C���ǂݍ���


		mWeaponName03.SetVertex(-200.0f, -70.0f, 20.0f, -140.0f);
		mWeaponName03.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		mWeaponName03.SetUv(mpMenu, TEST_CG);

		////�����o���̌Ăяo��
		mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
		mpMenu->load(ARMOR_NAME);	//�e�N�X�`���t�@�C���ǂݍ���

		mWeaponDetails.SetVertex(50.0f, 220.0f, 310.0f, -220.0f);
		mWeaponDetails.SetColor(1.0f, 1.0f, 1.0f, 0.0f);
		mWeaponDetails.SetUv(mpMenu, TEST_CG);

		break;
	}


	//�w�i�̌Ăяo��
	mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpTexture->load("testback_.tga");	//�e�N�X�`���t�@�C���ǂݍ���

	mBackGround.SetVertex(BG_SIZE); //�����ő傫���ύX
	mBackGround.SetColor(1.0f, 1.0f, 1.0f, 0.0f);
	mBackGround.SetUv(mpTexture, 0, 0, 1024, 768);



	////�߂�{�^���̌Ăяo��
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"backbutton.tga");	//�e�N�X�`���t�@�C���ǂݍ���


	mBackButton.SetVertex(BACK_RECT);
	mBackButton.SetColor(1.0f, 1.0f, 0.0f, 0.5f);
	mBackButton.SetUv(mpMenu, TEST_CG);




	////�쐬���܂����H�̌Ăяo��
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬


	mHelp.SetVertex(-120.0f, 160.0f, 120.0f, 60.0f);
	mHelp.SetColor(0.7f, 0.7f, 1.0f, 0.8f);
	mHelp.SetUv(mpMenu, 0, 46, 250, 89);


	////�͂��{�^���̌Ăяo��
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"start_menu_.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	

	mYes.SetVertex(-280.0f, -20.0f, -30.0f, -140.0f);
	mYes.SetColor(0.7f, 0.7f, 1.0f, 0.8f);
	mYes.SetUv(mpMenu, 0, 46, 250, 89);


	////�������{�^���̌Ăяo��
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(TGA_FILE"start_menu_.tga");	//�e�N�X�`���t�@�C���ǂݍ���


	mNo.SetVertex(30.0f, -20.0f, 280.0f, -140.0f);
	mNo.SetColor(0.7f, 0.7f, 1.0f, 0.8f);
	mNo.SetUv(mpMenu, 0, 46, 250, 89);




	/*�J�[�\���l�p�쐬*/
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);


	status = 0;//�f�t�H���g��0
}




void CShopCreating::Update(){

	mBackGround.SetColor(1.0f, 0.0f, 0.0f, 1.0f); //�ԐF
	mBackButton.SetColor(WHITE_COLOR); //���F
	mWeaponName00.SetColor(WHITE_COLOR); //�ΐF
	mWeaponName01.SetColor(WHITE_COLOR); //�F
	mWeaponName02.SetColor(WHITE_COLOR); //���F
	mWeaponName03.SetColor(WHITE_COLOR); //�D�F
	mWeaponDetails.SetColor(WHITE_COLOR); //���F

	mCursor.position = CMouse::GetInstance()->mPos;

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

		mHelp.Render();
		mYes.Render();
		mNo.Render();



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
			//ShopCreatingbgm.stop();

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
void CShopCreating::Render() {
	CRectangle2::Disp2D_Start();//�`��J�n
	mBackGround.Render();
	mWeaponName00.Render();
	mWeaponName01.Render();
	mWeaponName02.Render();
	mWeaponName03.Render();
	mBackButton.Render();
	mWeaponDetails.Render();
	mCursor.Render();
	CRectangle2::Disp2D_Exit();//�`��I��
	//odifit.Render();
	//thdifit.Render();
	//twdifit.Render();




}