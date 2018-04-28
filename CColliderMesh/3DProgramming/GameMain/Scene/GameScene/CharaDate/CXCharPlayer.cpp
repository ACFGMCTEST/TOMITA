#include "CXCharPlayer.h"
#include "windows.h"
#include "../../../Key/CKey.h"
#include "CSceneModel.h"
#include "../../../../Define/Define.h"
#include "../Map/CMap.h"
#include "../../../Key/CMouse.h"
#include "../../../Convenient/CConvenient.h"
#include "../UI/CScoreBoard.h"
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
#define OBB_WEAPON_SIZE new float[]{0.4f, 0.7f, 0.4f}
/*��*/
#define OBB_LEG_SIZE 0.3f
#define OBB_LEG_POS CVector3(0.0f,-1.0f,0.0f)

/*HP�o�[�̐ݒ�l*/
#define HP_BAR_POS CVector3(mPosition.x,mPosition.y + 1.8f,mPosition.z)
#define HP_BAR_SIZE -0.4f, 0.4f, -0.1f, 0.0f

/*�W�����v�̃X�s�[�h*/
#define JUMP_SPEED 0.7f//�W�����v����X�s�[�h
#define JUMP_MOVE(vel) vel * 0.7f//�W�����v�ړ� 



CXCharPlayer::CXCharPlayer() : mVelocity(0.0f), mFlagKnockback(false), mRotCount(0),
mGoCount(0), mGoPos(0), mGoPosSize(0), mGravitTime(GRA_INIT_TIME_COUNT), mFlagJump(false),mFlagSlpoe(false){
	mForward = CVector3(FORWARD);
	mpParent = this;

	mState = E_IDLE;
	ePriority = CTask::E_PLAYER;

};

/*�����蔻�菉����*/
void CXCharPlayer::ColInit(){
	/*�����蔻��C���X�^���X�쐬*/
	mpCBBody = new CCollider(CTask::E_COL_SPHEPE);
	mpCBWeapon = new CCollider(CTask::E_COL_BOX);
	mpCBLeg = new CCollider(CTask::E_COL_SPHEPE);

	mpColCapsule = new CColCapsule();
	mpColCapsule3 = new CCollider3Capsule();

	/*�y�A�����g�ݒ�*/
	mpCBBody->mpParent = this;
	mpCBWeapon->mpParent = this;
	mpCBLeg->mpParent = this;
}

/*
 Init
 ���f���ƏՓ˔���̐ݒ���s��
*/
void CXCharPlayer::Init(CModelX *model) {
	ColInit();

	//���f���̐ݒ�
	CModelXS::Init(model);
	
	/*�̂̓����蔻��*/
	mpCBBody->SetShere(OBB_SPHERE_BODY_SIZE, OBB_SPHERE_BODY_POS
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);
	/*����̓����蔻��*/
	mpCBWeapon->SetBoxOBB(OBB_WEAPON_POS, OBB_WEAPON_SIZE
		, &mpCombinedMatrix[model->FindFrame("metarig_WeaponHandle")->mIndex]);
	/*���̓����蔻��*/
	mpCBLeg->SetShere(OBB_LEG_SIZE, OBB_LEG_POS
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);

//	mpColCapsule->Init(this, CVector3(0.0f, 0.7f, 0.0f), CVector3(0.0f, -0.7f, 0.0f), 0.5f, CVector3(0.0f, 0.0f, 0.0f)
	mpColCapsule->Init(this, CVector3(0.0f, 1.2f, 0.0f), CVector3(0.0f, -1.2f, 0.0f), 0.5f, CVector3(0.0f, 0.0f, 0.0f)
		//		, &mpCombinedMatrix[model->FindFrame("Root")->mIndex]);
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);
	mpColCapsule3->Init(this, CVector3(0.0f, 1.2f, 0.0f), CVector3(0.0f, -1.2f, 0.0f), 0.5f
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);

	mHammerEffect.Init(CEffect2D::E_STATUS::E_HAMMER);

	mpCBBody->SetColor(BLUE_COLOR);//�{�f�B�[�̐F����
	//mpModel->SetColor(RED_COLOR);//���f���̐F����
	mPower = ATTACK_POWER;//�U����

	mVelocity = SPEED_RUN;

	PosUpdate();
	mPrevPos = mPosition;

//	CCollisionManager::GetInstance()->Add(CTask::E_TAG_PLAYER, mpCBLeg);//�����蔻��ǉ�
//	CCollisionManager::GetInstance()->Add(CTask::E_TAG_PLAYER, mpCBBody);//�����蔻��ǉ�
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_WEAPON, mpCBWeapon);//�����蔻��ǉ�

	CCollisionManager::GetInstance()->Add(CTask::E_TAG_PLAYER, mpColCapsule);//�����蔻��ǉ�
	CCollisionManager3::GetInstance()->Add(mpColCapsule3);//�����蔻��ǉ�
}

