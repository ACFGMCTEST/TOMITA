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
#define SEARCH_RANGE 3.0f
#define SERACH_SPHERE(mat) SEARCH_RANGE,CVector3(0.0f,0.0f,0.0f),mat//球体の設定(索敵に使う)


int CSlime::mAllCount = 0;

/*初期化処理*/
void CSlime::Init(CModelX *model){

	mStateMachine = (std::make_unique<CStateMachine>());
	mStateMachine->Register(SLI_STATE_IDLING, std::make_shared<CSlimeIdling>(), this);
	mStateMachine->Register(SLI_STATE_RUN, std::make_shared<CSlimeRun>(), this);
	mStateMachine->Register(SLI_STATE_DAMAGE, std::make_shared<CSlimeDamage>(), this);
	// 最初のステートを登録名で指定
	mStateMachine->SetStartState(SLI_STATE_IDLING);

	//モデルの設定
	CModelXS::Init(model);
	//カプセル　キャラクタ全体
	mpCaps   = new CColCapsule(this, COL_POS, COL_RADIUS, COL_BONE("Armature_Root_jnt"));
	//球体の当たり判定
	mpMatrix = COL_BONE("Armature_Root_jnt");
	mpSphere = new CColSphere(this, COL_SPHE_POS, COL_RADIUS, mpMatrix, CColBase::ENE_BODY);
	
	mPower = ATTACK_POWER;//攻撃力

	PosUpdate();
}
/*コンストラクタ*/
CSlime::CSlime(){
	eName = CTask::E_SLIME;
	mAllCount++;
	mNumber = mAllCount;
	CEnemyBase::CEnemyBase();
}
/*デストラクタ*/
CSlime::~CSlime(){
	mAllCount--;
	CTask *caps = mpCaps;
	CTask *sphe = mpSphere;
	CCollisionManager::GetInstance()->Kill(&caps);
	CCollisionManager::GetInstance()->Kill(&sphe);
}

/*更新処理*/
void CSlime::Update(){
	*mpMatrix = CMatrix44::MatrixTransform(mPosition, mRotation);
	CEnemyBase::Update();
	/*ステータス更新*/
	mStateMachine->Update();
}

/*描画処理*/
void CSlime::Render(){
	CEnemyBase::Render();
}

/*索敵関数*/
bool CSlime::Search(){

	/*索敵内に入れば動く*/
	CColSphere plCol = CColSphere(SERACH_SPHERE(CSceneModel::mpPlayer->mpMatrix));//プレイヤー
	CColSphere sliCol = CColSphere(SERACH_SPHERE(mpMatrix));//エネミー
	
	/*視界内に来ているか判断*/
	return CCollision::CollisionShpere(plCol.GetUpdate(), sliCol.GetUpdate());
}

/*球体内の当たり判定*/
void CSlime::SphereCol(CColSphere *sphere, CColBase *y){
	CColSphere  sph;//球の当たり判定
	/*相手のタイプ何か判断*/
	switch (y->mType) {
		/*相手が球の場合*/
	case CColBase::COL_SPHEPE:
		sph = (*(CColSphere*)y).GetUpdate();
		/*当たり判定計算*/
		if (CCollision::CollisionShpere(sph, *sphere) && sph.eState == CColBase::PL_BODY){
			Collision(&sph, sphere);
		}

	};
}