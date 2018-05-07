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
#define MODEL_FILE_UNITY			"x\\SDUnity\\SDUnityBoxing.x"
/*�A�j���[�V�����̃t�@�C���ꏊ*/
#define ANIMA_FILE_IDLING			"x\\Anima\\Idling.x"
#define ANIMA_FILE_ATTACK_RUN		"x\\Anima\\Run.x"
#define ANIMA_FILE_RUN				"x\\Anima\\Run.x"
#define ANIMA_FILE_ATTACK_IDLING	"x\\Anima\\Ani_AttackIdle.x"
#define ANIMA_FILE_ATTACK_INIT		"x\\Anima\\Ani_AttackInit.x"
#define ANIMA_FILE_ATTACK			"x\\Anima\\Attack2.x"
#define ANIMA_FILE_ATTACK_JUMP		"x\\Anima\\Ani_AttackJump.x"
#define ANIMA_FILE_JUMP				"x\\Anima\\Ani_Jump.x"
#define ANIMA_FILE_DAMAGE			"x\\Anima\\Ani_Damage.x"

/*lag���p*/
#define LAG_SIZE 0.1f //0�C1�b��lag���p
/*�p�b�N�̏����ʒu*/
#define PUCK_INIT_POS 0.0f,0.0f,-10.0f


/*�ÓI������*/
CXCharPlayer *CSceneModel::mpPlayer;

/*���ׂẴ��f���L�����폜*/
void CSceneModel::ModelAllKill(){
	mModelTaskManager.AllKill();
}

/*�R���X�g���N�^*/
CSceneModel::CSceneModel() :mMouseInitCount(0.0f),mLagTime(0.0f){


}

/*�f�X�g���N�^*/
CSceneModel::~CSceneModel(){
	

}

/*�v���C���[�ǉ�����*/
void CSceneModel::CPlayerAdd(CVector3 PlayerPos, CModelX *model){
	CXCharPlayer *pl = new CXCharPlayer(); //new�쐬

	pl->Init(model);
	pl->mPosition = PlayerPos;//�|�W�V�������߂�
	mModelTaskManager.Add(pl);//�^�X�N�ɒǉ�
	mpPlayer = pl; //����p
}

/*�G�l�~�[�ǉ�����*/
void CSceneModel::CEnemyAdd(CVector3 EnemyPos, CModelX *model){

	CXCharEnemy *ene = new CXCharEnemy();//�쐬

	ene->Init(model);
	ene->mPosition = EnemyPos;
	/*�����蔻��ǉ�����*/
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ATTACK_INIT_RANGE, ene->mpCBAttackInitBox);
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ATTACK_RANGE, ene->mpCBAttackBox);
	mModelTaskManager.Add(ene);
}

void CSceneModel::Init() {

	mMouseInitCount = 0.0f;							//�}�E�X�������ʒu�ɖ߂�܂ł̎���
	mLagTime = 0.0f;								//lag�ɂ��o�O�������

	CVector3 mPosition;								//�ʒu�@

	/*�v���C���[*/
	mModel.Load(MODEL_FILE_UNITY);

	/*�A�j���[�V�����ǉ�����*/
	for (int i = 0; i < CTask::E_STATE_ARRAY; i++)
	{
		switch (i)
		{
		case CTask::E_IDLING:
			mModel.AddAnimationSet(ANIMA_FILE_IDLING);//�ҋ@�ǉ�_0 
			break;
		case CTask::E_ATTACK_RUN:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK_RUN);//���߂Ȃ��瑖��ǉ�
			break;
		case CTask::E_RUN:
			mModel.AddAnimationSet(ANIMA_FILE_RUN);//����ǉ�
			break;
		case CTask::E_ATTACK_IDLING:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK_IDLING);//�U�����߃A�C�h���ǉ�
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
			mModel.AddAnimationSet(ANIMA_FILE_DAMAGE);//�_���[�W
			break;
		}
	}
	/*�L�����N�^�[������*/
	CPlayerAdd(CVector3(0.0f, 0.0f, 0.0f), &mModel);

}

void CSceneModel::Update() {
	
		/*lag���*/
		if (!CConvenient::Time(&mLagTime, LAG_SIZE)){
			CMouse::GetInstance()->mLeftFlag = false;
		}

		
		mModelTaskManager.AllUpdate();




	
}

void CSceneModel::Render() {
	
	mModelTaskManager.AllRender();

}

void CSceneModel::UpdateEffect(){
	mModelTaskManager.AllBillboardRender();
}