#include "../CGameScene.h"
#include "CTutorial.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CKey.h"
#include "../../../Camera/CCamera.h"
#include "../../../Key/CMouse.h"
#include "../../../Convenient/CConvenient.h"
#include "../../../Collision/CCollision.h"
#include "../CharaDate/Player/CPlayer.h"
#include "../CharaDate/Enemy/Slime/CSlime.h"
/*�e�N�X�`���̒��_�w��,�ȗ���*/
#define TEX_SIZE(v) v.left,v.top,v.right,v.bottom 

CTutorial* CTutorial::mpTutorial = 0;

//GetInstance
CTutorial* CTutorial::GetInstance() {
	if (mpTutorial == 0) {
		mpTutorial = new CTutorial();
	}
	return mpTutorial;
}

/*�R���X�g���N�^*/
CTutorial::CTutorial() : mFlagUv(false), eState(ESTATE::ALL_ENE_KILL)
, mTime(0){}
/*�f�X�g���N�^*/
CTutorial::~CTutorial(){}

/*������*/
void CTutorial::Init() {
	mFlagText = true;
	mFlagBG = true;
	mPos = CVector3(0.0f, 0.0f, 0.0f);
	eState = ESTATE::ALL_ENE_KILL;
	mTime = 0;
#define TEX_X 600//�e�N�X�`���̉���
#define TEX_Y 37//�e�N�X�`���s��
#define TEX_BG_Y 70//BG�̃T�C�YY
#define SIZE_DOUB 0.6f
	/*�T�C�Y*/
	mRect.SetVertex(RECT_SIZE(SIZE_DOUB, TEX_X, TEX_Y));
	mRect.mPosition.y = DISP_2D_Y / 2.5f;//�|�W�V�����ݒ�
	mBG.SetVertex(RECT_SIZE(SIZE_DOUB, TEX_X, TEX_BG_Y));
	mBG.mPosition = mRect.mPosition;
	const float ajust = 10;//�|�W�V���������p
	mBG.mPosition.y -= TEX_Y * SIZE_DOUB - ajust;
	/*�e�N�X�`��*/
	/*�e�N�X�`��*/
	mTex.Load(TGA_FILE"Tutorial\\Text.tga");
	mTexBG.Load(TGA_FILE"Tutorial\\TextBG.tga");
	/*���_���ۑ���ޕ���*/
	for (int i = 0; i < ESTATE::ARRAY; i++) {
		mVer[i] = STexVer(0.0f, TEX_Y * (i), TEX_X, TEX_Y * (i + 1));
	}
	/*UV���ւ�*/
	mRect.SetUv(&mTex, TEX_SIZE(mVer[eState]));
	mBG.SetUv  (&mTexBG, TEX_SIZE(STexVer(0,0, TEX_X, TEX_BG_Y)));
	/*�A���t�@����*/
	mRect.SetColor(NO_A_WHITE_COLOR, 0.5f);//�������ɂ���
}

