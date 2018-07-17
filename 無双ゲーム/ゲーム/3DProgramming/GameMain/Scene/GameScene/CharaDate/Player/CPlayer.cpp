#include "CPlayer.h"
#include "windows.h"
#include "../../../../Key/CKey.h"
#include "../CSceneModel.h"
#include "../../../../../Define/Define.h"
#include "../../Map/CMap.h"
#include "../../../../Key/CMouse.h"
#include "../../../../Convenient/CConvenient.h"
#include "../../../GameScene/Map/CMap.h"
#include "../../../ItemScene/CItem.h"
#include <math.h>
#include "../../../../Collision/CCollisionManager.h"
#include "../../../../Collision/CCollision.h"

/*当たり判定*/
#include "../../../../Collision/ColType/CColCapsule.h"
#include "../../../../Collision/ColType/CColTriangle.h"
/*エネミー*/
#include "../Enemy/CEnemyBase.h"
/*画像読み込みクラス*/
#include  "../../../../Graphic/CLoadTexManager.h"
/*向き*/
#define FORWARD_JUMP  0.0f,1.0f,1.0f//ジャンプ

/*あたり判定の設定値(main)*/
#define COL_RADIUS 0.5f//半径
#define COL_POS CVector3(0,1.5f,0),CVector3(0,-1.0f,0)//ポジションカプセル
#define COL_MATRIX(string) &mpCombinedMatrix[model->FindFrame(string)->mIndex]//マトリックス
/*腕*/
#define COL_ATTACK_RADIUS 0.7f
#define COL_RIGHT_POS CVector3(0.0f,0.5f,0.0f)
#define COL_BODY_POS CVector3(0.0f,0.0f,0.0f)
#define COL_LEFT_POS  CVector3(0.0f,0.5f,0.0f)

/*動きの回転する速さ*/
#define TURN_SPEED 10

/*エフェクトの設定*/
#define EFF_SIZE 10.0f,10.0f//サイズ
#define EFF_POS(pos) CVector3(pos.x,pos.y + 2.0f, pos.z)//エフェクトのポジション
#define TEX_EFF_SIZE 0.0f,0.0f,2000,250//テクスチャのサイズ
#define EFF_SET_ANIMA 8,250//設定のアニメーション
#define EFF_SPEED  0.02f//再生スピード
/*HPバー*/
#define HP_SIZE RECT_SIZE(0.5f,T_MANA_HP_SIZE.right,T_MANA_HP_SIZE.bottom,)

//ミニマップ設定用
void CPlayer::SetMiniMap() {
	/*ミニマップ用の描画*/
	mpMiniRect = new CBillBoard();
	SVer ver(10.0f);//サイズ
	CVector3 pos = CVector3(0.0f, 10.0f, 0.0f);//調整用の距離
	mpMiniRect->SetVertex(&MapCamera, ver, &mPosition, &mRotation, pos);//ビルボードの設定
#define TEX_SIZE 386,386, 0.0f, 0.0f //ミニマップのサイズ
	//テクスチャの設定
	mpMiniRect->SetUv(CLoadTexManager::GetInstance()->
		mpMiniMap[CLoadTexManager::PLAYER], TEX_SIZE);
	/*タスクマネージャーに追加*/
	CTaskManager::GetInstance()->Add(mpMiniRect);
	mpMiniRect->mRenderFlag = false;
}

CPlayer::CPlayer() : mVelocity(0.0f), mRotCount(0), mpHitEffect(0),
mGravitTime(GRA_INIT_TIME_COUNT), mFlagJump(false), mAdjust(), mpHp(0),
mFlagDamage(false),mFlagAttack(false),mpMiniRect(0)
{
	eName = CTask::E_PLAYER;
	mForward = CVector3(FORWARD);
	mpParent = this;
	SetMiniMap();
}


