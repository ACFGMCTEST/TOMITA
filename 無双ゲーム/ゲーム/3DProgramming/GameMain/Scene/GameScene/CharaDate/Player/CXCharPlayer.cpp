#include "CXCharPlayer.h"
#include "windows.h"
#include "../../../../Key/CKey.h"
#include "../CSceneModel.h"
#include "../../../../../Define/Define.h"
#include "../../Map/CMap.h"
#include "../../../../Key/CMouse.h"
#include "../../../../Convenient/CConvenient.h"
#include "../../../GameScene/Map/CMap.h"
#include "../../../ItemScene/CItem.h"
#include <math.h>
#include "../../../../Collision/CCollisionManager.h"
#include "../../../../Collision/CCollision.h"
/*�X�e�[�^�X*/
#include "State\Attack\CStatePlayerAttack.h"
#include "State\Idling\CStatePlayeridling.h"
#include "State\Jump\CStatePlayerJump.h"
#include "State\Run\CStatePlayerRun.h"
#include "../../../../../StateMachine/CStateMachine.h"


/*����*/
#define FORWARD_JUMP  0.0f,1.0f,1.0f//�W�����v

/*�����蔻��̐ݒ�l*/
/*��*/
#define OBB_SPHERE_BODY_SIZE 0.4f
#define OBB_SPHERE_BODY_POS CVector3(0.0f,0.0f,0.0f)
/*����*/
#define OBB_WEAPON_POS CVector3(0.0f,0.5f,0.0f)
#define OBB_WEAPON_SIZE CVector3(0.4f, 0.7f, 0.4f)
/*��*/
#define OBB_LEG_SIZE 0.3f
#define OBB_LEG_POS CVector3(0.0f,-1.0f,0.0f)

/*HP�o�[�̐ݒ�l*/
#define HP_BAR_POS CVector3(mPosition.x,mPosition.y + 1.8f,mPosition.z)
#define HP_BAR_SIZE -0.4f, 0.4f, -0.1f, 0.0f

/*�����̉�]���鑬��*/
#define TURN_SPEED 10

CXCharPlayer::CXCharPlayer() : mVelocity(0.0f), mFlagKnockback(false), mRotCount(0),
mGravitTime(GRA_INIT_TIME_COUNT), mFlagJump(false), mAdjust(),
mStateMachine(std::make_unique<CStateMachine>())
{
	// �������ɃX�e�[�g�́u�o�^���v
	// ��������StateBase���p�������N���X��shared_ptr�I�u�W�F�N�g�𐶐�
	mStateMachine->Register(PL_STATE_ATTACK, std::make_shared<CStatePlayerAttack>(),this);
	mStateMachine->Register(PL_STATE_IDLING, std::make_shared<CStatePlayerIdling>(),this);
	mStateMachine->Register(PL_STATE_RUN,    std::make_shared<CStatePlayerRun>(),this);
	mStateMachine->Register(PL_STATE_JUMP,   std::make_shared<CStatePlayerJump>(),this);
	// �ŏ��̃X�e�[�g��o�^���Ŏw��
	mStateMachine->SetStartState(PL_STATE_IDLING);

	mForward = CVector3(FORWARD);
	mpParent = this;

	mState = E_IDLING;
	ePriority = CTask::E_PLAYER;

};

/*�����蔻�菉����*/
void CXCharPlayer::ColInit(){
	/*�����蔻��̃C���X�^���X��*/
	//mpCBWeapon = new CCollider(CTask::E_COL_BOX);

	/*�y�A�����g�ݒ�*/
	//mpCBWeapon->mpParent = this;
}
#define COL_POS CVector3(0.0f, 1.5f, 0.0f), CVector3(0.0f, -0.9f, 0.0f)
/*
Init
���f���ƏՓ˔���̐ݒ���s��
*/
void CXCharPlayer::Init(CModelX *model) {
	ColInit();
	//���f���̐ݒ�
	CModelXS::Init(model);
	//�J�v�Z���@�L�����N�^�S��
	new CCollider3Capsule(this, COL_POS, 0.5f
		, &mpCombinedMatrix[model->FindFrame("metarig_hips")->mIndex]);

	mPower = ATTACK_POWER;//�U����

	PosUpdate();
	mPrevPos = mPosition;
}




/*�|�W�V�����̃A�b�v�f�[�g�֐�*/
void CXCharPlayer::PosUpdate(){
	CMatrix44 rot_y, pos, matrix;
	//��]�s��̍쐬
	rot_y.rotationY(mRotation.y);

	//�ړ��s����v�Z����
	pos.translate(mPosition);
	//��]�ړ��s������߂�
	matrix = pos * rot_y;

	//���_�f�[�^�̍X�V
	CModelXS::Update(matrix);
	mPrevPos = mPosition;
}

