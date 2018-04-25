#include "CRectangle2.h"
#include "../Define/Define.h"
#include "../Convenient/CConvenient.h"
#include <cassert>

/*�P�̂�COLOR��1.0f��肢���Ȃ��悤�ɂ���*/
#define LIMIT_COLOR 1.0f

CRectangle2::CRectangle2(float left, float top, float right, float bottom, float r, float g, float b, float a)
:	//�O�p�`�N���X�̃R���X�g���N�^���Ă�
mTriangle1(left, top, left, bottom, right, bottom, r, g, b, a),
mTriangle2(left, top, right, bottom, right, top, r, g, b, a), mpTexture(0), mDegree(0)
{}



CRectangle2::CRectangle2(float left, float top, float right, float bottom, float r, float g, float b, float a, CVector2 pos)
:	//�O�p�`�N���X�̃R���X�g���N�^���Ă�
mTriangle1(left, top, left, bottom, right, bottom, r, g, b, a),
mTriangle2(left, top, right, bottom, right, top, r, g, b, a), mPosition(pos), mpTexture(0), mDegree(0)
{};


CRectangle2::CRectangle2() :mpTexture(0), mFlagDeg(false), mDegree(0), mpPos(nullptr), mFlagVerInit(false),
 mPosition(0.0f, 0.0f), mFlagSaveTex(false),mTexScrollSideInit(0){}



//�`�悷��
void CRectangle2::Render() {
	/*�|�W�V�����ɒl���A�h���X���������ꍇ*/
	if (mpPos){
		mPosition = *mpPos;
	}

	if (mDegree != 0 || mFlagDeg){ //���l�p���ǂ���
		if (mpTexture != 0){ //�e�N�X�`�������邩�ǂ���
			//�e�N�X�`����L���ɂ���
			glEnable(GL_TEXTURE_2D);
			//�A���t�@�u�����h��L���ɂ���
			glEnable(GL_BLEND);
			//�u�����h���@���w��
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//�e�N�X�`�����w��
			glBindTexture(GL_TEXTURE_2D, mpTexture->id);
			//�O�p�`1�̕`��
			mTriangle1.Render(mPosition, mDegree, uv[0]);
			//�O�p�`2�̕`��
			mTriangle2.Render(mPosition, mDegree, uv[1]);
			//�e�N�X�`�������
			glBindTexture(GL_TEXTURE_2D, 0);
			//�A���t�@�u�����h�𖳌�
			glDisable(GL_BLEND);
			//�e�N�X�`���𖳌�
			glDisable(GL_TEXTURE_2D);
		}
		else{
			mTriangle1.Render(mPosition, mDegree);
			mTriangle2.Render(mPosition, mDegree);
			mFlagDeg = true;
		}
	}
	else if (mpTexture == 0) {
		mTriangle1.Render(mPosition);	//�O�p�`�P��`�悷��
		mTriangle2.Render(mPosition);	//�O�p�`�Q��`�悷��
	}
	else {
		//�e�N�X�`����L���ɂ���
		glEnable(GL_TEXTURE_2D);
		//�A���t�@�u�����h��L���ɂ���
		glEnable(GL_BLEND);
		//�u�����h���@���w��
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//�e�N�X�`�����w��
		glBindTexture(GL_TEXTURE_2D, mpTexture->id);
		//�O�p�`1�̕`��
		mTriangle1.Render(mPosition, uv[0]);
		//�O�p�`2�̕`��
		mTriangle2.Render(mPosition, uv[1]);
		//�e�N�X�`�������
		glBindTexture(GL_TEXTURE_2D, 0);
		//�A���t�@�u�����h�𖳌�
		glDisable(GL_BLEND);
		//�e�N�X�`���𖳌�
		glDisable(GL_TEXTURE_2D);
	}
}

//�X�V�����̐錾
void Update();
/*
left	�摜�̍���[�����_(0,0)�Ƃ��A�\��t�������̈�̍��̍��W�l
top		�摜�̍���[�����_(0,0)�Ƃ��A�\��t�������̈�̏�̍��W�l
right	�摜�̍���[�����_(0,0)�Ƃ��A�\��t�������̈�̉E�̍��W�l
bottom	�摜�̍���[�����_(0,0)�Ƃ��A�\��t�������̈�̉��̍��W�l
*/