CPlayer::~CPlayer() {
	if (mpHitEffect)mpHitEffect->CTask::mKillFlag = true;
	if (mpHp)mpHp->CTask::mKillFlag = true;
	if (mpMiniRect)mpMiniRect->CTask::mKillFlag = true;
	mStateMachine.AllDeregistration();//ステートマシン,アニメーション削除
}
/*
Init
モデルと衝突判定の設定を行う
*/
void CPlayer::Init(CModelX *model) {
	
	// 第一引数にステートの「登録名」
	// 第二引数でStateBaseを継承したクラスのshared_ptrオブジェクトを生成
	mStateMachine.Register(F_PL_ATTACK,	std::make_shared<CPlayerAttack>(), this);
	mStateMachine.Register(F_PL_IDLING,	std::make_shared<CPlayerIdling>	(), this);
	mStateMachine.Register(F_PL_RUN,		std::make_shared<CPlayerRun>(), this);
	mStateMachine.Register(F_PL_JUMP,		std::make_shared<CPlayerJump>(), this);
	mStateMachine.Register(F_PL_RUN_ATTACK,std::make_shared<CPlayerRunAttack>(), this);
	mStateMachine.Register(F_PL_DIED,      std::make_shared<CPlayerDied>(), this);
	mStateMachine.Register(F_PL_DAMAGE,	std::make_shared<CPlayerDamage>(), this);
	mStateMachine.Register(F_PL_AVOID,		std::make_shared<CPlayerAvoid>(), this);
	// 最初のステートを登録名で指定
	mStateMachine.SetStartState(F_PL_IDLING);
	mStr = F_PL_IDLING;//現在のステータスを入れる.
	//モデルの設定
	CModelXS::Init(model);
	//カプセル　キャラクタ全体
	new CColCapsule(this, COL_POS, COL_RADIUS, COL_MATRIX("metarig_hips"));
	mpMatrix = COL_MATRIX("metarig_hips");
	//球体　ボディ
	new CColSphere(this, COL_BODY_POS, COL_RADIUS, COL_MATRIX("metarig_hips"), CColBase::PL_BODY);
	//球体　腕.右
	new CColSphere(this, COL_RIGHT_POS, COL_ATTACK_RADIUS, COL_MATRIX("metarig_forearm_L"), CColBase::PL_ATTACK);
	//球体　腕.左
	new CColSphere(this, COL_LEFT_POS, COL_ATTACK_RADIUS, COL_MATRIX("metarig_forearm_R"), CColBase::PL_ATTACK);
	mPower = ATTACK_POWER;//攻撃力
	/*エフェクトの設定*/
	mpHitEffect = new CEffect2D();
	mpHitEffect->Init(CLoadTexManager::GetInstance()->mpHit,
		EFF_SIZE, STexVer(TEX_EFF_SIZE));//画像や頂点数代入
	mpHitEffect->SetAnima(EFF_SET_ANIMA);//アニメーションの準備
	CTaskManager::GetInstance()->Add(mpHitEffect);
	/*ｈｐ設定*/
	mpHp = new CHpBar2D();
	mpHp->Init(100, 100, HP_SIZE);
	mpHp->mPos = CVector2(-DISP_2D_X + mpHp->mWidth/2, DISP_2D_Y - mpHp->mHeight/2);
	mpHp->SetTex(CLoadTexManager::GetInstance()->mpHp2DFrame,
				CLoadTexManager::GetInstance()->mpHp2DGauge,
				T_MANA_HP_SIZE);
	CTaskManager::GetInstance()->Add(mpHp);
	


	PosUpdate();
}

/*ポジションのアップデート関数*/
void CPlayer::PosUpdate() {
	CMatrix44 rot_y, pos, matrix;
	//回転行列の作成
	rot_y.rotationY(mRotation.y);

	//移動行列を計算する
	pos.translate(mPosition);
	//回転移動行列を求める
	matrix = pos * rot_y;

	//頂点データの更新
	CModelXS::Update(matrix);

}

