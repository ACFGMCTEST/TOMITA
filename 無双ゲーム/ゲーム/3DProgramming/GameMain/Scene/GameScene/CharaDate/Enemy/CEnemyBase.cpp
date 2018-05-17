#include "CEnemyBase.h"
#include "../CSceneModel.h"

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

/*コンストラクタ*/
CEnemyBase::CEnemyBase(){
	CXCharPlayer::CXCharPlayer();
	mGravitTime = GRA_INIT_TIME_COUNT;
	mVelocity = 0.0f;
	mFlagKnockback = false;
	mForward = CVector3(FORWARD);
	/*親設定*/
	mpParent = this;
}

/*初期化処理*/
void CEnemyBase::Init(CModelX *model){
	
}


/*動かす関数*/
void CEnemyBase::AIMove(){
	mRotation = mForward.getRotationTowards(CSceneModel::mpPlayer->mPosition + mPosition * -1.0f);
	mForward = CVector3(FORWARD);
	CXCharPlayer::Move();
}

/*更新処理*/
void CEnemyBase::Update(){
	mAdjust = CVector3();
	mPrevPos = mPosition;
	Gravity();/*重力*/
	PosUpdate();//ポジションを更新
}

/*攻撃準備*/
void CEnemyBase::AttackInit(){
}