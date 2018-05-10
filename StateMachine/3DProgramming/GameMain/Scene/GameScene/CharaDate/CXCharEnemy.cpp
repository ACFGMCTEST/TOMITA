#include "CXCharEnemy.h"
#include "../CharaDate/CSceneModel.h"
#include "../../../Key/CKey.h"
#include "../../../Key/CMouse.h"
#include "../../../Convenient/CConvenient.h"
#include "../Map/CMap.h"
#include <time.h>

#include "../../../../GameMain/Collision/CCollision.h"
#include "../../../../GameMain/Collision/CCollisionManager.h"

/*��]���o����*/
#define ROT_PYCK_TIME 1.0f
/*�����蔻��*/
/*����*/
#define OBB_ATTACK_INIT_BOX_SIZE CVector3(20.0f, 4.0f, 20.0f)
#define OBB_ATTACK_INIT_BOX_POS CVector3(-0.01f, -0.06f, -0.1f)
/*�U��*/
#define OBB_ATTACK_BOX_SIZE CVector3(3.0f, 3.0f, 3.0f)
#define OBB_ATTACK_BOX_POS CVector3(-0.01f, -0.01f, -0.1f)
/*�S�[���̕����Ɍ�����*/
#define GOAL_POS_X (rand() % (int)MAPCHIP_SIZE*CMap::GoalCount()) - MAPCHIP_SIZE*CMap::GoalCount()*0.5f

int CXCharEnemy::mEnemyCountMax = 0;

CXCharEnemy::CXCharEnemy(){
	CXCharPlayer::CXCharPlayer();
	mVelocity = 0.0f;
	mFlagKnockback = false;
	mForward = CVector3(FORWARD);
	/*�e�ݒ�*/
	mpParent = this;


	mState = E_IDLE;
	ePriority = E_ENEMY;


}

/*�����蔻�菉����*/
void CXCharEnemy::ColInit(){
	mpCBAttackInitBox = new CCollider(CTask::E_COL_BOX);
	mpCBAttackBox = new CCollider(CTask::E_COL_BOX);
	/*�e�����߂�*/
	mpCBAttackInitBox->mpParent = this;
	mpCBAttackBox->mpParent = this;
}

/*����������*/
void CXCharEnemy::Init(CModelX *model){
	srand((unsigned)time(NULL));
	ColInit();

	CXCharPlayer::Init(model);

	/*�U���͈͂̓����蔻��*/
	mpCBAttackInitBox->SetBoxOBB(OBB_ATTACK_INIT_BOX_POS, OBB_ATTACK_INIT_BOX_SIZE
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);
	/*�U�������͈͂̓����蔻��*/
	mpCBAttackBox->SetBoxOBB(OBB_ATTACK_BOX_POS, OBB_ATTACK_BOX_SIZE
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ATTACK_INIT_RANGE, mpCBAttackInitBox);
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ATTACK_RANGE, mpCBAttackBox);


	PosUpdate();


}

/*�S�[���ɑł��������߂�֐�*/
CVector3 CXCharEnemy::GoalShot(){
	/*�i�s�����̉�]�n�����߂�*/
	CVector3 Vec;

	/*�łO�ɕǂ�����ꍇ*/
	//if (){
	
	//}
	/*�S�[���̕����Ɍ�����*/
	//else{
		Vec = CSceneModel::mpGoalPlayer->mPosition;

		int randMax = MAPCHIP_SIZE	*CMap::mMapX;//�ő�l
		int randMin = -MAPCHIP_SIZE *CMap::mMapX; //�ŏ��l

		Vec.x = rand() % randMax + randMin;
	//}


	return mForward.getRotationTowards(Vec + mPosition * -1.0f);
}