/*回転関数*/
void CPlayer::PlusRot(float rot) {

	mRotation.y += rot;//タス処理
	if (mRotation.y < 0) {//回転値がマイナスなら
		mRotation.y = ANGLE_360 + mRotation.y;//３６０以内にとどめる
	}
	if (mRotation.y > ANGLE_360) {//３６０以上の場合
		mRotation.y = mRotation.y + ANGLE_360;
	}
}
/*キャラクター回転差が小さい方向に回転する*/
int CPlayer::MoveRotation(int angle) {

	/*右回り*/
	int turnRight = angle - mRotation.y;
	/*過剰余剰*/
	LIMIT_ANGLE(turnRight);
	/*左回り*/
	int turnLeft = ANGLE_360 - turnRight;

	//printf("右回転:%d,左回転%d\n", turnRight, turnLeft);
	/*同じの場合 ||
	右に越えてしまう場合 ||
	左に越えてしまう場合 ||
	*/
	if (mRotation.y == angle ||
		mRotation.y <= angle && angle <= mRotation.y + TURN_SPEED ||
		mRotation.y - TURN_SPEED <= angle && angle <= mRotation.y) {
		return angle;
	}
	/*右方向確認*/
	if (turnRight < turnLeft) {
		return mRotation.y + TURN_SPEED;
	}
	/*方向確認*/
	else {
		return mRotation.y - TURN_SPEED;
	}


}


/*動くときの関数*/
void CPlayer::PlayerMoveRot() {

	LIMIT_ANGLE(mRotation.y);

	if (CKey::push('A')) {//左に移動
		mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_90) % 360);
	}
	if (CKey::push('D')) {//右に移動
		mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_270) % 360);
	}

	if (CKey::push('W')) {//前に移動

		mRotation.y = MoveRotation(((int)MainCamera.Rot().y) % 360);
		if (CKey::push('A')) {//左に移動
			mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_45) % 360);
		}
		if (CKey::push('D')) {//右に移動
			mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_315) % 360);
		}
	}

	if (CKey::push('S')) {
		mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_180) % 360);
		if (CKey::push('A')) {//左に移動
			mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_125) % 360);
		}
		if (CKey::push('D')) {//右に移動
			mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_225) % 360);
		}
	}

	Move();//移動させる

}
/*動かすときの処理
forward = 方向設定
velocity = 力
*/
void CPlayer::Move() {

	CMatrix44 rot_y, pos, matrix;
	CVector3 moveForward = mForward;//参照でいじれないので
	//回転行列の作成
	rot_y.rotationY(mRotation.y);
	//進行方向を計算
	moveForward = mForward * rot_y;
	//移動させる
	mPosition += moveForward * mVelocity;
}


/*重力*/
void CPlayer::Gravity() {
	/*地面についていないなら*/
	mPosition.y -= GRAVITY(mGravitTime);
	mGravitTime += GRA_TIME_UP;//時間が経つ
}
/*グラウンドの設定*/
void CPlayer::ColGround() {
	mGravitTime = GRA_INIT_TIME_COUNT;
	mFlagJump = false;//ジャンプ終了
}

/*更新処理*/
void CPlayer::Update() {
	/*デバック用*/
	if (CKey::push('I')) {
		mPosition.y += 2.0f;
		mGravitTime = 0;//時間が経つ
	}
	if (CKey::push('O')) {
		mGravitTime = 0;//時間が経つ
	}

	mAdjust = CVector3();
	Gravity();/*重力*/
	PosUpdate();//ポジションを更新
	/*ステータスマシン更新*/
	mStateMachine.Update();
}



/*Render*/
void CPlayer::Render() {
	CModelXS::Render();
}



/*あたり判定の時に呼び出し*/
void CPlayer::ColMove(int count, CVector3 Forward) {
	if (count <= -1) {//カウントがマイナスなら
		mVelocity = -KNOCK_BACK; //後ろ向きにする
		count *= -1;//プラスにする
	}
	else
	{
		mVelocity = -KNOCK_BACK;
	}
	mForward = Forward;
	mCountKnockBack = count;
}



