#ifndef SCENEMODEL_HPP
#define SCENEMODEL_HPP

#include "../../../Graphic/CModelX.h"
#include "../../../Matrix/CMatrix44.h"
#include "../../../Camera/CCamera.h"
#include "Player\CPlayer.h"


#include "../../../Graphic/CRectangle2.h"
#include "../../../Task/CTaskManager.h"

class CSceneModel{
private:
	CModelX mModPlayer;//モデル読み込み用
	CModelX mModSlime;//モデル読み込み用
	CModelX mModKingSlime;//モデル読み込み用

	float mMouseInitCount;//マウスが初期位置に戻るまでの時間
	float mLagTime;//lagによるバグ回避時間
public:

	static CPlayer *mpPlayer; //アクセス用 キャラクター操作に使うため 静的に
	


	/*すべてのモデルキャラ削除*/
	void ModelAllKill();

	/*プレイヤー追加関数*/
	void PlayerAdd();//プレイヤ－
	/*エネミー*/
	void SlimeAdd ();//スライム追加
	/*キングエネミー*/
	void KingSlimeAdd();//キングスライム追加

	CSceneModel();
	~CSceneModel();

	void Init();
	void Update();
	void Render();
};
#endif