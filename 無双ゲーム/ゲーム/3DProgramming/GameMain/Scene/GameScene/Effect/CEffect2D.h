//�y�c���l
#ifndef CEffect2D_HPP
#define CEffect2D_HPP
#include  "../../../Task/CTask.h"
#include "../../../Graphic/CRectangle.h"
#define TIP_ARRAY 11

/*�G�t�F�N�g�T�C�Y*/
#define EFF_SIZE(x,y)CVector3(-x,y,0.0f),\
	CVector3(-x, -y, 0.0f), \
	CVector3(x, -y, 0.0f), \
	CVector3(x, y, 0.0f)
/*�n���}�[�G�t�F�N�g�T�C�Y*/
#define HAMMER_EFFECT_SIZE	CVector3 (-0.1f, 0.1f,0.0f),\
	CVector3(-0.1f, -0.1f, 0.0f), \
	CVector3(0.1f, -0.1f, 0.0f), \
	CVector3(0.1f, 0.1f, 0.0f)
#define HAMMER_EFFECT_POS CVector3(0.0f, 0.8f, 0.0f)
#define HAMMER_SIZE_UP 0.002f //�T�C�Y�A�b�v����X�s�[�h

/*�G�t�F�N�g�̃|�W�V����*/
#define SPARK_EFFECT_POS CVector3(0.0f, 1.0f, 0.0f)

/*�e�N�X�`���̃G�t�F�N�g�T�C�Y*/
#define TEX_HAMMER_EFFECT_SIZE 0,0,960,192
#define TEX_HAMMER_EFFECT_WIDTH 192 //��
#define TEX_HAMMER_EFFECT_ANI_SIZE 5
/*�S�[��*/
#define TEX_SPARK_EFFECT_SIZE 0,0,1125,225
#define TEX_SPARK_EFFECT_WIDTH 225 //��
#define TEX_SPARK_EFFECT_ANI_SIZE 5

class CEffect2D : public CRectangle ,public CTask{
private:
	CTexture mTex;/*�e�N�X�`��*/
	float mAnimaCount;//���݂̖���
	float mAnimaSize;//�������邩
	float mAnimaFrameNum; //���݂̃i���o�[��
	float mTimeCount;//�J�E���g�p
	float mAnimaFrameMax; //�A�j���[�V�����̍ő�Frame���z�񐔂Ȃ̂Œ���
	float *mpWidthLeft, *mpWidthRight;//��
	float mTexLeft, mTexTop, mTexRight, mTexBottom; //�c��
	float mAnimaSpeed;//�Đ��X�s�[�h
	bool mAnimaFlag;//�A�j���[�V�������X�^�[�g���邩���߂�

	enum E_VER{
		E_LT,//����
		E_LB,//����
		E_RB,//�E��
		E_RT, //�E��
		E_ARRAY
	};
	CVector3 ver[E_ARRAY];//���_��
public:
	~CEffect2D();
	CEffect2D();
	/*�T�C�Y�w��*/
	void SetVertex(CVector3 v0, CVector3 v1, CVector3 v2, CVector3 v3);
	/*�A�j���[�V���������ƊԊu�w��*/
	void SetAnima(int size,float width);
	/*���݂̃t���[�����w��*/
	void SetFrame(int i);
	/*�T�C�Y�A�b�v*/
	void SizeUp(float up);
	/*�e�N�X�`���\��t��*/
	void SetTex(CTexture *name, float left, float top, float right, float bottom);
	/*�X�V����*/
	void Update();
	/*�`�揈��*/
	void Render();
	/*�A�j���[�V�����t���O��true��,�����ōĐ��X�s�[�h�ƃ|�W�V���������߂�*/
	void StartAnima(float speed ,CVector3 pos);
	/*�A�j���[�V�����t���O��false��*/
	void DisableAnima();

	/*�����ݒ�*/
	void CEffect2D::Init(char *name, float x, float y, STexVer texVer);
	/*�e�N�X�`��������Ƃ��̏�����*/
	void NoTexInit();



};
#endif
