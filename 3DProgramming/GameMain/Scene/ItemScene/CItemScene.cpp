#include "CItemScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"

CItemScene::CItemScene(){
	mItem.Init();//������
}

CItemScene::~CItemScene(){}

void CItemScene::Update(){
	mItem.Update();//�X�V
	mItem.Render();//�`��

	///*��������V�[���ڍs����*/

	/*�����蔻��*/
	if (CCollision2D::Collision2D(mItem.mCursor, mItem.mBackButton)){ //�J�[�\���������Ă���?
		if (CMouse::GetInstance()->mLeftFlag){//�}�E�X���N���b�N
			//B			CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_HOME);
			CSceneManager::GetInstance()->eStatus = CSceneManager::E_CHANGE;
			CScene::State = eSceneNo::E_HOME;
		}
	}

}