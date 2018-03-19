#include "CTutorial.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CKey.h"
#include "../UI/CScoreBoard.h"
#include "../../../Camera/CCamera.h"
#include "../../../Key/CMouse.h"
/*�T�C�Y*/
#define PERCENT_OPERA 1.2f
#define SIZE_OPERA			-200*PERCENT_OPERA,\
							20*PERCENT_OPERA,\
							200*PERCENT_OPERA,\
							-20*PERCENT_OPERA
/*�ǂݍ���*/
#define TEX_NAME			TGA_FILE"tutorial/operation.tga"

/*�e�N�X�`���T�C�Y*/
#define TEX_SIZE		0,0,400,280//���ׂĂ̑傫�� �㕝���o�S�O�ł�
#define TEX_SIZE(i)		0,i*40,400,40*(i+1)//i�Ńe�N�X�`������

/*�ʒu*/
#define FAST_POS			CVector2(0.0f,-100)	

#define POS(i)			CVector2(0.0f*(i+1),-100*(i+1))	

/*�R���X�g���N�^*/
CTutorial::CTutorial() : mFlagUv(false), eTutoState(E_RULE){}
/*�f�X�g���N�^*/
CTutorial::~CTutorial(){}
/*������*/
void CTutorial::Init(){
	/*�e�N�X�`���ǂݍ���*/
	mTex.load(TEX_NAME);

	for (int i = 0; i < ARRAY_OPERA; i++){
		/*�l�p�`�T�C�Y�ݒ�*/
		mOperation[i].SetVertex(SIZE_OPERA);
		/*�\��t��*/
		mOperation[i].SetUv(&mTex, TEX_SIZE(E_TEX_RULE));
	}

}

/*�X�V*/
void CTutorial::Update(){

	for (int i = 0; i < ARRAY_OPERA; i++){
		mOperation[i].position = FAST_POS;
	}

	/*�`���[���A����ԑJ��*/
	switch (eTutoState)
	{
	case CTutorial::E_RULE:

		/*�G���^�[�؂�ւ�*/
		if (CKey::once(VK_RETURN) || CMouse::GetInstance()->mOneLeftFlag){
			eTutoState = E_PUCK;
			MainCamera.StateChange(CCamera::E_STATE::E_PACK);
		}

		break;
	case E_PUCK:

		/*�G���^�[�؂�ւ�*/
		if (CKey::once(VK_RETURN) || CMouse::GetInstance()->mOneLeftFlag){
			eTutoState = E_GOAL;
			MainCamera.StateChange(CCamera::E_STATE::E_GOAL);
		}

		break;
	case E_GOAL:
		/*�G���^�[�؂�ւ�*/
		if (CKey::once(VK_RETURN) || CMouse::GetInstance()->mOneLeftFlag){
			eTutoState = E_WALK;
			MainCamera.StateChange(CCamera::E_STATE::E_CHARA);
		}
		break;
	case CTutorial::E_WALK:
		/*�e�N�X�`�����ւ�*/
		if (!mFlagUv){
			mOperation[0].SetUv(&mTex, TEX_SIZE(E_TEX_MOVE));
			mOperation[1].SetUv(&mTex, TEX_SIZE(E_TEX_MOVE));
			mFlagUv = true;
		}
		/*�G���^�[�؂�ւ�*/
		if (CKey::once(VK_RETURN) || CMouse::GetInstance()->mOneLeftFlag){
			eTutoState = E_CAMERA;
			mFlagUv = false;
		}
		break;
	case E_CAMERA:
		/*�|�W�V�����ς���*/
		for (int i = 0; i < ARRAY_OPERA; i++){
			mOperation[i].position = POS(i);
		}
		/*�e�N�X�`�����ւ�*/
		if (!mFlagUv){
			mOperation[0].SetUv(&mTex, TEX_SIZE(E_TEX_CAMERA_KEY));
			mOperation[1].SetUv(&mTex, TEX_SIZE(E_TEX_CAMERA_MOUSE));
			mFlagUv = true;
		}
		/*�G���^�[�؂�ւ�*/
		if (CKey::once(VK_RETURN) || CMouse::GetInstance()->mOneLeftFlag){
			eTutoState = E_ATTACK;
			mFlagUv = false;
		}
		break;

	case CTutorial::E_ATTACK:
		/*�|�W�V�����ς���*/
		for (int i = 0; i < ARRAY_OPERA; i++){
			mOperation[i].position = POS(i);
		}
		/*�e�N�X�`�����ւ�*/
		if (!mFlagUv){
			mOperation[0].SetUv(&mTex, TEX_SIZE(E_TEX_ATTACK_PUSH));
			mOperation[1].SetUv(&mTex, TEX_SIZE(E_TEX_ATACK_LONG));
			mFlagUv = true;
		}
		/*�G���^�[�؂�ւ�*/
		if (CKey::once(VK_RETURN) || CMouse::GetInstance()->mOneLeftFlag){
			eTutoState = E_PAUZE;
			mFlagUv = false;
		}
		break;
	case CTutorial::E_PAUZE:
		/*�e�N�X�`�����ւ�*/
		if (!mFlagUv){
			mOperation[0].SetUv(&mTex, TEX_SIZE(E_TEX_PAUZE));
			mOperation[1].SetUv(&mTex, TEX_SIZE(E_TEX_PAUZE));
			mFlagUv = true;
		}
		/*�G���^�[�؂�ւ�*/
		if (CKey::once(VK_RETURN) || CMouse::GetInstance()->mOneLeftFlag){
			eTutoState = E_ARRAY;
			mFlagUv = false;
		}
		break;
	case CTutorial::E_ARRAY:
		break;
	}
}

/*�`��*/
void CTutorial::Render(){
	/*�`���[�g���A�����Ȃ�*/
	if (eTutoState != E_ARRAY){
		CRectangle2::Disp2D_Start();//2D�����J�n
		/*�`��J�n*/
		for (int i = 0; i < ARRAY_OPERA; i++){
			mOperation[i].Render();

		}
		/*�`��I��*/
		CRectangle2::Disp2D_Exit();//2D�����I��
	}
}