/*��]�֐�*/
void CXCharPlayer::PlusRot(float rot){

	mRotation.y += rot;//�^�X����
	if (mRotation.y < 0){//��]�l���}�C�i�X�Ȃ�
		mRotation.y = ANGLE_360 + mRotation.y;//�R�U�O�ȓ��ɂƂǂ߂�
	}
	if (mRotation.y > ANGLE_360){//�R�U�O�ȏ�̏ꍇ
		mRotation.y = mRotation.y + ANGLE_360;
	}
}
/*�L�����N�^�[��]���������������ɉ�]����*/
int CXCharPlayer::MoveRotation(int angle){

	/*�E���*/
	int turnRight = angle - mRotation.y;
	/*�ߏ�]��*/
	LIMIT_ANGLE(turnRight);
	/*�����*/
	int turnLeft = ANGLE_360 - turnRight;

	//printf("�E��]:%d,����]%d\n", turnRight, turnLeft);
	/*�����̏ꍇ ||
	�E�ɉz���Ă��܂��ꍇ ||
	���ɉz���Ă��܂��ꍇ ||
	*/
	if (mRotation.y == angle ||
		mRotation.y <= angle && angle <= mRotation.y + TURN_SPEED ||
		mRotation.y - TURN_SPEED <= angle && angle <= mRotation.y){
		return angle;
	}
	/*�E�����m�F*/
	if (turnRight < turnLeft){
		return mRotation.y + TURN_SPEED;
	}
	/*�����m�F*/
	else{
		return mRotation.y - TURN_SPEED;
	}


}


/*�����Ƃ��̊֐�*/
void CXCharPlayer::PlayerMoveRot(){

	LIMIT_ANGLE(mRotation.y);

	if (CKey::push('A')){//���Ɉړ�
		mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_90) % 360);
	}
	if (CKey::push('D')){//�E�Ɉړ�
		mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_270) % 360);
	}

	if (CKey::push('W')){//�O�Ɉړ�

		mRotation.y = MoveRotation(((int)MainCamera.Rot().y) % 360);
		if (CKey::push('A')){//���Ɉړ�
			mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_45) % 360);
		}
		if (CKey::push('D')){//�E�Ɉړ�
			mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_315) % 360);
		}
	}

	if (CKey::push('S')){
		mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_180) % 360);
		if (CKey::push('A')){//���Ɉړ�
			mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_125) % 360);
		}
		if (CKey::push('D')){//�E�Ɉړ�
			mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_225) % 360);
		}
	}

	Move();//�ړ�������

}
/*�������Ƃ��̏���
forward = �����ݒ�
velocity = ��
*/
void CXCharPlayer::Move(){

	CMatrix44 rot_y, pos, matrix;
	CVector3 moveForward = mForward;//�Q�Ƃł�����Ȃ��̂�
	//��]�s��̍쐬
	rot_y.rotationY(mRotation.y);
	///�i�s�������v�Z
	moveForward = mForward * rot_y;
	//�ړ�������
	mPosition += moveForward * mVelocity;
}


/*�d��*/
void CXCharPlayer::Gravity(){
	/*�n�ʂɂ��Ă��Ȃ��Ȃ�*/
	mPosition.y -= GRAVITY(mGravitTime);
	mGravitTime += GRA_TIME_UP;//���Ԃ��o��
}
/*�O���E���h�̐ݒ�*/
void CXCharPlayer::ColGround(){
	mGravitTime = GRA_INIT_TIME_COUNT;
	mFlagJump = false;//�W�����v�I��
}

/*�X�V����*/
void CXCharPlayer::Update(){
	mAdjust = CVector3();
	mPrevPos = mPosition;
	Gravity();/*�d��*/
	PosUpdate();//�|�W�V�������X�V

	/*�X�e�[�^�X�}�V���X�V*/
	mStateMachine->Update();
	//��Ԃɂ��A�j���[�V�����ω�
	switch (mState)
	{
	case E_IDLING://����

		mCountKnockBack = 0;
		break;
	case E_RUN://����
		break;
	case E_ATTACK_RUN://�U������
		break;
	case E_ATTACK_INIT:
		ChangeAnimation(E_ATTACK_INIT, false, ANIMA_SPEED_ATTCK);
		break;
	case E_ATTACK://�U��
		break;
	case E_ATTACK_IDLING:
		ChangeAnimation(E_ATTACK_IDLING, true, ANIMA_SPEED_ATTCK);
		break;
	case E_JUMP:
		ChangeAnimation(E_JUMP, false, ANIMA_SPEED_JUMP);
		break;
	case E_ATTACK_JUMP:
		ChangeAnimation(E_ATTACK_JUMP, false, ANIMA_SPEED_JUMP);
		break;
	case E_DMGM://�_���[�W
		ChangeAnimation(E_DMGM, false, ANIMA_SPEED);
		if (mCountKnockBack <= 0){ //�J�E���g���O�ɂȂ��
			mCountKnockBack = 0;
		}
		else{
			mCountKnockBack -= 1;
		}
		break;
	};
}



