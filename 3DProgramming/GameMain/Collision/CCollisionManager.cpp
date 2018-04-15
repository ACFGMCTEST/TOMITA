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

/*��]���t�����ɂ���*/
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
	col->ePriority = (CTask::E_PRIORITY)tag;//�����蔻��p�̏��Ԃ�
	 
	CTaskManager::Add(col);
}



/*�����蔻��t���O*/
bool CCollisionManager::ColIf(CTask *Task_You, CTask *Task_I){
	CCollider *col_you, *col_I;
	col_you = dynamic_cast<CCollider*>(Task_You);
	col_I = dynamic_cast<CCollider*>(Task_I);
	/*�A�^�����蔻�f(����)*/
	switch (Task_You->eColTag)
	{
		/*�{�b�N�X�̏ꍇ*/
	case CTask::E_COL_BOX:

		/*�����蔻�蔻�f(����)*/
		switch (Task_I->eColTag)
		{
			/*�{�b�N�X�̏ꍇ*/
		case CTask::E_COL_BOX:
			/*����̃{�b�N�X�Ǝ����̃{�b�N�X�𔻒f*/
			return (CCollision::CollisionOBB(col_you->mObb, col_I->mObb));
			break;
			/*���̏ꍇ*/
		case CTask::E_COL_SPHEPE:
			/*����̃{�b�N�X�Ǝ����̋��𔻒f*/
			return (CCollision::CollSphereBox(col_I->mColSphere, col_you->mObb));
			break;
		}

		break;
		/*���肪���̏ꍇ*/
	case CTask::E_COL_SPHEPE:
		CColSphere *you = &col_you->mColSphere;
		/*�����蔻�蔻�f(����)*/
		switch (Task_I->eColTag)
		{
			/*�{�b�N�X�̏ꍇ*/
		case CTask::E_COL_BOX:
			return (CCollision::CollSphereBox(*you, col_I->mObb));
			break;
			/*���̏ꍇ*/
		case CTask::E_COL_SPHEPE:
			return !CCollision::CollisionShpere(*you, col_I->mColSphere);
			break;
		};
		break;
	}


	return false;
}

/*�v���C���[���������Ƃ��̏���*/
void CCollisionManager::PlayerCollision(CTask *Task_You, CTask *Player){

	/*�v���C���[�L���X�g*/
	CXCharPlayer *pl;//����
	pl = dynamic_cast<CXCharPlayer *>(Player->mpParent);//����
	
	/*�{�b�N�X�L���X�g*/
	CCollider *youBox,*plSphere;
	
	/*�p�b�N�L���X�g*/
	CXPuck *puck;

	/*�����蔻�肪�������f*/
	switch (Task_You->eTag)
	{

	case CTask::E_TAG_GROUND:
	case CTask::E_TAG_BOX:
		/*�L���X�g����*/
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

		
		/*�L���X�g����*/
		youBox = dynamic_cast<CCollider *>(Task_You);
		plSphere = dynamic_cast<CCollider *>(Player);


		/*�����蔻�肪���̎�*/
		if (pl->mpCBLeg == plSphere){
			pl->Collision(youBox->mObb, plSphere->mColSphere);
		}
		break;

	case CTask::E_TAG_PUCK:
		
		/*�p�b�N�L���X�g*/
		puck = dynamic_cast<CXPuck *>(Task_You->mpParent);
		youBox = dynamic_cast<CCollider *>(Task_You);
		plSphere = dynamic_cast<CCollider *>(Player);

		/*�p�b�N�̃X�s�[�h������ꍇ*/
		if (puck->mVelocity >= SPEED_DAMAGE){
			pl->AnimaState(CXCharPlayer::E_DMGM);
			pl->Collision(puck->mpCBSphere->mColSphere, plSphere->mColSphere);
		}

		/*�p�b�N�𒵂˕Ԃ�����*/
		puck->ColCharaReflect(youBox->mObb);
		break;
	};
}


