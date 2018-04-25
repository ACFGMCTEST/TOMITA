//�^�C�g���̃v���O���~���O
#include "CTitleScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"
CTitleScene::CTitleScene(){
//	SE_Enter.load(SOUNDFILE"SE_ENTER.mp3");
	mTitle.Init();
}

CTitleScene::~CTitleScene(){
//	SE_Enter.close();
}

void CTitleScene::Update() {
	
	mTitle.Update();
	mTitle.Render();

	/*�����蔻��*/
	if (CCollision2D::Collision2D(mTitle.mCursor, mTitle.mGameStart)){ //�J�[�\���������Ă���?
		if (CMouse::GetInstance()->mOneLeftFlag) {//�}�E�X���N���b�N
			//B			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_HOME);
			CSceneManager::GetInstance()->eStatus = CSceneManager::E_CHANGE;
			CScene::State = eSceneNo::E_HOME;
		}
	}
	
	if (CCollision2D::Collision2D(mTitle.mCursor, mTitle.mGameExit)){ //�J�[�\���������Ă���?
		if (CMouse::GetInstance()->mOneLeftFlag)//�}�E�X���N���b�N
			exit(0);
	}

}