#include "CXCharEnemy.h"
#include "../../CharaDate/CSceneModel.h"
#include "../../../../Key/CKey.h"
#include "../../../../Key/CMouse.h"
#include "../../../../Convenient/CConvenient.h"
#include "../../Map/CMap.h"
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


CXCharEnemy::CXCharEnemy(){
	CXCharPlayer::CXCharPlayer();
	mVelocity = 0.0f;
	mFlagKnockback = false;
	mForward = CVector3(FORWARD);
	/*親設定*/
	mpParent = this;


	mState = E_IDLING;
	ePriority = E_ENEMY;


}

/*当たり判定初期化*/
void CXCharEnemy::ColInit(){
	mpCBAttackInitBox = new CCollider(CTask::E_COL_BOX);
	mpCBAttackBox = new CCollider(CTask::E_COL_BOX);
	/*親を決める*/
	mpCBAttackInitBox->mpParent = this;
	mpCBAttackBox->mpParent = this;
}

/*初期化処理*/
void CXCharEnemy::Init(CModelX *model){
	srand((unsigned)time(NULL));
	ColInit();

	CXCharPlayer::Init(model);

	/*攻撃範囲の当たり判定*/
	mpCBAttackInitBox->SetBoxOBB(OBB_ATTACK_INIT_BOX_POS, OBB_ATTACK_INIT_BOX_SIZE
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);
	/*攻撃準備範囲の当たり判定*/
	mpCBAttackBox->SetBoxOBB(OBB_ATTACK_BOX_POS, OBB_ATTACK_BOX_SIZE
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);


	PosUpdate();


}

/*E_AIROT_STATEのステータス管理*/
void CXCharEnemy::AIRotStateUpdate(){

}


/*動かす関数*/
void CXCharEnemy::AIMove(){


}

/*更新処理*/
void CXCharEnemy::Update(){
	AnimaState(E_ATTACK_RUN);

	AIMove();
	mpCBAttackInitBox->Update();
	mpCBAttackBox->Update();
	CXCharPlayer::Update();
}

/*攻撃準備*/
void CXCharEnemy::AttackInit(){
	AnimaState(E_ATTACK_INIT);
}

/*攻撃*/
void CXCharEnemy::Attack(CCollider &col){
	//OBB衝突判定
	/*if (CCollision::CollSphereBox(col.mColSphere, mpCBWeapon->mObb)){
		AnimaState(E_ATTACK);
	}*/
	
}

/*障害物に当たった時のジャンプフラグ立て*/
void CXCharEnemy::ColEnabledJump(){
	mFlagJump = true;
	Jump();
}