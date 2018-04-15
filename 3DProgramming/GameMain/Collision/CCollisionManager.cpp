 #include "../Scene/GameScene/CharaDate/CXCharacter.h"
#include "../Scene/GameScene/CharaDate/CXCharEnemy.h"
#include "../Scene/GameScene/CharaDate/CSceneModel.h"
#include "../Scene/GameScene/UI/CScoreBoard.h"
#include "../../GameMain/Scene/CSceneManager.h"
#include "../Scene/GameScene/Map/Goal/CGoal.h"
#include "../Scene/GameScene//Map/Slope/CSlope.h"
#include "../Scene/GameScene/Puck/CXPuck.h"
#include "CCollisionManager.h"
#include "../Camera/CCamera.h"

/*回転を逆向きにする*/
#define REVERSE_ROT(rot) CVector3(rot.x,rot.y +180,rot.z)

CCollisionManager* CCollisionManager::mCollisionManager = 0;

//GetInstance
CCollisionManager* CCollisionManager::GetInstance() {
	if (mCollisionManager == 0) {
		mCollisionManager = new CCollisionManager();
	}
	return mCollisionManager;
}


void CCollisionManager::Add(CTask::E_TAG tag, CCollider *col){
	col->eTag = tag;
	col->ePriority = (CTask::E_PRIORITY)tag;//当たり判定用の順番に
	 
	CTaskManager::Add(col);
}



/*当たり判定フラグ*/
bool CCollisionManager::ColIf(CTask *Task_You, CTask *Task_I){
	CCollider *col_you, *col_I;
	col_you = dynamic_cast<CCollider*>(Task_You);
	col_I = dynamic_cast<CCollider*>(Task_I);
	/*アタリ判定判断(相手)*/
	switch (Task_You->eColTag)
	{
		/*ボックスの場合*/
	case CTask::E_COL_BOX:

		/*当たり判定判断(自分)*/
		switch (Task_I->eColTag)
		{
			/*ボックスの場合*/
		case CTask::E_COL_BOX:
			/*相手のボックスと自分のボックスを判断*/
			return (CCollision::CollisionOBB(col_you->mObb, col_I->mObb));
			break;
			/*球の場合*/
		case CTask::E_COL_SPHEPE:
			/*相手のボックスと自分の球を判断*/
			return (CCollision::CollSphereBox(col_I->mColSphere, col_you->mObb));
			break;
		}

		break;
		/*相手が球の場合*/
	case CTask::E_COL_SPHEPE:
		CColSphere *you = &col_you->mColSphere;
		/*当たり判定判断(自分)*/
		switch (Task_I->eColTag)
		{
			/*ボックスの場合*/
		case CTask::E_COL_BOX:
			return (CCollision::CollSphereBox(*you, col_I->mObb));
			break;
			/*球の場合*/
		case CTask::E_COL_SPHEPE:
			return !CCollision::CollisionShpere(*you, col_I->mColSphere);
			break;
		};
		break;
	}


	return false;
}

/*プレイヤー当たったときの処理*/
void CCollisionManager::PlayerCollision(CTask *Task_You, CTask *Player){

	/*プレイヤーキャスト*/
	CXCharPlayer *pl;//自分
	pl = dynamic_cast<CXCharPlayer *>(Player->mpParent);//自分
	
	/*ボックスキャスト*/
	CCollider *youBox,*plSphere;
	
	/*パックキャスト*/
	CXPuck *puck;

	/*あたり判定が何か判断*/
	switch (Task_You->eTag)
	{

	case CTask::E_TAG_GROUND:
	case CTask::E_TAG_BOX:
		/*キャスト処理*/
		youBox = dynamic_cast<CCollider *>(Task_You);
		plSphere = dynamic_cast<CCollider *>(Player);

		pl->Collision(youBox->mObb, plSphere->mColSphere);
		break;
	case CTask::E_TAG_NET:
		youBox = dynamic_cast<CCollider *>(Task_You);
		plSphere = dynamic_cast<CCollider *>(Player);

		pl->Collision(youBox->mObb,plSphere->mColSphere);

		break;
	case CTask::E_TAG_SLOPE:

		
		/*キャスト処理*/
		youBox = dynamic_cast<CCollider *>(Task_You);
		plSphere = dynamic_cast<CCollider *>(Player);


		/*当たり判定が足の時*/
		if (pl->mpCBLeg == plSphere){
			pl->Collision(youBox->mObb, plSphere->mColSphere);
		}
		break;

	case CTask::E_TAG_PUCK:
		
		/*パックキャスト*/
		puck = dynamic_cast<CXPuck *>(Task_You->mpParent);
		youBox = dynamic_cast<CCollider *>(Task_You);
		plSphere = dynamic_cast<CCollider *>(Player);

		/*パックのスピードがある場合*/
		if (puck->mVelocity >= SPEED_DAMAGE){
			pl->AnimaState(CXCharPlayer::E_DMGM);
			pl->Collision(puck->mpCBSphere->mColSphere, plSphere->mColSphere);
		}

		/*パックを跳ね返させる*/
		puck->ColCharaReflect(youBox->mObb);
		break;
	};
}


