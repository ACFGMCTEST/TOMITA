#include "CEnemyBase.h"
#include "../CSceneModel.h"
/*�����蔻��*/
#include "../../../../Collision/ColType/CColCapsule.h"
#include "../../../../Collision/ColType/CColTriangle.h"
#include "../../../../Collision/CCollision.h"

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
#define HP_SIZE -5.0f,5.0f,4.0f,4.5f
#define TEX_SIZE_HP 0,0,490,46
/*�R���X�g���N�^*/
CEnemyBase::CEnemyBase() : mFlagDamage(false){
	/*HP�ݒ�*/
	mpHp = new CHpBar();
	mpHp->Init(HP_MAX, HP_MAX, HP_SIZE, &mPosition);//�T�C�Y�ƃ|�W�V����
	mTexGauge.Load(TGA_FILE"UI\\Gauge.tga");//HP�e�N�X�`���ǂݍ���
	mTexmFrame.Load(TGA_FILE"UI\\Frame.tga");//HP�e�N�X�`���ǂݍ���
	mpHp->SetTex(&mTexmFrame,&mTexGauge, TEX_SIZE_HP);//�e�N�X�`��
	CTaskManager::GetInstance()->Add(mpHp);
	
	CXCharPlayer::CXCharPlayer();
	mGravitTime = GRA_INIT_TIME_COUNT;
	mVelocity = 0.0f;
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
	Gravity();/*�d��*/
	PosUpdate();//�|�W�V�������X�V
}

/*�U������*/
void CEnemyBase::AttackInit(){
}


/*�J�v�Z���������蔻��*/
void CEnemyBase::CapsuleCol(CColCapsule *cc, CColBase* y){
	CColTriangle ct(false);//�O�p�`�̓����蔻��
	CColCapsule  caps(false);//���̓����蔻��

	/*����̃^�C�v�������f*/
	switch (y->mType){
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

//m �����@y ����
bool CEnemyBase::Collision(CColBase* m, CColBase* y) {
	CColCapsule cc(false);
	/*�����̃^�C�v���������f*/
	switch (m->mType) {

	case CColBase::COL_CAPSULE://�����̓����蔻�肪�J�v�Z���̏ꍇ
		cc = *(CColCapsule*)m;//�J�v�Z���ɂ���
		CapsuleCol(&cc, y);//�J�v�Z���̓����蔻��
		break;
	};

	return false;
}
/*������Ԕ���*/
void CEnemyBase::BlowOff() {
	mRotation = mDamageRot;//��]�l�̕����ɔ��
	mVelocity = mDamagePower;//�U���͂ɂ���Đ�����ԓx���������߂�
	CXCharPlayer::Move();
}
/*�_���[�W���󂯂����̏���*/
void CEnemyBase::Damage(float power, CVector3 rot){
	mpHp->mValue -= power;
	/*�������Ȃ��Ȃ����Ƃ�����*/
	if (mpHp->mValue <= 0){
		CTask::mKillFlag = true;//�폜����t���O�𗧂Ă�
	}
	/*������ԏ����̏���*/
	mDamagePower = power;
	mDamageRot = rot;
	mFlagDamage = true;
}
/*�`�揈��*/
void CEnemyBase::Render(){
	CXCharPlayer::Render();
}