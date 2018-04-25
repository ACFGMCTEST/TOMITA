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


/*�T�C�Y�}�N��*/
#define BUTTON_SIZE(Double,x,y) -Double*x,Double*y,Double*x,-Double*y //�w�i�̃T�C�Y ���S�̒����p
#define BG_SIZE -DISP_X,DISP_Y,DISP_X,-DISP_Y //�w�i�̃T�C�Y
#define CURSOR_SIZE -10.0f,10.0f,10.0f,-10.0f//�J�[�\���̃T�C�Y
/*�|�W�V�����ړ�*/
#define BUTTON_POS(x,y) CVector2(DISP_X*x,DISP_Y*y)

/*�����`�N���X*/
class  CRectangle2 {
private:
	
	bool mFlagSaveTex;//�e�N�X�`�����Z�[�u���ꂽ�����f

	int mTexScrollSideInit;//�����̏ꏊ�ۑ�

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
	
	/*�������_�ݒ肳�ꂽ��*/
	bool mFlagVerInit;
	/*�����l���_�ꏊ*/
	float mSaveRight;
	float mSaveTop;
	float mSaveLeft;
	float mSaveBottom;

public:
	/*�e�N�X�`���̏c���ۊ�*/
	enum  E_TEXVER
	{
		E_TOP,
		E_BOTTOM,
		E_LEFT,
		E_RIGHT,
		E_ARRAY
	};
	float mSaveInitTexVer[E_ARRAY];//�e�N�X�`���̃T�C�Y�ۑ� ���߂̒l
	float mSaveTexVer[E_ARRAY];//�e�N�X�`���̃T�C�Y�ۑ� ���݂̒l

	CTriangle2	mTriangle1;	//�O�p�`�N���X�̎O�p�`�P
	CTriangle2	mTriangle2;	//�O�p�`�N���X�̎O�p�`�Q

	CVector2	mPosition;	//��ʒu
	CVector2	*mpPos;		//�A�h���X���������ꍇ�͂�������D��

	CTexture	*mpTexture;
	float		uv[2][6];

	int mDegree;//��]�ϐ�
	bool mFlagDeg;//��]���f

	/*���_*/
	float *mpLeft;
	float *mpRight;
	float *mpTop;
	float *mpBottom;
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
	void SetUv(CTexture *t, float left, float top, float right, float bottom);
	/*�e�N�X�`������ꍇ*/
	void Uv(float left, float top, float right, float bottom);
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

	/*�F�̊֐��@�A�b�v*/
	void ColorUp(float speed);
	/*�F�̊֐��@�_�E��*/
	void ColorDown(float speed);
	/*�F�̓_���֐�
	speed = ����
	upLimit = �J���[�A�b�v�̏��
	downLimit = �J���[�_�E���̏��
	*/
	void FlashingColor(float speed,float upLimit,float downLimit);
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
	double�@�g��k���̒l
	time ���܂łɏ������邩�̎���
	*/
	void RectScaling(float Double, float time);
	/*�g��k���֐� ���������Ȃ��o�[�W����
	double�@�g��k���̒l
	time ���܂łɏ������邩�̎���
	*/
	void RectScalingLeftPos(float Double, float time);
	
	/*��]������悤*/
	void CRectangle2::SetUvRot();
	/*2D�������J�n���鏈��*/
	static void Disp2D_Start();
	/*2D�������I�����鏈��*/
	static void Disp2D_Exit();

	/*�e�N�X�`�����X�N���[���֐�
	speed = Scroll�̑���
	InitSide =  Scroll�J�n�̉���
	*/
	void TexSideScroll(float speed,int InitSide);
	/*�e�N�X�`���c�X�N���[���֐�*/
	void TexVerticalScroll(float speed);

};

#endif