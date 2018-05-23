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
#include "State\RunAttack\CStatePlayerRunAttack.h"
/*�����蔻��*/
#include "../../../../Collision/ColType/CColCapsule.h"
#include "../../../../Collision/ColType/CColTriangle.h"

/*����*/
#define FORWARD_JUMP  0.0f,1.0f,1.0f//�W�����v

/*�����蔻��̐ݒ�l(main)*/
#define COL_RADIUS 0.6f//���a
#define COL_POS CVector3(0,1.5f,0),CVector3(0,-1.0f,0)//�|�W�V�����J�v�Z��
#define COL_MATRIX(string) &mpCombinedMatrix[model->FindFrame(string)->mIndex]//�}�g���b�N�X
/*�r*/
#define COL_ATTACK_RADIUS 0.4f
#define COL_RIGHT_POS CVector3(0.0f,0.5f,0.0f)
#define COL_LEFT_POS  CVector3(0.0f,0.5f,0.0f)
#define COL_LEFT_MATRIX(string)  &mpCombinedMatrix[model->FindFrame (string)->mIndex]//�}�g���b�N�X
#define COL_RIGHT_MATRIX(string) &mpCombinedMatrix[model->FindFrame(string)->mIndex]//�}�g���b�N�X


/*HP�o�[�̐ݒ�l*/
#define HP_BAR_POS CVector3(mPosition.x,mPosition.y + 1.8f,mPosition.z)
#define HP_BAR_SIZE -0.4f, 0.4f, -0.1f, 0.0f

/*�����̉�]���鑬��*/
#define TURN_SPEED 10

CXCharPlayer::CXCharPlayer() : mVelocity(0.0f), mFlagKnockback(false), mRotCount(0),
mGravitTime(GRA_INIT_TIME_COUNT), mFlagJump(false), mAdjust()
{
	eName = CTask::E_PLAYER;
	mForward = CVector3(FORWARD);
	mpParent = this;
};
/*
Init
���f���ƏՓ˔���̐ݒ���s��
*/
void CXCharPlayer::Init(CModelX *model) {
	mStateMachine = (std::make_unique<CStateMachine>());
	// �������ɃX�e�[�g�́u�o�^���v
	// ��������StateBase���p�������N���X��shared_ptr�I�u�W�F�N�g�𐶐�
	mStateMachine->Register(PL_STATE_ATTACK, std::make_shared<CStatePlayerAttack>(), this);
	mStateMachine->Register(PL_STATE_IDLING, std::make_shared<CStatePlayerIdling>(), this);
	mStateMachine->Register(PL_STATE_RUN, std::make_shared<CStatePlayerRun>(), this);
	mStateMachine->Register(PL_STATE_JUMP, std::make_shared<CStatePlayerJump>(), this);
	mStateMachine->Register(PL_STATE_RUN_ATTACK, std::make_shared<CStatePlayerRunAttack>(), this);
	// �ŏ��̃X�e�[�g��o�^���Ŏw��
	mStateMachine->SetStartState(PL_STATE_IDLING);

	//���f���̐ݒ�
	CModelXS::Init(model);

	//�J�v�Z���@�L�����N�^�S��
	new CColCapsule(this, COL_POS, COL_RADIUS, COL_MATRIX("metarig_hips"));
	mpMatrix = COL_MATRIX("metarig_hips");
	//���́@�r.�E
	new CColSphere(this, COL_RIGHT_POS, COL_ATTACK_RADIUS, COL_RIGHT_MATRIX("metarig_forearm_L"));
	//���́@�r.��
	new CColSphere(this, COL_LEFT_POS, COL_ATTACK_RADIUS, COL_LEFT_MATRIX("metarig_forearm_R"));

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

}