void CRectangle2::SetUv(CTexture *t, float left, float top, float right, float bottom) {
	mpTexture = t;
	uv[0][0] = uv[1][0] = (float)left / mpTexture->header.width;
	uv[0][1] = uv[1][1] = (float)(mpTexture->header.height - top) / mpTexture->header.height;
	uv[0][2] = (float)left / mpTexture->header.width;
	uv[0][3] = (float)(mpTexture->header.height - bottom) / mpTexture->header.height;
	uv[0][4] = uv[1][2] = (float)right / mpTexture->header.width;
	uv[0][5] = uv[1][3] = (float)(mpTexture->header.height - bottom) / mpTexture->header.height;
	uv[1][4] = (float)right / mpTexture->header.width;
	uv[1][5] = (float)(mpTexture->header.height - top) / mpTexture->header.height;

	/*�e�N�X�`���̒l�ۑ�*/
	if (!mFlagSaveTex){
		mSaveInitTexVer[E_TOP] = top;
		mSaveInitTexVer[E_BOTTOM] = bottom;
		mSaveInitTexVer[E_LEFT] = left;
		mSaveInitTexVer[E_RIGHT] = right;
		mFlagSaveTex = true;
	}
	mSaveTexVer[E_TOP] = top;
	mSaveTexVer[E_BOTTOM] = bottom;
	mSaveTexVer[E_LEFT] = left;
	mSaveTexVer[E_RIGHT] = right;
}
/*�e�N�X�`������ꍇ*/
void CRectangle2::Uv(float left, float top, float right, float bottom){
	/*�e�N�X�`�����Ȃ��ꍇ�G���[*/
	assert(mpTexture);
	SetUv(mpTexture, left, top, right, bottom);	
}


void CRectangle2::SetVertex(float left, float top, float right, float bottom) {

	mTriangle1.x1 = left; mTriangle1.y1 = top;
	mTriangle1.x2 = left; mTriangle1.y2 = bottom;
	mTriangle1.x3 = right; mTriangle1.y3 = bottom;
	mTriangle2.x1 = left; mTriangle2.y1 = top;
	mTriangle2.x2 = right; mTriangle2.y2 = bottom;
	mTriangle2.x3 = right; mTriangle2.y3 = top;
	mTriangle1.v1 = CVector2(left, top); mTriangle1.v2 = CVector2(left, bottom); mTriangle1.v3 = CVector2(right, bottom);
	mTriangle2.v1 = CVector2(left, top); mTriangle2.v2 = CVector2(right, bottom); mTriangle2.v3 = CVector2(right, top);
	mpLeft = &mTriangle1.x1;
	mpRight = &mTriangle1.x3;
	mpBottom = &mTriangle1.y3;
	mpTop = &mTriangle2.y1;

	/*�������_�����*/
	if (!mFlagVerInit){
		mSaveLeft = left;
		mSaveTop = top;
		mSaveRight = right;
		mSaveBottom = bottom;
		mFlagVerInit = true;
	}

}

void CRectangle2::SetColor(float r, float g, float b, float a) {
	/*1�Ԗ�*/
	CConvenient::LimitEqual(&mTriangle1.r, r, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&mTriangle1.g, g, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&mTriangle1.b, b, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&mTriangle1.a, a, LIMIT_COLOR, 0.0f);
	/*2�Ԗ�*/
	CConvenient::LimitEqual(&mTriangle2.r, r, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&mTriangle2.g, g, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&mTriangle2.b, b, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&mTriangle2.a, a, LIMIT_COLOR, 0.0f);
}

/*�t�F�[�h�֐�*/
#define SET_C3 mTriangle1.r,mTriangle1.g,mTriangle1.b //���̎l�p�`rgb


void CRectangle2::Fade(float speed, float a){
	float mFade4 = mTriangle1.a + speed;		//�t�F�[�h�֐��Ŏg��
	mFade4 += speed;
	if (mFade4 >= a){
		mFade4 = a;
	}
	SetColor(SET_C3, mFade4);
}

/*�t�F�[�h�֐�*/
void CRectangle2::FadeOut(float speed, float a){
	float mFade4 = mTriangle1.a - speed;		//�t�F�[�h�֐��Ŏg��
	mFade4 -= speed;
	if (mFade4 <= a){
		mFade4 = a;
	}
	SetColor(SET_C3, mFade4);
}
#define FLASHING_DOWN__C4(s) \
	mTriangle1.r - s, \
	mTriangle1.g - s, \
	mTriangle1.b - s, \
	mTriangle1.a - s //���̎l�p�`rgba

#define FLASHING_UP__C4(s) \
	mTriangle1.r + s, \
	mTriangle1.g + s, \
	mTriangle1.b + s, \
	mTriangle1.a + s //���̎l�p�`rgba

