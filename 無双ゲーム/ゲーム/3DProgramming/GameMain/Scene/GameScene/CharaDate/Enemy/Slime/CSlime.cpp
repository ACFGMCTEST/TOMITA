#include "CSlime.h"
#include <time.h>
/*モデル*/
#include "../../CSceneModel.h"
/*ステータス*/
#include "Attack\CSlimeAttack.h"
#include "Idling\CSlimeIdling.h"
#include "Jump\CSlimeJump.h"
#include "Run\CSlimeRun.h"
#include "Damage\CSlimeDamage.h"
/*当たり判定*/
#include "../../../../../Collision/ColType/CColTriangle.h"
#include "../../../../../Collision/CCollision.h"
#include "../../../../../Collision/ColType/CColSphere.h"


/*あたり判定の設定値*/
#define COL_RADIUS 1.0f
#define COL_POS CVector3(0.0f, 1.0f, 0.0f), CVector3(0.0f, 0.0f, 0.0f)
#define COL_SPHE_POS CVector3(0.0f, 0.0f, 0.0f)
#define COL_BONE(string) &mpCombinedMatrix[model->FindFrame(string)->mIndex]

/*回転感覚時間*/
#define ROT_PYCK_TIME 1.0f
/*当たり判定*/

/*攻撃*/
#define OBB_ATTACK_BOX_SIZE CVector3(3.0f, 3.0f, 3.0f)
#define OBB_ATTACK_BOX_POS CVector3(-0.01f, -0.01f, -0.1f)
/*ゴールの方向に向ける*/
#define GOAL_POS_X (rand() % (int)MAPCHIP_SIZE*CMap::GoalCount()) - MAPCHIP_SIZE*CMap::GoalCount()*0.5f

/*索敵範囲*/
#define SEARCH_RANGE 9.0f
#define ATTACK_RANGE 2.0f
#define SERACH_SPHERE(range,mat) range,CVector3(0.0f,0.0f,0.0f),mat//球体の設定(索敵に使う)

#define ATTACK_POWER 3.0f
int CSlime::mAllCount = 0;
/*スライムのステータス初期化 Kingスライムも同じものしよう*/
void CSlime::StateInit() {
	mStateMachine.Register(F_SLI_IDLING, std::make_shared<CSlimeIdling>(), this);
	mStateMachine.Register(F_SLI_RUN, std::make_shared<CSlimeRun>(), this);
	mStateMachine.Register(F_SLI_DAMAGE, std::make_shared<CSlimeDamage>(), this);
	mStateMachine.Register(F_SLI_ATTACK, std::make_shared<CSlimeAttack>(), this);
	// 最初のステートを登録名で指定
	mStateMachine.SetStartState(F_SLI_IDLING);
}
/*スライムの初期化*/
void CSlime::SlimeInit(CModelX *model) {

	//モデルの設定
	CModelXS::Init(model);
	//カプセル　キャラクタ全体
	mpCaps = new CColCapsule(this, COL_POS, COL_RADIUS, COL_BONE("Armature_Root_jnt"));
	//球体の当たり判定
	mpMatrix = COL_BONE("Armature_Root_jnt");
	mpSphere = new CColSphere(this, COL_SPHE_POS, COL_RADIUS, mpMatrix,
		CColBase::ENE_BODY);
	
	
	mPower = ATTACK_POWER;//攻撃力
	PosUpdate();
}
/*初期化処理*/
void CSlime::Init(CModelX *model){

	SlimeInit(model);
	StateInit();
	CEnemyBase::Init();
}
/*コンストラクタ*/
CSlime::CSlime(){
	mFlagDecoy = false;
	eName = CTask::E_SLIME;
	mAllCount++;
	mNumber = mAllCount;
}
/*デストラクタ*/
CSlime::~CSlime() {
	mAllCount--;
}
#define SPEED 1.0f//爆発のアニメーションスピード
/*当たり判定削除*/
void CSlime::Delete() {
	if(mpCaps && mpSphere){
		mpSphere->mKillFlag = true;
		mpCaps->mKillFlag = true;
		if (mpHp)mpHp->mKillFlag = true;
		mpExplosion->StartAnima(SPEED,mPosition);//爆発エフェクト準備
	}
	/*爆発が終わると*/
	if (mpExplosion->ExpEnd()) {
		CTask::mKillFlag = true;//削除するフラグを立てる
	}
}
/*更新処理*/
void CSlime::Update(){
	*mpMatrix = CMatrix44::MatrixTransform(mPosition, mRotation);
	CEnemyBase::Update();
	/*ステータス更新*/
	mStateMachine.Update();
}

