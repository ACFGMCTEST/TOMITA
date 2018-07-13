#include "CKingSlime.h"
#include "../CSlime.h"

#include "../../../CSceneModel.h"
#include "../../../../../../Collision/CCollision.h"
#include "../../../../../../Graphic/CLoadTexManager.h"

#define HP_AJUST_POS CVector3(0.0f,6.0f,0.0f)

/*�����蔻��ݒ�*/
#define COL_RADIUS 3.0f


/*����������*/
void CKingSlime::Init(CModelX *model)
{

	//���f���̐ݒ�
	CModelXS::Init(model);
	//�J�v�Z���@�L�����N�^�S��
	mpCaps = new CColCapsule(this, COL_POS, COL_RADIUS, COL_BONE("Armature_Root_jnt"));
	//���̂̓����蔻��
	mpMatrix = COL_BONE("Armature_Root_jnt");
	mpSphere = new CColSphere(this, COL_SPHE_POS, COL_RADIUS, mpMatrix, CColBase::ENE_BODY);

	mStateMachine.Register(F_SLI_IDLING, std::make_shared<CKingSlimeIdling>(), this);
	mStateMachine.Register(F_SLI_RUN,    std::make_shared<CKingSlimeRun>(), this);
	mStateMachine.Register(F_SLI_DAMAGE, std::make_shared<CKingSlimeDamage>(), this);
	mStateMachine.Register(F_SLI_ATTACK, std::make_shared<CKingSlimeAttack>(), this);
	// �ŏ��̃X�e�[�g��o�^���Ŏw��
	mStateMachine.SetStartState(F_SLI_IDLING);


	/*�x�[�X�̂���*/
	mPower = ATTACK_POWER;//�U����
	PosUpdate();
	SetHpBar(HP_AJUST_POS);//hp�o�[�̐ݒ�
	SetExp();//�����G�t�F�N�g�̐ݒ�
	CPlayer::CPlayer();
	mGravitTime = GRA_INIT_TIME_COUNT;
	mVelocity = 0.0f;
	mForward = CVector3(FORWARD);
	/*�e�ݒ�*/
	mpParent = this;
}

CKingSlime::CKingSlime()
{
	/*�~�j�}�b�v�ݒ�*/
#define TEX_SIZE 386,386, 0.0f, 0.0f //�~�j�}�b�v�̃T�C�Y
	mpMiniRect->SetUv(CLoadTexManager::GetInstance()->
		mpMiniMap[CLoadTexManager::KING], TEX_SIZE);
	mpMiniRect->SetVertex(SVer(11.0f));
}

/*�X�V����*/
void CKingSlime::Update() {
	CSlime::Update();
}
CKingSlime ::~CKingSlime()
{}


/*���G�͈�*/
#define ATTACK_RANGE 5.0f
#define SERACH_SPHERE(range,mat) range,CVector3(0.0f,0.0f,0.0f),mat//���̂̐ݒ�(���G�Ɏg��)
/*�U���͈�*/
bool CKingSlime::AttackRange() {

	/*���G���ɓ���Γ���*/
	CColSphere plCol = CColSphere(SERACH_SPHERE(ATTACK_RANGE, CSceneModel::mpPlayer->mpMatrix));//�v���C���[
	CColSphere sliCol = CColSphere(SERACH_SPHERE(ATTACK_RANGE, mpMatrix));//�G�l�~�[
	/*���E���ɗ��Ă��邩���f*/
	return CCollision::CollisionShpere(plCol.GetUpdate(), sliCol.GetUpdate());
}