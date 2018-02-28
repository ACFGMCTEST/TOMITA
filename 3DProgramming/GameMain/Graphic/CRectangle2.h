/*
�l�p�`�̃x�[�X�N���X()
�S���� �y�c���l
*/
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "CTriangle2.h"	//�O�p�`�N���X�̃w�b�_���C���N���[�h����
#include "../Vector/CVector2.h"	//2�����x�N�g���̃w�b�_���C���N���[�h����
#include "CTexture.h"
#include "../../Define/Define.h"


/*�����`�N���X*/
class  CRectangle2 {
private:
	/*�F���ő�l�ȏゾ�Ɩ߂�
	limit = �ő�l
	*num = �ύX���鐔
	*/
	void LimitEqual(float *num,float Limit);

	/*Flashing�֐��Ŏg��*/
	enum COLOR{
		UP, DOWN
	};

	COLOR eState = UP;
	/*�g��k���֐��̘A���Ŏg��*/
	enum E_Scalling{
		E_One, E_BIG, E_SMALL, //�P���̎�
		E_BIGREPEAT, E_SMALLREPEAT,//�A���̎�
		E_BIGONE, E_SMALLONE,//�P�񂾂��̎�
		E_BIGONE_OUT, E_SMALLONE_OUT,//�P�񂾂��I���̎�
	};
	E_Scalling eScalling = E_One;
	float m_BigX, m_BigY;//�傫���ق��L��
	float m_SmallX, m_SmallY;//�������ق��L��
	float m_ChangeSaveX, m_ChangeSaveY;//�l���ς�������f�p


public:
	CTriangle2	triangle1;	//�O�p�`�N���X�̎O�p�`�P
	CTriangle2	triangle2;	//�O�p�`�N���X�̎O�p�`�Q

	CVector2	position;	//��ʒu

	CTexture	*ptexture;
	float		uv[2][6];
	int degree;
	bool deg_enabled;
	float *mRLeft;
	float *mRRight;
	float *mRTop;
	float *mRBottom;
	/* ���_�P�`�R��X���W�AY���W�ƕ`��F�̒l�������ݒ肷��
	CRectangle(float left, float top, float right, float bottom, float r, float g, float b, float a)
	[in] left	���[�̒l
	[in] top	�㕔�̒l
	[in] right	�E�[�̒l
	[in] bottom	�����̒l
	[in] ir �Ԃ̒l�i0.0f�`1.0f�j
	[in] ig �΂̒l�i0.0f�`1.0f�j
	[in] ib �̒l�i0.0f�`1.0f�j
	[in] ia �����x�̒l�i0.0f�F�����`1.0f�F�s�����j
	*/
	CRectangle2(float left, float top, float right, float bottom, float r, float g, float b, float a);

	CRectangle2(float left, float top, float right, float bottom, float r, float g, float b, float a, CVector2 pos);
	CRectangle2();

	//�`�悷��
	void Render();

	/*
	left	�摜�̍���[�����_(0,0)�Ƃ��A�\��t�������̈�̍��̍��W�l
	top		�摜�̍���[�����_(0,0)�Ƃ��A�\��t�������̈�̏�̍��W�l
	right	�摜�̍���[�����_(0,0)�Ƃ��A�\��t�������̈�̉E�̍��W�l
	bottom	�摜�̍���[�����_(0,0)�Ƃ��A�\��t�������̈�̉��̍��W�l
	*/
	void SetUv(CTexture *t, int left, int top, int right, int bottom);
	/* setVertex
	left:����x���W
	top:���y���W
	right:�E��x���W
	bottom:����y���W
	�l�p�`�̊e���_�̍��W��ݒ肷��
	*/
	void SetVertex(float left, float top, float right, float bottom);
	/* setColor
	r:��(0.0�`1.0)
	g:��(0.0�`1.0)
	b:��(0.0�`1.0)
	a:�A���t�@(0.0�����`1.0�s����)
	�l�p�`�̐F��ݒ肷��
	*/
	void SetColor(float r, float g, float b, float a);
	/*
	�t�F�[�h�֐� speed = �t�F�[�h�̑���
	a = ALPHA
	*/
	void Fade(float speed, float a);
	/*
	�t�F�[�h�֐� speed = �t�F�[�h�̑���
	a = ALPHA
	*/
	void FadeOut(float speed, float a);

	/*�F�̓_�Ŋ֐�*/
	void ColorUp(float speed);
	void ColorDown(float speed);
	void FlashingColor(float speed);
	/*Gradation���[�v�֐��Ŏg������*/
	/*�J���[���ύX����*/
	enum E_COLOR_CHANGE{
		E_GREEN_YELLOW,	//�΂��物
		E_YELLOW_RED,	//�������
		E_RED_PURPLE,	//�Ԃ��率
		E_PURPLE_BLUE,	//�������
		E_BLUE_CYAN,	//�����
		E_CYAN_GREEN,	//�΂����
	};
	E_COLOR_CHANGE eColorChange;
	/*�O���f�[�V���������֐�
	�ǂ�����X�^�[�g���邩���߂�
	*/
	void SetGradationLoop(E_COLOR_CHANGE state);
	/*�O���f�[�V�����̃��[�v�֐�
	�F���Ƀ��[�v����֐�
	speed = ����
	*/
	void GradationLoop(float speed);
	/*�g��k���֐�
	state �傫�����鏬�������錈�߂�
	��,���@�g��k���̒l�@�v���X�����w��
	time ���܂łɏ������邩�̎���
	*/
	void RectScaling(float x, float y, float time);

	/*�A���o�[�W����
	��,���@�g��k���̒l�@�v���X�����w��
	flag�@false�͂P��A�������� true�͂����ƘA������
	*/
	void RectScaling(float x, float y, float time, bool flag);

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
	static void Disp2D_Start(){
		/*�`�揀��*/
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(-DISP_2D_X,DISP_2D_X,-DISP_2D_Y,DISP_2D_Y);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	}
	/*2D�������I�����鏈��*/
	static void Disp2D_Exit(){
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glDisable(GL_BLEND);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
	}
};

#endif