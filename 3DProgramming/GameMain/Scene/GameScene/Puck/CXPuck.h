#ifndef CXPuck_H
#define CXPuck_H

#include "../../../Vector/CVector3.h"
#include "../../../Collision/CCollider.h"
#include "../Map/Slope/CSlope.h"

//#include "CBillBoard.h"
#include "../../../Graphic/CModelX.h"

/*キャラステータス*/

/*吹き飛び*/
#define KNOCK_BACK  0.2f/*吹き飛びの度合い*/

/*進む方角*/
#define FORWARD 0.0f,0.0f,1.0f
#define FORWARD_SLOPE 0.0f,0.5f,0.5f//坂に上るとき


/*ゴールポジション*/
#define GOAL_POS_Z 20.0f//真ん中だとリスキルが発生するので少しずらす
#define GOAL_POS_PUCK_PLAYER CVector3(0.0f,30.0f,-GOAL_POS_Z)
#define GOAL_POS_PUCK_ENEMY  CVector3(0.0f,30.0f,GOAL_POS_Z)
/*
CXPuck
パッククラス
*/
class CXPuck : public CModelXS {
private:
	float mGravitTime;//重力の時間
	bool mFlagJump;//ジャンプ中か判断用
	CVector3 mRefrectVec;//跳ね返る方向
public:
	bool mFlagSlope;//坂
	bool mGoalStandUpFlag;//ゴールした時のフラグ
	float mSaveSpeed; //速さ　保存用
	float mVelocity; //速さ 使うもの
	CVector3 mForward;//進む向き
	CVector4 fortank; //自分が向いている向き
	CVector3 mPosition;	//位置
	CVector3 mRotation;	//回転

	CCollider *mpCBSphere;//当たり判定(球体)
	CCollider *mpCBRefBox;//当たり判定(box)跳ね返り判断用

	bool mRefFlag;//反射させるかのflag

	CXPuck();

	/*当たり判定初期化*/
	void ColInit();
	//初期化処理
	void Init(CModelX *model);
	//更新処理
	void Update();
	//描画処理
	void Render();

	void PosUpdate();//ポジションの変更関数　
	/*移動処理*/
	void Move();


	/*跳ね返り obb相手*/
	void ColReflect(const COBB &col);

	/*跳ね返り方向指定
	rot 回転地
	*/
	void ColReflect(CVector3 &rot,float &power);
	/*当たったとき動きを止める*/
	void ColStop(const COBB &obb1, const COBB &obb2);//相手のあたり判定
	/*減速処理*/
	void ColSlow();
	/*加速処理*/
	void ColFast();
	
	/*ジャンプ処理*/
	void Jump();
	/*ジャンプ処理 Jumpのフラグを立てる*/
	void EnabledJump();
	/*坂にあたった時のフラグ立て処理*/
	void  EnabledSlope();

	/*ゴールエネミー*/
	void GoalEnemy();
	/*ゴールプレイヤー*/
	void GoalPlayer();
	/*ポジションを上げる処理*/
	void StandUp();

	/*地面に当たった時の判定*/
	void ColGround();

	/*重力*/
	void Gravity();
	/*操作する場合*/
	void MyMove();
	/*簡易移動フラグ関数*/
	bool FlagMove();

	/*当たり判定呼び出し
	元の場所に戻すための関数
	*/
	void Collision(const COBB &box, const CColSphere &sphere);


	/*回転値リセット*/
	void RotReset();
};

#endif
