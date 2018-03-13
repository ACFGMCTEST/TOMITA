#include "CTutorial.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CKey.h"
#include "../UI/CScoreBoard.h"

/*�T�C�Y*/
#define SIZE_FRAME			-150,50,150,-50
#define SIZE_OPERA			-150,50,150,-50
/*�ǂݍ���*/
#define TEX_NAME_FRAME					TGA_FILE"tutorial/frame.tga"
#define TEX_NAME_OPE_RULE				TGA_FILE"tutorial/rule.tga"
#define TEX_NAME_OPE_WALK				TGA_FILE"tutorial/walk.tga"
#define TEX_NAME_OPE_CAMERA_KEY			TGA_FILE"tutorial/cameraKey.tga"
#define TEX_NAME_OPE_CAMERA_MOUSE		TGA_FILE"tutorial/cameraMouse.tga"
#define TEX_NAME_OPE_PAUSE				TGA_FILE"tutorial/pause.tga"
#define TEX_NAME_OPE_SPECIAL			TGA_FILE"tutorial/special.tga"
/*�e�N�X�`���T�C�Y*/
#define TEX_SIZE_FRAME		0,0,400,100	
#define TEX_SIZE_OPERA		0,0,400,100	
#define TEX_SIZE_WALK		0,0,400,100	
#define TEX_SIZE_MOUSE		0,0,400,100	
#define TEX_SIZE_KEY		0,0,400,100	

/*�ʒu*/
#define FAST_POS			CVector2(0.0f,100)	
/*�R���X�g���N�^*/
CTutorial::CTutorial() : mFlagUv(false), eTutoState(E_RULE){}
/*�f�X�g���N�^*/
CTutorial::~CTutorial(){}
/*������*/
void CTutorial::Init(){
	
	/*�e�N�X�`���ǂݍ���*/
	mTexFrame.load(TEX_NAME_FRAME);//�g���[�h
	mTexOperation.load(TEX_NAME_OPE_RULE);//RULE���[�h
	mTexWalk.load(TEX_NAME_OPE_WALK);//
	mTexCameraKey.load(TEX_NAME_OPE_CAMERA_KEY);
	mTexCameraMouse.load(TEX_NAME_OPE_CAMERA_MOUSE);

	for (int i = 0; i < ARRAY_OPERA; i++){
		/*�l�p�`�T�C�Y�ݒ�*/
		mOperation[i].SetVertex(SIZE_OPERA);
		/*�\��t��*/
		mOperation[i].SetUv(&mTexOperation, TEX_SIZE_OPERA);
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
		if (CKey::once(VK_RETURN)){
			eTutoState = E_WALK;
		}

		break;
	case CTutorial::E_WALK:
		/*�e�N�X�`�����ւ�*/
		if (!mFlagUv){
			mOperation[0].SetUv(&mTexWalk, TEX_SIZE_FRAME);
			mOperation[1].SetUv(&mTexWalk, TEX_SIZE_FRAME);
			mFlagUv = true;
		}
		/*�G���^�[�؂�ւ�*/
		if (CKey::once(VK_RETURN)){
			eTutoState = E_ATTACK;
			mFlagUv = false;
		}
		break;
	case CTutorial::E_ATTACK:
		/*�e�N�X�`�����ւ�*/
		if (!mFlagUv){
			mOperation[0].SetUv(&mTexCameraKey, TEX_SIZE_FRAME);
			mOperation[1].SetUv(&mTexCameraKey, TEX_SIZE_FRAME);
			mFlagUv = true;
		}
		/*�G���^�[�؂�ւ�*/
		if (CKey::once(VK_RETURN)){
			eTutoState = E_PAUZE;
			mFlagUv = false;
		}
		break;
	case CTutorial::E_PAUZE:
		/*�e�N�X�`�����ւ�*/
		if (!mFlagUv){
			mOperation[0].SetUv(&mTexCameraMouse, TEX_SIZE_FRAME);
			mOperation[1].SetUv(&mTexCameraMouse, TEX_SIZE_FRAME);
			mFlagUv = true;
		}
		/*�G���^�[�؂�ւ�*/
		if (CKey::once(VK_RETURN)){
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
	CRectangle2::Disp2D_Start();//2D�����J�n
	/*�`��J�n*/
	for (int i = 0; i < ARRAY_OPERA; i++){
		mOperation[i].Render();
		
	}
	/*�`��I��*/
	CRectangle2::Disp2D_Exit();//2D�����I��
}