/*�X�V*/
void CTutorial::Update(){
	/*�P�b�������� && �L�[��������ȊO�̎� �|�[�Y*/
	if (CConvenient::Time(&mTime, 0.5f)) {
		if (eState == ESTATE::ALL_ENE_KILL) {
			CGameScene::mPauseFlag = true;
		}
	}

	/*�e�L�X�g�؂�ւ�*/
	Change();


}
/*�����؂�ւ�*/
void CTutorial::Change() {
	/*
	�����蔻��ݒ�
	*/
#define SERACH_SPHERE(range,mat) range,CVector3(0.0f,0.0f,0.0f),mat//���̂̐ݒ�(���G�Ɏg��)
#define SEARCH_PL_RANGE 5.0f
#define SEARCH_RANGE 5.0f
	CMatrix44 m44 = CMatrix44();
	/*���G���ɓ���Γ���*/
	CColSphere plCol = CColSphere(SERACH_SPHERE(SEARCH_PL_RANGE, CSceneModel::mpPlayer->mpMatrix));//�v���C���[
	CColSphere Col = CColSphere(SERACH_SPHERE(SEARCH_RANGE, &m44));
	bool ChangeFlag = false;
	/*�����������Ă���Ȃ玟�̃e�L�X�g��*/
	switch (eState)
	{
		/*���ׂĂ̓G��|�����̏��*/
	case CTutorial::ALL_ENE_KILL:
		/*�L�[�������Ɠ���������*/
		if (CKey::once(VK_RETURN)) {
			eState = MOVE;
			CGameScene::mPauseFlag = false;
		}
		break;
		/*��������*/
	case CTutorial::MOVE:
		mFlagBG = false;
		//���E���ɗ��Ă��邩���f
		ChangeFlag =  !CCollision::CollisionShpere(plCol.GetUpdate(), Col.GetUpdate());
		if (ChangeFlag) {
			eState = ATTACK_AVOID;
		}
		break;
		/*�U���Ƃ悯�����*/
	case CTutorial::ATTACK_AVOID:
		/*�L�[�������Ɠ������� || ���ɂ���G��|���Ǝ��̃e�L�X�g��*/
		if (CSceneModel::mEnemyCount <= SLIME_MAX0-1) {
			eState = BLOW_OFF;
			CGameScene::mPauseFlag = true;
			mFlagBG = true;
		}
		break;
		/*������΂��ƃ_���[�W���������*/
	case CTutorial::BLOW_OFF:
		/*�L�[�������Ǝ��̐�����*/
		if (CKey::once(VK_RETURN)) {
			mFlagText = false;
			mFlagBG = false;
			CGameScene::mPauseFlag = false;
		}
		//�G�����ׂē|���ƃe�L�X�g�؂�ւ��ƍ���Ƀ��X�|�[��
		if(CSceneModel::mEnemyCount == 0){
			//����̓G�𑝂₷
			for (int i = 0; i < SLIME_MAX1; i++) {
				/*�ʒu�����Ȃ��悤�ɂ���*/
				const CVector3 pos = CVector3(-5 * i, 0.0f, 5 * i);
				CSlime *sl;
				sl = CSceneModel::GetInstance()->SlimeAdd(ENEMY_RESP_1, pos);//�X���C��
				sl->mFlagDecoy = true;
			}
			eState = HIGH_HILL_SLI;
			CGameScene::mPauseFlag = true;
		}
		break;
		/*�������*/
	case CTutorial::HIGH_HILL_SLI:
		mFlagText = true;
		mFlagBG = true;
		/*�G���^�[�������Ǝ��̃e�L�X�g��*/
		if (CKey::once(VK_RETURN)) {
			eState = JUMP;
			mFlagBG = false;
			CGameScene::mPauseFlag = false;
		}
		break;
		/*�W�����v����*/
	case CTutorial::JUMP:
		Col.mpCombinedMatrix = &CMap::GetInstance()->Matrix(ENEMY_RESP_1);
		/*����̃��X�|�[���n�_�ɋ߂Â��Ǝ��̃e�L�X�g�\����*/
		ChangeFlag = CCollision::CollisionShpere(plCol.GetUpdate(), Col.GetUpdate());
		/*��ɂ���Ȃ�*/
		if (ChangeFlag) {
			eState = PUSH_OFF;
			mFlagBG = true;
			mFlagText = true;
			CGameScene::mPauseFlag = true;
		}
		/*�G�����ׂē|���ƃ{�X�̐���*/
		if (CSceneModel::mEnemyCount == 0) {
			CSceneModel::GetInstance()->KingSlimeAdd();//�L���O�X���C���o��
			eState = KING_KILL;
			mFlagBG = true;
			mFlagText = true;
		}
		break;
		/*���䂩�痎�Ƃ���*/
	case CTutorial::PUSH_OFF:
		/*�L�[�������Ƃ����������*/
		if (CKey::once(VK_RETURN)) {
			mFlagBG = false;
			mFlagText = false;
			CGameScene::mPauseFlag = false;
		}
		/*�G�����ׂē|���ƃ{�X�̐���*/
		if (CSceneModel::mEnemyCount == 0) {
			CSceneModel::GetInstance()->KingSlimeAdd();//�L���O�X���C���o��
			eState = KING_KILL;
			mFlagBG = true;
			mFlagText = true;
		}
		break;
		/*�L���O��|����*/
	case CTutorial::KING_KILL:
		if (CKey::once(VK_RETURN)) {
			eState = SPECIAL_ATTACK;
			CGameScene::mPauseFlag = true;
		}
		break;
		/*�K�E�Z����*/
	case CTutorial::SPECIAL_ATTACK:
		if (CKey::once(VK_RETURN)) {
			eState = ARRAY;
			CGameScene::mPauseFlag = false;
		}
		break;
	case CTutorial::ARRAY:
#define ENEMY_MAX 20
		/*�X���C�������X�|�[�����Ă���*/
		if (CConvenient::Time(&mTime, 6.5f) && CSceneModel::mEnemyCount <= ENEMY_MAX) {
			CVector3 pos = CVector3(rand() % 4,0.0f,rand() % 4);
			CSceneModel::GetInstance()->SlimeAdd(ENEMY_RESP_2,pos);//�X���C��
			
			mTime = 0.0f;
		}
		break;
	default:
		break;
	}
	/*UV���ւ�*/
	mRect.SetUv(&mTex, TEX_SIZE(mVer[eState]));
}

/*�`��*/
void CTutorial::Render(){
	/*�`���[�g���A�����Ȃ�*/
	if (eState < ARRAY){
		CRectangle2::Disp2D_Start();//2D�����J�n
		/*�`��J�n*/
		if  (mFlagBG)mBG.Render();
		if(mFlagText)mRect.Render();
		/*�`��I��*/
		CRectangle2::Disp2D_Exit();//2D�����I��
	}
}