/*Render*/
void CXCharPlayer::Render() {
	CModelXS::Render();
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



void CXCharPlayer::SetAdjust(CVector3 *s, const CVector3 &t) {
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

/*�ʃo�[�W����*/
void CXCharPlayer::Collision(CColSphere *youSphere,CColSphere *sphere) {
	CVector3 savePos = sphere->mPos;//�v�Z�p
	float lengthX = mPosition.x - savePos.x;  //���ƃ|�W�V�����̋���
	float lengthY = mPosition.y - savePos.y;  //���ƃ|�W�V�����̋���
	float lengthZ = mPosition.z - savePos.z;  //���ƃ|�W�V�����̋���
	//Box��X�����������߂�
	CVector3 vx = *youSphere->mpCombinedMatrix * VEC_RIGHT;
	//Box��Y�����������߂�
	CVector3 vy = *youSphere->mpCombinedMatrix * VEC_TOP;
	//Box��Z�����������߂�
	CVector3 vz = *youSphere->mpCombinedMatrix * VEC_FRONT;
	//�l�p�`���狅�ւ̃x�N�g�������߂�
	CVector3 vectorBS = savePos - youSphere->mPos;
	//�l�p�`���狅�ցA�l�p�`��X���ɑ΂��钷���Ƃ̍������߂�
	float dx = sphere->mRadius + youSphere->mRadius - fabs(vx.Dot(vectorBS));
	//�l�p�`���狅�ցA�l�p�`��Y���ɑ΂��钷���Ƃ̍������߂�
	float dy = sphere->mRadius + youSphere->mRadius - fabs(vy.Dot(vectorBS));
	//�l�p�`���狅�ցA�l�p�`��Z���ɑ΂��钷���Ƃ̍������߂�
	float dz = sphere->mRadius + youSphere->mRadius - fabs(vz.Dot(vectorBS));

	//�Փ˂��Ă��邩���肷��
	if (dx > 0.0f && dy > 0.0f && dz > 0.0f) {
		if (dx > dy) {
			if (dy > dz) {
				//Z���Ŗ߂�
				if (vz.Dot(vectorBS) > 0.0f) {
					mPosition = savePos + vz * dz;
				}
				else {
					mPosition = savePos - vz * dz;
				}
			}
			else {
				/*�����{�f�B�̎����� && �W�����v���Ă��Ȃ��Ƃ�*/
				//Y���Ŗ߂�
				if (vy.Dot(vectorBS) > 0.0f) {
					mPosition = savePos + vy * dy;
				}
				else {
					mPosition = savePos - vy * dy;
				}
			}
		}
		else{
			if (dx > dz) {

				//Z���Ŗ߂�
				if (vz.Dot(vectorBS) > 0.0f) {
					mPosition = savePos + vz * dz;
				}
				else {
					mPosition = savePos - vz * dz;
				}
			}
			else {

				//X���Ŗ߂�
				if (vx.Dot(vectorBS) > 0.0f) {
					mPosition = savePos + vx * dx;
				}
				else {
					mPosition = savePos - vx * dx;
				}
			}
		}
	}
	mPosition.x += lengthX;
	mPosition.y += lengthY;
	mPosition.z += lengthZ;

	/*�}�g���b�N�X�����X�V*/
	CMatrix44 rot_y, pos, matrix;
	//��]�s��̍쐬
	rot_y.rotationY(mRotation.y);

	//�ړ��s����v�Z����
	pos.translate(mPosition);
	//��]�ړ��s������߂�
	matrix = pos * rot_y;
	//���_�f�[�^�̍X�V
	CModelXS::MatrixUpdate(matrix);

}


/*�J�v�Z���������蔻��*/
void CXCharPlayer::CapsuleCol(CColCapsule *cc, CColBase* y){
	CColTriangle ct(false);//�O�p�`�̓����蔻��
	CColCapsule  caps(false);//�J�v�Z���̓����蔻��
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
			CModelXS::Update(matrix);
		}
		break;
		/*���肪�J�v�Z���̏ꍇ*/
	case CColBase::COL_CAPSULE:
		//caps = (*(CColCapsule*)y).GetUpdate();//�J�v�Z���ɂ���
		//
		//if (CCollision::CollisionCapsule(cc, &caps)){
		//	/*����*/
		//	CColSphere TopColA(cc->mRadius, cc->mV[0], cc->mpCombinedMatrix);
		//	CColSphere TopColB(caps.mRadius, caps.mV[0], caps.mpCombinedMatrix);
		//	CColSphere BottomColA(cc->mRadius, cc->mV[1], cc->mpCombinedMatrix);
		//	CColSphere BottomColB(caps.mRadius, caps.mV[1], caps.mpCombinedMatrix);
		//	/*�����蔻��*/
		//	Collision(TopColA, TopColB);
		//};
	


		break;
	};
}
/*���̓��̓����蔻��*/
void CXCharPlayer::SphereCol(CColSphere *sphere, CColBase *y){
	CColSphere  sph;//���̓����蔻��
	/*����̃^�C�v�������f*/
	switch (y->mType) {
		/*���肪���̏ꍇ*/
	case CColBase::COL_SPHEPE:
		sph = (*(CColSphere*)y).GetUpdate();
		/*�����蔻��v�Z�@*/
		if (CCollision::CollisionShpere(sph,*sphere) && sph.mpParent->eName == CTask::E_SLIME){
			printf("���������Ă���G�l�~�[�̔ԍ�(%d)\n", sph.mpParent->mNumber);
			Collision(&sph,sphere);
		}

	};
}


//m �����@y ����
bool CXCharPlayer::Collision(CColBase* m, CColBase* y) {
	//CColBase *m = (CColBase*)me;
	//CColBase *y = (CColBase*)you;
	CColCapsule cc(false);
	CColSphere sph;
	/*�����̃^�C�v���������f*/
	switch (m->mType) {

	case CColBase::COL_CAPSULE://�����̓����蔻�肪�J�v�Z���̏ꍇ
		cc = *(CColCapsule*)m;//�J�v�Z���ɂ���
		CapsuleCol(&cc, y);//�J�v�Z���̓����蔻��
		break;
		
	case CColBase::COL_SPHEPE:
		sph = *(CColSphere*)m;//����
		SphereCol(&sph, y);//���̂̓����蔻��
		
	};

	return false;
}
