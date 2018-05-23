#include "CTutorial.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CKey.h"
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
	
}

/*�X�V*/
void CTutorial::Update(){

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
