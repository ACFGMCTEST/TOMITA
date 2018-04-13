#include "CQuestScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"
#include "../GameResult/CGameResult.h"


CQuestScene::CQuestScene(){
	mQuest.Init();//������
	
}

CQuestScene::~CQuestScene(){}

void CQuestScene::Update(){
	mQuest.Update();//�X�V
	mQuest.Render();//�`��



	/*��������V�[���ڍs����*/

	//�N�G�X�g00���N���b�N�����Ƃ�
	if (CCollision2D::Collision2D(mQuest.mCursor, mQuest.mQuestName00)){
		if (CMouse::GetInstance()->mOneLeftFlag){//�}�E�X���N���b�N
			CQuest::eChoice = CQuest::E_QUEST00;//�N�G�X�g00��I������
			CGameResult::mPrize = CGameResult::E_Quest0;
			/*�Q�[�����C���Ɉڍs*/
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_GAMEMAIN);
		}
	}
	//�N�G�X�g01���N���b�N�����Ƃ�
	if (CCollision2D::Collision2D(mQuest.mCursor, mQuest.mQuestName01)){
		if (CMouse::GetInstance()->mOneLeftFlag){//�}�E�X���N���b�N
			CQuest::eChoice = CQuest::E_QUEST01;//�N�G�X�g01��I������
			CGameResult::mPrize = CGameResult::E_Quest1;
			/*�Q�[�����C���Ɉڍs*/
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_GAMEMAIN);
		}
	}
	//�N�G�X�g02���N���b�N�����Ƃ�
	if (CCollision2D::Collision2D(mQuest.mCursor, mQuest.mQuestName02)){
		if (CMouse::GetInstance()->mOneLeftFlag){//�}�E�X���N���b�N
			CQuest::eChoice = CQuest::E_QUEST02;//�N�G�X�g02��I������
			CGameResult::mPrize = CGameResult::E_Quest2;
			/*�Q�[�����C���Ɉڍs*/
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_GAMEMAIN);
		}
	}
	////�N�G�X�g03���N���b�N�����Ƃ�
	//if (CCollision2D::Collision2D(mQuest.mCursor, mQuest.mQuestName03)){
	//	if (CMouse::GetInstance()->mOneLeftFlag){//�}�E�X���N���b�N
	//		CQuest::eChoice = CQuest::E_QUEST03;//�N�G�X�g03��I������
	//		CGameResult::mPrize = CGameResult::E_Quest3;
	//		/*�Q�[�����C���Ɉڍs*/
	//		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_GAMEMAIN);
	//	}
	//}



	//�z�[���{�^���Ƃ̘A��
	if (CCollision2D::Collision2D(mQuest.mCursor, mQuest.mBackButton)){ //�J�[�\���������Ă���?
		if (CMouse::GetInstance()->mOneLeftFlag)//�}�E�X���N���b�N
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_HOME);
	}


}