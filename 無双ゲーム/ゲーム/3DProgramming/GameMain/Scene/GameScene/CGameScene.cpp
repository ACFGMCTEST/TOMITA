#include "Windows.h"
#include "CGameScene.h"
#include "../../Collision/CCollisionManager.h"
#include "../../Key/CKey.h"
#include "../../Key/CMouse.h"
#include "./../CSceneManager.h"
#include "../QuestScene/CQuest.h"
#include "../../Graphic/CBillBoard.h"
#include "Tutorial\CTutorial.h"
#include  "Result\CResult.h"
#include "../../Sound/CLoadSoundManager.h"
#include "Pause\CPause.h"

CCamera MainCamera;
CCamera MapCamera;

bool CGameScene::mEnterEventFlag = false;

CGameScene::E_STATE CGameScene::eState = CGameScene::E_INIT;

CGameScene::CGameScene(){
	eState = E_INIT;

};

CGameScene::~CGameScene(){

}

/*�~�j�}�b�v����ɕ\���������*/
void CGameScene::MiniMapRender() {
	
	MapCamera.SetPos();

	MapCamera.Render();

	//�~�j�}�b�v�\���J�n
	MapCamera.StartMiniMap();
	

	CMap::GetInstance()->MiniMapRender();
	CTaskManager::GetInstance()->AllMiniMapRender();
	//�~�j�}�b�v�\���I��
	MapCamera.EndMiniMap();

	

}

//�J��Ԃ����s����鏈��
void CGameScene::Update() {
	switch (eState)
	{
	case E_INIT:
		CMap::GetInstance()->Init();
		CSceneModel::GetInstance()->Init();
		CResult::GetInstance()->Init();
		MainCamera.Init();
		CTutorial::GetInstance()->Init();

		eState = E_MAIN;
		break;
		
	case E_MAIN:

		MainCamera.Update();
		/*�|�[�Y�t���O������*/
		if (!mEnterEventFlag) {
			CMap::GetInstance()->Update();
			CTaskManager::GetInstance()->AllUpdate();
			CCollisionManager::GetInstance()->Update();
			CResult::GetInstance()->Update();
		}
		/*�`��*/
		CMap::GetInstance()->Render();
		CTaskManager::GetInstance()->AllRender();
		//�~�j�}�b�v�\��
		MiniMapRender();
		CResult::GetInstance()->Render();
		//�`���[�g���A���̍X�V�@�����Ŏ~�߂鏈���ȂǓ���Ă���
		CTutorial::GetInstance()->Update();
		CTutorial::GetInstance()->Render();

		//�|�[�Y���
		CPause::GetInstance()->Update();
		CPause::GetInstance()->Render();

		break;
	case E_END:
		CLoadSoundManager::Sound(BGM_GAME_MAIN)->Stop();
		CLoadSoundManager::Sound(BGM_GAME_MAIN)->Close();
		CCollisionManager::GetInstance()->AllKill();
		CTaskManager::GetInstance()->AllKill();
		
		eState = E_INIT;
		/*�^�C�g���ɖ߂�*/
		CSceneManager::GetInstance()->ChangeScene(eSceneNo::E_HOME);
		break;
	}


}
