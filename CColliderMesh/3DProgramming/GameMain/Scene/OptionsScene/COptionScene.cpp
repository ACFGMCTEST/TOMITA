#include "COptionScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"

COptionScene::COptionScene(){
	mOption.Init();//������
}

COptionScene::~COptionScene(){}

void COptionScene::Update(){
	mOption.Update();//�X�V
	mOption.Render();//�`��

	///*��������V�[���ڍs����*/

	/*�����蔻��*/
	if (CCollision2D::Collision2D(mOption.mCursor, mOption.mBackButton)){ //�J�[�\���������Ă���?
		if (CMouse::mLeftFlag){//�}�E�X���N���b�N
			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_HOME);
		}
	}
	///*�����蔻��*/
	//if (CCollision2D::Collision2D(mItem.mCursor, mItem.mShopButton)){ //�J�[�\���������Ă���?
	//	if (CMouse::mLeftFlag){//�}�E�X���N���b�N
	//		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_SHOP);
	//	}
	//}

}