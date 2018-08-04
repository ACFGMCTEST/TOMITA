#ifndef SOUND_LOAD_MANAGER_HPP
#define SOUND_LOAD_MANAGER_HPP

#include "CSound.h"
#include <string>
#include <vector>       // ヘッダファイルインクルード

#define BGM_GAME_MAIN   BGM_FILE"BGM.mp3"//BGM
#define SE_PUNCH		SE_FILE"PunchSwing.mp3"//パンチ音
#define SE_DAMAGE		SE_FILE"Damage.mp3"//ダメージ音
#define SE_PL_DAMAGE	SE_FILE"PlayerDamage.mp3"//ダメージ音
#define SE_FALL			SE_FILE"FallDamage.mp3"//落下音
#define SE_DECISION		SE_FILE"Decision.mp3"//決定音
#define SE_CURSOR_MOVE	SE_FILE"CursorMove.mp3"//カーソル移動音
#define SE_ENTER		SE_FILE"Enter.mp3"//エンター音


//サウンドの統括するクラス
class  CLoadSoundManager
{
private:
	//サウンドを追加していく
	std::vector<CSound*> mSound;
	//名前を指定するときに使う
	std::vector<std::string> mName;
 
	//ファイル読み込み
	void Load(char *name);
	CLoadSoundManager();

	static CLoadSoundManager *mpLoadSoundManager;

public:
	
	static CLoadSoundManager *GetInstance(); //GetInstance

	//引数の名前のサウンドファイルを返す .mp3
	static CSound *Sound(char*name);

	~ CLoadSoundManager();

};

#endif