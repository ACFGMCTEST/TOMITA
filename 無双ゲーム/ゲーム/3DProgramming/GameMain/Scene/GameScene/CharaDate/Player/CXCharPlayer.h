#ifndef CXCHARPLAYER_H
#define CXCHARPLAYER_H

#include "../../../../Graphic/CModelX.h"
#include "../../../../Vector/CVector3.h"
#include "../../Effect/CEffect2D.h"
#include "../../../../Key/CKey.h"
#include"../../../../../StateMachine/CStateMachine.h"
#include "../../../../../StateMachine/CStateBase.h"
#include "../../../../Collision/ColType/CColBase.h"
#include "../../../../Collision/ColType/CColCapsule.h"
#include "../../../../Collision/ColType/CColSphere.h"
//プレイヤーの数
#define CHARA_ARRAY 3
/*キャラステータス*/
/*進むスピード*/
#define SPEED_RUN 0.2f //MAX走る
#define SPEED_RUN_ACC(v) if (SPEED_RUN > v){v += SPEED_RUN* 0.1f; }else{v = SPEED_RUN;}//加速度計算上限に来た場合

/*攻撃力*/
#define ATTACK_POWER 2.0f

/*吹き飛び*/
#define KNOCK_BACK  0.2f/*吹き飛びの度合い*/
/*カウント具合*/
#define KNOCK_BACK_SMALL (int)1 * 5 
#define KNOCK_BACK_MIDDLE (int)4 * 5
#define KNOCK_BACK_BIG (int)6 * 5
/*POINTの換算具合*/
#define POINT_MAX 50 //５０まで
#define POINT_UP 0.1f //決め手型以外
#define POINT_UP_BIG 0.1f * 1.5f  //決め手型用
/*進む方角*/
#define FORWARD 0.0f,0.0f,1.0f
/*
CXCharPlayer
プレイヤークラス
*/
//class CXCharPlayer : public CXCharacter {
class CXCharPlayer : public CModelXS {
protected:
	/*ステータス管理マネージャー*/
	std::unique_ptr<CStateMachine> mStateMachine;//ステータス管理
	std::string mStr;//現在の状態
private:

	int mRotCount;//回転地カウント　移動するときに使う
	CKey AttackInitKey;//Init時に使う
	
public:
	CMatrix44 *mpMatrix;//当たり判定の原点
	float mGravitTime;//重力の時間
	float mVelocity; //速さ 使うもの
	float mPower;//攻撃力
	bool mFlagKnockback;//ノックバック中か判断
	bool mFlagJump;//ジャンプフラグ

	CVector3 mForward;//進む向き
	CVector4 fortank; //自分が向いている向き

	CVector3 mPosition;	//位置
	CVector3 mPrevPos; //前の位置保存場所 

	CVector3 mRotation;	//回転
	CXCharPlayer();
	//初期化処理
	void Init(CModelX *model);
	//更新処理
	void Update();
	//描画処理
	void Render();
	//billboardの描画処理
	void BillboardRender();

	/*回転関数
	rot = 回転値*/
	void PlusRot(float rot);
	void PosUpdate();//ポジションの変更関数　
	int mCountKnockBack; //ノックバックする回数

	/*当たったときに呼び出す
	count:移動回数
	Forward:進む方角
	*/
	void ColMove(int count, CVector3 Foward);

	/*回転するまで移動しない*/
	//bool FlagRotMove(int angle);

	/*POSだけのマトリックスアップデート*/
	void MatrixUpdate();

	/*移動させる*/
	void Move();

	/*当たり判定調整用*/
	void SetAdjust(CVector3 *s, const CVector3 &t);
	/*当たり判定*/
	bool Collision(CColBase* me, CColBase* you);
	/*カプセル内当たり判定*/
	void CapsuleCol(CColCapsule *caps, CColBase* y);
	/*玉バージョン*/
	void Collision(CColSphere *youSphere,CColSphere *sphere);
	/*球体内の当たり判定*/
	void SphereCol(CColSphere *sphere, CColBase *y);

	/*カプセルの移動*/
	//void ColCapsAdjus(CColCapsule *youCaps, CColCapsule *caps);

	/*重力
	自分の足がついているときを重力を止める場所にする
	*/
	void Gravity();
	/*グラウンドの設定*/
	void ColGround();

	/*キャラクター動く時の回転
	float = 向きたい方向
	*/
	int MoveRotation(int  angle);

	CVector3 mAdjust;


	/*操作する回転値計算*/
	void PlayerMoveRot();

	/*現在のstrをれる*/
	void State(std::string s);
};

#endif
