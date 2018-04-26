#include "CXCharPlayer.h"
#include "windows.h"
#include "../../../Key/CKey.h"
#include "CSceneModel.h"
#include "../../../../Define/Define.h"
#include "../Map/CMap.h"
#include "../../../Key/CMouse.h"
#include "../../../Convenient/CConvenient.h"
#include "../../GameScene/Map/CMap.h"
#include "../../ItemScene/CItem.h"
#include "../../../Camera/CCamera.h"
#include "../../../Convenient/CConvenient.h"
#include <math.h>


/*����*/
#define FORWARD_JUMP  0.0f,1.0f,1.0f//�W�����v

/*�����̉�]���鑬��*/
#define TURN_SPEED 10
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

/*�W�����v�̃X�s�[�h*/
#define JUMP_SPEED 0.7f//�W�����v����X�s�[�h
#define JUMP_MOVE(vel) vel * 0.7f//�W�����v�ړ� 

/*���������x*/
#define MOVE_ACC SPEED_RUN/10

CXCharPlayer::CXCharPlayer() : mVelocity(0.0f), mFlagKnockback(false), mRotCount(0),
mGoCount(0), mGoPos(0), mGoPosSize(0), mGravitTime(GRA_INIT_TIME_COUNT), mFlagJump(false),mFlagSlpoe(false){
	mForward = CVector3(FORWARD);
	mpParent = this;


	mState = E_IDLING;
	ePriority = CTask::E_PLAYER;

	

};

/*�����蔻�菉����*/
void CXCharPlayer::ColInit(){
	/*�����蔻��C���X�^���X�쐬*/
	mpCBBody = new CCollider(CTask::E_COL_SPHEPE);
	mpCBLeg = new CCollider(CTask::E_COL_SPHEPE);
	
	/*�y�A�����g�ݒ�*/
	mpCBBody->mpParent = this;
	mpCBLeg->mpParent = this;
}

/*Init = ���f���ƏՓ˔���̐ݒ���s��*/
void CXCharPlayer::Init(CModelX *model) {
	ColInit();

	//���f���̐ݒ�
	CModelXS::Init(model);
	
	/*�̂̓����蔻��*/
	mpCBBody->SetShere(OBB_SPHERE_BODY_SIZE, OBB_SPHERE_BODY_POS
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);
	/*���̓����蔻��*/
	mpCBLeg->SetShere(OBB_LEG_SIZE, OBB_LEG_POS
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);


	mpCBBody->SetColor(BLUE_COLOR);//�{�f�B�[�̐F����
	//mpModel->SetColor(RED_COLOR);//���f���̐F����
	mPower = ATTACK_POWER;//�U����

	mVelocity = SPEED_RUN;

	PosUpdate();
	mPrevPos = mPosition;

}

/*��������֐�*/
float VelocityMax = SPEED_RUN;//���E�l
void CXCharPlayer::MoveSpeed(){


	/*�X�L��������*/
	
		/*�U��������*/
		if (mState == E_ATTACK_IDLING || mState == E_ATTACK_RUN) VelocityMax = SPEED_ATTACK_RUN;
		/*�U���O*/
		if (mState == E_RUN)VelocityMax = SPEED_RUN;
	
	/*���E�l�܂ŉ���*/
	if (VelocityMax > mVelocity){
		mVelocity += MOVE_ACC;//����
	}
	else{
		mVelocity = VelocityMax;//���E�l�ɂ���
	}

	/*�W�����v���ňړ����Ă���ꍇ�����@����̂�*/
	if (mState == E_ATTACK_JUMP || mState == E_JUMP){
		if (mVelocity == SPEED_ATTACK_RUN_SKILL || mVelocity == SPEED_ATTACK_RUN ||
			mVelocity == SPEED_RUN_SKILL || mVelocity == SPEED_RUN){
			mVelocity -= SPEED_JUMP_DOWN;
		}
	}
	/*�����Ă��Ȃ��ꍇ*/
	if (mState == E_IDLING || mState == E_ATTACK_IDLING){ mVelocity = 0; }
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
}
/*�ȈՈړ��t���O*/
bool CXCharPlayer::FlagMove(){
	if (CKey::push('A') || CKey::push('D') || CKey::push('S') || CKey::push('W')){
		if (mState != E_ATTACK && mState != E_ATTACK_INIT){//�A�C�h�����������Ă��邩
			return true;
		}
	}
	return false;
}


