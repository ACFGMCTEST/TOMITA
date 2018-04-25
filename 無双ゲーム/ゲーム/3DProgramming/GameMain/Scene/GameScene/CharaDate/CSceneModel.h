#ifndef SCENEMODEL_HPP
#define SCENEMODEL_HPP

#include "../../../Graphic/CModelX.h"
#include "../../../Matrix/CMatrix44.h"
#include "../../../Camera/CCamera.h"
#include "CXCharPlayer.h"

#include "../../../Graphic/CRectangle2.h"
#include "../../../Task/CTaskManager.h"

/*モデルを集めたクラス*/
class CSceneModel{
private:
	float mMouseInitCount;//マウスが初期位置に戻るまでの時間
	float mLagTime;//lagによるバグ回避時間

	static CXCharPlayer *mpPlayer; //アクセス用 キャラクター操作に使うため 静的に

	CModelX mModel;//モデル読み込み用

	/*キャラ追加処理
	引数ポジション決める
	*/
	void CSceneModel::CPlayerAdd(CVector3 PlayerPos, CModelX *model);
	void CSceneModel::CEnemyAdd(CVector3 EnemyPos, CModelX *model);
	CTaskManager mModelTaskManager;
public:

	CSceneModel();
	~CSceneModel();

	/*プレイヤーの情報関数*/
	static CXCharPlayer Player();
	/*Modelのメモリ開放処理*/
	void ModelAllKill();

	void Update();
	void UpdateEffect();
	void Render();
};
#endif