#include "../CPlayer.h"
#include "CPlayerSpecial.h"
#include "../../../../../Graphic/CLoadTexManager.h"
#include "../../CSceneModel.h"
/*�X�s�[�h�̃t���[������velocity��ύX����*/
/*�t���[��*/
#define FRAME_VEL_ATTACK1 0
#define FRAME_VEL_ATTACK2 30
#define FRAME_VEL_ATTACK3 40
/*�X�s�[�h*/
#define VEL_ATTACK1 0.05f
#define VEL_ATTACK2 0
#define VEL_ATTACK3 0.07f
/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED 50

//�R���X�g���N�^
CPlayerSpecial::CPlayerSpecial():mpEffect3D(nullptr){}
//�f�X�g���N�^
CPlayerSpecial::~CPlayerSpecial() {}
//�ύX����֐�
void CPlayerSpecial::ChangeState(){
	/*�W�����v����ꍇ*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = F_PL_JUMP;//�W�����v
	}
	/*�A�C�h�����O����*/
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime){
		mNextRegisterName = F_PL_IDLING;
	}

	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) {
		mFlagNext = true;//�����������
		mpEffect->CTask::mKillFlag = true;
	}
}

/*�G�t�F�N�g�̐ݒ�*/
#define EFF_SIZE 3.0f,3.0f//�T�C�Y
#define EFF_POS(pos) CVector3(pos.x,pos.y + 2.0f, pos.z)//�G�t�F�N�g�̃|�W�V����
#define TEX_EFF_SIZE 0.0f,0.0f,960,192//�e�N�X�`���̃T�C�Y
#define EFF_SET_ANIMA 5,192//�ݒ�̃A�j���[�V����
#define EFF_SPEED  0.02f//�Đ��X�s�[�h
/*���߂ɌĂяo��*/
void CPlayerSpecial::Start() {
	/*�G�t�F�N�g�̐ݒ�*/
	mpEffect = new CEffect2D();
	mpEffect->Init(CLoadTexManager::GetInstance()->mpSaveUp,
		EFF_SIZE, STexVer(TEX_EFF_SIZE));//�摜�Ⓒ�_�����
	mpEffect->SetAnima(EFF_SET_ANIMA);//�A�j���[�V�����̏���
	CTaskManager::GetInstance()->Add(mpEffect);
	
}

/*�X�V����*/
void CPlayerSpecial::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);

	/*�A�j���[�V����*/
	pl->ChangeAnimation(F_PL_SPECIAL, false, ANIMA_SPEED);

	/*�G�t�F�N�g�ݒ�*/
	CVector3 pos = CVector3();
	mpEffect->StartAnima(EFF_SPEED,
		pos.Transeform(pl->mpCombinedMatrix
			[pl->mpModel->FindFrame("metarig_forearm_L")->mIndex]));
	/*�G�t�F�N�g�쐬����Ă��炸�@�p���`�������ꂽ�ꍇ*/
#define PUNCH_FRAME_SIZE 70//PUNCH�̃A�j���[�V�����̃t���[��
	if (!mpEffect3D && pl->mAnimationTime >= PUNCH_FRAME_SIZE) {
		pl->mPower = ATTACK_POWER*2.5f;
		pl->MpUp(-GAUGE_VER);//����
		/*�RD�̃G�t�F�N�g�쐬*/
		CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
		CEffect3D *mpEffect3D = new CEffect3D();
		mpEffect3D->Init(pl, &CSceneModel::GetInstance()->mModEffect3D
			, &pl->mPosition, &pl->mRotation);
		CTaskManager::GetInstance()->Add(mpEffect3D);
	}

}

//�J�ڎ��̏���
// isNext��false�ɖ߂������͂����ōs���Ƃ悢
void CPlayerSpecial::OnChangeEvent()
{

}