/*エネミーの当たり判定*/
void CCollisionManager::EnemyCollision(CTask *Task_You, CTask *Enemy){

	/*エネミーキャスト*/
	CXCharEnemy *ene;//自分
	ene = dynamic_cast<CXCharEnemy *>(Enemy->mpParent);
	/*パックキャスト*/
	CXPuck *puck;


	/*ボックスキャスト*/
	CCollider *youBox,*eneSphere;
	switch (Enemy->eTag)
	{
		/*エネミーの場合*/
	case CTask::E_TAG_ENEMY:
		/*あたり判定が何か判断*/
		switch (Task_You->eTag)
		{
			/*網と地面の場合*/
		case CTask::E_TAG_GROUND:
		case CTask::E_TAG_NET:

			youBox = dynamic_cast<CCollider *>(Task_You);
			eneSphere = dynamic_cast<CCollider *>(Enemy);
			
	
			/*元の一位戻す*/
			ene->Collision(youBox->mObb, eneSphere->mColSphere);
			
			break;
			/*障害物の場合*/
		case CTask::E_TAG_BOX:

			youBox = dynamic_cast<CCollider *>(Task_You);
			eneSphere = dynamic_cast<CCollider *>(Enemy);
			/*元の一位戻す*/
			ene->Collision(youBox->mObb, eneSphere->mColSphere);
			/*ジャンプさせる*/
			ene->ColEnabledJump();
			break;
		};
		break;



		/*攻撃準備範囲内の時*/
	case CTask::E_TAG_ATTACK_INIT_RANGE:
		switch (Task_You->eTag)
		{
		case CTask::E_TAG_PUCK:
			ene->AttackInit();
	
			break;
		};
		break;



		/*攻撃範囲内の時*/
	case CTask::E_TAG_ATTACK_RANGE:
		switch (Task_You->eTag)
		{

		case CTask::E_TAG_PUCK:
			puck = dynamic_cast<CXPuck *>(Task_You->mpParent);

			youBox = dynamic_cast<CCollider *>(Task_You);
			ene->Attack(*youBox);
		

			break;
		};
		break;

		/*坂の当たり判定*/
	case CTask::E_TAG_SLOPE:
		
		/*キャスト処理*/
		youBox = dynamic_cast<CCollider *>(Task_You);
		eneSphere = dynamic_cast<CCollider *>(Enemy);


		/*当たり判定が足の時*/
		if (ene->mpCBLeg == eneSphere){
			ene->Collision(youBox->mObb, eneSphere->mColSphere);
		
		}




		break;
	};
}


