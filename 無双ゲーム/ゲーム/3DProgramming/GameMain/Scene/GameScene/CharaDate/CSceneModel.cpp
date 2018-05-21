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
#include "../CharaDate/Enemy/Slime/CSlime.h"
#include "../CGameScene.h"



#define Char_HP_SIZE 600.0f,600.0f,0.8f,0.1f //�L������HP
/*�L�����N�^�[�̃|�W�V����*/
#define PLAYER_POS i*2,0.0f,0.0f//�v���C���[�̃|�W�V����
#define ENEMY_POS  i*3.0f,0.0f,10.0f//�G�l�~�[�̃|�W�V����

/*�p�x*/
#define ANGLE_360 360
#define ANGLE_90  90
#define ANGLE_50  50
#define ANGLE_5   5.0f
#define ANGLE_180 180.0f
/*�T�C�Y*/
#define COL_INIT_MOUSE_SIZE -DISP_X/2, DISP_Y/2, DISP_X/2, -DISP_Y/2

/*���f���̃t�@�C���ꏊ*/
/*�v���C���[*/
#define MODEL_FILE_UNITY		"x\\SDUnity\\SDUnityBoxing.x"
/*�A�j���[�V�����̃t�@�C���ꏊ*/
#define F_PL_IDLING				"x\\Anima\\Idling.x"
#define F_PL_RUN				"x\\Anima\\Run.x"
#define F_PL_RUN_ATTACK			"x\\Anima\\powerRunAttack.x"
#define F_PL_ATTACK				"x\\Anima\\Attack2.x"
#define F_PL_ATTACK_JUMP		"x\\Anima\\Ani_AttackJump.x"
#define F_PL_JUMP				"x\\Anima\\Ani_Jump.x"
#define F_PL_DAMAGE				"x\\Anima\\Ani_Damage.x"

/*�G�l�~�[*/
/*�X���C��*/
#define MODEL_FILE_SLIME		"x\\Slime\\Slime.x"//�X���C��	
#define SLIME_MAX 10//�X���C���̐�
#define SLIME_POS(i) CVector3(i * SLIME_MAX,0,i * SLIME_MAX)//�X���C���̐�
/*�A�j���[�V�����̃t�@�C���ꏊ*/
#define F_SLI_IDLING			"x\\Slime\\Anima\\Idling.x"
#define F_SLI_RUN				"x\\Slime\\Anima\\Run.x"
#define F_SLI_ATTACK			"x\\Slime\\Anima\\Attack2.x"
#define F_SLI_JUMP				"x\\Slime\\Anima\\Ani_Jump.x"
#define F_SLI_DAMAGE			"x\\Slime\\Anima\\Ani_Damage.x"

/*lag���p*/
#define LAG_SIZE 0.1f //0�C1�b��lag���p
/*�p�b�N�̏����ʒu*/
#define PUCK_INIT_POS 0.0f,0.0f,-10.0f
/*�ÓI������*/
CXCharPlayer *CSceneModel::mpPlayer;

/*���ׂẴ��f���L�����폜*/
void CSceneModel::ModelAllKill(){
	CTaskManager::GetInstance()->AllKill();
}

/*�R���X�g���N�^*/
CSceneModel::CSceneModel() :mMouseInitCount(0.0f),mLagTime(0.0f){


}

/*�f�X�g���N�^*/
CSceneModel::~CSceneModel(){
	

}

/*�v���C���[�ǉ�����*/
void CSceneModel::PlayerAdd(){
	/*�v���C���[*/
	mModPlayer.Load(MODEL_FILE_UNITY);
	/*�A�j���[�V�����ǉ�����*/
	for (int i = 0; i < CTask::E_STATE_ARRAY; i++)
	{
		switch (i)
		{
		case CTask::E_IDLING:
			mModPlayer.AddAnimationSet(F_PL_IDLING);//�ҋ@�ǉ�_0 
			break;
		case CTask::E_RUN:
			mModPlayer.AddAnimationSet(F_PL_RUN);//����ǉ�
			break;
		case CTask::E_RUN_ATTACK:
			mModPlayer.AddAnimationSet(F_PL_RUN_ATTACK);//����U��
			break;
		case CTask::E_ATTACK:
			mModPlayer.AddAnimationSet(F_PL_ATTACK);//�U���ǉ�_2 
			break;
		case CTask::E_JUMP:
			mModPlayer.AddAnimationSet(F_PL_JUMP);//�W�����v�ǉ�
			break;
		case CTask::E_DMGM:
			mModPlayer.AddAnimationSet(F_PL_DAMAGE);//�_���[�W
			break;
		}
	}

	CXCharPlayer *pl = new CXCharPlayer(); //new�쐬

	pl->Init(&mModPlayer);
	CTaskManager::GetInstance()->Add(pl);//�^�X�N�ɒǉ�
	mpPlayer = pl; //����p
}

/*�G�l�~�[�ǉ�����(�X���C��)*/
void CSceneModel::SlimeAdd(){
	/*�R�s�[�p*/
	CModelX *temp = &mModSlime;
	/*�v���C���[*/
	temp->Load(MODEL_FILE_SLIME);
	/*�A�j���[�V�����ǉ�����*/
	for (int i = 0; i < CTask::E_STATE_ARRAY; i++)
	{
		switch (i)
		{
		case CTask::E_IDLING:
			temp->AddAnimationSet(F_SLI_IDLING);//�ҋ@�ǉ�_0 
			break;
		case CTask::E_RUN:
			temp->AddAnimationSet(F_SLI_RUN);//����ǉ�
			break;
		case CTask::E_ATTACK:
			temp->AddAnimationSet(F_SLI_ATTACK);//�U���ǉ�_2 
			break;
		case CTask::E_JUMP:
			temp->AddAnimationSet(F_SLI_JUMP);//�W�����v�ǉ�
			break;
		case CTask::E_DMGM:
			temp->AddAnimationSet(F_SLI_DAMAGE);//�_���[�W
			break;
		}
	}

	CSlime *sl[SLIME_MAX];
	for (int i = 0; i < SLIME_MAX; i++)
	{
		/*�C���X�^���X�쐬*/
		sl[i] = new CSlime();
		sl[i]->Init(temp);
		sl[i]->mPosition = SLIME_POS(i);
		CTaskManager::GetInstance()->Add(sl[i]);//�^�X�N�ɒǉ�
	}
}

void CSceneModel::Init() {
	mMouseInitCount = 0.0f;							//�}�E�X�������ʒu�ɖ߂�܂ł̎���
	mLagTime = 0.0f;								//lag�ɂ��o�O�������

	CVector3 mPosition;								//�ʒu�@

	/*�v���C���[������*/
	PlayerAdd();
	/*�G�l�~�[*/
	SlimeAdd();//�X���C��


}

void CSceneModel::Update() {
	/*lag���*/
	if (!CConvenient::Time(&mLagTime, LAG_SIZE)){
		CMouse::GetInstance()->mLeftFlag = false;
	}

	CTaskManager::GetInstance()->AllUpdate();
}

void CSceneModel::Render() {
	CTaskManager::GetInstance()->AllRender();
}

void CSceneModel::UpdateEffect(){
	CTaskManager::GetInstance()->AllBillboardRender();
}