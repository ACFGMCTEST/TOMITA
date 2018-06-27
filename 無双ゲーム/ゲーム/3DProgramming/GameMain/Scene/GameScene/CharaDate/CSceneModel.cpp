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

/*�v���C���[�ǉ�����*/
void CSceneModel::PlayerAdd(){
	/*�v���C���[*/
	mModPlayer.TexDirectory(MODEL_FILE"SDUnity\\");
	mModPlayer.Load(MODEL_FILE_UNITY);

	mModPlayer.AddAnimationSet(F_PL_IDLING);//�ҋ@�ǉ�_0 
	mModPlayer.AddAnimationSet(F_PL_RUN);//����ǉ�
	mModPlayer.AddAnimationSet(F_PL_ATTACK);//�U���ǉ�_2 
	mModPlayer.AddAnimationSet(F_PL_RUN_ATTACK);//����U��
	mModPlayer.AddAnimationSet(F_PL_JUMP);//�W�����v�ǉ�
	mModPlayer.AddAnimationSet(F_PL_DAMAGE);//�_���[�W
	mModPlayer.AddAnimationSet(F_PL_DIED);//���S
	mModPlayer.AddAnimationSet(F_PL_AVOID);//���

	CPlayer *pl = new CPlayer(); //new�쐬

	pl->Init(&mModPlayer);
	pl->mPosition.y = POS_Y;
	CTaskManager::GetInstance()->Add(pl);//�^�X�N�ɒǉ�
	mpPlayer = pl; //����p
}

/*�G�l�~�[�ǉ�����(�X���C��)*/
void CSceneModel::SlimeAdd(){
	/*�R�s�[�p*/
	CModelX *temp = &mModSlime;
	/*�v���C���[*/
	temp->TexDirectory(MODEL_FILE"Slime\\");
	temp->Load(MODEL_FILE_SLIME);


	/*�A�j���[�V�����ǉ�����*/
	temp->AddAnimationSet(F_SLI_IDLING);
	temp->AddAnimationSet(F_SLI_RUN);
	temp->AddAnimationSet(F_SLI_DAMAGE);
	temp->AddAnimationSet(F_SLI_ATTACK);


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

/*�L���O�G�l�~�[*/
void CSceneModel::KingSlimeAdd() {
	mModKingSlime.TexDirectory(MODEL_FILE"Slime\\King\\");
	mModKingSlime.Load(KING_MODEL_FILE_SLIME);

	/*�A�j���[�V�����ǉ�����*/
	mModKingSlime.AddAnimationSet(F_SLI_KING_IDLING);
	mModKingSlime.AddAnimationSet(F_SLI_KING_RUN);
	mModKingSlime.AddAnimationSet(F_SLI_KING_DAMAGE);
	mModKingSlime.AddAnimationSet(F_SLI_KING_ATTACK);

	CKingSlime *sl = new CKingSlime();
	sl->Init(&mModKingSlime);
	sl->mPosition = sl->mPosition *   CMap::GetInstance()->mRespawn;
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
