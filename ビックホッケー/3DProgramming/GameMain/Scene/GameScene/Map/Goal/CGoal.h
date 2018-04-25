#ifndef CXGoal_H
#define CXGoal_H

#include "../../../../Vector/CVector3.h"
#include "../../../../Collision/CCollider.h"

//#include "CBillBoard.h"
#include "../../../../Graphic/CModelX.h"
#include "../../Effect/CExplosion.h"
#include"../../../../Graphic/CBox.h"
/*キャラステータス*/

/*吹き飛び*/
#define KNOCK_BACK  0.2f/*吹き飛びの度合い*/

/*進む方角*/
#define FORWARD 0.0f,0.0f,1.0f


/*ゴールポジション*/
#define GOAL_POS_Goal_PLAYER CVector3(CMap::PlayerFirstPos().x,CMap::PlayerFirstPos().y - 2.0f,CMap::PlayerFirstPos().z + 10.0f)
#define GOAL_POS_Goal_ENEMY  CVector3(CMap::EnemyFirstPos().x, CMap::EnemyFirstPos().y - 2.0f, CMap::EnemyFirstPos().z - 10.0f)
/*
CXGoal
ゴールクラス
*/
class CGoal :public CBox{
public:
	CVector3 mForward;//進む向き
	CVector4 fortank; //自分が向いている向き
	CVector3 mPosition;	//位置
	CVector3 mRotation;	//回転

	CCollider *mCBBox;//当たり判定

	CExplosion mEffect;//ゴールした時のエフェクト

	CGoal(CVector3 pos,CTask::E_TAG tag);

	/*当たり判定初期化*/
	void ColInit();
	//初期化処理
	void Init(CVector3 pos);
	//更新処理
	void Update();
	//描画処理
	void Render();
	//billboardの描画処理
	void BillboardRender();
	//ポジションの変更関数　
	void PosUpdate();
	/*ゴールした時の演出*/
	void GoalPerformance();

};

#endif
