#include <Windows.h>
#include "CSceneModel.h"
#include "../../../Task/CTaskManager.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CKey.h"
#include "../../../Collision/CCollisionManager.h"
#include "../Map/CMap.h"
#include "../../../Collision/CCollision2D.h"
#include "../../../Key/CMouse.h"
#include "../../../Convenient/CConvenient.h"
#include "CXCharEnemy.h"
#include "../CGameScene.h"
#include "../Map/Goal/CXGoal.h"
#include "../Puck/CXPuck.h"


#define Char_HP_SIZE 600.0f,600.0f,0.8f,0.1f //�L������HP
/*�L�����N�^�[�̃|�W�V����*/
#define PLAYER_POS i*2,0.0f,0.0f//�v���C���[�̃|�W�V����
#define ENEMY_POS i*3.0f,0.0f,10.0f//�G�l�~�[�̃|�W�V����
/*�J�����̈ʒu*/
#define CAMERA_OFFSET 0.0f, 0.5f, 4.0f //�J�����ʒu�v���C���[����̑��Έʒu
#define CAMERA_POS CVector3(mCharcter->mPosition.x,mCharcter->mPosition.y+2.3f,mCharcter->mPosition.z)
/*�p�x*/
#define ANGLE_360 360
#define ANGLE_90  90
#define ANGLE_50  50
#define ANGLE_5   5.0f
#define ANGLE_180 180.0f
/*�T�C�Y*/
#define COL_INIT_MOUSE_SIZE -DISP_X/2, DISP_Y/2, DISP_X/2, -DISP_Y/2
/*�J����*/
#define ANGLE_SPEED 3.0f//�J�����X�s�[�h
#define CAMERA_IF_DIVIDE  50//�J�����X�s�[�h�����p
#define CAMERA_DIVIDE  10//�J�����X�s�[�h�����p
#define ARRIVAL_TIME 0.1f//�҂�����

/*���f���̃t�@�C���ꏊ*/
#define MODEL_FILE_UNITY			"x\\SDUnity\\SDUniEriHammer.x"
//#define MODEL_FILE_SD_ELIZABETH		"x\\ElizabethWarren\\ElizabethSDWeapon.x"
#define MODEL_FILE_ELIZABETH		"x\\ElizabethWarren\\ElizabethSD.x"
#define MODEL_FILE_PUCK				"x\\Puck\\Puck.x"
#define MODEL_FILE_GOAL				"x\\Goal\\goal.x"
/*�A�j���[�V�����̃t�@�C���ꏊ*/
#define ANIMA_FILE_IDLE				"x\\Anima\\Ani_Idle2.x"
#define ANIMA_FILE_ATTACK_RUN		"x\\Anima\\Ani_AttackRun.x"
#define ANIMA_FILE_RUN				"x\\Anima\\Ani_Run.x"
#define ANIMA_FILE_ATTACK_IDLE		"x\\Anima\\Ani_AttackIdle.x"
#define ANIMA_FILE_ATTACK_INIT		"x\\Anima\\Ani_AttackInit.x"
#define ANIMA_FILE_ATTACK			"x\\Anima\\Ani_Attack.x"
#define ANIMA_FILE_ATTACK_JUMP		"x\\Anima\\Ani_AttackJump.x"
#define ANIMA_FILE_JUMP				"x\\Anima\\Ani_Jump.x"
/*lag���p*/
#define LAG_SIZE 0.1f //0�C1�b��lag���p
/*�p�b�N�̏����ʒu*/
#define PUCK_INIT_POS 0.0f,0.0f,-10.0f
/*�ÓI������*/
CXCharPlayer *CSceneModel::mCharcter;
CVector3 CSceneModel::mRotation;
CXPuck *CSceneModel::mpPuck;
CXGoal *CSceneModel::mpGoalPlayer;

/*�R���X�g���N�^*/
CSceneModel::CSceneModel() :mMouseInitCount(0.0f),mLagTime(0.0f){
//	mCharcter = new CXCharPlayer();

}

/*�f�X�g���N�^*/
CSceneModel::~CSceneModel(){
	//P_DELETE(mCharcter);

}
/*�v���C���[�ǉ�����*/
void CSceneModel::CPlayerAdd(CVector3 PlayerPos, CModelX *model){
	CXCharPlayer *pl = new CXCharPlayer(); //new�쐬

	pl->Init(model);
	pl->mPosition = PlayerPos;//�|�W�V�������߂�

	CCollisionManager::GetInstance()->Add(CTask::E_TAG_PLAYER, pl->mpCBLeg);//�����蔻��ǉ�
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_PLAYER, pl->mpCBBody);//�����蔻��ǉ�
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_WEAPON, pl->mpCBWeapon);//�����蔻��ǉ�
	mModelTaskManager.Add(pl);//�^�X�N�ɒǉ�
	mCharcter = pl; //����p
}

