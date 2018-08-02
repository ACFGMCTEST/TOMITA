#include "CKingSlime.h"
#include "../CSlime.h"

#include "../../../CSceneModel.h"
#include "../../../../../../Collision/CCollision.h"
#include "../../../../../../Graphic/CLoadTexManager.h"

#define HP_AJUST_POS CVector3(0.0f,6.0f,0.0f)

/*�����蔻��ݒ�*/
#define COL_RADIUS 3.0f

#define ATTACK_POWER 5.0f
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
	SetHpBar(ENE_HP_MAX(3.0f),HP_AJUST_POS);//hp�o�[�̐ݒ�
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
	mWeight = OBJECT_WIGHT(2.5f);
	CTask::eName = CTask::E_KING_SLIME;
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

/*�J�v�Z���������蔻��*/
void CKingSlime::CapsuleCol(CColCapsule *cc, CColBase* y) {
	CColTriangle ct;//�O�p�`�̓����蔻��
	CColCapsule  caps;//���̓����蔻��
					  //����̃^�C�v�������f
	switch (y->mType) {
		/*���肪�O�p�̏ꍇ*/
	case CColBase::COL_TRIANGLE:
		ct = (*(CColTriangle*)y).GetUpdate();
		/*�����蔻��v�Z*/
		if (CCollision::IntersectTriangleCapsule3(ct.mV[0], ct.mV[1], ct.mV[2],
			cc->mV[0], cc->mV[1], cc->mRadius, &cc->mAdjust)) {
			CKingSlime::FallDamage(FALL_SAFE);

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

//m �����@y ����
bool CKingSlime ::Collision(CColBase* m, CColBase* y) {

	CColCapsule cc;
	CColSphere sph;
	/*�����̃^�C�v���������f*/
	switch (m->mType) {

	case CTask::COL_CAPSULE://�����̓����蔻�肪�J�v�Z���̏ꍇ
		cc = *(CColCapsule*)m;//�J�v�Z���ɂ���
		CKingSlime::CapsuleCol(&cc, y);//�J�v�Z���̓����蔻��
		break;
	case CTask::COL_SPHEPE:
		sph = *(CColSphere*)m;
		SphereCol(&sph, y);
		break;
	};

	return false;
}


/*�`�揈��*/
void CKingSlime::Render() {
	CSlime::Render();
}
CKingSlime ::~CKingSlime()
{
}


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

/*�����Ƃ��납�痎����ƃ_���[�W ����:�������n�_�Ƃ̍���*/
#define FALL_DAMAGE(dama,height) dama * height
void CKingSlime::FallDamage(float height) {
	/*�����Ƃ��납�痎������*/
	if (mGroundPos.y > mPosition.y + height && HP() > 0) {
		mpHp->mValue -= FALL_DAMAGE(mFallDamage, mGroundPos.y - mPosition.y);
		mStateMachine.ForceChange(F_SLI_KING_DAMAGE);
		CLoadSoundManager::Sound(SE_FALL)->Play();
	}
}