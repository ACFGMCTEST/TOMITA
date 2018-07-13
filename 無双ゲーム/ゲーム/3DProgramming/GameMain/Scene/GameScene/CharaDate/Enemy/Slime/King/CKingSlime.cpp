#include "CKingSlime.h"
#include "../CSlime.h"

#include "../../../CSceneModel.h"
#include "../../../../../../Collision/CCollision.h"
#include "../../../../../../Graphic/CLoadTexManager.h"

#define HP_AJUST_POS CVector3(0.0f,6.0f,0.0f)

/*当たり判定設定*/
#define COL_RADIUS 3.0f


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
	SetHpBar(HP_AJUST_POS);//hpバーの設定
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
CKingSlime ::~CKingSlime()
{}


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