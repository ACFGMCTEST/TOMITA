#ifndef CSCENEMANAGER_HPP
#define CSCENEMANAGER_HPP
#include "../Scene/CScene.h"
#include "../Sound/CSound.h"

/*�V�[���Ǘ��N���X*/
class CSceneManager{
private:
	static CSceneManager *mSceneManager;
	CSound mBgm;//BGM

public:

	int NextNo;
	enum EState
	{
		E_INIT,
		E_LOOP
	};
	EState eStatus = E_INIT;
	static CSceneManager *GetInstance(); //GetInstance

	void ChangeScene(eSceneNo no);	//�V�[���؂�ւ�
	void DeleteScene();			//KILL
	void SceneMain();
	CSceneManager();
	~CSceneManager();

};
#endif