/*�G�l�~�[�̓����蔻��*/
void CCollisionManager::EnemyCollision(CTask *Task_You, CTask *Enemy){

	/*�G�l�~�[�L���X�g*/
	CXCharEnemy *ene;//����
	ene = dynamic_cast<CXCharEnemy *>(Enemy->mpParent);
	/*�p�b�N�L���X�g*/
	CXPuck *puck;


	/*�{�b�N�X�L���X�g*/
	CCollider *youBox,*eneSphere;
	switch (Enemy->eTag)
	{
		/*�G�l�~�[�̏ꍇ*/
	case CTask::E_TAG_ENEMY:
		/*�����蔻�肪�������f*/
		switch (Task_You->eTag)
		{
			/*�Ԃƒn�ʂ̏ꍇ*/
		case CTask::E_TAG_GROUND:
		case CTask::E_TAG_NET:

			youBox = dynamic_cast<CCollider *>(Task_You);
			eneSphere = dynamic_cast<CCollider *>(Enemy);
			
	
			/*���̈�ʖ߂�*/
			ene->Collision(youBox->mObb, eneSphere->mColSphere);
			
			break;
			/*��Q���̏ꍇ*/
		case CTask::E_TAG_BOX:

			youBox = dynamic_cast<CCollider *>(Task_You);
			eneSphere = dynamic_cast<CCollider *>(Enemy);
			/*���̈�ʖ߂�*/
			ene->Collision(youBox->mObb, eneSphere->mColSphere);
			/*�W�����v������*/
			ene->ColEnabledJump();
			break;
		};
		break;



		/*�U�������͈͓��̎�*/
	case CTask::E_TAG_ATTACK_INIT_RANGE:
		switch (Task_You->eTag)
		{
		case CTask::E_TAG_PUCK:
			ene->AttackInit();
	
			break;
		};
		break;



		/*�U���͈͓��̎�*/
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

		/*��̓����蔻��*/
	case CTask::E_TAG_SLOPE:
		
		/*�L���X�g����*/
		youBox = dynamic_cast<CCollider *>(Task_You);
		eneSphere = dynamic_cast<CCollider *>(Enemy);


		/*�����蔻�肪���̎�*/
		if (ene->mpCBLeg == eneSphere){
			ene->Collision(youBox->mObb, eneSphere->mColSphere);
		
		}




		break;
	};
}