/*E_AIROT_STATE�̃X�e�[�^�X�Ǘ�*/
void CXCharEnemy::AIRotStateUpdate(){
	/*
	�������|�W�V�����ɖ߂�Ƃ���
	����̐w�n�Ƀp�b�N�����邱��

	�p�b�N�Ɍ����Ƃ���
	�����̐w�n�Ƀp�b�N���邱��
	�����̏����|�W�V���������ɖ߂�����

	�S�[���Ɍ����Ƃ���
	�U��������Ԃł��邱��

	*/
	//if (!CSceneModel::mpPuck->mGoalStandUpFlag){
	eAIRotState = E_ROT_PUCK;

	//	}
	//else{

	/*�p�b�N�������̐w�n�łȂ��Ƃ���*/
	if (CSceneModel::mpPuck->mPosition.z <= 0){
		eAIRotState = E_ROT_FAST_POS;
		/*���̈ʒu�ɖ߂�����*/
		if (mPosition.z >= CMap::EnemyFirstPos().z){
			AnimaState(E_ATTACK_IDLE);
		}
	}
	//}
	if (mState == E_ATTACK){
		eAIRotState = E_ROT_GOAL;
	}
}


/*�������֐�*/
void CXCharEnemy::AIMove(){
	AnimaState(E_ATTACK_INIT);
	//�i�s�����@z���v���X���O��
	mForward = CVector3(FORWARD);
	AIRotStateUpdate();
	
	switch (eAIRotState)
	{
		/*�������|�W�V������*/
	case CXCharEnemy::E_ROT_FAST_POS:
		/*�����̏����ʒu�Ɍ�����
		�p�b�N���S�[�����łȂ����
		*/
		if (CSceneModel::mpPuck->mPosition.y == 0){
			mRotation = mForward.getRotationTowards(CMap::EnemyFirstPos() + mPosition * -1.0f);
		}
		/*�p�b�N���S�[����*/
		else{
			mRotation = mForward.getRotationTowards(CMap::PlayerFirstPos() + mPosition * -1.0f);
		}
		break;
		/*�p�b�N��*/
	case CXCharEnemy::E_ROT_PUCK:
		/*�p�b�N�����Ɍ�����*/
		mRotation = mForward.getRotationTowards(CSceneModel::mpPuck->mPosition + mPosition * -1.0f);
		break;

		/*����̃S�[���ɓ����*/
	case CXCharEnemy::E_ROT_GOAL:
		mRotation = GoalShot();
		break;
	};

	/*�p�b�N�̃X�s�[�h���~�܂��Ă���ꍇ*/
	if (CSceneModel::mpPuck->mVelocity == 0){
		AnimaState(E_ATTACK_INIT);
	}
	/*�����Ă��鎞 &&�@�p�b�N���n�ʂɂ��Ă���Ƃ�*/
	if (mState == E_ATTACK_RUN || mState == E_RUN &&
		CSceneModel::mpPuck->mPosition.y == 0){
		CMatrix44 rot_y, pos, matrix;
		//��]�s��̍쐬
		rot_y.rotationY(mRotation.y);
		///�i�s�������v�Z
		mForward = mForward * rot_y;
		//�ړ�������
		mPosition += mForward * mVelocity;

	}
	PosUpdate();

}

/*�X�V����*/
void CXCharEnemy::Update(){
	AnimaState(E_ATTACK_RUN);

	AIMove();
	mpCBAttackInitBox->Update();
	mpCBAttackBox->Update();
	CXCharPlayer::Update();
}

/*�U������*/
void CXCharEnemy::AttackInit(){
	AnimaState(E_ATTACK_INIT);
}

/*�U��*/
void CXCharEnemy::Attack(CCollider &col){
	//OBB�Փ˔���
	if (CCollision::CollSphereBox(col.mColSphere, mpCBWeapon->mObb)){
		AnimaState(E_ATTACK);
	}
	
}

/*��Q���ɓ����������̃W�����v�t���O����*/
void CXCharEnemy::ColEnabledJump(){
	mFlagJump = true;
	Jump();
}