//�FDOWN
void CRectangle2::ColorDown(float speed){
	if (mTriangle1.r > 0.0f){
		SetColor(FLASHING_DOWN__C4(speed));
	}
	if (mTriangle1.r <= 0){
		SetColor(0.0f, 0.0f, 0.0f, mTriangle1.a);
	}
}
/*�FUP*/
void CRectangle2::ColorUp(float speed){
	if (mTriangle1.r < 1.0f){
		SetColor(FLASHING_UP__C4(speed));
	}
	if (mTriangle1.r <= 0){
		SetColor(1.0f, 1.0f, 1.0f, mTriangle1.a);
	}
}
/*�F�̓_��*/
void CRectangle2::FlashingColor(float speed,float upLimit,float downLimit){
	switch (eState)
	{
	case UP:
		SetColor(FLASHING_UP__C4(speed));
		if (mTriangle1.r >= upLimit){
			eState = DOWN;
		}
		break;
	case DOWN:
		SetColor(FLASHING_DOWN__C4(speed));
		if (mTriangle1.r <=  downLimit){
			eState = UP;
		}
		break;
	}

}

/*Gradation�����֐�*/
void CRectangle2::SetGradationLoop(CRectangle2::E_COLOR_CHANGE state){
	eColorChange = state;
	/*�F���K��l�ɐݒ�*/
	switch (state)
	{
	case CRectangle2::E_GREEN_YELLOW:
		SetColor(GREEN_COLOR);
		break;
	case CRectangle2::E_YELLOW_RED:
		SetColor(YELLOW_COLOR);
		break;
	case CRectangle2::E_RED_PURPLE:
		SetColor(RED_COLOR);
		break;
	case CRectangle2::E_PURPLE_BLUE:
		SetColor(PURPLE_COLOR);
		break;
	case CRectangle2::E_BLUE_CYAN:
		SetColor(BLUE_COLOR);
		break;
	case CRectangle2::E_CYAN_GREEN:
		SetColor(CYAN_COLOR);
		break;
	default:
		break;
	}


}

/*�O���f�[�V�����֐�*/
void CRectangle2::GradationLoop(float speed){
	float red, green, blue, alpha;//�ۑ��p�J���[
	/*�J���[�ύX���Ă���*/
	red = mTriangle1.r;
	green = mTriangle1.g;
	blue = mTriangle1.b;
	alpha = mTriangle1.a;
	/*�F�ύX*/
	switch (eColorChange)
	{
		/*�΂��物*/
	case CRectangle2::E_GREEN_YELLOW:
		red += speed;
		/*�Ԃ��ő�Ȃ�,���݉�*/
		if (red >= LIMIT_COLOR){
			eColorChange = E_YELLOW_RED;
		}
		break;
		/*�������*/
	case CRectangle2::E_YELLOW_RED:
		green -= speed;
		/*�΂��ŏ��Ȃ�,���ݐ�*/
		if (green <= 0.0f){
			eColorChange = E_RED_PURPLE;
		}
		break;
		/*�Ԃ��率*/
	case CRectangle2::E_RED_PURPLE:
		blue += speed;
		/*�Ԃ��ő�Ȃ�,���ݎ�*/
		if (blue >= LIMIT_COLOR){
			eColorChange = E_PURPLE_BLUE;
		}
		break;
		/*�������*/
	case CRectangle2::E_PURPLE_BLUE:
		red -= speed;
		/*�Ԃ��ŏ��Ȃ�,���ݐ�*/
		if (red <= 0.0f){
			eColorChange = E_BLUE_CYAN;
		}
		break;
		/*�����*/
	case CRectangle2::E_BLUE_CYAN:
		green += speed;
		/*�΂��ő�Ȃ�,���ݐ�*/
		if (green >= LIMIT_COLOR){
			eColorChange = E_CYAN_GREEN;
		}
		break;
		/*�΂����*/
	case CRectangle2::E_CYAN_GREEN:
		blue -= speed;
		/*���ŏ��Ȃ�,���ݗ�*/
		if (blue <= 0.0f){
			eColorChange = E_GREEN_YELLOW;
		}
		break;
	default:
		break;
	}
	/*�J���[*/
	SetColor(red,green,blue,alpha);
}

