#ifndef SCENEMODEL_HPP
#define SCENEMODEL_HPP

#include "../../../Graphic/CModelX.h"
#include "../../../Matrix/CMatrix44.h"
#include "../../../Camera/CCamera.h"
#include "Player\CXCharPlayer.h"


#include "../../../Graphic/CRectangle2.h"
#include "../../../Task/CTaskManager.h"

class CSceneModel{
private:
	float mMouseInitCount;//マウスが初期位置に戻るまでの時間
	float mLagTime;//lagによるバグ回避時間

public:

	static CXCharPlayer *mpPlayer; //アクセス用 キャラクター操作に使うため 静的に
	

	CMatrix44 mMatrix;

	CModelX mModel;//モデル読み込み用
	CModelX mModelE;//モデル読み込み用
	CModelX mModelPuck;//モデル読み込み用
	
	CModelX mModelGoal;//モデル読み込み用プレイヤー
	CModelX mModelEGoal;//モデル読み込み用エネミー

	CVector3 mPosition; //位置　

	/*すべてのモデルキャラ削除*/
	void ModelAllKill();

	/*キャラ追加処理
	引数ポジション決める
	*/
	void CSceneModel::CPlayerAdd(CVector3 PlayerPos, CModelX *model);
	void CSceneModel::CEnemyAdd (CVector3 EnemyPos,  CModelX *model);
	CTaskManager mModelTaskManager;
	CSceneModel();
	~CSceneModel();

	void Init();
	void Update();
	void UpdateEffect();
	void Render();
};
#endif