/*Render*/
void CXCharPlayer::Render() {
	//27
	//HP�o�[�̐ݒ�
	//mHpBar.mPosition = mPosition;
	//mHpBar.mPosition.y += 1.8f;
	//mHpBar.Update();	//�X�V
	//mHpBar.Render();	//�`��
	CModelXS::Render();
#ifdef _DEBUG
	//	mpCBBody->Render();
	//	mpCBWeapon->Render();
	//	mpCBLeg->Render();
	//	mpColCapsule->Render();
#endif
}

/*�G�t�F�N�g�̕`�揈��*/
void CXCharPlayer::BillboardRender(){
	CVector3 pos = HAMMER_EFFECT_POS;
	pos = pos * mpCombinedMatrix[mpModel->FindFrame("metarig_WeaponHandle")->mIndex];//�}�g���b�N�X����

}

/*�����蔻��̎��ɌĂяo��*/
void CXCharPlayer::ColMove(int count, CVector3 Forward){
	if (count <= -1){//�J�E���g���}�C�i�X�Ȃ�
		mVelocity = -KNOCK_BACK; //�������ɂ���
		count *= -1;//�v���X�ɂ���
	}
	else
	{
		mVelocity = -KNOCK_BACK;
	}
	mForward = Forward;
	mCountKnockBack = count;
}

/*�����蔻��Ăяo��
���̏ꏊ�ɖ߂����߂̊֐�
*/
bool CXCharPlayer::Collision(const COBB &box, const CColSphere &sphere) {
	return Collision(&box, &sphere);
}

bool CXCharPlayer::Collision(const COBB *box, const CColSphere *sphere) {
	return true;
}




/*�����蔻��*/
bool CXCharPlayer::Collision(CCollider2* me, CCollider2* you) {
	
	switch (me->eColTag) {
	case E_COL_CAPSULE:
		if (you->eColTag == E_COL_TRIANGLE &&
			(you->eTag == E_TAG_GROUND ||
			you->eTag == E_TAG_WALL)) {
			CVector3 cross;
			float length;
			CVector3 adjust;
			if (CCollision::IntersectTriangleCapsule3(you->mV[1][0], you->mV[1][1], you->mV[1][2],
				me->mV[1][0], me->mV[1][1], me->mF[0], &adjust, &cross, &length)) {
				if (cross == CVector3())
					return false;
				//				if (you->eTag == E_TAG_BOX)
				ColGround();//�n�ʂɂ��������̏���
				mPosition = mPosition + adjust;
			}
		}
		break;
	case E_COL_SPHEPE:
		if (you->eTag == E_TAG_GROUND) {
			if (you->eColTag == E_COL_BOX)
				return Collision((COBB*)&you->mObb, (CColSphere*)&me->mColSphere);
		}
	}

	return false;
}
void SetAdjust(CVector3 *s, const CVector3 &t) {
	//x
	if (s->x > 0) {
		if (t.x > 0) {
			if (s->x < t.x)
				s->x = t.x;
		}
		else {
			if (s->x < -t.x)
				s->x = t.x;
		}
	}
	else {
		if (t.x > 0) {
			if (-s->x < t.x)
				s->x = t.x;
		}
		else {
			if (-s->x < -t.x)
				s->x = t.x;
		}
	}
	//y
	if (s->y > 0) {
		if (t.y > 0) {
			if (s->y < t.y)
				s->y = t.y;
		}
		else {
			if (s->y < -t.y)
				s->y = t.y;
		}
	}
	else {
		if (t.y > 0) {
			if (-s->y < t.y)
				s->y = t.y;
		}
		else {
			if (-s->y < -t.y)
				s->y = t.y;
		}
	}
	//z
	if (s->z > 0) {
		if (t.z > 0) {
			if (s->z < t.z)
				s->z = t.z;
		}
		else {
			if (s->z < -t.z)
				s->z = t.z;
		}
	}
	else {
		if (t.z > 0) {
			if (-s->z < t.z)
				s->z = t.z;
		}
		else {
			if (-s->z < -t.z)
				s->z = t.z;
		}
	}
}
//m �����@y ����
bool CXCharPlayer::Collision(CCollider3* m, CCollider3* y) {
	//CCollider3 *m = (CCollider3*)me;
	//CCollider3 *y = (CCollider3*)you;

	switch (m->mType) {
	case CCollider3::COL_CAPSULE:
		CCollider3Capsule *cc = (CCollider3Capsule*)m;
		switch (y->mType) {
		case CCollider3::COL_TRIANGLE:
			CCollider3Triangle ct = (*(CCollider3Triangle*)y).GetUpdate();
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
				UpdateSkinMatrix(matrix);
			}
			break;
		}
		break;
	}

	return false;
}
