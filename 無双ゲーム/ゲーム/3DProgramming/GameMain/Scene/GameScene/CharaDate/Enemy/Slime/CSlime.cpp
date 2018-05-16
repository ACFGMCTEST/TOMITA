#include "CSlime.h"
#include <time.h>
/*ステータス*/
#include "State\Attack\CStateSlimeAttack.h"
#include "State\Idling\CStateSlimeIdling.h"
#include "State\Jump\CStateSlimeJump.h"
#include "State\Run\CStateSlimeRun.h"
/*当たり判定*/
#include "../../../../../Collision/ColType/CColCapsule.h"
#include "../../../../../Collision/ColType/CColTriangle.h"


/*あたり判定の設定値*/
#define COL_RADIUS 0.6f
#define COL_POS CVector3(0.0f, 1.0f, 0.0f), CVector3(0.0f, 0.0f, 0.0f)
#define COL_BONE &mpCombinedMatrix[model->FindFrame("Armature_Root_jnt")->mIndex]

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


/*初期化処理*/
void CSlime::Init(CModelX *model){
	mStateMachine = (std::make_unique<CStateMachine>());
	// 第一引数にステートの「登録名」
	// 第二引数でStateBaseを継承したクラスのshared_ptrオブジェクトを生成
	mStateMachine->Register(SLI_STATE_ATTACK, std::make_shared<CStateSlimeAttack>(), this);
	mStateMachine->Register(SLI_STATE_IDLING, std::make_shared<CStateSlimeIdling>(), this);
	mStateMachine->Register(SLI_STATE_RUN, std::make_shared<CStateSlimeRun>(), this);
	mStateMachine->Register(SLI_STATE_JUMP, std::make_shared<CStateSlimeJump>(), this);
	// 最初のステートを登録名で指定
	mStateMachine->SetStartState(SLI_STATE_IDLING);

	//モデルの設定
	CModelXS::Init(model);
	//カプセル　キャラクタ全体
	new CColCapsule(this, COL_POS, COL_RADIUS, COL_BONE);

	mPower = ATTACK_POWER;//攻撃力

	PosUpdate();
	mPrevPos = mPosition;
}
/*コンストラクタ*/
CSlime::CSlime(){
	CEnemyBase::CEnemyBase();
}
/*更新処理*/
void CSlime::Update(){
	CEnemyBase::Update();
	/*ステータス更新*/
	mStateMachine->Update();
}
/*描画処理*/
void CSlime::Render(){
	CXCharPlayer::Render();
}