void CPlayer::SetAdjust(CVector3 *s, const CVector3 &t) {
	//x
	if (s->x > 0) {
		if (t.x > 0) {
			if (s->x < t.x)
				s->x = t.x;
		}
		else {
			if (s->x < -t.x)
				s->x = t.x;
		}
	}
	else {
		if (t.x > 0) {
			if (-s->x < t.x)
				s->x = t.x;
		}
		else {
			if (-s->x < -t.x)
				s->x = t.x;
		}
	}
	//y
	if (s->y > 0) {
		if (t.y > 0) {
			if (s->y < t.y)
				s->y = t.y;
		}
		else {
			if (s->y < -t.y)
				s->y = t.y;
		}
	}
	else {
		if (t.y > 0) {
			if (-s->y < t.y)
				s->y = t.y;
		}
		else {
			if (-s->y < -t.y)
				s->y = t.y;
		}
	}
	//z
	if (s->z > 0) {
		if (t.z > 0) {
			if (s->z < t.z)
				s->z = t.z;
		}
		else {
			if (s->z < -t.z)
				s->z = t.z;
		}
	}
	else {
		if (t.z > 0) {
			if (-s->z < t.z)
				s->z = t.z;
		}
		else {
			if (-s->z < -t.z)
				s->z = t.z;
		}
	}
}

/*玉バージョン*/
void CPlayer::Collision(CColSphere *youSphere, CColSphere *sphere) {
	CVector3 savePos = sphere->mPos;//計算用
	float lengthX = mPosition.x - savePos.x;  //球とポジションの距離
	float lengthY = mPosition.y - savePos.y;  //球とポジションの距離
	float lengthZ = mPosition.z - savePos.z;  //球とポジションの距離
	//BoxのX軸方向を求める
	CVector3 vx = *youSphere->mpCombinedMatrix * VEC_RIGHT;
	//BoxのY軸方向を求める
	CVector3 vy = *youSphere->mpCombinedMatrix * VEC_TOP;
	//BoxのZ軸方向を求める
	CVector3 vz = *youSphere->mpCombinedMatrix * VEC_FRONT;
	//四角形から球へのベクトルを求める
	CVector3 vectorBS = savePos - youSphere->mPos;
	//四角形から球へ、四角形のX軸に対する長さとの差を求める
	float dx = sphere->mRadius + youSphere->mRadius - fabs(vx.Dot(vectorBS));
	//四角形から球へ、四角形のY軸に対する長さとの差を求める
	float dy = sphere->mRadius + youSphere->mRadius - fabs(vy.Dot(vectorBS));
	//四角形から球へ、四角形のZ軸に対する長さとの差を求める
	float dz = sphere->mRadius + youSphere->mRadius - fabs(vz.Dot(vectorBS));

	//衝突しているか判定する
	if (dx > 0.0f && dy > 0.0f && dz > 0.0f) {
		if (dx > dy) {
			if (dy > dz) {
				//Z軸で戻す
				if (vz.Dot(vectorBS) > 0.0f) {
					mPosition = savePos + vz * dz;
				}
				else {
					mPosition = savePos - vz * dz;
				}
			}
			else {
				///*球がボディの時判定 && ジャンプしていないとき*/
				////Y軸で戻す
				//if (vy.Dot(vectorBS) > 0.0f) {
				//	mPosition = savePos + vy * dy;
				//}
				//else {
				//	mPosition = savePos - vy * dy;
				//}
			}
		}
		else {
			if (dx > dz) {

				//Z軸で戻す
				if (vz.Dot(vectorBS) > 0.0f) {
					mPosition = savePos + vz * dz;
				}
				else {
					mPosition = savePos - vz * dz;
				}
			}
			else {

				//X軸で戻す
				if (vx.Dot(vectorBS) > 0.0f) {
					mPosition = savePos + vx * dx;
				}
				else {
					mPosition = savePos - vx * dx;
				}
			}
		}
	}
	mPosition.x += lengthX;
	mPosition.y += lengthY;
	mPosition.z += lengthZ;

	/*マトリックスだけ更新*/
	CMatrix44 rot_y, pos, matrix;
	//回転行列の作成
	rot_y.rotationY(mRotation.y);

	//移動行列を計算する
	pos.translate(mPosition);
	//回転移動行列を求める
	matrix = pos * rot_y;
	//頂点データの更新
	CModelXS::MatrixUpdate(matrix);

}