/*�G�l�~�[�ǉ�����*/
void CSceneModel::CEnemyAdd(CVector3 EnemyPos, CModelX *model){

	CXCharEnemy *ene = new CXCharEnemy();//�쐬

	ene->Init(model);
	ene->mPosition = EnemyPos;
	/*�����蔻��ǉ�����*/
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ENEMY, ene->mpCBLeg);//�����蔻��ǉ�
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ENEMY, ene->mpCBBody);
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_WEAPON,ene->mpCBWeapon);
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ATTACK_INIT_RANGE, ene->mpCBAttackInitBox);
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ATTACK_RANGE, ene->mpCBAttackBox);
	mModelTaskManager.Add(ene);
}
/*�p�b�N�ǉ�����*/
void CSceneModel::CPuckAdd(CVector3 PuckPos, CModelX *model){
	
	CXPuck *puck = new CXPuck();//�쐬
	puck->Init(model);
	puck->mPosition = PuckPos;
	/*�����蔻��ǉ�*/
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_PUCK, puck->mpCBSphere);
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_PUCK, puck->mpCBRefBox);
	mModelTaskManager.Add(puck);
	mpPuck = puck;//�A�N�Z�X�p�ɓ����
}
/*�S�[���v���C���[�ǉ�����*/
void CSceneModel::CGoalPlayerAdd(CVector3 GoalPos, CModelX *model){
	CXGoal *goal = new CXGoal();//�쐬
	goal->Init(model,GoalPos);
	/*�v���C���[�̏ꍇ�������Ɍ�����*/
	goal->mRotation.y -= ANGLE_180;
	/*�����_�[���Ԍ��߂�*/
	goal->ePriority = CTask::E_GOAL_PLAYER;
	/*�����蔻��ǉ�����*/
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_GOAL_PLAYER, goal->mCBBox);
	mModelTaskManager.Add(goal);
	mpGoalPlayer = goal;
}

/*�S�[���G�l�~�[�ǉ�����*/
void CSceneModel::CGoalEnemyAdd(CVector3 GoalPos, CModelX *model){
	CXGoal *goal = new CXGoal();//�쐬
	goal->Init(model, GoalPos);
	/*�����_�[���Ԍ��߂�*/
	goal->ePriority = CTask::E_GOAL_PLAYER;
	/*�����蔻��ǉ�����*/
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_GOAL_ENEMY, goal->mCBBox);
	mModelTaskManager.Add(goal);
}

