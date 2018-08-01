#include "CEnemyBase.h"
#include "../CSceneModel.h"
/*当たり判定*/
#include "../../../../Collision/ColType/CColCapsule.h"
#include "../../../../Collision/ColType/CColTriangle.h"
#include "../../../../Collision/CCollision.h"
#include "../../../../Graphic/CLoadTexManager.h"
#include "Slime\CSlime.h"
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
#define HP_SIZE 10.0f,1.0f
#define HP_AJUST_POS CVector3( 0.0f,4.0f,0.0f)//調整用
/*爆発テクスチャ*/
#define EXP_SIZE 0.3f,0.3f//サイズ
#define TAX_EXP_SIZE  0,0,270,270
#define EXP_SET_ANIMA 1,270


/*hp設定　ajust*/
void CEnemyBase::SetHpBar(float hp,CVector3 ajust) {
	/*HP設定*/
	mpHp = new CHpBar();
	mpHp->Init(&MainCamera,hp, hp, HP_SIZE, &mPosition,ajust);//サイズとポジション
	mpHp->SetTex(CLoadTexManager::GetInstance()->mpHp2DFrame,
		CLoadTexManager::GetInstance()->mpHp2DGauge, T_MANA_HP_SIZE);//テクスチャ
	CTaskManager::GetInstance()->Add(mpHp);


}
/*爆発設定*/
void CEnemyBase::SetExp() {
	/*爆発の設定*/
	mpExplosion = new CExplosion();
	mpExplosion->Init(CLoadTexManager::GetInstance()->mpSpark,
		EXP_SIZE, STexVer(TAX_EXP_SIZE));
	mpExplosion->SetAnima(EXP_SET_ANIMA);
	CTaskManager::GetInstance()->Add(mpExplosion);
}

#define FALL_DAMAGE 8.0f//落ちた時のダメージ量
/*コンストラクタ*/
CEnemyBase::CEnemyBase() : mFlagBlowDamage(false){
	
	/*ミニマップ設定*/
#define TEX_SIZE 386,386, 0.0f, 0.0f //ミニマップのサイズ
	mpMiniRect->SetUv(CLoadTexManager::GetInstance()->
		mpMiniMap[CLoadTexManager::ENEMY], TEX_SIZE);
	mpMiniRect->SetVertex(SVer(5.0f));//サイズ設定
	mFallDamage = FALL_DAMAGE;
}
/*デストラクタ*/
CEnemyBase::~CEnemyBase() {
	CSceneModel::mEnemyCount--;
#define MP_UP 20
	CSceneModel::mpPlayer->MpUp(MP_UP);
	if(mpExplosion)mpExplosion->mKillFlag = true;
	if(mpHp)mpHp->mKillFlag = true;
}

/*初期化処理*/
void CEnemyBase::Init() {
	SetHpBar(HP_MAX,HP_AJUST_POS);//hpバーの設定
	SetExp();//爆発エフェクトの設定
	mGravitTime = GRA_INIT_TIME_COUNT;
	mVelocity = 0.0f;
	mForward = CVector3(FORWARD);
	/*親設定*/
	mpParent = this;
}


/*動かす関数*/
void CEnemyBase::AIMove() {
	mRotation = mForward.getRotationTowards(CSceneModel::mpPlayer->mPosition + mPosition * -1.0f);
	mForward = CVector3(FORWARD);
	CPlayer::Move();
}

/*更新処理*/
void CEnemyBase::Update() {
	/*描画していないときはアップデートしない*/
	mAdjust = CVector3();
	Gravity();/*重力*/
	PosUpdate();//ポジションを更新
	//地面より下に落ちてしまったときの対処
	if (mPosition.y <= -10) {
		mpHp->mValue = 0;
	}
}

/*攻撃準備*/
void CEnemyBase::AttackInit() {
}




/*球体内当たり判定*/
void CEnemyBase::SphereCol(CColSphere *m, CColBase* y) {

	CColSphere  sph;//球の当たり判定
	CEnemyBase *ene;
	CPlayer *pl;
	/*相手のタイプ何か判断*/
	switch (y->mType) {
		/*相手が球の場合*/
	case CColBase::COL_SPHEPE:
		sph = (*(CColSphere*)y).GetUpdate();
		/*当たり判定計算*/
		if (CCollision::CollisionShpere(sph, *m)) {
			/*ほかのエネミーに当たっているとき ダメージを受けているとき*/
			if (sph.eState == CColBase::ENE_BODY && mFlagDamage) {
				ene = (CEnemyBase*)sph.mpParent;
				if (mFlagBlowDamage) {
					ene->Damage(mDamagePower, mDamageRot);
				}
			}
			/*プレイヤーに当たった時*/
			if (mFlagAttack && sph.eState == CColBase::PL_BODY   ||
				mFlagAttack && sph.eState == CColBase::PL_ATTACK )
			{
				pl = (CPlayer*)sph.mpParent;
				/*プレイヤーが回避していないとき HPがあるとき*/
				if (!pl->StateFlag(F_PL_DAMAGE) && pl->HP() > 0) {
					pl->Damage(mPower, mRotation);
				}
			}
		}


	};
}

#define AJUST_BLOW_OFF_POWER(pow) pow*2.0f //全体の攻撃調整
/*ダメージを受けた時の処理*/
float CEnemyBase::Damage(float power, CVector3 rot) {
	mpHp->mValue -= power;
	/*吹っ飛ぶ処理の準備*/
	mDamagePower = AJUST_BLOW_OFF_POWER(power);
	mDamageRot = rot;
	mFlagDamage = true;
	return mpHp->mValue;
}
/*描画処理*/
void CEnemyBase::Render() {
	CModelXS::Render();
}

