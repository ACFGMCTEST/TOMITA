#include "CTitleScene.h"
#include "../../Key/CKey.h"
#include "../CSceneManager.h"

/*コンストラクタ*/
CTitleScene::CTitleScene():mTitle(){
	SE_Enter.Load(SOUNDFILE"SE_ENTER.mp3");
}
/*デストラクタ*/
CTitleScene::~CTitleScene(){
	SE_Enter.Close();
}

/*更新処理*/
void CTitleScene::Update() {

	mTitle.Update();
	mTitle.Render();
	/*シーン遷移処理*/
	if (mTitle.SceneFlag()){
		CSceneManager::GetInstance()->ChangeScene(E_HOME);
	}
}