void CSceneModel::Init() {
	mMouseInitCount = 0.0f;							//�}�E�X�������ʒu�ɖ߂�܂ł̎���
	mLagTime = 0.0f;								//lag�ɂ��o�O�������
	mCharcter = 0;									//�A�N�Z�X�p �L�����N�^�[����Ɏg������ �ÓI��
	mRotation = CVector3(0.0f, 0.0f, 0.0f);		//�L�����N�^�[����Ɏg������ �ÓI��

	CVector3 mPosition;								//�ʒu�@

	//mSaveMousePos = CVector2(0.0f, 0.0f);			//�}�E�X�̃|�W�V����
	//mColInitMouse.position = CVector2(0.0f, 0.0f);//�}�E�X�̏����ʒu


	/*�v���C���[*/
	mModel.Load(MODEL_FILE_UNITY);
	/*�A�j���[�V�����ǉ�����*/
	for (int i = 0; i < CTask::E_STATE_ARRAY; i++)
	{
		switch (i)
		{
		case CTask::E_IDLE:
			mModel.AddAnimationSet(ANIMA_FILE_IDLE);//�ҋ@�ǉ�_0 
			break;
		case CTask::E_ATTACK_RUN:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK_RUN);//���߂Ȃ��瑖��ǉ�
			break;
		case CTask::E_RUN:
			mModel.AddAnimationSet(ANIMA_FILE_RUN);//����ǉ�
			break;
		case CTask::E_ATTACK_IDLE:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK_IDLE);//�U�����߃A�C�h���ǉ�
			break;
		case CTask::E_ATTACK_INIT:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK_INIT);//�U�����߃A�C�h���ǉ�
			break;
		case CTask::E_ATTACK:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK);//�U���ǉ�_2 
			break;
		case CTask::E_JUMP:
			mModel.AddAnimationSet(ANIMA_FILE_JUMP);//�W�����v�ǉ�
			break;
		case CTask::E_ATTACK_JUMP:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK_JUMP);//�U�����W�����v�ǉ� 
			break;
		case CTask::E_DMGM:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK_JUMP);//�W�����v�ǉ� 
			break;
		}
	}

	CPlayerAdd(CMap::PlayerFirstPos(), &mModel);
	/*�G�l�~�[*/
	mModelE.Load(MODEL_FILE_ELIZABETH);

	/*�A�j���[�V�����ǉ�����*/
	for (int i = 0; i < CTask::E_STATE_ARRAY; i++)
	{
		switch (i)
		{
		case CTask::E_IDLE:

			mModelE.AddAnimationSet(ANIMA_FILE_IDLE);//�ҋ@�ǉ�_0 
			break;
		case CTask::E_ATTACK_RUN:
			mModelE.AddAnimationSet(ANIMA_FILE_ATTACK_RUN);//���߂Ȃ��瑖��ǉ�
			break;
		case CTask::E_RUN:
			mModelE.AddAnimationSet(ANIMA_FILE_RUN);//����ǉ�
			break;
		case CTask::E_ATTACK_IDLE:
			mModelE.AddAnimationSet(ANIMA_FILE_ATTACK_IDLE);//�U�����߃A�C�h���ǉ�
			break;
		case CTask::E_ATTACK_INIT:
			mModelE.AddAnimationSet(ANIMA_FILE_ATTACK_INIT);//�U�����߃A�C�h���ǉ�
			break;
		case CTask::E_ATTACK:
			mModelE.AddAnimationSet(ANIMA_FILE_ATTACK);//�U���ǉ�_2 
			break;
		case CTask::E_JUMP:
			mModelE.AddAnimationSet(ANIMA_FILE_JUMP);//�W�����v�ǉ�
			break;
		case CTask::E_ATTACK_JUMP:
			mModelE.AddAnimationSet(ANIMA_FILE_ATTACK_JUMP);//�U�����W�����v�ǉ� 
			break;
		case CTask::E_DMGM:
			mModelE.AddAnimationSet(ANIMA_FILE_ATTACK_JUMP);//�W�����v�ǉ� 
			break;
		}
	}

	CEnemyAdd(CMap::EnemyFirstPos(), &mModelE);
	/*�p�b�N*/
	mModelPuck.Load(MODEL_FILE_PUCK);						//���[�h
	//mModelPuck.Load(MODEL_FILE_GOAL);						//���[�h
	mModelPuck.AddAnimationSet(ANIMA_FILE_IDLE);			//�������
	CPuckAdd(CVector3(PUCK_INIT_POS), &mModelPuck);				//�p�b�N�ǉ�����
	/*�S�[���v���C���[*/
	mModelGoal.Load(MODEL_FILE_GOAL);						//���[�h
	mModelGoal.AddAnimationSet(ANIMA_FILE_IDLE);			//�������
	CGoalPlayerAdd(CMap::GoalPlayerFirstPos(), &mModelGoal);			//�p�b�N�ǉ�����
	/*�S�[���G�l�~�[*/
	mModelEGoal.Load(MODEL_FILE_GOAL);						//���[�h
	mModelEGoal.AddAnimationSet(ANIMA_FILE_IDLE);			//�������
	CGoalEnemyAdd(CMap::GoalEnemyFirstPos(), &mModelEGoal);	//�p�b�N�ǉ�����

	///*�}�E�X�̃T�C�Y*/
	//mColInitMouse.SetVertex(COL_INIT_MOUSE_SIZE);
	//mColInitMouse.SetColor(WHITE_COLOR);
}

