#include "CKingSlime.h"
#include "../CSlime.h"

#include "../../../CSceneModel.h"
#include "../../../../../../Collision/CCollision.h"
#include "../../../../../../Graphic/CLoadTexManager.h"

#define HP_AJUST_POS CVector3(0.0f,6.0f,0.0f)

/*当たり判定設定*/
#define COL_RADIUS 3.0f

#define ATTACK_POWER 5.0f
/*初期化処理*/
void CKingSlime::Init(CModelX *model)
{

	//モデルの設定
	CModelXS::Init(model);
	//カプセル　キャラクタ全体
	mpCaps = new CColCapsule(this, COL_POS, COL_RADIUS, COL_BONE("Armature_Root_jnt"));
	//球体の当たり判定
	mpMatrix = COL_BONE("Armature_Root_jnt");
	mpSphere = new CColSphere(this, COL_SPHE_POS, COL_RADIUS, mpMatrix, CColBase::ENE_BODY);

	mStateMachine.Register(F_SLI_IDLING, std::make_shared<CKingSlimeIdling>(), this);
	mStateMachine.Register(F_SLI_RUN,    std::make_shared<CKingSlimeRun>(), this);
	mStateMachine.Register(F_SLI_DAMAGE, std::make_shared<CKingSlimeDamage>(), this);
	mStateMachine.Register(F_SLI_ATTACK, std::make_shared<CKingSlimeAttack>(), this);
	// 最初のステートを登録名で指定
	mStateMachine.SetStartState(F_SLI_IDLING);


	/*ベースのもの*/
	mPower = ATTACK_POWER;//攻撃力
	PosUpdate();
	SetHpBar(ENE_HP_MAX(3.0f),HP_AJUST_POS);//hpバーの設定
	SetExp();//爆発エフェクトの設定
	CPlayer::CPlayer();
	mGravitTime = GRA_INIT_TIME_COUNT;
	mVelocity = 0.0f;
	mForward = CVector3(FORWARD);
	/*親設定*/
	mpParent = this;
}

CKingSlime::CKingSlime()
{
	mWeight = OBJECT_WIGHT(2.5f);
	CTask::eName = CTask::E_KING_SLIME;
	/*ミニマップ設定*/
#define TEX_SIZE 386,386, 0.0f, 0.0f //ミニマップのサイズ
	mpMiniRect->SetUv(CLoadTexManager::GetInstance()->
		mpMiniMap[CLoadTexManager::KING], TEX_SIZE);
	mpMiniRect->SetVertex(SVer(11.0f));
}

/*更新処理*/
void CKingSlime::Update() {
	CSlime::Update();
}

/*カプセル内当たり判定*/
void CKingSlime::CapsuleCol(CColCapsule *cc, CColBase* y) {
	CColTriangle ct;//三角形の当たり判定
	CColCapsule  caps;//球の当たり判定
					  //相手のタイプ何か判断
	switch (y->mType) {
		/*相手が三角の場合*/
	case CColBase::COL_TRIANGLE:
		ct = (*(CColTriangle*)y).GetUpdate();
		/*当たり判定計算*/
		if (CCollision::IntersectTriangleCapsule3(ct.mV[0], ct.mV[1], ct.mV[2],
			cc->mV[0], cc->mV[1], cc->mRadius, &cc->mAdjust)) {
			CKingSlime::FallDamage(FALL_SAFE);

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

//m 自分　y 相手
bool CKingSlime ::Collision(CColBase* m, CColBase* y) {

	CColCapsule cc;
	CColSphere sph;
	/*自分のタイプが何か判断*/
	switch (m->mType) {

	case CTask::COL_CAPSULE://自分の当たり判定がカプセルの場合
		cc = *(CColCapsule*)m;//カプセルにする
		CKingSlime::CapsuleCol(&cc, y);//カプセルの当たり判定
		break;
	case CTask::COL_SPHEPE:
		sph = *(CColSphere*)m;
		SphereCol(&sph, y);
		break;
	};

	return false;
}


/*描画処理*/
void CKingSlime::Render() {
	CSlime::Render();
}
CKingSlime ::~CKingSlime()
{
}


/*索敵範囲*/
#define ATTACK_RANGE 5.0f
#define SERACH_SPHERE(range,mat) range,CVector3(0.0f,0.0f,0.0f),mat//球体の設定(索敵に使う)
/*攻撃範囲*/
bool CKingSlime::AttackRange() {

	/*索敵内に入れば動く*/
	CColSphere plCol = CColSphere(SERACH_SPHERE(ATTACK_RANGE, CSceneModel::mpPlayer->mpMatrix));//プレイヤー
	CColSphere sliCol = CColSphere(SERACH_SPHERE(ATTACK_RANGE, mpMatrix));//エネミー
	/*視界内に来ているか判断*/
	return CCollision::CollisionShpere(plCol.GetUpdate(), sliCol.GetUpdate());
}

/*高いところから落ちるとダメージ 引数:落ちた地点との差分*/
#define FALL_DAMAGE(dama,height) dama * height
void CKingSlime::FallDamage(float height) {
	/*高いところから落ちたら*/
	if (mGroundPos.y > mPosition.y + height && HP() > 0) {
		mpHp->mValue -= FALL_DAMAGE(mFallDamage, mGroundPos.y - mPosition.y);
		mStateMachine.ForceChange(F_SLI_KING_DAMAGE);
		CLoadSoundManager::Sound(SE_FALL)->Play();
	}
}