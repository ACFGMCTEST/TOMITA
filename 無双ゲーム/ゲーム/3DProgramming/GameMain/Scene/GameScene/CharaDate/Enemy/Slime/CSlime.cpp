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
#define SEARCH_RANGE 9.0f
#define ATTACK_RANGE 2.0f
#define SERACH_SPHERE(range,mat) range,CVector3(0.0f,0.0f,0.0f),mat//���̂̐ݒ�(���G�Ɏg��)

#define ATTACK_POWER 3.0f
int CSlime::mAllCount = 0;
/*�X���C���̃X�e�[�^�X������ King�X���C�����������̂��悤*/
void CSlime::StateInit() {
	mStateMachine.Register(F_SLI_IDLING, std::make_shared<CSlimeIdling>(), this);
	mStateMachine.Register(F_SLI_RUN, std::make_shared<CSlimeRun>(), this);
	mStateMachine.Register(F_SLI_DAMAGE, std::make_shared<CSlimeDamage>(), this);
	mStateMachine.Register(F_SLI_ATTACK, std::make_shared<CSlimeAttack>(), this);
	// �ŏ��̃X�e�[�g��o�^���Ŏw��
	mStateMachine.SetStartState(F_SLI_IDLING);
}
/*�X���C���̏�����*/
void CSlime::SlimeInit(CModelX *model) {

	//���f���̐ݒ�
	CModelXS::Init(model);
	//�J�v�Z���@�L�����N�^�S��
	mpCaps = new CColCapsule(this, COL_POS, COL_RADIUS, COL_BONE("Armature_Root_jnt"));
	//���̂̓����蔻��
	mpMatrix = COL_BONE("Armature_Root_jnt");
	mpSphere = new CColSphere(this, COL_SPHE_POS, COL_RADIUS, mpMatrix,
		CColBase::ENE_BODY);
	
	
	mPower = ATTACK_POWER;//�U����
	PosUpdate();
}
/*����������*/
void CSlime::Init(CModelX *model){

	SlimeInit(model);
	StateInit();
	CEnemyBase::Init();
}
/*�R���X�g���N�^*/
CSlime::CSlime(){
	mFlagDecoy = false;
	eName = CTask::E_SLIME;
	mAllCount++;
	mNumber = mAllCount;
}
/*�f�X�g���N�^*/
CSlime::~CSlime() {
	mAllCount--;
}
#define SPEED 1.0f//�����̃A�j���[�V�����X�s�[�h
/*�����蔻��폜*/
void CSlime::Delete() {
	if(mpCaps && mpSphere){
		mpSphere->mKillFlag = true;
		mpCaps->mKillFlag = true;
		if (mpHp)mpHp->mKillFlag = true;
		mpExplosion->StartAnima(SPEED,mPosition);//�����G�t�F�N�g����
	}
	/*�������I����*/
	if (mpExplosion->ExpEnd()) {
		CTask::mKillFlag = true;//�폜����t���O�𗧂Ă�
	}
}
/*�X�V����*/
void CSlime::Update(){
	*mpMatrix = CMatrix44::MatrixTransform(mPosition, mRotation);
	CEnemyBase::Update();
	/*�X�e�[�^�X�X�V*/
	mStateMachine.Update();
}

/*�`�揈��*/
void CSlime::Render(){
	CEnemyBase::Render();
}
/*�J�v�Z���������蔻��*/
void CSlime::CapsuleCol(CColCapsule *cc, CColBase* y) {
	CColTriangle ct;//�O�p�`�̓����蔻��
	CColCapsule  caps;//���̓����蔻��

					  /*����̃^�C�v�������f*/
	switch (y->mType) {
		/*���肪�O�p�̏ꍇ*/
	case CColBase::COL_TRIANGLE:
		ct = (*(CColTriangle*)y).GetUpdate();
		/*�����蔻��v�Z*/
		if (CCollision::IntersectTriangleCapsule3(ct.mV[0], ct.mV[1], ct.mV[2],
			cc->mV[0], cc->mV[1], cc->mRadius, &cc->mAdjust)) {
			CSlime::FallDamage(FALL_SAFE);

			ColGround();//�n�ʂɂ��������̏���
			SetAdjust(&mAdjust, cc->mAdjust);
			mPosition = mPosition + mAdjust;
			CMatrix44 rot_y, pos, matrix;
			//��]�s��̍쐬
			rot_y.rotationY(mRotation.y);
			//�ړ��s����v�Z����
			pos.translate(mPosition);
			//��]�ړ��s������߂�
			matrix = pos * rot_y;
			//UpdateSkinMatrix(matrix);
			CModelXS::Update(matrix);
		}
		break;
	};
}

/*���G�֐�*/
bool CSlime::Search(){
	if (!mFlagDecoy) {
#define SERACH_SPHERE(range,mat) range,CVector3(0.0f,0.0f,0.0f),mat//���̂̐ݒ�(���G�Ɏg��)
		/*���G���ɓ���Γ���*/
		CColSphere plCol = CColSphere(SERACH_SPHERE(SEARCH_RANGE, CSceneModel::mpPlayer->mpMatrix));//�v���C���[
		CColSphere sliCol = CColSphere(SERACH_SPHERE(SEARCH_RANGE, mpMatrix));//�G�l�~�[

		/*���E���ɗ��Ă��邩���f*/
		return CCollision::CollisionShpere(plCol.GetUpdate(), sliCol.GetUpdate());
	}
	return false;
}

/*�����Ƃ��납�痎����ƃ_���[�W ����:�������n�_�Ƃ̍���*/
#define FALL_DAMAGE(dama,height) dama * height
void CSlime::FallDamage(float height) {
	/*�����Ƃ��납�痎������*/
	if (mGroundPos.y > mPosition.y + height && HP() > 0) {
		mpHp->mValue -= FALL_DAMAGE(mFallDamage, mGroundPos.y - mPosition.y);
		mStateMachine.ForceChange(F_SLI_DAMAGE);
	}
}

/*�U���͈�*/
bool CSlime::AttackRange() {

	/*���G���ɓ���Γ���*/
	CColSphere plCol = CColSphere(SERACH_SPHERE(ATTACK_RANGE,CSceneModel::mpPlayer->mpMatrix));//�v���C���[
	CColSphere sliCol = CColSphere(SERACH_SPHERE(ATTACK_RANGE,mpMatrix));//�G�l�~�[
	/*���E���ɗ��Ă��邩���f*/
	return CCollision::CollisionShpere(plCol.GetUpdate(), sliCol.GetUpdate());
}



//m �����@y ����
bool CSlime::Collision(CColBase* m, CColBase* y) {
	
	CColCapsule cc;
	CColSphere sph;
	/*�����̃^�C�v���������f*/
	switch (m->mType) {

	case CTask::COL_CAPSULE://�����̓����蔻�肪�J�v�Z���̏ꍇ
		cc = *(CColCapsule*)m;//�J�v�Z���ɂ���
		CSlime::CapsuleCol(&cc, y);//�J�v�Z���̓����蔻��
		break;
	case CTask::COL_SPHEPE:
		sph = *(CColSphere*)m;
		CEnemyBase::SphereCol(&sph, y);
		break;
	};

	return false;
}