void CSceneModel::Update() {
	if (CGameScene::Transition == CGameScene::E_ACTIVE){

		/*lag���*/
		if (!CConvenient::Time(&mLagTime, LAG_SIZE)){
			CMouse::mLeftFlag = false;
		}


		/*�J�����ݒ�*/
		if (CKey::push(VK_LEFT)) {//��
			mRotation.y += ANGLE_SPEED;
		}
		if (CKey::push(VK_RIGHT)) {//�E
			mRotation.y -= ANGLE_SPEED;
		}
		if (CKey::push(VK_DOWN) && mRotation.x < ANGLE_90) {//��
			mRotation.x += ANGLE_SPEED;
		}
		if (CKey::push(VK_UP) && mRotation.x > -ANGLE_90) {//��
			mRotation.x -= ANGLE_SPEED;
		}
		/*���[�e�[�V�������}�C�i�X�̏ꍇ*/
		if (mRotation.y < 0){
			mRotation.y = ANGLE_360 + mRotation.y;
		}

		///*�J�����ݒ�}�E�X*/
		//if (CMouse::mPos.x != mSaveMousePos.x && mSaveMousePos.x  > CMouse::mPos.x){//��
		//	mRotation.y += (mSaveMousePos.x - CMouse::mPos.x) / CAMERA_DIVIDE;

		//	CMouse::SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//�J�[�\�����E�B���h�E�̒��S�ɂ���

		//}
		//if (CMouse::mPos.x != mSaveMousePos.x && mSaveMousePos.x < CMouse::mPos.x){//�E
		//	mRotation.y += (mSaveMousePos.x - CMouse::mPos.x) / CAMERA_DIVIDE;

		//	CMouse::SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//�J�[�\�����E�B���h�E�̒��S�ɂ���
		//}
		//if (CMouse::mPos.y != mSaveMousePos.y && mSaveMousePos.y> CMouse::mPos.y && mRotation.x < ANGLE_50){//��
		//	mRotation.x += (mSaveMousePos.y - CMouse::mPos.y) / CAMERA_DIVIDE;


		//	CMouse::SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//�J�[�\�����E�B���h�E�̒��S�ɂ���
		//}
		//if (CMouse::mPos.y != mSaveMousePos.y && mSaveMousePos.y   < CMouse::mPos.y && mRotation.x > -ANGLE_50){//��
		//	mRotation.x += (mSaveMousePos.y - CMouse::mPos.y) / CAMERA_DIVIDE;


			CMouse::SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//�J�[�\�����E�B���h�E�̒��S�ɂ���
		//}
		///*���S���炻���Ɛ^�񒆂ɖ߂�����*/
		//if (CCollision2D::Collision2D(mColInitMouse, CMouse::mRect)){
		//	/*���Ԃ��o�Ɛ^�񒆂ɖ߂�*/
		//	if (CConvenient::Time(&mMouseInitCount, ARRIVAL_TIME) &&
		//		mSaveMousePos.x == CMouse::mPos.x &&
		//		mSaveMousePos.y == CMouse::mPos.y){ //0.1�b�ԓ����Ȃ����
		//		CMouse::SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//�J�[�\�����E�B���h�E�̒��S�ɂ���
		//		mMouseInitCount = 0;//0�ɖ߂�

		//	}
		//}
		//else
		//{
		//	CMouse::SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//�J�[�\�����E�B���h�E�̒��S�ɂ���
		//}

		//mSaveMousePos = CMouse::mPos;//�Z�[�u����

		mModelTaskManager.AllUpdate();




	}
	
}

void CSceneModel::Render() {
	mRotation.y =abs(mRotation.y);

	//printf("%f\n", mRotation.y);
	int mRotPercent = mRotation.y;
	//�J�����ʒu�v���C���[����̑��Έʒu
	CVector3 cp(CAMERA_OFFSET);
	//�J�����̉�]�s��
	CMatrix44 mat;
	//�L�����N�^�[�̈ʒu����J�����ʒu���v�Z
	CVector3 SavePos = CAMERA_POS;

	/*�R�l��*/
	cp.z *= -1;
	mRotPercent %= ANGLE_360;
	CVector3 rot = mRotation;
	mRotation.y = mRotPercent;//�R�U�O�ɂ���
	rot.y = mRotPercent;
	mat.rotationX(rot.x);
	mat.rotationY(rot.y);

	//�J��������]������
	cp = cp * mat;
	cp += SavePos;
	//�J�����̎��_(eye)�ƒ��ӓ_(pos)��ݒ�

	MainCamera.pos[0] = SavePos.x;
	MainCamera.pos[1] = SavePos.y;
	MainCamera.pos[2] = SavePos.z;
	MainCamera.eye[0] = cp.x;
	MainCamera.eye[1] = cp.y;
	MainCamera.eye[2] = cp.z;


	mModelTaskManager.AllRender();

}

void CSceneModel::UpdateEffect(){
	mModelTaskManager.AllBillboardRender();
}