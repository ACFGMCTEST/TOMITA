#include "CLoadSoundManager.h"


CLoadSoundManager *CLoadSoundManager::mpLoadSoundManager = 0;
//GetInstance
CLoadSoundManager* CLoadSoundManager::GetInstance() {
	if (mpLoadSoundManager == 0) {
		mpLoadSoundManager = new CLoadSoundManager();
	}
	return mpLoadSoundManager;
}

//ファイル読み込み
void CLoadSoundManager::Load(char *name) {
	mSound.push_back(new CSound(name));
	mName.push_back(name);
}

CLoadSoundManager::CLoadSoundManager() {
	Load(BGM_GAME_MAIN);//ゲームメイン部分で流れるもの
	Load(SE_PUNCH);//パンチ音
	Load(SE_DAMAGE);//ダメージ音
	Load(SE_PL_DAMAGE);//plaeyrダメージ音
	Load(SE_FALL);//落下ダメージ
	Load(SE_CURSOR_MOVE);//カーソル移動
	Load(SE_DECISION);//決定音
	Load(SE_ENTER);//エンター音
}

//サウンド呼び出し
CSound *CLoadSoundManager::Sound(char *name) {


#define CLASS CLoadSoundManager::GetInstance()
	for (int i = 0; i < CLASS->mSound.size(); i++)
	{
		//ネームが一致した場合
		if (CLASS->mName[i] == name) {
			return CLASS->mSound[i];
		}
	}

	printf("%sはありません\n", name);
	return nullptr;
}

CLoadSoundManager::~CLoadSoundManager() {}
