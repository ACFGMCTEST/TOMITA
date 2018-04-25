#ifndef SCENEMODEL_HPP
#define SCENEMODEL_HPP

#include "../../../Graphic/CModelX.h"
#include "../../../Matrix/CMatrix44.h"
#include "../../../Camera/CCamera.h"
#include "../Map/Goal/CGoal.h"
#include "CXCharPlayer.h"

#include "../../../Graphic/CRectangle2.h"
#include "../../../Task/CTaskManager.h"
#include "../Puck/CXPuck.h"

class CSceneModel{
private:
	float mMouseInitCount;//マウスが初期位置に戻るまでの時間
	float mLagTime;//lagによるバグ回避時間
public:

	//敵キャラのインスタンス
	static CXCharPlayer *mCharcter; //アクセス用 キャラクター操作に使うため 静的に


	CMatrix44 mMatrix;

	CModelX mModel;//モデル読み込み用
	CModelX mModelE;//モデル読み込み用
	CModelX mModelPuck;//モデル読み込み用
	
	CModelX mModelGoal;//モデル読み込み用プレイヤー
	CModelX mModelEGoal;//モデル読み込み用エネミー

	CVector3 mPosition; //位置　

	
	/*パックアクセス用　エネミーで使う*/
	static CXPuck *mpPuck;


	//エネミーモデル

	/*キャラ追加処理
	引数ポジション決める
	*/
	void CSceneModel::CPlayerAdd(CVector3 PlayerPos, CModelX *model);
	void CSceneModel::CEnemyAdd(CVector3 EnemyPos, CModelX *model);
	void CSceneModel::CPuckAdd(CVector3 PuckPos, CModelX *model);
	void CSceneModel::CGoalPlayerAdd(CVector3 GoalPos, CModelX *model);
	void CSceneModel::CGoalEnemyAdd(CVector3 GoalPos, CModelX *model);
//	CTaskManager mModelTaskManager;
	CSceneModel();
	~CSceneModel();

	void Init();
	void Update();
	void UpdateEffect();
	void Render();
};
#endif