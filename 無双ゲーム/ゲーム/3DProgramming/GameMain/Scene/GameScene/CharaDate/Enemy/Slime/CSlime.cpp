#include "CSlime.h"
#include <time.h>
/*���f��*/
#include "../../CSceneModel.h"
/*�X�e�[�^�X*/
#include "State\Attack\CStateSlimeAttack.h"
#include "State\Idling\CStateSlimeIdling.h"
#include "State\Jump\CStateSlimeJump.h"
#include "State\Run\CStateSlimeRun.h"
/*�����蔻��*/
#include "../../../../../Collision/ColType/CColCapsule.h"
#include "../../../../../Collision/ColType/CColTriangle.h"
#include "../../../../../Collision/CCollision.h"
#include "../../../../../Collision/ColType/CColSphere.h"


/*�����蔻��̐ݒ�l*/
#define COL_RADIUS 0.6f
#define COL_POS CVector3(0.0f, 1.0f, 0.0f), CVector3(0.0f, 0.0f, 0.0f)
#define COL_BONE &mpCombinedMatrix[model->FindFrame("Armature_Root_jnt")->mIndex]

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

/*���G�͈�*/
#define SEARCH_RANGE 3.0f
#define SERACH_SPHERE(mat) SEARCH_RANGE,CVector3(0.0f,0.0f,0.0f),mat//���̂̐ݒ�(���G�Ɏg��)


int CSlime::mAllCount = 0;

/*����������*/
void CSlime::Init(CModelX *model){
	mStateMachine = (std::make_unique<CStateMachine>());
	// �������ɃX�e�[�g�́u�o�^���v
	// ��������StateBase���p�������N���X��shared_ptr�I�u�W�F�N�g�𐶐�
	mStateMachine->Register(SLI_STATE_ATTACK, std::make_shared<CStateSlimeAttack>(), this);
	mStateMachine->Register(SLI_STATE_IDLING, std::make_shared<CStateSlimeIdling>(), this);
	mStateMachine->Register(SLI_STATE_RUN,    std::make_shared<CStateSlimeRun>(), this);
	mStateMachine->Register(SLI_STATE_JUMP,   std::make_shared<CStateSlimeJump>(), this);
	// �ŏ��̃X�e�[�g��o�^���Ŏw��
	mStateMachine->SetStartState(SLI_STATE_IDLING);

	//���f���̐ݒ�
	CModelXS::Init(model);
	//�J�v�Z���@�L�����N�^�S��
	new CColCapsule(this, COL_POS, COL_RADIUS, COL_BONE);
	mpMatrix = COL_BONE;

	mPower = ATTACK_POWER;//�U����

	PosUpdate();
	mPrevPos = mPosition;
}
/*�R���X�g���N�^*/
CSlime::CSlime(){
	mAllCount++;
	mNumber = mAllCount;
	CEnemyBase::CEnemyBase();
}
/*�f�X�g���N�^*/
CSlime::~CSlime(){
	mAllCount--;
}

/*�X�V����*/
void CSlime::Update(){
	CEnemyBase::Update();
	/*�X�e�[�^�X�X�V*/
	mStateMachine->Update();
}
/*�`�揈��*/
void CSlime::Render(){
	CXCharPlayer::Render();
}

/*���G�֐�*/
bool CSlime::Search(){

	/*���G���ɓ���Γ���*/
	CColSphere plCol = CColSphere(SERACH_SPHERE(CSceneModel::mpPlayer->mpMatrix));//�v���C���[
	CColSphere sliCol = CColSphere(SERACH_SPHERE(mpMatrix));//�G�l�~�[
	
	/*���E���ɗ��Ă��邩���f*/
	return CCollision::CollisionShpere(plCol.GetUpdate(), sliCol.GetUpdate());
}