/*�p�b�N�̓����蔻��*/
void  CCollisionManager::PuckCollision(CTask *Task_You, CTask *Puck){


	CXPuck *puck = dynamic_cast<CXPuck*>(Puck->mpParent);//����

	/*�L���X�g���g������*/
	CXCharPlayer *chara;
	/*�S�[���L���X�g*/
	CGoal *goal;
	//OBB�Փ˔���



	/*�L���X�g*/
	CCollider *you;

	/*�����蔻�肪�������f*/
	switch (Task_You->eTag)
	{
		/*�n��*/
	case CTask::E_TAG_GROUND:
		/*�L���X�g����*/
		you = dynamic_cast<CCollider *>(Task_You);
		puck->Collision(you->mObb, puck->mpCBSphere->mColSphere);

		break;
		/*�{�b�N�X*/
	case CTask::E_TAG_BOX:
	//case CTask::E_TAG_SLOPE_REF:


		/*�L���X�g����*/
		you = dynamic_cast<CCollider *>(Task_You);

		/*���̂̏ꍇ*/
		if (puck->mpCBSphere == Puck){
			puck->Collision(you->mObb, puck->mpCBSphere->mColSphere);
		}
		/*�{�b�N�X�̏ꍇ*/
		if (puck->mpCBRefBox == Puck){
			/*������ɂ������Ă��Ȃ��Ȃ璵�˕Ԃ�*/
			if (!puck->mFlagSlope){
				puck->ColReflect(you->mObb);
			}
		}
		break;

		//������
	case CTask::E_TAG_SLOW_FLOOR:
		puck->ColSlow();
		break;

		//������
	case CTask::E_TAG_FAST_FLOOR:
		puck->ColFast();
		break;


		/*�g�����|����*/
	case CTask::E_TAG_TRAMPOLINE:
		puck->EnabledJump();
		break;

		/*�E�G�|��*/
	case CTask::E_TAG_WEAPON:

		chara = dynamic_cast<CXCharPlayer*>(Task_You->mpParent->mpParent);
		//�L�����N�^�[���U����Ԃ����f
		if (chara->mState == CXCharPlayer::E_ATTACK){
			puck = dynamic_cast<CXPuck*>(Puck->mpParent);//����
			puck->ColReflect(chara->mRotation, chara->mPower);
		}

		break;

		/*�S�[���v���C���[*/
	case CTask::E_TAG_GOAL_PLAYER:

		CScoreBoard::GetInstance()->GoalPlayer();
		puck->GoalPlayer();//�v���C���[���ɃS�[�������Ȃ�

		/*�S�[���Ăяo��*/
		goal = dynamic_cast<CGoal*>(Task_You->mpParent);
		goal->GoalPerformance();
		break;

		/*�S�[���G�l�~�[*/
	case CTask::E_TAG_GOAL_ENEMY:

		CScoreBoard::GetInstance()->GoalEnemy();
		puck->GoalEnemy();//�G�l�~�[���ɃS�[�������Ȃ�

		/*�S�[���Ăяo��*/
		goal = dynamic_cast<CGoal*>(Task_You->mpParent);
		goal->GoalPerformance();

		break;

		/*��*/
	case CTask::E_TAG_SLOPE:

		/*���̂̏ꍇ*/
		if (puck->mpCBSphere == Puck){

			/*�L���X�g����*/
			you = dynamic_cast<CCollider *>(Task_You);
			puck->Collision(you->mObb, puck->mpCBSphere->mColSphere);
			/*��ɂ������Ă���t���O�𗧂Ă�*/
			puck->EnabledSlope();
		}

		break;
	};
}

/*�J�����̓����蔻��*/
void  CCollisionManager::CameraCollision(CTask *Task_You, CTask *Camera){

	
	/*�L���X�g*/
	CCollider *youBox;

	/*�����蔻�肪�������f*/
	switch (Task_You->eTag)
	{
	case CTask::E_TAG_HIGH_BOX:
	case CTask::E_TAG_BOX:
			/*�L���X�g����*/
			youBox = dynamic_cast<CCollider *>(Task_You);
			MainCamera.Collision(youBox->mObb);
			break;
	};
}

/*�X�V2�i��*/
void CCollisionManager::Update(CTask *t){
	CTask *task;
	task = mpRoot;
	/*�T������*/
	while (task != 0)
	{
		/*�������̈ȊO*/
		if (t != task && t != 0 && task != 0){
			switch (t->eTag)
			{
			case CTask::E_TAG_CAMERA:
				/*�������Ă��ďꍇ����*/
				if (ColIf(task, t)){
					CameraCollision(task, t);//task����,t�p�b�N
				}
				break;
			case CTask::E_TAG_PLAYER:
				/*�������Ă��ďꍇ����*/
				if (ColIf(task, t)){
					PlayerCollision(task, t);//task����,t�v���C���[
				}
				break;
			case CTask::E_TAG_ENEMY:
			case CTask::E_TAG_ATTACK_INIT_RANGE:
			case CTask::E_TAG_ATTACK_RANGE:
				/*�������Ă��ďꍇ����*/
				if (ColIf(task, t)){
					EnemyCollision(task, t);//task����,t�G�l�~�[
				}
				break;
			case CTask::E_TAG_PUCK:
				//printf("�J�����ɓ������Ă�����̂�%d�ł�\n", task->eTag);
				/*�������Ă��ďꍇ����*/
				if (ColIf(task, t)){
					PuckCollision(task, t);//task����,t�p�b�N
				}
				break;
		
			}
		}
		task = task->mpNext;
	}

}

/*�X�V����*/
void CCollisionManager::Update(){



	CTask *task;
	task = mpRoot;


	/*�T������*/
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