/*描画処理*/
void CSlime::Render(){
	CEnemyBase::Render();
}
/*カプセル内当たり判定*/
void CSlime::CapsuleCol(CColCapsule *cc, CColBase* y) {
	CColTriangle ct;//三角形の当たり判定
	CColCapsule  caps;//球の当たり判定

					  /*相手のタイプ何か判断*/
	switch (y->mType) {
		/*相手が三角の場合*/
	case CColBase::COL_TRIANGLE:
		ct = (*(CColTriangle*)y).GetUpdate();
		/*当たり判定計算*/
		if (CCollision::IntersectTriangleCapsule3(ct.mV[0], ct.mV[1], ct.mV[2],
			cc->mV[0], cc->mV[1], cc->mRadius, &cc->mAdjust)) {
			CSlime::FallDamage(FALL_SAFE);

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

/*索敵関数*/
bool CSlime::Search(){
	if (!mFlagDecoy) {
#define SERACH_SPHERE(range,mat) range,CVector3(0.0f,0.0f,0.0f),mat//球体の設定(索敵に使う)
		/*索敵内に入れば動く*/
		CColSphere plCol = CColSphere(SERACH_SPHERE(SEARCH_RANGE, CSceneModel::mpPlayer->mpMatrix));//プレイヤー
		CColSphere sliCol = CColSphere(SERACH_SPHERE(SEARCH_RANGE, mpMatrix));//エネミー

		/*視界内に来ているか判断*/
		return CCollision::CollisionShpere(plCol.GetUpdate(), sliCol.GetUpdate());
	}
	return false;
}

/*高いところから落ちるとダメージ 引数:落ちた地点との差分*/
#define FALL_DAMAGE(dama,height) dama * height
void CSlime::FallDamage(float height) {
	/*高いところから落ちたら*/
	if (mGroundPos.y > mPosition.y + height && HP() > 0) {
		mpHp->mValue -= FALL_DAMAGE(mFallDamage, mGroundPos.y - mPosition.y);
		mStateMachine.ForceChange(F_SLI_DAMAGE);
	}
}

/*攻撃範囲*/
bool CSlime::AttackRange() {

	/*索敵内に入れば動く*/
	CColSphere plCol = CColSphere(SERACH_SPHERE(ATTACK_RANGE,CSceneModel::mpPlayer->mpMatrix));//プレイヤー
	CColSphere sliCol = CColSphere(SERACH_SPHERE(ATTACK_RANGE,mpMatrix));//エネミー
	/*視界内に来ているか判断*/
	return CCollision::CollisionShpere(plCol.GetUpdate(), sliCol.GetUpdate());
}



//m 自分　y 相手
bool CSlime::Collision(CColBase* m, CColBase* y) {
	
	CColCapsule cc;
	CColSphere sph;
	/*自分のタイプが何か判断*/
	switch (m->mType) {

	case CTask::COL_CAPSULE://自分の当たり判定がカプセルの場合
		cc = *(CColCapsule*)m;//カプセルにする
		CSlime::CapsuleCol(&cc, y);//カプセルの当たり判定
		break;
	case CTask::COL_SPHEPE:
		sph = *(CColSphere*)m;
		CEnemyBase::SphereCol(&sph, y);
		break;
	};

	return false;
}



