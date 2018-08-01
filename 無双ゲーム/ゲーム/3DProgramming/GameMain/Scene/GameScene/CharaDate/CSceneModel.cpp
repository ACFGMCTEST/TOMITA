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
int  CSceneModel::mEnemyCount = 0;

//�ȈՃ��X�|�[���ʒu�����߂�
#define RESP(pObj,name)pObj->mPosition =  pObj->mPosition * \
		CMap::GetInstance()->Matrix(name);

/*�R���X�g���N�^*/
CSceneModel::CSceneModel(){


}

CSceneModel *CSceneModel::mpSceneModel = 0;
//GetInstance
CSceneModel* CSceneModel::GetInstance() {
	if (mpSceneModel == 0) {
		mpSceneModel = new CSceneModel();
	}
	return mpSceneModel;
}

/*�f�X�g���N�^*/
CSceneModel::~CSceneModel(){
	

}

/*�v���C���[�ǉ�����*/
void CSceneModel::PlayerAdd(){
	/*�v���C���[�������G�t�F�N�g*/
	mModEffect3D.TexDirectory(MODEL_FILE"Effect\\");
	mModEffect3D.Load(MODEL_FILE"Effect\\Effect.x");
	mModEffect3D.AddAnimationSet(MODEL_FILE"Effect\\EffectAnima.x");

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
	mModPlayer.AddAnimationSet(F_PL_SPECIAL);//�X�y�V�����Z


	CPlayer *pl = new CPlayer(); //new�쐬

	pl->Init(&mModPlayer);
	pl->mPosition.y = POS_Y;
	CTaskManager::GetInstance()->Add(pl);//�^�X�N�ɒǉ�
	mpPlayer = pl; //����p
}

/*�G�l�~�[�ǉ�����(�X���C��)*/
void CSceneModel::SlimeInit(){
	/*�v���C���[*/
	mModSlime.TexDirectory(MODEL_FILE"Slime\\");
	mModSlime.Load(MODEL_FILE_SLIME);


	/*�A�j���[�V�����ǉ�����*/
	mModSlime.AddAnimationSet(F_SLI_IDLING);
	mModSlime.AddAnimationSet(F_SLI_RUN);
	mModSlime.AddAnimationSet(F_SLI_DAMAGE);
	mModSlime.AddAnimationSet(F_SLI_ATTACK);

}

/*���X�|�[���w�肵��Add*/
CSlime *CSceneModel::SlimeAdd(char *name,CVector3 ajustPos) {
	mEnemyCount++;
	CSlime *sl;
	/*�C���X�^���X�쐬*/
	sl= new CSlime();
	sl->Init(&mModSlime);
	/*pos�w��*/
	RESP(sl, name);//���X�|�[���ꏊ�w��@
	sl->mPosition += ajustPos;
	CTaskManager::GetInstance()->Add(sl);//�^�X�N�ɒǉ�
	return sl;
}

/*�L���O�G�l�~�[*/
void CSceneModel::KingSlimeAdd() {
	CKingSlime *sl = new CKingSlime();
	sl->Init(&mModKingSlime);
	sl->mPosition = sl->mPosition *   CMap::GetInstance()->Matrix("Armature_KingEnemy");
	CTaskManager::GetInstance()->Add(sl);//�^�X�N�ɒǉ�
}
/*����������*/
void CSceneModel::KingSlimeInit() {
	mModKingSlime.TexDirectory(MODEL_FILE"Slime\\King\\");
	mModKingSlime.Load(KING_MODEL_FILE_SLIME);

	/*�A�j���[�V�����ǉ�����*/
	mModKingSlime.AddAnimationSet(F_SLI_KING_IDLING);
	mModKingSlime.AddAnimationSet(F_SLI_KING_RUN);
	mModKingSlime.AddAnimationSet(F_SLI_KING_DAMAGE);
	mModKingSlime.AddAnimationSet(F_SLI_KING_ATTACK);

}

void CSceneModel::Init() {
	mEnemyCount = 0;
	
	/*�v���C���[������*/
	PlayerAdd();
	/*�G�l�~�[*/
	SlimeInit();
	for (int i = 0; i < SLIME_MAX0; i++) {
		/*�ʒu�����Ȃ��悤�ɂ���*/
		const CVector3 pos = CVector3(5.0f * i, 0.0f, 5.0f * i);
		SlimeAdd(ENEMY_RESP_0,pos);//�X���C��
	}
	KingSlimeInit();//�X���C��

}



