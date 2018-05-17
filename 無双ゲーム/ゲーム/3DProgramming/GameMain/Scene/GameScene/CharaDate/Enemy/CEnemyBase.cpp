#include "CEnemyBase.h"
#include "../CSceneModel.h"

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

/*�R���X�g���N�^*/
CEnemyBase::CEnemyBase(){
	CXCharPlayer::CXCharPlayer();
	mGravitTime = GRA_INIT_TIME_COUNT;
	mVelocity = 0.0f;
	mFlagKnockback = false;
	mForward = CVector3(FORWARD);
	/*�e�ݒ�*/
	mpParent = this;
}

/*����������*/
void CEnemyBase::Init(CModelX *model){
	
}


/*�������֐�*/
void CEnemyBase::AIMove(){
	mRotation = mForward.getRotationTowards(CSceneModel::mpPlayer->mPosition + mPosition * -1.0f);
	mForward = CVector3(FORWARD);
	CXCharPlayer::Move();
}

/*�X�V����*/
void CEnemyBase::Update(){
	mAdjust = CVector3();
	mPrevPos = mPosition;
	Gravity();/*�d��*/
	PosUpdate();//�|�W�V�������X�V
}

/*�U������*/
void CEnemyBase::AttackInit(){
}