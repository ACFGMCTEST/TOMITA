#ifndef CBOX_H
#define CBOX_H
#include "CShader.h"
#include "CRectangle.h"
#include "CTexture.h"
#include "../../Base/CBase.h"
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


class CBox :public CBase{
private:
	CTexture *mpTextrue;//�e�N�X�`��

public:
	float mDiffuse[4];//�J���[�ݒ�
	float *mColorRGBA[4];//�J���[�ݒ�

	CRectangle mRect[6];	//�ʂ�6��
	GLuint	mMyVertexBuffer;
	///*�I�[�������_�[�p*/
	//static CMatrix44 *mAllBoxTransformMatrixSize;
	//static int mAllBoxSize;
	//static GLuint mAllBoxMyVertexBuffer;
	//static CAllBoxVertex mAllBox;
	//CShader mShader;
	/*�傫���L���p*/
	float mSizeX1;
	float mSizeX2;
	float mSizeY1;
	float mSizeY2;
	float mSizeZ1;
	float mSizeZ2;

	/*���_�ꏊ*/
	enum E_VER{
		E_x1, E_x2, E_z1, E_z2, E_y1, E_y2
	};

	//���_�f�[�^�̐ݒ� 1�̂ق����}�C�i�X�ŊO���@1�̂ق����v���X�œ���
	void SetVertex(float x1, float x2, float y1, float y2, float z1, float z2);
	enum E_TexBox 
	{
		E_SPEED_UP,			//������
		E_SPEED_DOWN,		//������
		E_TRAMPOLINE,		//�g�����|����
		E_BOX,				//�{�b�N�X
		E_NET,				//��
		E_WALL,				//��
		E_SLOPE,			//��
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
	CBox() :mSizeX1(0.0f), mSizeX2(0.0f), mSizeY1(0.0f), mSizeY2(0.0f), mSizeZ1(0.0f), mSizeZ2(0.0f){
		for (int i = 0; i < 6; i++) mRect[i].SetDiffuse(1.0f, 1.0f, 0.0f, 1.0f);

	}


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