/*�����Ƃ��̊֐�*/
void CXCharPlayer::MyMove(){
	
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






	/*�X�e�[�^�X�ݒ�*/
	if (FlagMove() && mCountKnockBack == 0){//Knockback���Ă��Ȃ����
		/*���鋗��;��]�l;����̃A�j���ɐ؂�ւ�*/
		AnimaState(E_ATTACK_RUN); //���߂Ȃ��瑖��
		AnimaState(E_RUN);
	}
	else{
		AnimaState(E_ATTACK_IDLING);
		AnimaState(E_IDLING);
	}
	MoveSpeed();//�ړ��ʕω��֐�
	if (FlagMove() && mState != E_IDLING && mState != E_ATTACK_IDLING && mState != E_ATTACK_INIT &&
		mState != E_JUMP && mState != E_ATTACK_JUMP){//���莞�͈ړ�
		//�i�s�����ݒ�@z���v���X���O���̃��f�� ��ɏ���Ă��Ȃ��Ƃ�
		if (!mFlagSlpoe)mForward = CVector3(FORWARD);
		//else mForward = CVector3(0.0f, 0.5f, 1.0f);

		/*���false��*/
		mFlagSlpoe = false;

		Move(mForward,mVelocity);//�ړ�������
	}


}

/*�������Ƃ��̏���
forward = �����ݒ�
velocity = ��
*/
void CXCharPlayer::Move(const CVector3 &forward,float velocity){

	CMatrix44 rot_y, pos, matrix;
	CVector3 moveForward = forward;//�Q�Ƃł�����Ȃ��̂�
	//��]�s��̍쐬
	rot_y.rotationY(mRotation.y);
	///�i�s�������v�Z
	moveForward = forward * rot_y;
	//�ړ�������
	mPosition += moveForward * velocity;
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
	AnimaState(E_ATTACK_IDLING);
	AnimaState(E_IDLING);
}



/*�A�^�b�N�̃X�e�[�^�X*/
bool CXCharPlayer::FlagAttackState(){
	return (mState == E_ATTACK_IDLING || mState == E_ATTACK_INIT || mState == E_ATTACK_RUN);
}

