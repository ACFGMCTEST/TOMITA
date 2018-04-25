#include "CTitleScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"

/*�R���X�g���N�^*/
CTitleScene::CTitleScene():mTitle(){
	SE_Enter.Load(SOUNDFILE"SE_ENTER.mp3");
}
/*�f�X�g���N�^*/
CTitleScene::~CTitleScene(){
	SE_Enter.Close();
}

/*�X�V����*/
void CTitleScene::Update() {

	mTitle.Update();
	mTitle.Render();
	/*�V�[���J�ڏ���*/
	if (mTitle.SceneFlag()){
		CSceneManager::GetInstance()->ChangeScene(E_HOME);
	}
}