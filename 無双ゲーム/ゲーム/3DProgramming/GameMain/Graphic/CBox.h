#ifndef CBOX_H
#define CBOX_H
#include "CShader.h"
#include "CRectangle.h"
#include "CTexture.h"
#include "../../3DBase/C3DBase.h"
#include "../Vector/CVector2.h"
#include "../../Define/Define.h"

/*�ʂ̐�*/
#define BOX_FACE_NUM 6
/*�{�b�N�X�̍��W������ �V�F�[�_�[�p*/
class CBoxVertex{
public:
	CVector3 mPosition;
	CVector3 mNormal;
	float mColor[4];
	CVector2 mTextureCoords;

	CBoxVertex(){}
};


class CBox :public C3DBase{
private:
	CTexture *mpTextrue;//�e�N�X�`��

public:
	float mDiffuse[4];//�J���[�ݒ�
	float *mColorRGBA[4];//�J���[�ݒ�

	CRectangle mRect[6];	//�ʂ�6��
	GLuint	mMyVertexBuffer;
	
	/*�傫���L���p*/
	float mSize;
	/*���_�ꏊ*/
	enum E_VER{
		E_x1, E_x2, E_z1, E_z2, E_y1, E_y2
	};

	//���_�f�[�^�̐ݒ� 1�̂ق����}�C�i�X�ŊO���@1�̂ق����v���X�œ���
	void SetVertex(float size);
	enum E_TexBox 
	{
		E_SKY_BOX,
	};
	E_TexBox eTexState;
	//�e�N�X�`���̐ݒ�
	void SetTex(E_TexBox eTexState);

	//�F�w��
	void SetColor(float r,float g,float b,float a){
		for (int i = 0; i < 6; i++){
			mRect[i].SetDiffuse(r, g, b, a);
		}
	}

	//���ׂĂ�UV�𓯂���
	void AllUV(CTexture *texture, int left, int top, int right, int bottom);
	/*�t�F�[�h�C��*/
	void Fade(float speed,float a){
		for (int i = 0; i < 6; i++){
			mRect[i].Fade(speed, a);

		}
	}
	/*�t�F�[�h�A�E�g*/
	void FadeOut(float speed, float a){
		for (int i = 0; i < 6; i++){
			mRect[i].FadeOut(speed, a);
		}
	}

	//�`�揈��
	void Render();
	/*�オ�Ȃ��o�[�W����*/
	void Render2();
	/*���̂�*/
	void RenderTop();

	/*�R���X�g���N�^*/
	CBox() :mSize(0.0f){
		for (int i = 0; i < 6; i++) mRect[i].SetDiffuse(1.0f, 1.0f, 0.0f, 1.0f);

	}
	

	/*�e�N�X�`�����X�N���[���֐�*/
	void TexSideScroll(float speed);
	/*�e�N�X�`���c�X�N���[���֐�*/
	void TexVerticalScroll(float speed);

};

#endif