/*�g��k���֐�*/
void CRectangle2::RectScaling(float Double, float time){
	/*���X�������ĂȂ��ꍇ�G���[*/
	assert(mFlagVerInit);

	float speedx, speedy;
	/*�傫���Ȃ�X�s�[�h*/
	speedx = *mpRight * 1 / FPS * time;
	speedy = *mpTop * 1 / FPS  * time;

	if (*mpRight + speedx > mSaveRight * Double && mSaveRight * Double > *mpRight - speedx){ return; }

	/*�傫���ꍇ*/
	if (*mpRight + speedx > mSaveRight * Double){
		/*����������*/
		SetVertex
			(
			*mpLeft   + speedx,
			*mpTop    - speedy,
			*mpRight  - speedx,
			*mpBottom + speedy
			);

	}
	/*�������ꍇ*/
	else{
		/*�傫������*/
		SetVertex
			(
			*mpLeft - speedx,
			*mpTop + speedy,
			*mpRight + speedx,
			*mpBottom - speedy
			);
	}
	

}

/*�g��k���֐� ���������Ȃ��o�[�W����
double�@�g��k���̒l
time ���܂łɏ������邩�̎���
*/
void CRectangle2::RectScalingLeftPos(float Double, float time){
	/*���X�������ĂȂ��ꍇ�G���[*/
	assert(mFlagVerInit);

	float speedx, speedy;
	/*�傫���Ȃ�X�s�[�h*/
	speedx = *mpRight * 1 / FPS * time;
	speedy = *mpTop * 1 / FPS  * time;

	if (*mpRight + speedx > mSaveRight * Double && mSaveRight * Double > *mpRight - speedx){ return; }

	/*�傫���ꍇ*/
	if (*mpRight + speedx > mSaveRight * Double){
		/*����������*/
		SetVertex
			(
			*mpLeft + speedx,
			*mpTop - speedy,
			*mpRight - speedx,
			*mpBottom + speedy
			);
		mPosition.x -= speedx ;
	}
	/*�������ꍇ*/
	else{
		/*�傫������*/
		SetVertex
			(
			*mpLeft - speedx,
			*mpTop + speedy,
			*mpRight + speedx,
			*mpBottom - speedy
			);
		mPosition.x += speedx ;
	}

}

/*��]������悤*/
void CRectangle2::SetUvRot() {

	float saveUv0[2] = { uv[0][0], uv[0][1] };
	uv[0][0] = uv[3][0];
	uv[0][1] = uv[3][1];

	float saveUv2[2] = { uv[2][2], uv[2][1] };
	uv[2][0] = uv[1][0];
	uv[2][1] = uv[1][1];

	uv[1][0] = saveUv0[0];
	uv[1][1] = saveUv0[1];

	uv[3][0] = saveUv2[0];
	uv[3][1] = saveUv2[1];
}
/*2D�������J�n���鏈��*/
void CRectangle2::Disp2D_Start(){
	/*�`�揀��*/
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-DISP_2D_X, DISP_2D_X, -DISP_2D_Y, DISP_2D_Y);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}
/*2D�������I�����鏈��*/
void CRectangle2::Disp2D_Exit(){
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
}

/*�e�N�X�`�����X�N���[���֐�*/
void CRectangle2::TexSideScroll(float speed,int InitSide){
	float left, top, right, bottom;
	/*�ۑ�*/
	left = mSaveTexVer[E_LEFT];
	top = mSaveTexVer[E_TOP];
	bottom = mSaveTexVer[E_BOTTOM];
	/*���߂�Scroll�ꏊ�̈ʒu�����߂�*/
	if (mTexScrollSideInit == 0){
		mTexScrollSideInit = InitSide;
		right = mTexScrollSideInit;
	}else{
		right = mSaveTexVer[E_RIGHT];
	}

	/*�v�Z*/
	CConvenient::LoopPlus(&left, speed, mSaveInitTexVer[E_RIGHT], mSaveInitTexVer[E_LEFT]);
	CConvenient::LoopPlus(&right, speed, mSaveInitTexVer[E_RIGHT] + mTexScrollSideInit,
		mSaveInitTexVer[E_LEFT] + mTexScrollSideInit);
	SetUv(mpTexture, left, top, right, bottom);

}


/*�e�N�X�`���c�X�N���[���֐�*/
void CRectangle2::TexVerticalScroll(float speed){
	float left, top, right, bottom;
	/*�ۑ�*/
	left = mSaveTexVer[E_LEFT];
	top = mSaveTexVer[E_TOP];
	right = mSaveTexVer[E_RIGHT];
	bottom = mSaveTexVer[E_BOTTOM];
	/*�v�Z*/
	CConvenient::LoopPlus(&top, speed, mSaveInitTexVer[E_TOP], mSaveInitTexVer[E_BOTTOM]);
	CConvenient::LoopPlus(&bottom, speed, mSaveInitTexVer[E_TOP], mSaveInitTexVer[E_BOTTOM]);
	SetUv(mpTexture, left, top, right, bottom);

}