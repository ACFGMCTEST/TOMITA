#include "CHomeScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"

CHomeScene::CHomeScene(){
	mHome.Init();//������
}

CHomeScene::~CHomeScene(){}

void CHomeScene::Update(){
	mHome.Update();//�X�V
	mHome.Render();//�`��
	
	//printf("%d  %d\n", mHome.mStatus,mHome.mMove);

	/*��������V�[���ڍs����*/
	/*�����蔻��*/
	if (CCollision2D::Collision2D(mHome.mCursor, mHome.mSelectButton) && mHome.mStatus == mHome.QUEST&&mHome.mMove==false){ //�J�[�\���������Ă���?
		if (CMouse::mOneLeftFlag){//�}�E�X���N���b�N
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_QUEST);
			return;
		}
	}
	/*�����蔻��*/
	if (CCollision2D::Collision2D(mHome.mCursor, mHome.mShopButton) && mHome.mStatus == mHome.SHOP&&mHome.mMove == false){ //�J�[�\���������Ă���?
		if (CMouse::mOneLeftFlag){//�}�E�X���N���b�N
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_SHOP);
			return;

		}
	}

	/*�����蔻��*/
	if (CCollision2D::Collision2D(mHome.mCursor, mHome.mItemButton) && mHome.mStatus == mHome.ITEM&&mHome.mMove == false){ //�J�[�\���������Ă���?
		if (CMouse::mOneLeftFlag){//�}�E�X���N���b�N
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_ITEM);
			return;

		}
	}

	/*�����蔻��*/
	if (CCollision2D::Collision2D(mHome.mCursor, mHome.mTitleButton) && mHome.mStatus == mHome.TITLE&&mHome.mMove == false){ //�J�[�\���������Ă���?
		if (CMouse::mOneLeftFlag){//�}�E�X���N���b�N
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_TITLE);
			return;

		}
	}



}