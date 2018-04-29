#include "CXCharEnemy.h"
#include "../CharaDate/CSceneModel.h"
#include "../../../Key/CKey.h"
#include "../../../Key/CMouse.h"
#include "../../../Convenient/CConvenient.h"
#include "../Map/CMap.h"
#include <time.h>

#include "../../../../GameMain/Collision/CCollision.h"
#include "../../../../GameMain/Collision/CCollisionManager.h"

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

int CXCharEnemy::mEnemyCountMax = 0;

CXCharEnemy::CXCharEnemy(){
	CXCharPlayer::CXCharPlayer();
	mVelocity = 0.0f;
	mFlagKnockback = false;
	mForward = CVector3(FORWARD);
	/*親設定*/
	mpParent = this;


	mState = E_IDLE;
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
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ATTACK_INIT_RANGE, mpCBAttackInitBox);
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ATTACK_RANGE, mpCBAttackBox);


	PosUpdate();


}

/*ゴールに打つ方向を決める関数*/
CVector3 CXCharEnemy::GoalShot(){
	/*進行方向の回転地を決める*/
	CVector3 Vec;

	/*打つ前に壁がある場合*/
	//if (){
	
	//}
	/*ゴールの方向に向ける*/
	//else{
		Vec = CSceneModel::mpGoalPlayer->mPosition;

		int randMax = MAPCHIP_SIZE	*CMap::mMapX;//最大値
		int randMin = -MAPCHIP_SIZE *CMap::mMapX; //最小値

		Vec.x = rand() % randMax + randMin;
	//}


	return mForward.getRotationTowards(Vec + mPosition * -1.0f);
}


/*E_AIROT_STATEのステータス管理*/
void CXCharEnemy::AIRotStateUpdate(){
	/*
	元居たポジションに戻るときは
	相手の陣地にパックがあること

	パックに向くときは
	自分の陣地にパックあること
	自分の初期ポジションより後ろに戻った時

	ゴールに向くときは
	攻撃した状態であること

	*/
	//if (!CSceneModel::mpPuck->mGoalStandUpFlag){
	eAIRotState = E_ROT_PUCK;

	//	}
	//else{

	/*パックが自分の陣地でないときは*/
	if (CSceneModel::mpPuck->mPosition.z <= 0){
		eAIRotState = E_ROT_FAST_POS;
		/*元の位置に戻った時*/
		if (mPosition.z >= CMap::EnemyFirstPos().z){
			AnimaState(E_ATTACK_IDLE);
		}
	}
	//}
	if (mState == E_ATTACK){
		eAIRotState = E_ROT_GOAL;
	}
}


/*動かす関数*/
void CXCharEnemy::AIMove(){
	AnimaState(E_ATTACK_INIT);
	//進行方向　z軸プラスが前方
	mForward = CVector3(FORWARD);
	AIRotStateUpdate();
	
	switch (eAIRotState)
	{
		/*元居たポジションに*/
	case CXCharEnemy::E_ROT_FAST_POS:
		/*自分の初期位置に向ける
		パックがゴール中でなければ
		*/
		if (CSceneModel::mpPuck->mPosition.y == 0){
			mRotation = mForward.getRotationTowards(CMap::EnemyFirstPos() + mPosition * -1.0f);
		}
		/*パックがゴール中*/
		else{
			mRotation = mForward.getRotationTowards(CMap::PlayerFirstPos() + mPosition * -1.0f);
		}
		break;
		/*パックに*/
	case CXCharEnemy::E_ROT_PUCK:
		/*パック方向に向ける*/
		mRotation = mForward.getRotationTowards(CSceneModel::mpPuck->mPosition + mPosition * -1.0f);
		break;

		/*相手のゴールに入れる*/
	case CXCharEnemy::E_ROT_GOAL:
		mRotation = GoalShot();
		break;
	};

	/*パックのスピードが止まっている場合*/
	if (CSceneModel::mpPuck->mVelocity == 0){
		AnimaState(E_ATTACK_INIT);
	}
	/*走っている時 &&　パックが地面についているとき*/
	if (mState == E_ATTACK_RUN || mState == E_RUN &&
		CSceneModel::mpPuck->mPosition.y == 0){
		CMatrix44 rot_y, pos, matrix;
		//回転行列の作成
		rot_y.rotationY(mRotation.y);
		///進行方向を計算
		mForward = mForward * rot_y;
		//移動させる
		mPosition += mForward * mVelocity;

	}
	PosUpdate();

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
	if (CCollision::CollSphereBox(col.mColSphere, mpCBWeapon->mObb)){
		AnimaState(E_ATTACK);
	}
	
}

/*障害物に当たった時のジャンプフラグ立て*/
void CXCharEnemy::ColEnabledJump(){
	mFlagJump = true;
	Jump();
}