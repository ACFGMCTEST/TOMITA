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
#include <math.h>
#include "../../../Collision/CCollisionManager.h"
#include "../../../Collision/CCollision.h"


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

/*�W�����v�̃X�s�[�h*/
#define JUMP_SPEED 0.7f//�W�����v����X�s�[�h
#define JUMP_MOVE(vel) vel * 0.7f//�W�����v�ړ� 


/*�����̉�]���鑬��*/
#define TURN_SPEED 10

CXCharPlayer::CXCharPlayer() : mVelocity(0.0f), mFlagKnockback(false), mRotCount(0),
mGoCount(0), mGoPos(0), mGoPosSize(0), mGravitTime(GRA_INIT_TIME_COUNT), mFlagJump(false), mFlagSlpoe(false), mAdjust(){
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

	//mpModel->SetColor(RED_COLOR);//���f���̐F����
	mPower = ATTACK_POWER;//�U����

	mVelocity = SPEED_RUN;

	PosUpdate();
	mPrevPos = mPosition;

	//CCollisionManager::GetInstance()->Add(CTask::E_TAG_PLAYER, mpCBLeg);//�����蔻��ǉ�
	//CCollisionManager::GetInstance()->Add(CTask::E_TAG_PLAYER, mpCBBody);//�����蔻��ǉ�
	//CCollisionManager::GetInstance()->Add(CTask::E_TAG_WEAPON, mpCBWeapon);//�����蔻��ǉ�


}

/*��������֐�*/
void CXCharPlayer::MoveSpeed(){

	if (mState == E_ATTACK_RUN)	mVelocity = SPEED_ATTACK_RUN_SKILL;

	if (mState == E_RUN)		mVelocity = SPEED_RUN_SKILL;

	/*�U��������*/
	if (mState == E_ATTACK_IDLING || mState == E_ATTACK_RUN) mVelocity = SPEED_ATTACK_RUN;
	/*�U���O*/
	if (mState == E_RUN)mVelocity = SPEED_RUN;

	/*�W�����v���ňړ����Ă���ꍇ�����@����̂�*/
	if (mVelocity == SPEED_ATTACK_RUN_SKILL || mVelocity == SPEED_ATTACK_RUN ||
		mVelocity == SPEED_RUN_SKILL || mVelocity == SPEED_RUN){
		mVelocity -= SPEED_JUMP_DOWN;
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
	mPrevPos = mPosition;
}

/*�����̐���*/
bool CXCharPlayer::DirectionAnima(){

	return true;
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

		Move(mForward, mVelocity);//�ړ�������
	}


}

/*�������Ƃ��̏���
forward = �����ݒ�
velocity = ��
*/
void CXCharPlayer::Move(const CVector3 &forward, float velocity){

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
}

