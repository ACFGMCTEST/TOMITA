#include "CQuestScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"
#include "../GameResult/CGameResult.h"


CQuestScene::CQuestScene()
//	: mpQuest(0)
{
//	mpQuest = new CQuest();
	mpQuest.Init();//������
	
}

CQuestScene::~CQuestScene(){

	//if (mpQuest) {
	//	delete mpQuest;
	//	mpQuest = 0;
	//}

}

void CQuestScene::Update(){
	mpQuest.Update();//�X�V
	mpQuest.Render();//�`��



	/*��������V�[���ڍs����*/

	//�N�G�X�g00���N���b�N�����Ƃ�
	if (CCollision2D::Collision2D(mpQuest.mCursor, mpQuest.mQuestName00)){
		if (CMouse::GetInstance()->mOneLeftFlag){//�}�E�X���N���b�N
			CQuest::eChoice = CQuest::E_QUEST00;//�N�G�X�g00��I������
			CGameResult::mPrize = CGameResult::E_Quest0;
			/*�Q�[�����C���Ɉڍs*/
			//B			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_GAMEMAIN);
			CSceneManager::GetInstance()->eStatus = CSceneManager::E_CHANGE;
			CScene::State = eSceneNo::E_GAMEMAIN;
		}
	}
	//�N�G�X�g01���N���b�N�����Ƃ�
	if (CCollision2D::Collision2D(mpQuest.mCursor, mpQuest.mQuestName01)){
		if (CMouse::GetInstance()->mOneLeftFlag){//�}�E�X���N���b�N
			CQuest::eChoice = CQuest::E_QUEST01;//�N�G�X�g01��I������
			CGameResult::mPrize = CGameResult::E_Quest1;
			/*�Q�[�����C���Ɉڍs*/
			//B			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_GAMEMAIN);
			CSceneManager::GetInstance()->eStatus = CSceneManager::E_CHANGE;
			CScene::State = eSceneNo::E_GAMEMAIN;
		}
	}
	//�N�G�X�g02���N���b�N�����Ƃ�
	if (CCollision2D::Collision2D(mpQuest.mCursor, mpQuest.mQuestName02)){
		if (CMouse::GetInstance()->mOneLeftFlag){//�}�E�X���N���b�N
			CQuest::eChoice = CQuest::E_QUEST02;//�N�G�X�g02��I������
			CGameResult::mPrize = CGameResult::E_Quest2;
			/*�Q�[�����C���Ɉڍs*/
			//B			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_GAMEMAIN);
			CSceneManager::GetInstance()->eStatus = CSceneManager::E_CHANGE;
			CScene::State = eSceneNo::E_GAMEMAIN;
		}
	}



	//�z�[���{�^���Ƃ̘A��
	if (CCollision2D::Collision2D(mpQuest.mCursor, mpQuest.mBackButton)){ //�J�[�\���������Ă���?
		if (CMouse::GetInstance()->mOneLeftFlag) {//�}�E�X���N���b�N
			//B			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_HOME);
			CSceneManager::GetInstance()->eStatus = CSceneManager::E_CHANGE;
			CScene::State = eSceneNo::E_HOME;
		}
	}


}