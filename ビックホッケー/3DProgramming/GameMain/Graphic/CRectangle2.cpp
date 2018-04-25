#include "CRectangle2.h"
#include "../Define/Define.h"
#include "../Convenient/CConvenient.h"

/*�P�̂�COLOR��1.0f��肢���Ȃ��悤�ɂ���*/
#define LIMIT_COLOR 1.0f

CRectangle2::CRectangle2(float left, float top, float right, float bottom, float r, float g, float b, float a)
:	//�O�p�`�N���X�̃R���X�g���N�^���Ă�
triangle1(left, top, left, bottom, right, bottom, r, g, b, a),
triangle2(left, top, right, bottom, right, top, r, g, b, a), ptexture(0), degree(0)
{}



CRectangle2::CRectangle2(float left, float top, float right, float bottom, float r, float g, float b, float a, CVector2 pos)
:	//�O�p�`�N���X�̃R���X�g���N�^���Ă�
triangle1(left, top, left, bottom, right, bottom, r, g, b, a),
triangle2(left, top, right, bottom, right, top, r, g, b, a), position(pos), ptexture(0), degree(0)
{};


CRectangle2::CRectangle2() :ptexture(0), deg_enabled(false), degree(0), 
m_BigX(0.0f), m_BigY(0.0f), m_SmallX(0.0f), m_SmallY(0.0f), position(0.0f, 0.0f){}