/*カプセル内当たり判定*/
void CPlayer::CapsuleCol(CColCapsule *cc, CColBase* y) {
	CColTriangle ct;//三角形の当たり判定
	CColCapsule  caps;//カプセルの当たり判定
	/*相手のタイプ何か判断*/
	switch (y->mType) {
		/*相手が三角の場合*/
	case CColBase::COL_TRIANGLE:
		ct = (*(CColTriangle*)y).GetUpdate();
		/*当たり判定計算*/
		if (CCollision::IntersectTriangleCapsule3(ct.mV[0], ct.mV[1], ct.mV[2],
			cc->mV[0], cc->mV[1], cc->mRadius, &cc->mAdjust)) {
			ColGround();//地面にあった時の処理
			SetAdjust(&mAdjust, cc->mAdjust);
			mPosition = mPosition + mAdjust;
			CMatrix44 rot_y, pos, matrix;
			//回転行列の作成
			rot_y.rotationY(mRotation.y);
			//移動行列を計算する
			pos.translate(mPosition);
			//回転移動行列を求める
			matrix = pos * rot_y;
			CModelXS::Update(matrix);
		}
		break;
		/*相手がカプセルの場合*/
	case CColBase::COL_CAPSULE:

		break;
	};
}

/*球体内の当たり判定*/
void CPlayer::SphereCol(CColSphere *sphere, CColBase *y) {

	CColSphere  sph;//球の当たり判定
	CEnemyBase *ene;
	/*相手のタイプ何か判断*/
	switch (y->mType) {
		/*相手が球の場合*/
	case CColBase::COL_SPHEPE:
		/*HPがある場合*/
		if (HP() > 0) {
			sph = (*(CColSphere*)y).GetUpdate();
			/*当たり判定計算*/
			if (CCollision::CollisionShpere(sph, *sphere) && sph.eState == CColBase::ENE_BODY) {
				ene = (CEnemyBase*)sph.mpParent;
				/*
				当たり判定が攻撃の場合
				攻撃している場合
				*/
				if (sphere->eState == CColBase::PL_ATTACK && mStr == F_PL_ATTACK) {
					//エネミーのダメージとHPを入れる
					float eneHp = ene->Damage(mPower, mRotation);	
					//エフェクト発動
					mpHitEffect->StartAnima(EFF_SPEED, EFF_POS(mPosition));
				}
				/*回避中は当たらない && エネミーがダメージを追っているとき*/
				if (mStr != F_PL_AVOID) Collision(&sph, sphere);
			}
		}


	};
}

//m 自分　y 相手
bool CPlayer::Collision(CColBase* m, CColBase* y) {

	CColCapsule cc;
	CColSphere sph;
	/*自分のタイプが何か判断*/
	switch (m->mType) {

	case CColBase::COL_CAPSULE://自分の当たり判定がカプセルの場合
		cc = *(CColCapsule*)m;//カプセルにする
		CapsuleCol(&cc, y);//カプセルの当たり判定
		break;

	case CColBase::COL_SPHEPE:
		sph = *(CColSphere*)m;//球体
		SphereCol(&sph, y);//球体の当たり判定

	};

	return false;
}

/*現在のstrをれる*/
void CPlayer::State(std::string s) {
	mStr = s;
}


#define AJUST_BLOW_OFF_POWER(pow) pow*0.1f //吹き飛ぶ威力
/*ダメージを受けた時の処理*/
void CPlayer::Damage(float power, CVector3 rot) {
	mpHp->mValue -= power;
	/*吹っ飛ぶ処理の準備*/
	mDamagePower = AJUST_BLOW_OFF_POWER(power);
	mDamageRot = rot;
	mFlagDamage = true;

	mStateMachine.ForceChange(F_PL_DAMAGE);

}

/*吹っ飛ぶ判定*/
/*吹き飛ぶ力 吹き飛ぶ力と現在の移動量で計算する*/
void CPlayer::BlowSpeed() {
#define DECELE_SPEED 0.2f//減速するスピード
	mDamagePower = mDamagePower - mDamagePower * DECELE_SPEED;
	mVelocity = mDamagePower;
	if (mVelocity < 0) mVelocity = 0;//0以下にはならない
}

void CPlayer::BlowOff() {
	CVector3 save = mRotation;//元に戻すため
	mRotation = mDamageRot;//回転値の方向に飛ぶ
	BlowSpeed();
	CPlayer::Move();
	mRotation = save;
}