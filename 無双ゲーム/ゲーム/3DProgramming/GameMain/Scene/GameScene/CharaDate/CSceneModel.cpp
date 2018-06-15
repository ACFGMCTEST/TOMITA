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

/*�L�����N�^�[*/
#include "../CharaDate/Enemy/Slime/CSlime.h"
#include "../CharaDate/Enemy/Slime/King/CKingSlime.h"

#include "../CGameScene.h"



#define Char_HP_SIZE 600.0f,600.0f,0.8f,0.1f //�L������HP
/*�L�����N�^�[�̃|�W�V����*/
#define POS_Y 10

/*�p�x*/
#define ANGLE_360 360
#define ANGLE_90  90
#define ANGLE_50  50
#define ANGLE_5   5.0f
#define ANGLE_180 180.0f
/*�T�C�Y*/
#define COL_INIT_MOUSE_SIZE -DISP_X/2, DISP_Y/2, DISP_X/2, -DISP_Y/2

/*lag���p*/
#define LAG_SIZE 0.1f //0�C1�b��lag���p
/*�ÓI������*/
CPlayer *CSceneModel::mpPlayer;

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
/*�v���C���[*/
#define MODEL_FILE_UNITY		MODEL_FILE"SDUnity\\SDUnityBoxing.x"
/*�A�j���[�V�����̃t�@�C���ꏊ*/
#define F_PL_IDLING				MODEL_FILE"SDUnity\\Anima\\Idling.x"
#define F_PL_RUN				MODEL_FILE"SDUnity\\Anima\\Run.x"
#define F_PL_RUN_ATTACK			MODEL_FILE"SDUnity\\Anima\\powerRunAttack.x"
#define F_PL_ATTACK				MODEL_FILE"SDUnity\\Anima\\Attack2.x"
#define F_PL_JUMP				MODEL_FILE"SDUnity\\Anima\\Jump.x"
#define F_PL_DAMAGE				MODEL_FILE"SDUnity\\Anima\\Damage.x"
#define F_PL_AVOID				MODEL_FILE"SDUnity\\Anima\\Avoid.x"