/*パックの当たり判定*/
void  CCollisionManager::PuckCollision(CTask *Task_You, CTask *Puck){


	CXPuck *puck = dynamic_cast<CXPuck*>(Puck->mpParent);//自分

	/*キャスト中身を見る*/
	CXCharPlayer *chara;
	/*ゴールキャスト*/
	CGoal *goal;
	//OBB衝突判定



	/*キャスト*/
	CCollider *you;

	/*あたり判定が何か判断*/
	switch (Task_You->eTag)
	{
		/*地面*/
	case CTask::E_TAG_GROUND:
		/*キャスト処理*/
		you = dynamic_cast<CCollider *>(Task_You);
		puck->Collision(you->mObb, puck->mpCBSphere->mColSphere);

		break;
		/*ボックス*/
	case CTask::E_TAG_BOX:
	//case CTask::E_TAG_SLOPE_REF:


		/*キャスト処理*/
		you = dynamic_cast<CCollider *>(Task_You);

		/*球体の場合*/
		if (puck->mpCBSphere == Puck){
			puck->Collision(you->mObb, puck->mpCBSphere->mColSphere);
		}
		/*ボックスの場合*/
		if (puck->mpCBRefBox == Puck){
			/*もし坂にあたっていないなら跳ね返る*/
			if (!puck->mFlagSlope){
				puck->ColReflect(you->mObb);
			}
		}
		break;

		//減速床
	case CTask::E_TAG_SLOW_FLOOR:
		puck->ColSlow();
		break;

		//加速床
	case CTask::E_TAG_FAST_FLOOR:
		puck->ColFast();
		break;


		/*トランポリン*/
	case CTask::E_TAG_TRAMPOLINE:
		puck->EnabledJump();
		break;

		/*ウエポン*/
	case CTask::E_TAG_WEAPON:

		chara = dynamic_cast<CXCharPlayer*>(Task_You->mpParent->mpParent);
		//キャラクターが攻撃状態か判断
		if (chara->mState == CXCharPlayer::E_ATTACK){
			puck = dynamic_cast<CXPuck*>(Puck->mpParent);//自分
			puck->ColReflect(chara->mRotation, chara->mPower);
		}

		break;

		/*ゴールプレイヤー*/
	case CTask::E_TAG_GOAL_PLAYER:

		CScoreBoard::GetInstance()->GoalPlayer();
		puck->GoalPlayer();//プレイヤー側にゴールしたなら

		/*ゴール呼び出し*/
		goal = dynamic_cast<CGoal*>(Task_You->mpParent);
		goal->GoalPerformance();
		break;

		/*ゴールエネミー*/
	case CTask::E_TAG_GOAL_ENEMY:

		CScoreBoard::GetInstance()->GoalEnemy();
		puck->GoalEnemy();//エネミー側にゴールしたなら

		/*ゴール呼び出し*/
		goal = dynamic_cast<CGoal*>(Task_You->mpParent);
		goal->GoalPerformance();

		break;

		/*坂*/
	case CTask::E_TAG_SLOPE:

		/*球体の場合*/
		if (puck->mpCBSphere == Puck){

			/*キャスト処理*/
			you = dynamic_cast<CCollider *>(Task_You);
			puck->Collision(you->mObb, puck->mpCBSphere->mColSphere);
			/*坂にあたっているフラグを立てる*/
			puck->EnabledSlope();
		}

		break;
	};
}

/*カメラの当たり判定*/
void  CCollisionManager::CameraCollision(CTask *Task_You, CTask *Camera){

	
	/*キャスト*/
	CCollider *youBox;

	/*あたり判定が何か判断*/
	switch (Task_You->eTag)
	{
	case CTask::E_TAG_HIGH_BOX:
	case CTask::E_TAG_BOX:
			/*キャスト処理*/
			youBox = dynamic_cast<CCollider *>(Task_You);
			MainCamera.Collision(youBox->mObb);
			break;
	};
}

/*更新2段目*/
void CCollisionManager::Update(CTask *t){
	CTask *task;
	task = mpRoot;
	/*探索処理*/
	while (task != 0)
	{
		/*同じもの以外*/
		if (t != task && t != 0 && task != 0){
			switch (t->eTag)
			{
			case CTask::E_TAG_CAMERA:
				/*当たっていて場合処理*/
				if (ColIf(task, t)){
					CameraCollision(task, t);//task何か,tパック
				}
				break;
			case CTask::E_TAG_PLAYER:
				/*当たっていて場合処理*/
				if (ColIf(task, t)){
					PlayerCollision(task, t);//task何か,tプレイヤー
				}
				break;
			case CTask::E_TAG_ENEMY:
			case CTask::E_TAG_ATTACK_INIT_RANGE:
			case CTask::E_TAG_ATTACK_RANGE:
				/*当たっていて場合処理*/
				if (ColIf(task, t)){
					EnemyCollision(task, t);//task何か,tエネミー
				}
				break;
			case CTask::E_TAG_PUCK:
				//printf("カメラに当たっているものは%dです\n", task->eTag);
				/*当たっていて場合処理*/
				if (ColIf(task, t)){
					PuckCollision(task, t);//task何か,tパック
				}
				break;
		
			}
		}
		task = task->mpNext;
	}

}

/*更新処理*/
void CCollisionManager::Update(){



	CTask *task;
	task = mpRoot;


	/*探索処理*/
	while (task != 0)
	{
		Update(task);
		task = task->mpNext;
	}


#ifdef _DEBUG 
	//AllRender();
#endif
}

CCollisionManager::CCollisionManager(){}
CCollisionManager::~CCollisionManager(){}