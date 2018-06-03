#include "CEnemyBase.h"
#include "../CSceneModel.h"
/*当たり判定*/
#include "../../../../Collision/ColType/CColCapsule.h"
#include "../../../../Collision/ColType/CColTriangle.h"
#include "../../../../Collision/CCollision.h"

#include <time.h>
/*回転感覚時間*/
#define ROT_PYCK_TIME 1.0f
/*当たり判定*/
/*準備*/
#define OBB_ATTACK_INIT_BOX_SIZE CVector3(20.0f, 4.0f, 20.0f)
#define OBB_ATTACK_INIT_BOX_POS CVector3(-0.01f, -0.06f, -0.1f)
/*攻撃*/
#define OBB_ATTACK_BOX_SIZE CVector3(3.0f, 3.0f, 3.0f)
#define OBB_ATTACK_BOX_POS CVector3(-0.01f, -0.01f, -0.1f)
/*ゴールの方向に向ける*/
#define GOAL_POS_X (rand() % (int)MAPCHIP_SIZE*CMap::GoalCount()) - MAPCHIP_SIZE*CMap::GoalCount()*0.5f
/*hpバー*/
#define HP_MAX 10.0f
#define HP_SIZE -5.0f,5.0f,4.0f,4.5f
#define TEX_SIZE_HP 0,0,490,46
/*吹き飛ぶ力*/
#define DMAGE_SPEED(power) power * 1.0f//吹っ飛ぶ力
/*コンストラクタ*/
CEnemyBase::CEnemyBase() : mFlagDamage(false) {
	/*HP設定*/
	mpHp = new CHpBar();
	mpHp->Init(HP_MAX, HP_MAX, HP_SIZE, &mPosition);//サイズとポジション
	mTexGauge.Load(TGA_FILE"UI\\Gauge.tga");//HPテクスチャ読み込む
	mTexmFrame.Load(TGA_FILE"UI\\Frame.tga");//HPテクスチャ読み込む
	mpHp->SetTex(&mTexmFrame, &mTexGauge, TEX_SIZE_HP);//テクスチャ
	CTaskManager::GetInstance()->Add(mpHp);

	CPlayer::CPlayer();
	mGravitTime = GRA_INIT_TIME_COUNT;
	mVelocity = 0.0f;
	mForward = CVector3(FORWARD);
	/*親設定*/
	mpParent = this;
}

/*初期化処理*/
void CEnemyBase::Init(CModelX *model) {

}


/*動かす関数*/
void CEnemyBase::AIMove() {
	mRotation = mForward.getRotationTowards(CSceneModel::mpPlayer->mPosition + mPosition * -1.0f);
	mForward = CVector3(FORWARD);
	CPlayer::Move();
}

/*更新処理*/
void CEnemyBase::Update() {
	mAdjust = CVector3();
	Gravity();/*重力*/
	PosUpdate();//ポジションを更新
}

/*攻撃準備*/
void CEnemyBase::AttackInit() {
}


/*カプセル内当たり判定*/
void CEnemyBase::CapsuleCol(CColCapsule *cc, CColBase* y) {
	CColTriangle ct(false);//三角形の当たり判定
	CColCapsule  caps(false);//球の当たり判定

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
			//UpdateSkinMatrix(matrix);
			CModelXS::Update(matrix);
		}
		break;
	};
}

/*球体内当たり判定*/
void CEnemyBase::SphereCol(CColSphere *m, CColBase* y) {

	CColSphere  sph;//球の当たり判定
	CEnemyBase *ene;
	/*相手のタイプ何か判断*/
	switch (y->mType) {
		/*相手が球の場合*/
	case CColBase::COL_SPHEPE:
		sph = (*(CColSphere*)y).GetUpdate();
		/*当たり判定計算 ほかのエネミーに当たっているとき ダメージを受けているとき*/
		if (CCollision::CollisionShpere(sph, *m) && sph.eState == CColBase::ENE_BODY && mFlagDamage) {
			ene = (CEnemyBase*)sph.mpParent;
			ene->Damage(mDamagePower, mDamageRot);
		}


	};
}
//m 自分　y 相手
bool CEnemyBase::Collision(CColBase* m, CColBase* y) {
	CColCapsule cc;
	CColSphere sph;
	/*自分のタイプが何か判断*/
	switch (m->mType) {

	case CTask::COL_CAPSULE://自分の当たり判定がカプセルの場合
		cc = *(CColCapsule*)m;//カプセルにする
		CapsuleCol(&cc, y);//カプセルの当たり判定
		break;
	case CTask::COL_SPHEPE:
		sph = *(CColSphere*)m;
		SphereCol(&sph, y);
		break;
	};

	return false;
}

/*吹っ飛ぶ判定*/
void CEnemyBase::BlowOff() {
	mRotation = mDamageRot;//回転値の方向に飛ぶ
	mVelocity = DMAGE_SPEED(mDamagePower);//攻撃力によって吹っ飛ぶ度合いを決める
	CPlayer::Move();
}
/*ダメージを受けた時の処理*/
void CEnemyBase::Damage(float power, CVector3 rot) {
	mpHp->mValue -= power;
	/*ｈｐがなくなったとき消す*/
	if (mpHp->mValue <= 0) {
		CTask::mKillFlag = true;//削除するフラグを立てる
	}
	/*吹っ飛ぶ処理の準備*/
	mDamagePower = power;
	mDamageRot = rot;
	mFlagDamage = true;
}
/*描画処理*/
void CEnemyBase::Render() {
	CPlayer::Render();
}