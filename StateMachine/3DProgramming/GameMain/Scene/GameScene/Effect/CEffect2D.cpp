//�x�c���l
#include"CEffect2D.h"
#include <fstream> 
#include "../../../../Define/Define.h"
#include "../../../Camera/CCamera.h"
#include "../../../Convenient/CConvenient.h"
#include "../../../Graphic/CLoadTexManager.h"
/*�A�j���[�V�����ς��X�s�[�h*/
#define ANIMA_SPEED 0.05f
/*�傫�������p*/
#define SIZE_UP_DIVIDE 3.0f //�T�C�Y�����p
/*�@������*/
#define VEC_NORMAL 1.0f,1.0f,0.0f
#include<stdio.h>



CEffect2D::CEffect2D() : mAnimaCount(0), mAnimaSize(0), mTimeCount(0), 
mAnimaFrameNum(0), mAnimaFrameMax(0), mAnimaFlag(false){}

CEffect2D::~CEffect2D(){}

/*�A�j���[�V�����ݒ�*/
void CEffect2D::SetAnima(int size, float width){
	mAnimaFrameMax = size; //Frame�ő吔�L�^ 
	mpWidthLeft = new float[size]; //�T�C�Y�ۑ�
	mpWidthRight = new float[size]; //�T�C�Y�ۑ�
	for (int i = 1; i <= size; i++){
		mpWidthLeft[i - 1] = i * width - width;
		mpWidthRight[i - 1] = width * i;
	}
	SetFrame(0);//�����l�ɐݒ�

}
/*�T�C�Y�w��*/
void CEffect2D::SetVertex(CVector3 v0, CVector3 v1, CVector3 v2, CVector3 v3){
	ver[E_LT] = v0;
	ver[E_LB] = v1;
	ver[E_RB] = v2;
	ver[E_RT] = v3;
	CRectangle::SetVertex(ver[E_LT], ver[E_LB], ver[E_RB], ver[E_RT]);
}
/*���݂̃t���[�����w��*/
void CEffect2D::SetFrame(int i){
	SetUv(mpTexture, mpWidthLeft[i], mTexTop, mpWidthRight[i], mTexBottom);
}
/*�e�N�X�`���ݒ�*/
void CEffect2D::SetTex(CTexture *name,float left,float top,float right,float bottom){
	mTexLeft = left;
	mTexTop = top;
	mTexRight = right;
	mTexBottom = bottom;
	mpTexture = name;
	SetUv(mpTexture, left, top, right, bottom);
}
/*�X�V����*/
void CEffect2D::Update(CVector3 pos){
	/*�A�j���[�V������flag�����Ɛi�߂�*/
	if (mAnimaFlag){
		if (CConvenient::Time(&mTimeCount, ANIMA_SPEED)){
			mAnimaFrameNum++;//�R�}��i�߂�
			SetFrame(mAnimaFrameNum);//�A�j���[�V�����R�}�w��
			if (mAnimaFrameMax - 1 == mAnimaFrameNum){//�ő�l�̏ꍇ
				mAnimaFrameNum = 0;//�J�E���g���[����
			}
			mTimeCount = 0;//�J�E���g�����Z�b�g
		}
	}
	/*�r���{�[�h�ݒ�*/
	mpCamera = &MainCamera; 
	mMatrix.identity();
	mMatrix.translate(pos);
	mMatrix = mMatrix * mpCamera->mCameraInverse;

}
/*�T�C�Y�A�b�v*/
void CEffect2D::SizeUp(float up){
	
	
	for (int i = 0; i < CEffect2D::E_ARRAY; i++)
	{
		if (ver[i].x < 6.0f&&ver[i].y < 6.0f){
			ver[i].x += CConvenient::plmi(ver[i].x)*up*SIZE_UP_DIVIDE;
			ver[i].y += CConvenient::plmi(ver[i].y)*up *SIZE_UP_DIVIDE;
		}
	}
	SetVertex(ver[E_LT], ver[E_LB], ver[E_RB], ver[E_RT]);
}
void CEffect2D::Render(){
	/*�}�g���b�N�X�̌v�Z*/
	glPushMatrix();
	glMultMatrixf(mMatrix.f);
	/*�`��*/
	CRectangle::Render();
	glPopMatrix();

}
/*�A�j���[�V�����t���O��true��*/
void CEffect2D::EnableAnima(){
	mAnimaFlag = true;
}
/*�A�j���[�V�����t���O��false��*/
void CEffect2D::DisableAnima(){
	mAnimaFlag = false;
}

/*�����̒l�ɖ߂�*/
void CEffect2D::Init(CEffect2D::E_STATUS eStatus){
	switch (eStatus)
	{
		/*�n���}�[*/
	case CEffect2D::E_HAMMER:
		/*�n���}�[�G�t�F�N�g����������*/
		SetVertex(HAMMER_EFFECT_SIZE);
		SetDiffuse(WHITE_COLOR);
		SetNormal(VEC_NORMAL);
		SetTex(CLoadTexManager::GetInstance()->mpHammer, TEX_HAMMER_EFFECT_SIZE);
		SetAnima(TEX_HAMMER_EFFECT_ANI_SIZE, TEX_HAMMER_EFFECT_WIDTH);
		break;
		/*�S�[��*/
	case CEffect2D::E_SPARK:

		/*�S�[���G�t�F�N�g����������*/
		SetVertex(SPARK_EFFECT_SIZE);
		SetDiffuse(WHITE_COLOR);
		SetNormal(VEC_NORMAL);
		SetTex(CLoadTexManager::GetInstance()->mpSpark, TEX_SPARK_EFFECT_SIZE);
		SetAnima(TEX_SPARK_EFFECT_ANI_SIZE, TEX_SPARK_EFFECT_WIDTH);
		break;
	}


}
/*�e�N�X�`��������Ƃ��̏�����*/
void CEffect2D::NoTexInit(){
	/*�n���}�[�G�t�F�N�g����������*/
	SetVertex(HAMMER_EFFECT_SIZE);
	SetFrame(0);//�����l�ɐݒ�
}