#ifndef SCENEMODEL_HPP
#define SCENEMODEL_HPP

#include "../../../Graphic/CModelX.h"
#include "../../../Matrix/CMatrix44.h"
#include "../../../Camera/CCamera.h"
#include "Player\CPlayer.h"
#include "Enemy\Slime\CSlime.h"

#include "../../../Graphic/CRectangle2.h"
#include "../../../Task/CTaskManager.h"

class CSceneModel{
private:
	static CSceneModel *mpSceneModel;
	CModelX mModPlayer;//モデル読み込み用
	CModelX mModSlime;//モデル読み込み用
	CModelX mModKingSlime;//モデル読み込み用
	

	CSceneModel();
public:
	CModelX mModEffect3D;//モデル3D

	static CSceneModel *GetInstance(); //GetInstance
	static CPlayer *mpPlayer; //アクセス用 キャラクター操作に使うため 静的に
	static int mEnemyCount;//マップ上にいるエネミーの数



	/*プレイヤー追加関数*/
	void PlayerAdd();//プレイヤ−
	/*エネミー*/
	void SlimeInit();//スライム追加
	/*リスポーン指定してAdd*/
	CSlime *SlimeAdd(char *RespawnM44Name,CVector3 ajustPos);
	/*キングエネミー*/
	void KingSlimeInit();
	void KingSlimeAdd();//キングスライム追加

	~CSceneModel();

	void Init(); 
};
#endif