/*�ȈՃA�j���[�V�����؂�ւ�*/
void CXCharPlayer::AnimaState(ESTATE state){





	switch (state)
	{
		/*�ҋ@��*/
	case CTask::E_IDLING:
		/*�U���łȂ��ꍇ �W�����v�o�Ȃ��ꍇ*/
		if (!FlagAttackState() && !mFlagJump){
			if (mState == E_RUN || mState == E_ATTACK && mAnimationTime > mpModel->mAnimationSet[mAnimationIndex]->mMaxTime)
				mState = state;
		}
		/*�W�����v�̏ꍇ �t���[�����Ō�̎��͏��������Ă���*/
		if (mState == E_JUMP && mAnimationTime > mpModel->mAnimationSet[mAnimationIndex]->mMaxTime){
			mState = state;
		}
		//DAMAGE���I����Ă���ꍇ
		if (mState == E_DMGM && mAnimationTime > mpModel->mAnimationSet[mAnimationIndex]->mMaxTime){
			mState = state;
		}
		break;

		/*���蒆*/
	case CTask::E_RUN:
		if (!mFlagJump && mState != E_ATTACK_IDLING && mState != E_ATTACK_JUMP &&
			mState != E_ATTACK_RUN && mState != E_ATTACK){
			mState = state;
		}

		break;


		/*�U�����ߑ��蒆*/
	case CTask::E_ATTACK_RUN:
		/*�A�^�b�N�A�C�h�����ł���ړ����Ă���ꍇ*/
		if (mState == E_ATTACK_IDLING){
			mState = state;
		}
		break;


		/*�U��������*/
	case CTask::E_ATTACK_INIT:

		/*�A�^�b�N�����Ă��Ȃ���*/
		if (!FlagAttackState() && mState != E_ATTACK && mState != E_ATTACK_JUMP){
				mState = state;
		}

		break;


		/*�U����*/
	case CTask::E_ATTACK:
		if (mState == E_ATTACK_INIT || mState == E_ATTACK_IDLING || mState == E_ATTACK_RUN || mState == E_ATTACK_JUMP)
			mState = state;
		break;


		/*�U���ҋ@��*/
	case CTask::E_ATTACK_IDLING:
		/*�U���������I�������*/
		if (mState == E_ATTACK_INIT && mAnimationTime > mpModel->mAnimationSet[mAnimationIndex]->mMaxTime){
			mState = state;
		}
		/*�����Ă���Ƃ�*/
		if(mState == E_ATTACK_RUN){
			mState = state;
		}
		/*�A�^�b�N�W�����v���I�������Ƃ�*/
		if (mState == E_ATTACK_JUMP && mAnimationTime > mpModel->mAnimationSet[mAnimationIndex]->mMaxTime){
			mState = state;
		}
		break;


		/*�U���W�����v*/
	case CTask::E_ATTACK_JUMP:
		if (FlagAttackState() && mState != E_JUMP && mState != E_ATTACK){
			mState = state;
		}
		break;


		/*�W�����v*/
	case CTask::E_JUMP:

		if (!FlagAttackState() && mState != E_ATTACK_JUMP && mState != E_ATTACK){
			mState = state;
		}
		break;


		/*�_���[�W*/
	case CTask::E_DMGM:
		mState = state;
		break;
	default:
		break;
	}
}
/*�L�����N�^�[��]���������������ɉ�]����*/
int CXCharPlayer::MoveRotation(int angle){

	/*�E���*/
	int turnRight = angle - mRotation.y;
	/*�ߏ�]��*/
	LIMIT_ANGLE(turnRight);
	/*�����*/
	int turnLeft = ANGLE_360  - turnRight;

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
	else{return mRotation.y - TURN_SPEED;
	}
	
	
}

