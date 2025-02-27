#ifndef CSCENEMANAGER_HPP
#define CSCENEMANAGER_HPP
#include "../Scene/CScene.h"

class CSceneManager{
private:
	static CSceneManager *mSceneManager;
	CSceneManager();

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
	~CSceneManager();

};
#endif