#ifndef TRIANGULAR_PRISM_H
#define TRIANGULAR_PRISM_H

#include "CShader.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CTexture.h"
#include "../../3DBase/C3DBase.h"
#include "../Vector/CVector2.h"
#include "../../Define/Define.h"

/*�ʂ̐�*/
#define BOX_FACE_NUM 6

class CTriangularPrism :public C3DBase{
private:
	CTexture *mpTextrue;//�e�N�X�`��

public:
	enum E_COLOR{
		E_RED,//��
		E_GREEN,//��
		E_BLUE,//��
		E_ALPHA,//�����x
		E_ARRAY,//�z��
	};
	float mDiffuse[E_ARRAY];//�J���[�ݒ�
	/*�l�p�`_�ʂ̕���*/
	enum E_RECT_FACE{
		E_BACK,//���
		E_BOTTOM,//��
		E_SLANTING,//�ȂȂ�
		E_RECT_ARRAY,//�z��
	};
	/*��*/
	CRectangle mRect[E_RECT_FACE::E_RECT_ARRAY];	//�ʂ�3��
	/*�O�p�`_�ʂ̕���*/
	enum E_TRIANGLE_FACE{
		E_LEFT,//��
		E_RIGHT,//�E
		E_TRI_ARRAY,//�z��
	};
	CTriangle mTriangle[E_TRIANGLE_FACE::E_TRI_ARRAY];//�ʂ����


	//���_�f�[�^�̐ݒ� 1�̂ق����}�C�i�X�ŊO���@1�̂ق����v���X�œ���
	void SetVertex(float x1, float x2, float y1, float y2, float z1, float z2);
	enum E_TexBox 
	{
		E_SLOPE,			//��
	};
	E_TexBox eTexState;
	//�e�N�X�`���̐ݒ�
	void SetTex(E_TexBox eTexState);

	//�F�w��
	void SetColor(float r, float g, float b, float a);

	//���ׂĂ�UV�𓯂���
	void AllUV(CTexture *texture, int left, int top, int right, int bottom);


	//�`�揈��
	void Render();

	/*�傫����ς���֐�
	float Double �́@�{��������
	*/
	void SizeDouble(float Double);

	/*�e�N�X�`�����X�N���[���֐�*/
	void TexSideScroll(float speed);
	/*�e�N�X�`���c�X�N���[���֐�*/
	void TexVerticalScroll(float speed);

};

#endif