/*�X�V����*/
void CXCharPlayer::Update(){
	mPrevPos = mPosition;
	mFlagSlpoe = false;
	//�L�����N�^�[���I�΂�Ă�����̂����f && DAMAGE��������Ă��Ȃ��ꍇ
	if (mState != E_DMGM){

		//�X�L�������I�I�I
		if (CKey::push(KEY_SKILL)){
			mSkillTime = mGageLimit;
		}
	

		///*��񉟂����Ƃ�*/
		if (AttackInitKey.push(KEY_ATTACK) || AttackInitKey.push(KEY_ATTACK2) || CMouse::GetInstance()->mOneLeftFlag){//K�{�^����
			AnimaState(E_ATTACK_INIT); //���߂̂������������Ăяo��
		}
		/*�������̎�*/
		else if (CKey::push(KEY_ATTACK) || CKey::push(KEY_ATTACK2) || CMouse::GetInstance()->mLeftFlag){
			//�X�L���Q�[�W����
			AnimaState(E_ATTACK_IDLING);
		}
		/*�������Ƃ�*/
		else{
			AnimaState(E_ATTACK);
		}

		MyMove();//��������

		/*�W�����v*/
		if (CKey::once(KEY_JUMP) || mFlagJump){
			mFlagJump = true;

			AnimaState(E_ATTACK_JUMP);
			AnimaState(E_JUMP);
		}
	
		
	}

	if (mFlagJump)Jump();//�t���O�������Ă���Ƃ��W�����v
	Gravity();/*�d��*/
	MoveSpeed();
	PosUpdate();//�|�W�V�������X�V


	//�����蔻��X�V
	mpCBBody->Update();
	mpCBLeg->Update();
	//��Ԃɂ��A�j���[�V�����ω�
	switch (mState)
	{
	case E_IDLING://����
		
		ChangeAnimation(E_IDLING, true, ANIMA_SPEED_IDOL);
		mCountKnockBack = 0;
		break;
	case E_RUN://����
		ChangeAnimation(E_RUN, true, ANIMA_SPEED_RUN);
		break;
	case E_ATTACK_RUN://�U������
		ChangeAnimation(E_ATTACK_RUN, true, ANIMA_SPEED_RUN);
		HammerUp();//Hammer�̗��߂鏈��
		
		break;
	case E_ATTACK_INIT:
		ChangeAnimation(E_ATTACK_INIT, false, ANIMA_SPEED_ATTCK);
		break;
	case E_ATTACK://�U��
		ChangeAnimation(E_ATTACK, false, ANIMA_SPEED_ATTCK);
		//�A�j���[�V�������I��
		if (mAnimationTime >
			mpModel->mAnimationSet[mAnimationIndex]->mMaxTime){
			HammerInit();
		}
		break;
	case E_ATTACK_IDLING:
		ChangeAnimation(E_ATTACK_IDLING, true, ANIMA_SPEED_ATTCK);
		HammerUp();//Hammer�̗��߂鏈��
		break;
	case E_JUMP:
		ChangeAnimation(E_JUMP, false, ANIMA_SPEED_JUMP);
		break;
	case E_ATTACK_JUMP:
		ChangeAnimation(E_ATTACK_JUMP, false, ANIMA_SPEED_JUMP);
		break;
	case E_DMGM://�_���[�W
		ChangeAnimation(E_DMGM, false, ANIMA_SPEED_DAMAGE);
		HammerInit();
	
		break;
	};
	AnimaState(E_ATTACK_IDLING);
	AnimaState(E_IDLING);
}

/*Hammer�̗��߂鏈��*/
void CXCharPlayer::HammerUp(){
	mPower += POWER_UP;//���߂Ă����ƍU���͂��オ��
	if (mPower >= ATTACK_POWER_MAX){
		mPower = ATTACK_POWER_MAX;
	}
	else{
	}
}

/*Hammer�̏���������*/
void CXCharPlayer::HammerInit(){
	mPower = ATTACK_POWER;//�߂�
}

/*Render*/
void CXCharPlayer::Render() {
	
	CModelXS::Render();
#ifdef _DEBUG
	mpCBBody->Render();
	mpCBLeg->Render();
#endif
}

/*�G�t�F�N�g�̕`�揈��*/
void CXCharPlayer::BillboardRender(){
	CVector3 pos = HAMMER_EFFECT_POS;
	pos = pos * mpCombinedMatrix[mpModel->FindFrame("metarig_WeaponHandle")->mIndex];//�}�g���b�N�X����v�Z

}