//�`�悷��
void CRectangle2::Render() {


	if (degree != 0 || deg_enabled){ //���l�p���ǂ���
		if (ptexture != 0){ //�e�N�X�`�������邩�ǂ���
			//�e�N�X�`����L���ɂ���
			glEnable(GL_TEXTURE_2D);
			//�A���t�@�u�����h��L���ɂ���
			glEnable(GL_BLEND);
			//�u�����h���@���w��
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//�e�N�X�`�����w��
			glBindTexture(GL_TEXTURE_2D, ptexture->id);
			//�O�p�`1�̕`��
			triangle1.Render(position, degree, uv[0]);
			//�O�p�`2�̕`��
			triangle2.Render(position, degree, uv[1]);
			//�e�N�X�`�������
			glBindTexture(GL_TEXTURE_2D, 0);
			//�A���t�@�u�����h�𖳌�
			glDisable(GL_BLEND);
			//�e�N�X�`���𖳌�
			glDisable(GL_TEXTURE_2D);
		}
		else{
			triangle1.Render(position, degree);
			triangle2.Render(position, degree);
			deg_enabled = true;
		}
	}
	else if (ptexture == 0) {
		triangle1.Render(position);	//�O�p�`�P��`�悷��
		triangle2.Render(position);	//�O�p�`�Q��`�悷��
	}
	else {
		//�e�N�X�`����L���ɂ���
		glEnable(GL_TEXTURE_2D);
		//�A���t�@�u�����h��L���ɂ���
		glEnable(GL_BLEND);
		//�u�����h���@���w��
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//�e�N�X�`�����w��
		glBindTexture(GL_TEXTURE_2D, ptexture->id);
		//�O�p�`1�̕`��
		triangle1.Render(position, uv[0]);
		//�O�p�`2�̕`��
		triangle2.Render(position, uv[1]);
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

void CRectangle2::SetUv(CTexture *t, int left, int top, int right, int bottom) {
	ptexture = t;
	uv[0][0] = uv[1][0] = (float)left / ptexture->header.width;
	uv[0][1] = uv[1][1] = (float)(ptexture->header.height - top) / ptexture->header.height;
	uv[0][2] = (float)left / ptexture->header.width;
	uv[0][3] = (float)(ptexture->header.height - bottom) / ptexture->header.height;
	uv[0][4] = uv[1][2] = (float)right / ptexture->header.width;
	uv[0][5] = uv[1][3] = (float)(ptexture->header.height - bottom) / ptexture->header.height;
	uv[1][4] = (float)right / ptexture->header.width;
	uv[1][5] = (float)(ptexture->header.height - top) / ptexture->header.height;
}
void CRectangle2::Uv(int left, int top, int right, int bottom) {
	/*�e�N�X�`��������ꍇ*/
	if (ptexture){
		SetUv(ptexture, left, top, right, bottom);
	}
	else{
		printf("�e�N�X�`���������Ă��܂���.SetUv()�œ\���Ă�������\n");
	}

}

void CRectangle2::SetVertex(float left, float top, float right, float bottom) {

	triangle1.x1 = left; triangle1.y1 = top;
	triangle1.x2 = left; triangle1.y2 = bottom;
	triangle1.x3 = right; triangle1.y3 = bottom;
	triangle2.x1 = left; triangle2.y1 = top;
	triangle2.x2 = right; triangle2.y2 = bottom;
	triangle2.x3 = right; triangle2.y3 = top;
	triangle1.v1 = CVector2(left, top); triangle1.v2 = CVector2(left, bottom); triangle1.v3 = CVector2(right, bottom);
	triangle2.v1 = CVector2(left, top); triangle2.v2 = CVector2(right, bottom); triangle2.v3 = CVector2(right, top);
	mRLeft = &triangle1.x1;
	mRRight = &triangle1.x3;
	mRBottom = &triangle1.y3;
	mRTop = &triangle2.y1;

}

void CRectangle2::SetColor(float r, float g, float b, float a) {
	/*1�Ԗ�*/
	CConvenient::LimitEqual(&triangle1.r, r, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&triangle1.g, g, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&triangle1.b, b, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&triangle1.a, a, LIMIT_COLOR, 0.0f);
	/*2�Ԗ�*/
	CConvenient::LimitEqual(&triangle2.r, r, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&triangle2.g, g, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&triangle2.b, b, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&triangle2.a, a, LIMIT_COLOR, 0.0f);
}

/*�t�F�[�h�֐�*/
#define SET_C3 triangle1.r,triangle1.g,triangle1.b //���̎l�p�`rgb


void CRectangle2::Fade(float speed, float a){
	float mFade4 = triangle1.a + speed;		//�t�F�[�h�֐��Ŏg��
	mFade4 += speed;
	if (mFade4 >= a){
		mFade4 = a;
	}
	SetColor(SET_C3, mFade4);
}

/*�t�F�[�h�֐�*/
void CRectangle2::FadeOut(float speed, float a){
	float mFade4 = triangle1.a - speed;		//�t�F�[�h�֐��Ŏg��
	mFade4 -= speed;
	if (mFade4 <= a){
		mFade4 = a;
	}
	SetColor(SET_C3, mFade4);
}
#define FLASHING_DOWN__C4 \
	triangle1.r - speed, \
	triangle1.g - speed, \
	triangle1.b - speed, \
	triangle1.a - speed //���̎l�p�`rgba

#define FLASHING_UP__C4 \
	triangle1.r + speed, \
	triangle1.g + speed, \
	triangle1.b + speed, \
	triangle1.a + speed //���̎l�p�`rgba

//�FDOWN
void CRectangle2::ColorDown(float speed){
	if (triangle1.r > 0.0f){
		SetColor(FLASHING_DOWN__C4);
	}
	if (triangle1.r <= 0){
		SetColor(0.0f, 0.0f, 0.0f, triangle1.a);
	}
}
/*�FUP*/
void CRectangle2::ColorUp(float speed){
	if (triangle1.r < 1.0f){
		SetColor(FLASHING_UP__C4);
	}
	if (triangle1.r <= 0){
		SetColor(1.0f, 1.0f, 1.0f, triangle1.a);
	}
}
/*�F�̓_��*/
void CRectangle2::FlashingColor(float speed){
	switch (eState)
	{
	case UP:
		SetColor(FLASHING_UP__C4);
		if (triangle1.r >= 1.0f){
			eState = DOWN;
		}
		break;
	case DOWN:
		SetColor(FLASHING_DOWN__C4);
		if (triangle1.r <= 0){
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
	red = triangle1.r;
	green = triangle1.g;
	blue = triangle1.b;
	alpha = triangle1.a;
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
void CRectangle2::RectScaling(float x, float y, float time){
	float speedx, speedy;
	speedx = time / FPS;
	speedy = time / FPS;
	switch (eScalling)
	{
		/*�g�傩�k�����f*/
	case CRectangle2::E_One:
		if (*mRRight <= x){
			/*�傫���̋L��*/
			m_BigX = x;
			m_BigY = y;
			m_SmallX = *mRRight;
			m_SmallY = *mRTop;
			/*�؂�ւ�����*/
			eScalling = CRectangle2::E_BIG;
		}
		else{
			/*�傫���L��*/
			m_BigX = *mRRight;
			m_BigY = *mRTop;
			m_SmallX = x;
			m_SmallY = y;
			/*�؂�ւ�����*/
			eScalling = CRectangle2::E_SMALL;
		}
		m_ChangeSaveX = x;
		m_ChangeSaveY = y;
		break;
		/*�傫���Ȃ鏈��*/
	case CRectangle2::E_BIG:
	case CRectangle2::E_BIGREPEAT:
	case CRectangle2::E_BIGONE:
	case CRectangle2::E_BIGONE_OUT:
		/*X�g��*/
		if (*mRRight < m_BigX){
			SetVertex(*mRLeft - speedx, *mRTop, *mRRight + speedx, *mRBottom);
		}
		else{
			SetVertex(-m_BigX, *mRTop, m_BigX, *mRBottom);

		}
		/*�x�g��*/
		if (*mRTop < m_BigY){
			SetVertex(*mRLeft, *mRTop + speedy, *mRRight, *mRBottom - speedy);
		}
		else{
			SetVertex(*mRLeft, m_BigY, *mRRight, -m_BigY);
		}
		/*�����l���ς������*/
		if (eScalling == E_BIG && x != m_ChangeSaveX ||
			eScalling == E_BIG &&y != m_ChangeSaveY){
			eScalling = CRectangle2::E_One;
		}

		break;
		/*�������Ȃ鏈��*/
	case CRectangle2::E_SMALL:
	case CRectangle2::E_SMALLREPEAT:
	case CRectangle2::E_SMALLONE:
	case CRectangle2::E_SMALLONE_OUT:

		/*X�k��*/

		if (*mRRight > m_SmallX){
			SetVertex(*mRLeft + speedx, *mRTop, *mRRight - speedx, *mRBottom);
		}
		else{
			SetVertex(-m_SmallX, *mRTop, m_SmallX, *mRBottom);

		}
		/*�x�k��*/
		if (*mRTop > m_SmallY){
			SetVertex(*mRLeft, *mRTop - speedy, *mRRight, *mRBottom + speedy);
		}
		else{
			SetVertex(*mRLeft, m_SmallY, *mRRight, -m_SmallY);
		}
		/*�����l���ς������*/
		if (eScalling == E_SMALL && x != m_ChangeSaveX ||
			eScalling == E_SMALL && y != m_ChangeSaveY){
			eScalling = CRectangle2::E_One;
		}

		break;
	};

}
/*�A���o�[�W����*/
void CRectangle2::RectScaling(float x, float y, float time, bool flag){

	switch (flag)
	{
		/*�A��������*/
	case true:
		switch (eScalling)
		{
		case CRectangle2::E_One:
			if (*mRRight <= x){
				/*�傫���̋L��*/
				m_BigX = x;
				m_BigY = y;
				m_SmallX = *mRRight;
				m_SmallY = *mRTop;
				/*�؂�ւ�����*/
				eScalling = CRectangle2::E_BIGREPEAT;
			}
			else{
				/*�傫���L��*/
				m_BigX = *mRRight;
				m_BigY = *mRTop;
				m_SmallX = x;
				m_SmallY = y;
				/*�؂�ւ�����*/
				eScalling = CRectangle2::E_SMALLREPEAT;
			}
			break;
		case CRectangle2::E_BIGREPEAT:
			/*�g��k��*/
			RectScaling(m_BigX, m_BigY, time);
			if (*mRRight >= m_BigX && *mRTop >= m_BigY){ //���E�܂ő傫���Ȃ��
				eScalling = CRectangle2::E_SMALL;
			}
			break;
		case CRectangle2::E_SMALLREPEAT:
			/*�g��k��*/
			RectScaling(m_SmallX, m_SmallY, time);
			if (*mRRight <= m_SmallX && *mRTop <= m_SmallY){ //���E�܂ŏ������Ȃ��
				eScalling = CRectangle2::E_BIG;
			}
			break;
		};
		break;
		/*��񂾂��A��������*/
	case false:
		switch (eScalling)
		{
		case CRectangle2::E_One:
			if (*mRRight <= x){
				/*�傫���̋L��*/
				m_BigX = x;
				m_BigY = y;
				m_SmallX = *mRRight;
				m_SmallY = *mRTop;
				/*�؂�ւ�����*/
				eScalling = CRectangle2::E_BIGONE;
			}
			else{
				/*�傫���L��*/
				m_BigX = *mRRight;
				m_BigY = *mRTop;
				m_SmallX = x;
				m_SmallY = y;
				/*�؂�ւ�����*/
				eScalling = CRectangle2::E_SMALLONE;
			}
			break;
		case CRectangle2::E_BIGONE:
			/*�g��k��*/
			RectScaling(m_BigX, m_BigX, time);
			if (*mRRight >= m_BigX && *mRTop >= m_BigY){ //���E�܂ő傫���Ȃ��
				eScalling = CRectangle2::E_SMALLONE_OUT;
			}
			break;
		case CRectangle2::E_SMALLONE:
			/*�g��k��*/
			RectScaling(m_SmallX, m_SmallY, time);
			if (*mRRight <= m_SmallX && *mRTop <= m_SmallY){ //���E�܂ŏ������Ȃ��
				eScalling = CRectangle2::E_BIGONE_OUT;
			}
		case CRectangle2::E_BIGONE_OUT:
			/*�g��k��*/
			RectScaling(m_BigX, m_BigX, time);
			if (*mRRight >= m_BigX && *mRTop >= m_BigY){ //���E�܂ő傫���Ȃ��
				break;
			}
			break;
		case CRectangle2::E_SMALLONE_OUT:
			/*�g��k��*/
			RectScaling(m_SmallX, m_SmallY, time);
			if (*mRRight <= m_SmallX && *mRTop <= m_SmallY){ //���E�܂ŏ������Ȃ��
				break;
			}
			break;
		};
		break;
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