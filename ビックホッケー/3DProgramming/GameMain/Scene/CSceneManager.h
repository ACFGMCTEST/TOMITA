#ifndef CSCENEMANAGER_HPP
#define CSCENEMANAGER_HPP
#include "../Scene/CScene.h"
#include "../Sound/CSound.h"

/*シーン管理クラス*/
class CSceneManager{
private:
	static CSceneManager *mSceneManager;
	
	CSound mSEClear;//ゲームクリア
	CSound mSEOver;//ゲームオーバー

public:

	int NextNo;
	enum EState
	{
		E_INIT,
		E_LOOP
	};
	EState eStatus = E_INIT;
	static CSceneManager *GetInstance(); //GetInstance

	void ChangeScene(eSceneNo no);	//シーン切り替え
	void DeleteScene();			//KILL
	void SceneMain();
	CSceneManager();
	~CSceneManager();

};
#endif