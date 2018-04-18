//�����O��
#include"CQuest.h"
#include "../../Key/CKey.h"
#include"../../../Define/define.h"
#include <fstream> 
#include<stdio.h>
#include "../../Key/CMouse.h"
#include "../../Collision/CCollision2D.h"

#define QUEST_NAME0 TGA_FILE"questname0.tga"
#define QUEST_NAME1 TGA_FILE"questname1.tga"
#define QUEST_NAME2 TGA_FILE"questname2.tga"
#define QUEST_NAME3 TGA_FILE"questname3.tga"

#define NAME_SIZE -310.0f, 50.0f, 310.0f, -50.0f
#define NAME_Y -0//�������p
#define NAME_INTRV 1.1f//�l�[���̊Ԋu
//�l�[���{�[�h�̃|�W�V����
#define NAME_POS0	CVector2(0, 160 + NAME_Y)
#define NAME_POS1	CVector2(0,  0 + NAME_Y)
#define NAME_POS2	CVector2(0, -160 + NAME_Y)
//#define NAME_POS3	CVector2(0,-200)
//�l�[���{�[�h�̉e
#define NAME_POS0S	CVector2(10, 150 + NAME_Y)
#define NAME_POS1S	CVector2(10,  -10 + NAME_Y)
#define NAME_POS2S	CVector2(10, -170 + NAME_Y)
//#define NAME_POS3S	CVector2(10,-210)


#define BACK       TGA_FILE"backbutton.tga"
/*tex�t�F�C��*/
#define CURSOR_CG 0,0,150,120

/*�ÓI������*/
CQuest::E_CHOICE CQuest::eChoice = E_QUEST00;


CQuest::~CQuest(){
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



void CQuest::Init(){

	alpha = 0.0f;
	alpha2 = 0.0f;

	//�w�i�̌Ăяo��
	mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpTexture->load(TGA_FILE"BG.tga");	//�e�N�X�`���t�@�C���ǂݍ���
	
	mBG.SetVertex(BG_SIZE); //�����ő傫���ύX
	mBG.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	mBG.SetUv(mpTexture, 0, 0, 1024, 768);



	////�N�G�X�g��00
	mpTexture = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpTexture->load(QUEST_NAME0);	//�e�N�X�`���t�@�C���ǂݍ���
	mQuestName00.SetVertex(NAME_SIZE);
	mQuestName00.SetColor(WHITE_COLOR);
	mQuestName00.SetUv(mpTexture, TEST_CG);
	mQuestName00.position = NAME_POS0;

	mShadow[0] = mQuestName00;
	mShadow[0].SetColor(SKELETON_BLACK_COLOR);
	mShadow[0].position = NAME_POS0S;

	//�N�G�X�g��01
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(QUEST_NAME1);	//�e�N�X�`���t�@�C���ǂݍ���
	mQuestName01.SetVertex(NAME_SIZE);
	mQuestName01.SetColor(WHITE_COLOR);
	mQuestName01.SetUv(mpMenu, TEST_CG);
	mQuestName01.position = NAME_POS1;

	mShadow[1] = mQuestName01;
	mShadow[1].SetColor(SKELETON_BLACK_COLOR);
	mShadow[1].position = NAME_POS1S;

	//�N�G�X�g��02
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(QUEST_NAME2);	//�e�N�X�`���t�@�C���ǂݍ���
	mQuestName02.SetVertex(NAME_SIZE);
	mQuestName02.SetColor(WHITE_COLOR);
	mQuestName02.SetUv(mpMenu, TEST_CG);
	mQuestName02.position = NAME_POS2;

	mShadow[2] = mQuestName02;
	mShadow[2].SetColor(SKELETON_BLACK_COLOR);
	mShadow[2].position = NAME_POS2S;


	////�߂�{�^���̌Ăяo��
	mpMenu = new CTexture();	//�e�N�X�`���N���X�̃C���X�^���X�쐬
	mpMenu->load(BACK);	//�e�N�X�`���t�@�C���ǂݍ���
	mBackButton.SetVertex(BACK_RECT);
	mBackButton.SetColor(WHITE_COLOR);
	mBackButton.SetUv(mpMenu, BACK_CG);
	mBackButton.position = BACK_POS;



	/*�J�[�\���l�p�쐬*/
	mpTexCursor = new CTexture();
	mpTexCursor->load(TGA_FILE"cursor.tga");
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(mpTexCursor, CURSOR_CG);

}




void CQuest::Update(){
	mQuestName00.SetColor(WHITE_COLOR);
	mQuestName01.SetColor(WHITE_COLOR);
	mQuestName02.SetColor(WHITE_COLOR);
	//mQuestName03.SetColor(WHITE_COLOR);
	mQuestName00.position = NAME_POS0;
	mQuestName01.position = NAME_POS1;
	mQuestName02.position = NAME_POS2;
	//mQuestName03.position = NAME_POS3;

	//�N���b�N���ɉ������܂ꂽ�悤�Ȍ`��
	if (CCollision2D::Collision2D(mCursor, mQuestName00)){mQuestName00.SetColor(GRAY_COLOR);
	if (CMouse::GetInstance()->mOneLeftFlag){ mQuestName00.position = NAME_POS0S; mQuestName00.SetColor(DARK_GRAY_COLOR); }
	}
	if (CCollision2D::Collision2D(mCursor, mQuestName01)){mQuestName01.SetColor(GRAY_COLOR);
	if (CMouse::GetInstance()->mOneLeftFlag){ mQuestName01.position = NAME_POS1S;  mQuestName01.SetColor(DARK_GRAY_COLOR); }
	}
	if (CCollision2D::Collision2D(mCursor, mQuestName02)){mQuestName02.SetColor(GRAY_COLOR);
	if (CMouse::GetInstance()->mOneLeftFlag){ mQuestName02.position = NAME_POS2S; mQuestName02.SetColor(DARK_GRAY_COLOR); }
	}
	
	mBackButton.SetColor(WHITE_COLOR);
	if (CCollision2D::Collision2D(mCursor, mBackButton)){
mBackButton.SetColor(GRAY_COLOR);
	}
	mCursor.position = CMouse::GetInstance()->mPos;

};

/*
�`�揈���݂̂��s���B
*/
void CQuest::Render() {
	CRectangle2::Disp2D_Start();//�`��͂���
	mBG.Render();
	for (int i = 0; i < BOARD; i++)
	{
		mShadow[i].Render();
	}

	mQuestName00.Render();
	mQuestName01.Render();
	mQuestName02.Render();
	mBackButton.Render();

	mCursor.Render();
	CRectangle2::Disp2D_Exit();;//�`��I��
	


}