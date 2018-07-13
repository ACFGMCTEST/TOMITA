#include "../CGameScene.h"
#include "CTutorial.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CKey.h"
#include "../../../Camera/CCamera.h"
#include "../../../Key/CMouse.h"
#include "../../../Convenient/CConvenient.h"
#include "../../../Collision/CCollision.h"
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
	/*�P�b�������� && �͂��߂̂�*/
	if (CConvenient::Time(&mTime, 1.0f) && eState  == ESTATE::ALL_ENE_KILL) {
		CGameScene::mPauseFlag = true;
	}
	/*Enter�������Ɖ�ʐ؂�ւ�*/
	if (CKey::once(VK_RETURN)) {
		Change();
		CGameScene::mPauseFlag = false;
	}
}
/*�����؂�ւ�*/
void CTutorial::Change() {
	int i = eState + 1;
	eState = (ESTATE)i;//������i�߂�;
	/*UV���ւ�*/
	mRect.SetUv(&mTex, TEX_SIZE(mVer[eState]));
}

/*�`��*/
void CTutorial::Render(){
	/*�`���[�g���A�����Ȃ�*/
	if (eState < ARRAY){
		CRectangle2::Disp2D_Start();//2D�����J�n
		/*�`��J�n*/
		mBG.Render();
		mRect.Render();
		/*�`��I��*/
		CRectangle2::Disp2D_Exit();//2D�����I��
	}
}