/*��������֐�*/
void CXCharPlayer::MoveSpeed(){

	/*�X�L��������*/
	if (CScoreBoard::mFlagSkill0&&CItem::status==CItem::WEAPON0){
		if(mState == E_ATTACK_RUN)	mVelocity = SPEED_ATTACK_RUN_SKILL;

		if (mState == E_RUN)		mVelocity = SPEED_RUN_SKILL;
	}
	else{
		/*�U��������*/
		if (mState == E_ATTACK_IDLE || mState == E_ATTACK_RUN) mVelocity = SPEED_ATTACK_RUN;
		/*�U���O*/
		if (mState == E_RUN)mVelocity = SPEED_RUN;
	}
	/*�W�����v���ňړ����Ă���ꍇ�����@����̂�*/
	if (mVelocity == SPEED_ATTACK_RUN_SKILL || mVelocity == SPEED_ATTACK_RUN || 
		mVelocity == SPEED_RUN_SKILL || mVelocity == SPEED_RUN){
		mVelocity -= SPEED_JUMP_DOWN;
	}
	/*�����Ă��Ȃ��ꍇ*/
	if (mState == E_IDLE || mState == E_ATTACK_IDLE){ mVelocity = 0; }
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
/*�ȈՈړ��t���O*/
bool CXCharPlayer::FlagMove(){
	if (CKey::push('A') || CKey::push('D') || CKey::push('S') || CKey::push('W')){
		if (mState != E_ATTACK && mState != E_ATTACK_INIT){//�A�C�h�����������Ă��邩
			return true;
		}
	}
	return false;
}

/*��]����܂ňړ����Ȃ�*/
bool CXCharPlayer::FlagRotMove(int angle){
	int middle = abs((int)mRotation.y) % ANGLE_360;
	
	angle = (abs((int)CSceneModel::mRotation.y) + angle) % ANGLE_360;

	if (middle == angle){
		return true;
	}
	return false;
}


bool CXCharPlayer::FlagRight(){
	float Rot;
	if (mRotation.y <= ANGLE_180){
		Rot =mRotation.y;
	}
	else{
		Rot = mRotation.y - ANGLE_360;
	}

	if (Rot - CSceneModel::mRotation.y < ANGLE_90){

		return true;
	}
	else{
		return false;
	}
}
/*�����̐���*/
bool CXCharPlayer::DirectionAnima(){

	return true;
}

bool CXCharPlayer::FlagLeft(){
	
	float Rot;
	if (mRotation.y <= ANGLE_180){
		Rot = CSceneModel::mRotation.y - mRotation.y;
	}
	else{
		Rot = CSceneModel::mRotation.y - mRotation.y - ANGLE_360;
	}

	if (Rot < -ANGLE_90){
		return true;
	}
	else{
	
		return false;
	}
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

/*�����Ƃ��̊֐�*/
void CXCharPlayer::MyMove(){
	if (mRotation.y >= ANGLE_360){
		mRotation.y = 0;
	}
	/*�U������Ƃ��J�����̕����Ɍ���*/
	if (mState == E_ATTACK || mState == E_ATTACK_INIT)	mRotation = CSceneModel::mRotation;


	if (CKey::push('A')){//���Ɉړ�
		///*��]*/
		//if (FlagLeft())PlusRot(ANGLE_5);//��]�l���
		//else 
			mRotation.y = ((int)CSceneModel::mRotation.y + ANGLE_90) % 360;

	}
	if (CKey::push('D')){//�E�Ɉړ�
		mRotation.y = ((int)CSceneModel::mRotation.y + ANGLE_270) % 360;
	}




	if (CKey::push('W')){//�O�Ɉړ�

		mRotation.y = CSceneModel::mRotation.y;


		if (CKey::push('A')){//���Ɉړ�
			///*��]*/
			//if (FlagLeft())PlusRot(ANGLE_5);//��]�l���
			//else 
			mRotation.y += ANGLE_45;

		}
		if (CKey::push('D')){//�E�Ɉړ�
			mRotation.y -= ANGLE_45;
		}


	}





	if (CKey::push('S')){

		mRotation.y = CSceneModel::mRotation.y;
		mRotation.y -= ANGLE_180;//���Ό����ɂ���


		if (CKey::push('A')){//���Ɉړ�
			mRotation.y -= ANGLE_45;

		}
		if (CKey::push('D')){//�E�Ɉړ�
			mRotation.y += ANGLE_45;

		}

	}


	/*�X�e�[�^�X�ݒ�*/
	if (FlagMove() && mCountKnockBack == 0){//Knockback���Ă��Ȃ����
		/*���鋗��;��]�l;����̃A�j���ɐ؂�ւ�*/
		AnimaState(E_ATTACK_RUN); //���߂Ȃ��瑖��
		AnimaState(E_RUN);
	}
	else{
		AnimaState(E_ATTACK_IDLE);
		AnimaState(E_IDLE);
	}
	MoveSpeed();//�ړ��ʕω��֐�
	if (FlagMove() && mState != E_IDLE && mState != E_ATTACK_IDLE && mState != E_ATTACK_INIT &&
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
}

/*�o�H�T���@���ؗp*/
void CXCharPlayer::CostMapping(int x, int z, int count,int *CostMap, bool FastFlag){
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

/*�o�H�T���@�S�[�����玩���̏ꏊ��*/
void CXCharPlayer::SearchGoPos(int x, int z, int count, int *Arrysize, const int CostMap[], CVector4 **Pos, bool FastFlag){
	if (CostMap[z*CMap::mMapX + x] > 0){//�R�X�g�̔ԍ��ɒl�������Ă���ꍇ
		if (FastFlag){
			CVector4 dummy;
			(*Pos) = &dummy;
			(*Pos) = new CVector4[CostMap[z*CMap::mMapX + x]](); //FastFlag�@���߂̎�����true
			*Arrysize = CostMap[z*CMap::mMapX + x] - 1;//�z�񐔋L��
		}

		(*Pos)[count] = CVector4((x - CMap::mMapX / 2) * (MAPCHIP_SIZE * 2), 0, (z - CMap::mMapZ / 2) * (MAPCHIP_SIZE * 2));//�ꏊ�ۑ�
		count++;

		if (CostMap[z*CMap::mMapX + x] == 1){
			return;//�R�X�g���O�������炱��ȉ��̏������s��Ȃ�
		}

#define  IF_NOLIMIT(z,x) CMap::mNowMapDate[z][x] != 1 &&\
	z >= 0 && x >= 0 && z < CMap::mMapZ && x < CMap::mMapX //��Q�����Ȃ��Ƃ�
		/*�R�X�g��������Ⴂ�Ƃ���ɍs������*/
		/*��̒i*/
		if (CostMap[(z - 1)*CMap::mMapX + (x - 1)] + 1 == CostMap[z * CMap::mMapX + x]){ //����
			SearchGoPos(x - 1, z - 1, count, Arrysize, CostMap, Pos, false);
			return;
		}
		if (CostMap[(z - 1) * CMap::mMapX + x] + 1 == CostMap[z*CMap::mMapX + x]){ //��
			SearchGoPos(x, z - 1, count, Arrysize, CostMap, Pos, false);
			return;
		}
		if (CostMap[(z - 1) * CMap::mMapX + x + 1] + 1 == CostMap[z*CMap::mMapX + x]){ //�E��
			SearchGoPos(x + 1, z - 1, count, Arrysize, CostMap, Pos, false);
			return;
		}
		/*�^�񒆂̒i*/
		if (CostMap[z * CMap::mMapX + x - 1] + 1 == CostMap[z * CMap::mMapX + x]){ //��
			SearchGoPos(x - 1, z, count, Arrysize, CostMap, Pos, false);
			return;
		}
		if (CostMap[z * CMap::mMapX + x + 1] + 1 == CostMap[z * CMap::mMapX + x]){ //�E
			SearchGoPos(x + 1, z, count, Arrysize, CostMap, Pos, false);
			return;
		}
		/*���̒i*/
		if (CostMap[(z + 1) * CMap::mMapX + x - 1] + 1 == CostMap[(z * CMap::mMapX) + x]){ //����
			SearchGoPos(x - 1, z + 1, count, Arrysize, CostMap, Pos, false);
			return;
		}
		if (CostMap[(z + 1) * CMap::mMapX + x] + 1 == CostMap[z * CMap::mMapX + x]){ //��
			SearchGoPos(x, z + 1, count, Arrysize, CostMap, Pos, false);
			return;
		}
		if (CostMap[(z + 1) * CMap::mMapX + x + 1] + 1 == CostMap[(z * CMap::mMapX) + x]){ //�E��
			SearchGoPos(x + 1, z + 1, count, Arrysize, CostMap, Pos, false);
			return;
		}
	}
	return;
}

/*�o�H�T������������*/
void CXCharPlayer::SearchGoPosInit(){
	/*mGoPos�̏�����*/
	if (mGoPos != 0){ //�l�������Ă���Ȃ�
		delete[] mGoPos;
		mGoPos = nullptr;
	}
	mGoCount = 0;//���ɖ߂�
	mGoPosSize = 0;
}

/*�A�^�b�N�̃X�e�[�^�X*/
bool CXCharPlayer::FlagAttackState(){
	return (mState == E_ATTACK_IDLE || mState == E_ATTACK_INIT || mState == E_ATTACK_RUN);
}

/*�ȈՃA�j���[�V�����؂�ւ�*/
void CXCharPlayer::AnimaState(ESTATE state){





	switch (state)
	{
		/*�ҋ@��*/
	case CTask::E_IDLE:
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
		if (!mFlagJump && mState != E_ATTACK_IDLE && mState != E_ATTACK_JUMP &&
			mState != E_ATTACK_RUN && mState != E_ATTACK){
			mState = state;
		}

		break;


		/*�U�����ߑ��蒆*/
	case CTask::E_ATTACK_RUN:
		/*�A�^�b�N�A�C�h�����ł���ړ����Ă���ꍇ*/
		if (mState == E_ATTACK_IDLE){
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
		if (mState == E_ATTACK_INIT || mState == E_ATTACK_IDLE || mState == E_ATTACK_RUN || mState == E_ATTACK_JUMP)
			mState = state;
		break;


		/*�U���ҋ@��*/
	case CTask::E_ATTACK_IDLE:
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

/*�X�V����*/
void CXCharPlayer::Update(){
	mPrevPos = mPosition;

	//�L�����N�^�[���I�΂�Ă�����̂����f
	if (CSceneModel::mCharcter == this){

		//�X�L�������I�I�I
		if (CKey::push(KEY_SKILL)){
			if (CScoreBoard::skillgage >= mGageLimit && !CScoreBoard::mFlagSkill0){
				CScoreBoard::mFlagSkill0 = true;
				mSkillTime = mGageLimit;
			}
		}
	
		if (CScoreBoard::mFlagSkill0&&mSkillTime>0.0f){
			CScoreBoard::skillgage -= mGageDecrease;
			mSkillTime -= mGageDecrease;
		}
		else{
			CScoreBoard::mFlagSkill0 = false;
		}


		///*��񉟂����Ƃ�*/
		if (AttackInitKey.Onces(KEY_ATTACK)){//K�{�^����
			AnimaState(E_ATTACK_INIT); //���߂̂������������Ăяo��
		}
		/*�������̎�*/
		else if (CKey::push(KEY_ATTACK)){
			//�X�L���Q�[�W����
			if (CScoreBoard::skillgage <= mGageLimit && !CScoreBoard::mFlagSkill0){
				CScoreBoard::skillgage += mGageDecrease;
			}
			AnimaState(E_ATTACK_IDLE);
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
	//mpCBBody->Update();
	//mpCBWeapon->Update();
	//mpCBLeg->Update();

	//��Ԃɂ��A�j���[�V�����ω�
	switch (mState)
	{
	case E_IDLE://����
		
		ChangeAnimation(E_IDLE, true, ANIMA_SPEED);
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
	case E_ATTACK_IDLE:
		ChangeAnimation(E_ATTACK_IDLE, true, ANIMA_SPEED_ATTCK);
		HammerUp();//Hammer�̗��߂鏈��
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
	AnimaState(E_ATTACK_IDLE);
	AnimaState(E_IDLE);
}

/*Hammer�̗��߂鏈��*/
void CXCharPlayer::HammerUp(){
	/*�n���}�[�̃A�j������*/

	//�f�t�H���g���
	if (CItem::status == CItem::WEAPON0){
		mPower += POWER_UP;//���߂Ă����ƍU���͂��オ��
		if (mPower >= ATTACK_POWER_MAX){
			mPower = ATTACK_POWER_MAX;
			mHammerEffect.EnableAnima();//�A�j���[�V������L���ɂ���
		}
		else{
			mHammerEffect.SizeUp(POWER_UP);//�T�C�Y��傫������
			mpCBWeapon->SizeUP(HAMMER_SIZE_UP);
		}
	}
	//����1
	if (CItem::status == CItem::WEAPON1){
		mPower += W_0_POWER_UP;//���߂Ă����ƍU���͂��オ��
		if (!CScoreBoard::mFlagSkill0){//�X�L������������Ă��Ȃ��Ƃ�
			if (mPower >= ATTACK_W0_POWER_MAX){
				mPower = ATTACK_W0_POWER_MAX;
				mHammerEffect.EnableAnima();//�A�j���[�V������L���ɂ���
			}
			else{
				mHammerEffect.SizeUp(POWER_UP);//�T�C�Y��傫������
				mpCBWeapon->SizeUP(POWER_UP);
			}
		}
		else if (CScoreBoard::mFlagSkill0){//�X�L��������
			if (mPower >= ATTACK_WS0_POWER_MAX){
				mPower = ATTACK_WS0_POWER_MAX;
				mHammerEffect.EnableAnima();//�A�j���[�V������L���ɂ���
			}
			else{
				mHammerEffect.SizeUp(POWER_UP);//�T�C�Y��傫������
				mpCBWeapon->SizeUP(POWER_UP);
			}
		}
	}
	//����2
	if (CItem::status == CItem::WEAPON2){
		if (mPower >= ATTACK_W1_POWER_MAX){
			mPower = ATTACK_W1_POWER_MAX;
			mHammerEffect.EnableAnima();//�A�j���[�V������L���ɂ���
			if (!CScoreBoard::mFlagSkill0){
				mPower += W_1_POWER_UP;
			}//�T�C�Y��傫������
			else if (CScoreBoard::mFlagSkill0){
				mPower += WS_1_POWER_UP;
			}
		}
		else{
			if (!CScoreBoard::mFlagSkill0){
				mHammerEffect.SizeUp(POWER_UP);
				mpCBWeapon->SizeUP(POWER_UP);
			}
			else if (CScoreBoard::mFlagSkill0){
				mHammerEffect.SizeUp(WS_1_POWER_UP);
				mpCBWeapon->SizeUP(POWER_UP);
			}
		}
	}

	//����3
	if (CItem::status == CItem::WEAPON3){
		mPower += W_2_POWER_UP;
		if (mPower >= ATTACK_W2_POWER_MAX){
			mPower = ATTACK_W2_POWER_MAX;
			mHammerEffect.EnableAnima();//�A�j���[�V������L���ɂ���
		}
		else{
			mHammerEffect.SizeUp(W_2_POWER_UP);//�T�C�Y��傫������
			mpCBWeapon->SizeUP(W_2_POWER_UP);
		}
	}
	//����4
	mPower += W_3_POWER_UP;
	if (CItem::status == CItem::WEAPON4){
		if (mPower >= ATTACK_W3_POWER_MAX){
			mPower = ATTACK_W3_POWER_MAX;
			mHammerEffect.EnableAnima();//�A�j���[�V������L���ɂ���
		}
		else{
			mHammerEffect.SizeUp(W_3_POWER_UP);//�T�C�Y��傫������
			mpCBWeapon->SizeUP(W_3_POWER_UP);
		}
	}

}

/*Hammer�̏���������*/
void CXCharPlayer::HammerInit(){
	mHammerEffect.NoTexInit();
	mHammerEffect.DisableAnima();//�A�j���[�V�����𖳌��ɂ���
	mPower = ATTACK_POWER;//�߂�
	/*����̓����蔻��*/
	mpCBWeapon->SetBoxOBB(OBB_WEAPON_POS, OBB_WEAPON_SIZE
		, &mpCombinedMatrix[mpModel->FindFrame("metarig_WeaponHandle")->mIndex]);
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
	mpColCapsule->Render();
	mpColCapsule3->Render();
#endif
}

/*�G�t�F�N�g�̕`�揈��*/
void CXCharPlayer::BillboardRender(){
	CVector3 pos = HAMMER_EFFECT_POS;
	pos = pos * mpCombinedMatrix[mpModel->FindFrame("metarig_WeaponHandle")->mIndex];//�}�g���b�N�X����v�Z
	mHammerEffect.Update(pos);//�|�W�V�����v�Z
	mHammerEffect.Render();

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
	SearchGoPosInit();
}

/*�����蔻��Ăяo��
���̏ꏊ�ɖ߂����߂̊֐�
*/
bool CXCharPlayer::Collision(const COBB &box, const CColSphere &sphere) {
	return Collision(&box, &sphere);
}

bool CXCharPlayer::Collision(const COBB *box, const CColSphere *sphere) {

	CVector3 savePos = sphere->mPos;//�v�Z�p

	float lengthX = mPosition.x - savePos.x;  //���ƃ|�W�V�����̋���
	float lengthY = mPosition.y - savePos.y;  //���ƃ|�W�V�����̋���
	float lengthZ = mPosition.z - savePos.z;  //���ƃ|�W�V�����̋���

	//Box��X�����������߂�
	CVector3 vx = box->mMatrixRotation * VEC_RIGHT;
	//Box��Y�����������߂�
	CVector3 vy = box->mMatrixRotation * VEC_TOP;
	//Box��Z�����������߂�
	CVector3 vz = box->mMatrixRotation * VEC_FRONT;

	vx = box->mAxis[0];
	vy = box->mAxis[1];
	vz = box->mAxis[2];

	//�l�p�`���狅�ւ̃x�N�g�������߂�
	CVector3 vectorBS = savePos - box->mPos;

	//�l�p�`���狅�ցA�l�p�`��X���ɑ΂��钷���Ƃ̍������߂�
	float dx = sphere->mRadius + box->mLength[0] - fabs(vx.Dot(vectorBS));
	//�l�p�`���狅�ցA�l�p�`��Y���ɑ΂��钷���Ƃ̍������߂�
	float dy = sphere->mRadius + box->mLength[1] - fabs(vy.Dot(vectorBS));
	//�l�p�`���狅�ցA�l�p�`��Z���ɑ΂��钷���Ƃ̍������߂�
	float dz = sphere->mRadius + box->mLength[2] - fabs(vz.Dot(vectorBS));

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
				if (sphere == &mpCBLeg->mColSphere){
					ColGround();//�n�ʂɂ��������̏���
					//Y���Ŗ߂�
					if (vy.Dot(vectorBS) > 0.0f) {
						mPosition = savePos + vy * dy;
					}
					else {
						mPosition = savePos - vy * dy;
					}
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
	else {
		return false;
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
	//mpCBBody->Update();
	//mpCBWeapon->Update();
	//mpCBLeg->Update();

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
			you->eTag == E_TAG_SLOPE ||
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
		if (you->eTag == E_TAG_BOX ||
			you->eTag == E_TAG_GROUND) {
			if (you->eColTag == E_COL_BOX)
				return Collision((COBB*)&you->mObb, (CColSphere*)&me->mColSphere);
		}
	}

	return false;
}

bool CXCharPlayer::Collision(CTask* me, CTask* you) {
	CCollider3 *m = (CCollider3*)me;
	CCollider3 *y = (CCollider3*)you;

	switch (m->mType) {
	case CCollider3::COL_CAPSULE:
		CCollider3Capsule *cc = (CCollider3Capsule*)me;
		switch (y->mType) {
		case CCollider3::COL_TRIANGLE:
			CCollider3Triangle ct = *(CCollider3Triangle*)y;
			ct.Update();
			if (CCollision::IntersectTriangleCapsule3(ct.mV[0], ct.mV[1], ct.mV[2],
				cc->mV[0], cc->mV[1], cc->mRadius, &cc->mAdjust)) {
				/*
//				if (cross == CVector3())
//					return false;
				//				if (you->eTag == E_TAG_BOX)
				*/
				ColGround();//�n�ʂɂ��������̏���
				mPosition = mPosition + cc->mAdjust;
			}
			break;
		}
		break;
	}

	return false;
}