/*�o�H�T���@���ؗp*/
void CXCharPlayer::CostMapping(int x, int z, int count, int *CostMap, bool FastFlag){
	//count++;
	////if (CMap::mNowMapDate[z][x] == CMap::E_BUIL || CMap::mNowMapDate[z][x] == CMap::E_HOLE) /*��Q������*/
	//if (CMap::mNowMapDate[z][x] == CMap::E_GOAL_6 ) /*��Q������*/
	//{
	//	return;//�ǂ���������
	//}
	//if (CostMap[z*CMap::mMapX + x] == -1){//�����l�Ȃ�
	//	CostMap[z*CMap::mMapX + x] = count;//�J�E���g��
	//}
	//else if (CostMap[z*CMap::mMapX + x] > count){
	//	CostMap[z*CMap::mMapX + x] = count;//�J�E���g��
	//}
	//else return;
	//if (x < CMap::mMapX - 1) CostMapping(x + 1, z, count, CostMap, false);
	//if (x > 0) CostMapping(x - 1, z, count, CostMap, false);
	//if (z < CMap::mMapZ - 1)CostMapping(x, z + 1, count, CostMap, false);
	//if (z > 0)CostMapping(x, z - 1, count, CostMap, false);
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
		if (mState == E_ATTACK_RUN){
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

/*�X�V����*/
void CXCharPlayer::Update(){
	mAdjust = CVector3();
	mPrevPos = mPosition;



		///*��񉟂����Ƃ�*/
		if (AttackInitKey.Onces(KEY_ATTACK)){//K�{�^����
			AnimaState(E_ATTACK_INIT); //���߂̂������������Ăяo��
		}
		/*�������̎�*/
		else if (CKey::push(KEY_ATTACK)){
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



	if (mFlagJump)Jump();//�t���O�������Ă���Ƃ��W�����v
	Gravity();/*�d��*/
	MoveSpeed();
	PosUpdate();//�|�W�V�������X�V


	//�����蔻��X�V
	//mpCBBody->Update();
	//mpCBWeapon->Update();
	//mpCBLeg->Update();

	//��Ԃɂ��A�j���[�V�����ω�
	switch (mState)
	{
	case E_IDLING://����

		ChangeAnimation(E_IDLING, true, ANIMA_SPEED);
		mCountKnockBack = 0;
		break;
	case E_RUN://����
		ChangeAnimation(E_RUN, true, ANIMA_SPEED_RUN);
		break;
	case E_ATTACK_RUN://�U������
		ChangeAnimation(E_ATTACK_RUN, true, ANIMA_SPEED_RUN);
		break;
	case E_ATTACK_INIT:
		ChangeAnimation(E_ATTACK_INIT, false, ANIMA_SPEED_ATTCK);
		break;
	case E_ATTACK://�U��
		ChangeAnimation(E_ATTACK, false, ANIMA_SPEED_ATTCK);
		//�A�j���[�V�������I��
		if (mAnimationTime >
			mpModel->mAnimationSet[mAnimationIndex]->mMaxTime){
		}
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
	AnimaState(E_ATTACK_IDLING);
	AnimaState(E_IDLING);
}



/*Render*/
void CXCharPlayer::Render() {
	//27
	//HP�o�[�̐ݒ�
	//mHpBar.mPosition = mPosition;
	//mHpBar.mPosition.y += 1.8f;
	//mHpBar.Update();	//�X�V
	//mHpBar.Render();	//�`��
	if (mAdjust == CVector3()) {
		CModelXS::Render();
	}
	else {
		mPosition = mPosition + mAdjust;
		CMatrix44 rot_y, pos, matrix;
		//��]�s��̍쐬
		rot_y.rotationY(mRotation.y);

		//�ړ��s����v�Z����
		pos.translate(mPosition);
		//��]�ړ��s������߂�
		matrix = pos * rot_y;

		UpdateSkinMatrix(matrix);
		CModelXS::Render();
	}
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


/*�W�����v�֐�*/
void  CXCharPlayer::Jump(){
	Move(mForward, JUMP_MOVE(mVelocity));
	float jumpVilocity = JUMP_SPEED - GRAVITY(mGravitTime);//��������
	/*�W�����v��0���傫���ꍇ*/
	mPosition.y += jumpVilocity;


}

/*��ɂ��������̔���*/
void CXCharPlayer::ColSlope(){

	///*��(��)�ƍ�(��)���������Ă���ꍇ*/
	//if (CCollision::CollSphereBox(mpCBLeg->mColSphere,slope.mpColBox->mObb)){
	//	//mPosition = slope.MiddlePos(mPosition);
	//}
	mFlagSlpoe = true;
	ColGround();

}

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



#define SETADJUST(m, t)  {\
if (m.x > 0) {\
if (t.x > 0) {\
	if (m.x < t.x) \
	m.x = t.x; \
} \
else {\
		if (m.x < -t.x) \
		m.x = t.x; \
	} \
} \
else {\
			if (t.x > 0) {\
				if (-m.x < t.x) \
				m.x = t.x; \
			} \
				else {\
				if (-m.x < -t.x) \
				m.x = t.x; \
				} \
		} \
				if (m.y > 0) {\
				if (t.y > 0) {\
					if (m.y < t.y) \
					m.y = t.y; \
				} \
				else {\
						if (m.y < -t.y) \
						m.y = t.y; \
					} \
				} \
				else  {\
							if (t.y > 0) {\
								if (-m.y < t.y) \
								m.y = t.y; \
							} \
							else {\
									if (-m.y < -t.y) \
									m.y = t.y; \
								} \
						} \
						if (m.z > 0) {\
							if (t.z > 0) {\
								if (m.z < t.z) \
								m.z = t.z; \
							} \
							else {\
									if (m.z < -t.z) \
									m.z = t.z; \
								} \
						} \
						else {\
										if (t.z > 0) {\
											if (-m.z < t.z) \
											m.z = t.z; \
										} \
										else {\
												if (-m.z < -t.z) \
												m.z = t.z; \
											} \
									} \
} \
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
				SETADJUST(mAdjust, cc->mAdjust);
			}
			break;
		}
		break;
	}

	return false;
}