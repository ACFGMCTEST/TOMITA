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
#include "../../../../Graphic/CHpBar2D.h"
#include "../../../../Graphic/CBillBoard.h"
#include "../../Effect/CEffect3D.h"
#include " ../../../../../../Sound/CLoadSoundManager.h"
//プレイヤーの数
#define CHARA_ARRAY 3
/*キャラステータス*/
/*進むスピード*/
#define SPEED_RUN 0.4f //MAX走る
#define SPEED_RUN_ACC(v) if (SPEED_RUN > v){v += SPEED_RUN* 0.1f; }else{v = SPEED_RUN;}//加速度計算上限に来た場合

/*攻撃力*/
#define ATTACK_POWER 3.5f

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

/*ステータス*/
#include "Attack\CPlayerAttack.h"
#include "Idling\CPlayeridling.h"
#include "Jump\CPlayerJump.h"
#include "Run\CPlayerRun.h"
#include "RunAttack\CPlayerRunAttack.h"
#include "Damage\CPlayerDamage.h"
#include "Died\CPlayerDied.h"
#include "Avoid\CPlayerAvoid.h"
#include "Special\CPlayerSpecial.h"

/*あたり判定の設定値*/
#define COL_RADIUS 1.0f
#define COL_POS CVector3(0.0f, 1.0f, 0.0f), CVector3(0.0f, 0.0f, 0.0f)
#define COL_SPHE_POS CVector3(0.0f, 0.0f, 0.0f)
#define COL_BONE(string) &mpCombinedMatrix[model->FindFrame(string)->mIndex]

/*プレイヤー*/
#define MODEL_FILE_UNITY		MODEL_FILE"SDUnity\\SDUnityBoxing.x"
/*アニメーションのファイル場所*/
#define F_PL_IDLING				MODEL_FILE"SDUnity\\Anima\\Idling.x"
#define F_PL_RUN				MODEL_FILE"SDUnity\\Anima\\Run.x"
#define F_PL_RUN_ATTACK			MODEL_FILE"SDUnity\\Anima\\powerRunAttack.x"
#define F_PL_ATTACK				MODEL_FILE"SDUnity\\Anima\\Attack2.x"
#define F_PL_JUMP				MODEL_FILE"SDUnity\\Anima\\Jump.x"
#define F_PL_DAMAGE				MODEL_FILE"SDUnity\\Anima\\Damage.x"
#define F_PL_DIED			    MODEL_FILE"SDUnity\\Anima\\Died.x"
#define F_PL_AVOID				MODEL_FILE"SDUnity\\Anima\\Avoid.x"
#define F_PL_SPECIAL			MODEL_FILE"SDUnity\\Anima\\Special.x"
/*地面から落ちた時*/
#define FALL_SAFE 9.0f//許容範囲
#define GAUGE_VER 100//ゲージのサイズ

//吹き飛ぶときに使う 減速値 プレイヤーは１倍
#define OBJECT_WIGHT(wight) wight * 3.0f
#define BLOW_DECELERA(wig)wig * 0.05f 
/*
CPlayer
プレイヤークラス
*/
class CPlayer : public CModelXS {
protected:
	CStateMachine mStateMachine;//ステータス管理
	CVector3 mPrevPos;//移動前のポジション
	CVector3 mDamageRot;//ダメージを受けた回転値
	float mDamagePower;//吹っ飛ぶ値
	float mFallDamage;//落ちた時のダメージ量
	float mWeight;//重さ
	CVector3 mGroundPos;//現在いる地面の場所
	CBillBoard *mpMiniRect;//ミニマップ用
	/*ミニマップ設定用*/
	void SetMiniMap();
	/*高いところから落ちるとダメージ 引数:落ちた地点との差分*/
	void FallDamage(float height);

private:


	CHpBar2D *mpHp;//hp
	CHpBar2D *mpMp;//Mp


	CKey AttackInitKey;//Init時に使う
	int mRotCount;//回転地カウント　移動するときに使う
public:

	bool mFlagDamage;//ダメージ中のフラ
	bool mFlagAttack;//攻撃するフラグ
	

	CMatrix44 *mpMatrix;//当たり判定の原点

	CVector3 mForward;//進む向き
	CVector3 mPosition;	//位置
	CVector3 mRotation;	//回転


	float mGravitTime;//重力の時間
	float mVelocity; //速さ 使うもの
	float mPower;//攻撃力
	
	bool mFlagJump;//ジャンプフラグ

	CPlayer();
	~CPlayer();
	//初期化処理
	void Init(CModelX *model);
	//更新処理
	void Update();
	//描画処理
	void Render();

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



	/*吹き飛ぶ力 吹き飛ぶ力と現在の移動量で計算する*/
	void BlowSpeed();
	/*吹っ飛ぶ判定:*/
	void BlowOff();
	/*ダメージを受けた時の処理*/
	void Damage(float power, CVector3 rot);


	/*体力ゲージのHp取得*/
	float HP() { return mpHp->mValue;}
	//mpゲージmpを上昇させる 引数分アップ
	void MpUp(float up);
	/*現在の状態判断*/
	bool StateFlag(std::string s) { return mStateMachine.StateFlag(s); }
};

#endif