/*�����蔻��Ăяo��
���̏ꏊ�ɖ߂����߂̊֐�
*/
void CXCharPlayer::Collision(const COBB &box,const CColSphere &sphere) {



	CVector3 savePos = sphere.mPos;//�v�Z�p

	float lengthX = mPosition.x - savePos.x;  //���ƃ|�W�V�����̋���
	float lengthY = mPosition.y - savePos.y;  //���ƃ|�W�V�����̋���
	float lengthZ = mPosition.z - savePos.z;  //���ƃ|�W�V�����̋���


	//Box��X�����������߂�
	CVector3 vx = box.mMatrixRotation * VEC_RIGHT;
	//Box��Y�����������߂�
	CVector3 vy = box.mMatrixRotation * VEC_TOP;
	//Box��Z�����������߂�
	CVector3 vz = box.mMatrixRotation * VEC_FRONT;

	vx = box.mAxis[0];
	vy = box.mAxis[1];
	vz = box.mAxis[2];



	//�l�p�`���狅�ւ̃x�N�g�������߂�
	CVector3 vectorBS = savePos - box.mPos;


	//�l�p�`���狅�ցA�l�p�`��X���ɑ΂��钷���Ƃ̍������߂�
	float dx = sphere.mRadius + box.mLength[0] - fabs(vx.Dot(vectorBS));
	//�l�p�`���狅�ցA�l�p�`��Y���ɑ΂��钷���Ƃ̍������߂�
	float dy = sphere.mRadius + box.mLength[1] - fabs(vy.Dot(vectorBS));
	//�l�p�`���狅�ցA�l�p�`��Z���ɑ΂��钷���Ƃ̍������߂�
	float dz = sphere.mRadius + box.mLength[2] - fabs(vz.Dot(vectorBS));

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
				//if (&sphere == &mpCBLeg->mColSphere){
					ColGround();//�n�ʂɂ��������̏���
					//Y���Ŗ߂�
					if (vy.Dot(vectorBS) > 0.0f) {
						mPosition = savePos + vy * dy;
					}
					else {
						mPosition = savePos - vy * dy;
					}
				//}
			
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

	//�����蔻��X�V
	mpCBBody->Update();
	mpCBLeg->Update();
	
}
/*�ʃo�[�W����*/
void CXCharPlayer::Collision(const CColSphere &youSphere, const CColSphere &sphere) {



	CVector3 savePos = sphere.mPos;//�v�Z�p

	float lengthX = mPosition.x - savePos.x;  //���ƃ|�W�V�����̋���
	float lengthY = mPosition.y - savePos.y;  //���ƃ|�W�V�����̋���
	float lengthZ = mPosition.z - savePos.z;  //���ƃ|�W�V�����̋���


	//Box��X�����������߂�
	CVector3 vx = youSphere.mMatrixRotation * VEC_RIGHT;
	//Box��Y�����������߂�
	CVector3 vy = youSphere.mMatrixRotation * VEC_TOP;
	//Box��Z�����������߂�
	CVector3 vz = youSphere.mMatrixRotation * VEC_FRONT;



	//�l�p�`���狅�ւ̃x�N�g�������߂�
	CVector3 vectorBS = savePos - youSphere.mPos;


	//�l�p�`���狅�ցA�l�p�`��X���ɑ΂��钷���Ƃ̍������߂�
	float dx = sphere.mRadius + youSphere.mRadius - fabs(vx.Dot(vectorBS));
	//�l�p�`���狅�ցA�l�p�`��Y���ɑ΂��钷���Ƃ̍������߂�
	float dy = sphere.mRadius + youSphere.mRadius - fabs(vy.Dot(vectorBS));
	//�l�p�`���狅�ցA�l�p�`��Z���ɑ΂��钷���Ƃ̍������߂�
	float dz = sphere.mRadius + youSphere.mRadius - fabs(vz.Dot(vectorBS));

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
				//if (&sphere == &mpCBLeg->mColSphere){
					ColGround();//�n�ʂɂ��������̏���
					//Y���Ŗ߂�
					if (vy.Dot(vectorBS) > 0.0f) {
						mPosition = savePos + vy * dy;
					}
					else {
						mPosition = savePos - vy * dy;
					}
				//}

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

	//�����蔻��X�V
	mpCBBody->Update();
	mpCBLeg->Update();

}



/*�W�����v�֐�*/
void  CXCharPlayer::Jump(){
	Move(mForward, JUMP_MOVE(mVelocity));
	float jumpVilocity = JUMP_SPEED - GRAVITY(mGravitTime);//��������
	/*�W�����v��0���傫���ꍇ*/
		mPosition.y += jumpVilocity;
	

}
