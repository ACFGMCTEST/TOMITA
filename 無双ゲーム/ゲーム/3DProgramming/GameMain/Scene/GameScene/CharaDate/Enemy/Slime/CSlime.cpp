#include "CSlime.h"
#include <time.h>
/*���f��*/
#include "../../CSceneModel.h"
/*�X�e�[�^�X*/
#include "Attack\CSlimeAttack.h"
#include "Idling\CSlimeIdling.h"
#include "Jump\CSlimeJump.h"
#include "Run\CSlimeRun.h"
#include "Damage\CSlimeDamage.h"
/*�����蔻��*/
#include "../../../../../Collision/ColType/CColTriangle.h"
#include "../../../../../Collision/CCollision.h"
#include "../../../../../Collision/ColType/CColSphere.h"


/*�����蔻��̐ݒ�l*/
#define COL_RADIUS 1.0f
#define COL_POS CVector3(0.0f, 1.0f, 0.0f), CVector3(0.0f, 0.0f, 0.0f)
#define COL_SPHE_POS CVector3(0.0f, 0.0f, 0.0f)
#define COL_BONE(string) &mpCombinedMatrix[model->FindFrame(string)->mIndex]

/*��]���o����*/
#define ROT_PYCK_TIME 1.0f
/*�����蔻��*/

/*�U��*/
#define OBB_ATTACK_BOX_SIZE CVector3(3.0f, 3.0f, 3.0f)
#define OBB_ATTACK_BOX_POS CVector3(-0.01f, -0.01f, -0.1f)
/*�S�[���̕����Ɍ�����*/
#define GOAL_POS_X (rand() % (int)MAPCHIP_SIZE*CMap::GoalCount()) - MAPCHIP_SIZE*CMap::GoalCount()*0.5f

/*���G�͈�*/
#define SEARCH_RANGE 3.0f
#define SERACH_SPHERE(mat) SEARCH_RANGE,CVector3(0.0f,0.0f,0.0f),mat//���̂̐ݒ�(���G�Ɏg��)


int CSlime::mAllCount = 0;

/*����������*/
void CSlime::Init(CModelX *model){

	mStateMachine = (std::make_unique<CStateMachine>());
	mStateMachine->Register(SLI_STATE_IDLING, std::make_shared<CSlimeIdling>(), this);
	mStateMachine->Register(SLI_STATE_RUN, std::make_shared<CSlimeRun>(), this);
	mStateMachine->Register(SLI_STATE_DAMAGE, std::make_shared<CSlimeDamage>(), this);
	// �ŏ��̃X�e�[�g��o�^���Ŏw��
	mStateMachine->SetStartState(SLI_STATE_IDLING);

	//���f���̐ݒ�
	CModelXS::Init(model);
	//�J�v�Z���@�L�����N�^�S��
	mpCaps   = new CColCapsule(this, COL_POS, COL_RADIUS, COL_BONE("Armature_Root_jnt"));
	//���̂̓����蔻��
	mpMatrix = COL_BONE("Armature_Root_jnt");
	mpSphere = new CColSphere(this, COL_SPHE_POS, COL_RADIUS, mpMatrix, CColBase::ENE_BODY);
	
	mPower = ATTACK_POWER;//�U����

	PosUpdate();
}
/*�R���X�g���N�^*/
CSlime::CSlime(){
	eName = CTask::E_SLIME;
	mAllCount++;
	mNumber = mAllCount;
	CEnemyBase::CEnemyBase();
}
/*�f�X�g���N�^*/
CSlime::~CSlime(){
	mAllCount--;
	CTask *caps = mpCaps;
	CTask *sphe = mpSphere;
	CCollisionManager::GetInstance()->Kill(&caps);
	CCollisionManager::GetInstance()->Kill(&sphe);
}

/*�X�V����*/
void CSlime::Update(){
	*mpMatrix = CMatrix44::MatrixTransform(mPosition, mRotation);
	CEnemyBase::Update();
	/*�X�e�[�^�X�X�V*/
	mStateMachine->Update();
}

/*�`�揈��*/
void CSlime::Render(){
	CEnemyBase::Render();
}

/*���G�֐�*/
bool CSlime::Search(){

	/*���G���ɓ���Γ���*/
	CColSphere plCol = CColSphere(SERACH_SPHERE(CSceneModel::mpPlayer->mpMatrix));//�v���C���[
	CColSphere sliCol = CColSphere(SERACH_SPHERE(mpMatrix));//�G�l�~�[
	
	/*���E���ɗ��Ă��邩���f*/
	return CCollision::CollisionShpere(plCol.GetUpdate(), sliCol.GetUpdate());
}

/*���̓��̓����蔻��*/
void CSlime::SphereCol(CColSphere *sphere, CColBase *y){
	CColSphere  sph;//���̓����蔻��
	/*����̃^�C�v�������f*/
	switch (y->mType) {
		/*���肪���̏ꍇ*/
	case CColBase::COL_SPHEPE:
		sph = (*(CColSphere*)y).GetUpdate();
		/*�����蔻��v�Z*/
		if (CCollision::CollisionShpere(sph, *sphere) && sph.eState == CColBase::PL_BODY){
			Collision(&sph, sphere);
		}

	};
}