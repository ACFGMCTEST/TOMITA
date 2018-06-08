#include "CEnemyBase.h"
#include "../CSceneModel.h"
/*�����蔻��*/
#include "../../../../Collision/ColType/CColCapsule.h"
#include "../../../../Collision/ColType/CColTriangle.h"
#include "../../../../Collision/CCollision.h"
#include "../../../../Graphic/CLoadTexManager.h"
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
/*hp�o�[*/
#define HP_MAX 10.0f 
#define HP_SIZE -5.0f,4.0f,5.0f,3.0f
#define TEX_SIZE_HP 0,0,490,46
/*�����e�N�X�`��*/
#define EXP_SIZE 0.3f,0.3f//�T�C�Y
#define TAX_EXP_SIZE  0,0,270,270
#define EXP_SET_ANIMA 1,270
/*�R���X�g���N�^*/
CEnemyBase::CEnemyBase(){
	/*HP�ݒ�*/
	mpHp = new CHpBar();
	mpHp->Init(HP_MAX, HP_MAX, HP_SIZE, &mPosition);//�T�C�Y�ƃ|�W�V����
	mpHp->SetTex(CLoadTexManager::GetInstance()->mpHp2DFrame,
				 CLoadTexManager::GetInstance()->mpHp2DGauge, TEX_SIZE_HP);//�e�N�X�`��
	CTaskManager::GetInstance()->Add(mpHp);
	CPlayer::CPlayer();
	/*�����̐ݒ�*/
	mpExplosion = new CExplosion();
	mpExplosion->Init(CLoadTexManager::GetInstance()->mpSpark,
		EXP_SIZE, STexVer(TAX_EXP_SIZE));
	mpExplosion->SetAnima(EXP_SET_ANIMA);
	CTaskManager::GetInstance()->Add(mpExplosion);
	
	mGravitTime = GRA_INIT_TIME_COUNT;
	mVelocity = 0.0f;
	mForward = CVector3(FORWARD);
	/*�e�ݒ�*/
	mpParent = this;
}
/*�f�X�g���N�^*/
CEnemyBase::~CEnemyBase() {
	if(mpExplosion)mpExplosion->mKillFlag = true;
	if(mpHp)mpHp->mKillFlag = true;
}

/*����������*/
void CEnemyBase::Init(CModelX *model) {

}


/*�������֐�*/
void CEnemyBase::AIMove() {
	mRotation = mForward.getRotationTowards(CSceneModel::mpPlayer->mPosition + mPosition * -1.0f);
	mForward = CVector3(FORWARD);
	CPlayer::Move();
}

/*�X�V����*/
void CEnemyBase::Update() {
	/*�`�悵�Ă��Ȃ��Ƃ��̓A�b�v�f�[�g���Ȃ�*/
	mAdjust = CVector3();
	Gravity();/*�d��*/
	PosUpdate();//�|�W�V�������X�V
}

/*�U������*/
void CEnemyBase::AttackInit() {
}


/*�J�v�Z���������蔻��*/
void CEnemyBase::CapsuleCol(CColCapsule *cc, CColBase* y) {
	CColTriangle ct(false);//�O�p�`�̓����蔻��
	CColCapsule  caps(false);//���̓����蔻��

	/*����̃^�C�v�������f*/
	switch (y->mType) {
		/*���肪�O�p�̏ꍇ*/
	case CColBase::COL_TRIANGLE:
		ct = (*(CColTriangle*)y).GetUpdate();
		/*�����蔻��v�Z*/
		if (CCollision::IntersectTriangleCapsule3(ct.mV[0], ct.mV[1], ct.mV[2],
			cc->mV[0], cc->mV[1], cc->mRadius, &cc->mAdjust)) {
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

/*���̓������蔻��*/
void CEnemyBase::SphereCol(CColSphere *m, CColBase* y) {

	CColSphere  sph;//���̓����蔻��
	CEnemyBase *ene;
	CPlayer *pl;
	/*����̃^�C�v�������f*/
	switch (y->mType) {
		/*���肪���̏ꍇ*/
	case CColBase::COL_SPHEPE:
		sph = (*(CColSphere*)y).GetUpdate();
		/*�����蔻��v�Z*/
		if (CCollision::CollisionShpere(sph, *m)) {
			/*�ق��̃G�l�~�[�ɓ������Ă���Ƃ� �_���[�W���󂯂Ă���Ƃ�*/
			if (sph.eState == CColBase::ENE_BODY && mFlagDamage) {
				ene = (CEnemyBase*)sph.mpParent;
				ene->Damage(mDamagePower, mDamageRot);
			}
			/*�v���C���[�ɓ���������*/
			if (mFlagAttack && sph.eState == CColBase::PL_BODY && mStr == SLI_STATE_ATTACK ||
				mFlagAttack && sph.eState == CColBase::PL_ATTACK && mStr == SLI_STATE_ATTACK)
			{
				pl = (CPlayer*)sph.mpParent;
				pl->Damage(mPower, mRotation);
			}
		}


	};
}
//m �����@y ����
bool CEnemyBase::Collision(CColBase* m, CColBase* y) {
	CColCapsule cc;
	CColSphere sph;
	/*�����̃^�C�v���������f*/
	switch (m->mType) {

	case CTask::COL_CAPSULE://�����̓����蔻�肪�J�v�Z���̏ꍇ
		cc = *(CColCapsule*)m;//�J�v�Z���ɂ���
		CapsuleCol(&cc, y);//�J�v�Z���̓����蔻��
		break;
	case CTask::COL_SPHEPE:
		sph = *(CColSphere*)m;
		SphereCol(&sph, y);
		break;
	};

	return false;
}


/*�_���[�W���󂯂����̏���*/
void CEnemyBase::Damage(float power, CVector3 rot) {
	mpHp->mValue -= power;
	/*������ԏ����̏���*/
	mDamagePower = power;
	mDamageRot = rot;
	mFlagDamage = true;
}
/*�`�揈��*/
void CEnemyBase::Render() {
	CPlayer::Render();
}