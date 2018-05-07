#include "CXCharEnemy.h"
#include "../../CharaDate/CSceneModel.h"
#include "../../../../Key/CKey.h"
#include "../../../../Key/CMouse.h"
#include "../../../../Convenient/CConvenient.h"
#include "../../Map/CMap.h"
#include <time.h>

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


CXCharEnemy::CXCharEnemy(){
	CXCharPlayer::CXCharPlayer();
	mVelocity = 0.0f;
	mFlagKnockback = false;
	mForward = CVector3(FORWARD);
	/*�e�ݒ�*/
	mpParent = this;


	mState = E_IDLING;
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


	PosUpdate();


}

/*E_AIROT_STATE�̃X�e�[�^�X�Ǘ�*/
void CXCharEnemy::AIRotStateUpdate(){

}


/*�������֐�*/
void CXCharEnemy::AIMove(){


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
	/*if (CCollision::CollSphereBox(col.mColSphere, mpCBWeapon->mObb)){
		AnimaState(E_ATTACK);
	}*/
	
}

/*��Q���ɓ����������̃W�����v�t���O����*/
void CXCharEnemy::ColEnabledJump(){
	mFlagJump = true;
	Jump();
}