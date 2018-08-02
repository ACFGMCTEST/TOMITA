#include"CPause.h"
#include "../../../Key/CKey.h"

CPause *CPause::mpPause = 0;

//GetInstance
CPause* CPause::GetInstance() {
	if (mpPause == 0) {
		mpPause = new CPause();
	}
	return mpPause;
}


CPause::~CPause() {

}

CPause::CPause() : mPauseFlag(false){
#define BUTTON_SET(x,y,py) CVector2(x,y),\
 CVector2(DISP_2D_X - x/2,DISP_2D_Y/2 * py - y/2)  //�|�W�V����
	//Cursor�ݒ�
	mCursor.SetVerPos(BUTTON_SET(70,70,0));
	//�|�[�Y���
	mPause.SetVerPos(BUTTON_SET(570, 70, 3));
	//���C���ɂ��ǂ�
	mMainBack.SetVerPos(BUTTON_SET(370, 70, 2));
	//�^�C�g���ɖ߂�
	mCursor.SetVerPos(BUTTON_SET(370, 70, 1));

}

/*�X�V����*/
void CPause::Update() {
	//�G�X�P�[�v�L�[�Ő؂�ւ�
	if (CKey::once(VK_ESCAPE)) {
		if (mPauseFlag) mPauseFlag = false;
		else mPauseFlag = true;
	}

};
/*
�`�揈���݂̂��s���B
*/
void CPause::Render() {

	CRectangle2::Disp2D_Start();//2D�����J�n

	if (mPauseFlag) {
		mCursor.Render();
		mPause.Render();//�|�[�Y���
		mMainBack.Render();//���C���ɖ߂�
		mTitleBack.Render();
	}
	
	CRectangle2::Disp2D_Exit();//2D�����I��

}