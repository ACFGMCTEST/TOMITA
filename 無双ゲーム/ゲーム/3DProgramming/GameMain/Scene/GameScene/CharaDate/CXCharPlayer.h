#ifndef CXCHARPLAYER_H
#define CXCHARPLAYER_H

#include "../../../Graphic/CModelX.h"
#include "../../../Vector/CVector3.h"
#include "../../../Collision/CCollider.h"
#include "../Effect/CEffect2D.h"
#include "../../../Key/CKey.h"

//プレイヤーの数
#define CHARA_ARRAY 3
/*キャラステータス*/
/*進むスピード*/
#define SPEED_RUN 0.35f //走る
#define SPEED_RUN_SKILL 0.6f //スキル時の走行スピード

#define SPEED_ATTACK_RUN SPEED_RUN*0.8f //ため走る
#define SPEED_JUMP_DOWN 0.05f //ジャンプ中はveloctyをマイナスする
#define SPEED_ATTACK_RUN_SKILL 0.4 //スキル発動時の移動速度

#define SKILL_TIME_LIMIT 1200.0f

/*吹き飛ばす力*/
#define ATTACK_POWER 0.02f
#define ATTACK_POWER_MAX 0.5f		//デフォルト

#define ATTACK_W0_POWER_MAX	0.65f	//武器事の攻撃力
#define ATTACK_WS0_POWER_MAX 1.3f	//武器事の攻撃力
#define ATTACK_W1_POWER_MAX 0.6f
#define ATTACK_W2_POWER_MAX 1.11f
#define ATTACK_W3_POWER_MAX 0.55f

#define POWER_UP 0.001f//攻撃のあがり幅
#define W_0_POWER_UP 0.0013f
#define W_1_POWER_UP 0.0012f
#define WS_1_POWER_UP 0.01f
#define W_2_POWER_UP 0.00222f
#define W_3_POWER_UP 0.0011f

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

/*プレイヤークラス*/
class CXCharPlayer : public CModelXS {
private:
	int mRotCount;//回転地カウント　移動するときに使う
	CKey AttackInitKey;//Init時に使う
public:
	float mGravitTime;//重力の時間
	float mVelocity; //速さ 使うもの
	float mPower;//攻撃力
	bool mFlagKnockback;//ノックバック中か判断
	bool mFlagJump;//ジャンプフラグ
	bool mFlagSlpoe;//今坂に当たっているか判断


	const float mGageDecrease = 0.17f;//スキルゲージの１フレーム毎の減少速度
	const float mGageLimit=200.0f;	//スキルゲージのリミット都合がいいので時間制御も兼ねる

	float mSkillTime;//スキルの発動時間

	CVector3 mForward;//進む向き
	CVector4 fortank; //自分が向いている向き

	CVector3 mPosition;	//位置
	CVector3 mPrevPos; //前の位置保存場所 

	CVector3 mRotation;	//回転
	/*向き*/
	enum E_DIRECTION{
	E_RIGHT,
	E_LEFT,
	E_TOP,
	E_BOTTOM
	};
	E_DIRECTION eDirection;//現在の方向
	bool DirectionAnima();//向きの制御 アニメーションが終わるまで移動しない
	//25
	//衝突判定（体）
	//CCollider *mCBBody;
	CCollider *mpCBBody;//球判定
	CCollider *mpCBLeg;//足
	//衝突判定（武器）
	CCollider *mpCBWeapon;
	/*ハンマーのEFFECT*/
	CEffect2D mHammerEffect;

	CXCharPlayer();
	//初期化処理
	void Init(CModelX *model);
	/*あたり判定初期化*/
	void ColInit();
	//更新処理
	void Update();
	//描画処理
	void Render();
	//billboardの描画処理
	void BillboardRender();
	void PosUpdate();//ポジションの変更関数　
	int mCountKnockBack; //ノックバックする回数


	/*操作する場合*/
	void MyMove();
	/*簡易移動フラグ関数*/
	bool FlagMove();
	/*簡易アニメーション切り替え*/
	void AnimaState(ESTATE state);

	/*POSだけのマトリックスアップデート*/
	void MatrixUpdate();


	/*アタックのステータス 攻撃中判断*/
	bool FlagAttackState();
	/*速さ制御関数*/
	void MoveSpeed();
	/*動かすときの処理
	forward = 方向設定
	velocity = 力
	*/
	void Move(const CVector3 &forward,float velocity);

	/*おもな当たり判定呼び出し*/
	void Collision(const COBB &box, const CColSphere &sphere);
	/*玉判定*/
	void Collision(const CColSphere &youSphere, const CColSphere &sphere);

	///*ボックスにあたったとき*/
	//void CollisionBox(const COBB &box, const CColSphere &sphere);
	///*坂にあたったとき*/
	//void CollisionSlope(const COBB &box, const CColSphere &sphere);



	/*ハンマーの溜める処理*/
	void HammerUp();
	/*Hammerの初期化処理*/
	void HammerInit();
	/*重力
	自分の足がついているときを重力を止める場所にする
	*/
	void Gravity();

	/*ジャンプ関数
	当たり判定の仕様
	自分の当たり判定に入っている
	地面に一番近い

	もしかしたら当たり判定がうまいこと働いてきれいに止まってくるかも
	ガクブル現象がなければしなくていいんだけど
	*/
	void Jump();
	/*グラウンドの設定*/
	void ColGround();
	/*キャラクター動く時の回転
	float = 向きたい方向
	*/
	int MoveRotation(int  angle);

};

#endif
