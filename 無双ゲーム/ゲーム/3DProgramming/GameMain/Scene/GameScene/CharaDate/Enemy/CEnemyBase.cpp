#include "CEnemyBase.h"
#include "../CSceneModel.h"
/*�����蔻��*/
#include "../../../../Collision/ColType/CColCapsule.h"
#include "../../../../Collision/ColType/CColTriangle.h"
#include "../../../../Collision/CCollision.h"
#include "../../../../Graphic/CLoadTexManager.h"
#include "Slime\CSlime.h"
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
#define HP_SIZE 10.0f,1.0f
#define HP_AJUST_POS CVector3( 0.0f,4.0f,0.0f)//�����p
/*�����e�N�X�`��*/
#define EXP_SIZE 0.3f,0.3f//�T�C�Y
#define TAX_EXP_SIZE  0,0,270,270
#define EXP_SET_ANIMA 1,270


/*hp�ݒ�@ajust*/
void CEnemyBase::SetHpBar(float hp,CVector3 ajust) {
	/*HP�ݒ�*/
	mpHp = new CHpBar();
	mpHp->Init(&MainCamera,hp, hp, HP_SIZE, &mPosition,ajust);//�T�C�Y�ƃ|�W�V����
	mpHp->SetTex(CLoadTexManager::GetInstance()->mpHp2DFrame,
		CLoadTexManager::GetInstance()->mpHp2DGauge, T_MANA_HP_SIZE);//�e�N�X�`��
	CTaskManager::GetInstance()->Add(mpHp);


}
/*�����ݒ�*/
void CEnemyBase::SetExp() {
	/*�����̐ݒ�*/
	mpExplosion = new CExplosion();
	mpExplosion->Init(CLoadTexManager::GetInstance()->mpSpark,
		EXP_SIZE, STexVer(TAX_EXP_SIZE));
	mpExplosion->SetAnima(EXP_SET_ANIMA);
	CTaskManager::GetInstance()->Add(mpExplosion);
}

#define FALL_DAMAGE 8.0f//���������̃_���[�W��
/*�R���X�g���N�^*/
CEnemyBase::CEnemyBase() : mFlagBlowDamage(false){
	
	/*�~�j�}�b�v�ݒ�*/
#define TEX_SIZE 386,386, 0.0f, 0.0f //�~�j�}�b�v�̃T�C�Y
	mpMiniRect->SetUv(CLoadTexManager::GetInstance()->
		mpMiniMap[CLoadTexManager::ENEMY], TEX_SIZE);
	mpMiniRect->SetVertex(SVer(5.0f));//�T�C�Y�ݒ�
	mFallDamage = FALL_DAMAGE;
}
/*�f�X�g���N�^*/
CEnemyBase::~CEnemyBase() {
	CSceneModel::mEnemyCount--;
#define MP_UP 20
	CSceneModel::mpPlayer->MpUp(MP_UP);
	if(mpExplosion)mpExplosion->mKillFlag = true;
	if(mpHp)mpHp->mKillFlag = true;
}

/*����������*/
void CEnemyBase::Init() {
	SetHpBar(HP_MAX,HP_AJUST_POS);//hp�o�[�̐ݒ�
	SetExp();//�����G�t�F�N�g�̐ݒ�
	mGravitTime = GRA_INIT_TIME_COUNT;
	mVelocity = 0.0f;
	mForward = CVector3(FORWARD);
	/*�e�ݒ�*/
	mpParent = this;
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
	//�n�ʂ�艺�ɗ����Ă��܂����Ƃ��̑Ώ�
	if (mPosition.y <= -10) {
		mpHp->mValue = 0;
	}
}

/*�U������*/
void CEnemyBase::AttackInit() {
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
				if (mFlagBlowDamage) {
					ene->Damage(mDamagePower, mDamageRot);
				}
			}
			/*�v���C���[�ɓ���������*/
			if (mFlagAttack && sph.eState == CColBase::PL_BODY   ||
				mFlagAttack && sph.eState == CColBase::PL_ATTACK )
			{
				pl = (CPlayer*)sph.mpParent;
				/*�v���C���[��������Ă��Ȃ��Ƃ� HP������Ƃ�*/
				if (!pl->StateFlag(F_PL_DAMAGE) && pl->HP() > 0) {
					pl->Damage(mPower, mRotation);
				}
			}
		}


	};
}

#define AJUST_BLOW_OFF_POWER(pow) pow*2.0f //�S�̂̍U������
/*�_���[�W���󂯂����̏���*/
float CEnemyBase::Damage(float power, CVector3 rot) {
	mpHp->mValue -= power;
	/*������ԏ����̏���*/
	mDamagePower = AJUST_BLOW_OFF_POWER(power);
	mDamageRot = rot;
	mFlagDamage = true;
	return mpHp->mValue;
}
/*�`�揈��*/
void CEnemyBase::Render() {
	CModelXS::Render();
}