/*�v���C���[�ǉ�����*/
void CSceneModel::PlayerAdd(){
	/*�v���C���[*/
	mModPlayer.Load(MODEL_FILE_UNITY);
	/*�A�j���[�V�����ǉ�����*/
	for (int i = 0; i < CPlayer::E_STATE_ARRAY; i++)
	{
		switch (i)
		{
		case CPlayer::E_IDLING:
			mModPlayer.AddAnimationSet(F_PL_IDLING);//�ҋ@�ǉ�_0 
			break;
		case CPlayer::E_RUN:
			mModPlayer.AddAnimationSet(F_PL_RUN);//����ǉ�
			break;
		case CPlayer::E_ATTACK:
			mModPlayer.AddAnimationSet(F_PL_ATTACK);//�U���ǉ�_2 
			break;
		case CPlayer::E_RUN_ATTACK:
			mModPlayer.AddAnimationSet(F_PL_RUN_ATTACK);//����U��
			break;
		case CPlayer::E_JUMP:
			mModPlayer.AddAnimationSet(F_PL_JUMP);//�W�����v�ǉ�
			break;
		case CPlayer::E_DAMAGE:
			mModPlayer.AddAnimationSet(F_PL_DAMAGE);//�_���[�W
			break;
		case CPlayer::E_AVOID:
			mModPlayer.AddAnimationSet(F_PL_AVOID);//���
			break;
		}
	}

	CPlayer *pl = new CPlayer(); //new�쐬

	pl->Init(&mModPlayer);
	pl->mPosition.y = POS_Y;
	CTaskManager::GetInstance()->Add(pl);//�^�X�N�ɒǉ�
	mpPlayer = pl; //����p
}
/*�G�l�~�[*/
/*�X���C��*/
#define MODEL_FILE_SLIME		MODEL_FILE"Slime\\Slime.x"//�X���C��	
#define SLIME_MAX 5//�X���C���̐�
#define SLIME_POS(i) CVector3(i * SLIME_MAX + 10,POS_Y,i * SLIME_MAX + 10)//�X���C���̐�
/*�A�j���[�V�����̃t�@�C���ꏊ*/
#define F_SLI_IDLING			MODEL_FILE"Slime\\Anima\\Idling.x"
#define F_SLI_RUN				MODEL_FILE"Slime\\Anima\\Run.x"
#define F_SLI_DAMAGE			MODEL_FILE"Slime\\Anima\\Damage.x"
#define F_SLI_ATTACK			MODEL_FILE"Slime\\Anima\\Attack.x"
/*�G�l�~�[�ǉ�����(�X���C��)*/
void CSceneModel::SlimeAdd(){
	/*�R�s�[�p*/
	CModelX *temp = &mModSlime;
	/*�v���C���[*/
	temp->Load(MODEL_FILE_SLIME);
	/*�A�j���[�V�����ǉ�����*/
	for (int i = 0; i < CSlime::E_STATE_ARRAY; i++)
	{
		CSlime::E_STATE state = (CSlime::E_STATE)i;
		switch (state)
		{
		case CSlime::E_IDLING:
			temp->AddAnimationSet(F_SLI_IDLING);
			break;
		case CSlime::E_RUN:
			temp->AddAnimationSet(F_SLI_RUN);
			break;
		case CSlime::E_DAMAGE:
			temp->AddAnimationSet(F_SLI_DAMAGE);
			break;
		case CSlime::E_ATTACK:
			temp->AddAnimationSet(F_SLI_ATTACK);
			break;
		};
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

/*�X���C��*/
#define KING_MODEL_FILE_SLIME		MODEL_FILE"Slime\\King\\KingSlime.x"//�X���C��	
#define SLIME_MAX 5//�X���C���̐�
#define KING_SLIME_POS CVector3(0 ,POS_Y,SLIME_MAX*3)//�X���C���̐�
/*�A�j���[�V�����̃t�@�C���ꏊ*/
#define F_SLI_IDLING			MODEL_FILE"Slime\\King\\Anima\\Idling.x"
#define F_SLI_RUN				MODEL_FILE"Slime\\King\\Anima\\Run.x"
#define F_SLI_DAMAGE			MODEL_FILE"Slime\\King\\Anima\\Damage.x"
#define F_SLI_ATTACK			MODEL_FILE"Slime\\King\\Anima\\Attack.x"
/*�L���O�G�l�~�[*/
void CSceneModel::KingSlimeAdd() {
	mModKingSlime.FileName(MODEL_FILE"Slime\\King\\");
	mModKingSlime.Load(KING_MODEL_FILE_SLIME);
	/*�A�j���[�V�����ǉ�����*/
	for (int i = 0; i < CSlime::E_STATE_ARRAY; i++)
	{
		CSlime::E_STATE state = (CSlime::E_STATE)i;
		switch (state)
		{
		case CSlime::E_IDLING:
			mModKingSlime.AddAnimationSet(F_SLI_IDLING);
			break;
		case CSlime::E_RUN:
			mModKingSlime.AddAnimationSet(F_SLI_RUN);
			break;
		case CSlime::E_DAMAGE:
			mModKingSlime.AddAnimationSet(F_SLI_DAMAGE);
			break;
		case CSlime::E_ATTACK:
			mModKingSlime.AddAnimationSet(F_SLI_ATTACK);
			break;
		};
	}

	CKingSlime *sl = new CKingSlime();
	sl->Init(&mModKingSlime);
	
	sl->mPosition = sl->mPosition.Transeform(CMap::GetInstance()->mRespawn);
	printf("%f,%f,%f", sl->mPosition.x, sl->mPosition.y, sl->mPosition.z);
	CTaskManager::GetInstance()->Add(sl);//�^�X�N�ɒǉ�
}

void CSceneModel::Init() {
	mMouseInitCount = 0.0f;							//�}�E�X�������ʒu�ɖ߂�܂ł̎���
	mLagTime = 0.0f;								//lag�ɂ��o�O�������

	
	/*�v���C���[������*/
	PlayerAdd();
	/*�G�l�~�[*/
	SlimeAdd();//�X���C��
	KingSlimeAdd();//�X���C��

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
