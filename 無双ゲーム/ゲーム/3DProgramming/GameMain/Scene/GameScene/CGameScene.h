#ifndef MAIN_HPP
#define MAIN_HPP

#include "CharaDate/CSceneModel.h"
#include "Map/CMap.h"
#include "../CScene.h"
#include "Pause/CPause.h"
#include "Tutorial\CTutorial.h"


class CGameScene : public CScene{
private:
	CRectangle2 mPauze;//ポーズ
	CRectangle2 mMainBack;//ゲームに戻る
	CRectangle2 mStageSelectBack;//ステージセレクトに戻る
public:
	static bool mEnterEventFlag;//trueでアップデート停止,



	/*状態*/
	enum E_STATE{
		E_INIT,
		E_MAIN,
		E_END
	};
	static E_STATE eState;


	CGameScene();
	~CGameScene();
	/*更新*/
	void Update();
	/*ミニマップ左上に表示するもの*/
	void MiniMapRender();
};

#endif
