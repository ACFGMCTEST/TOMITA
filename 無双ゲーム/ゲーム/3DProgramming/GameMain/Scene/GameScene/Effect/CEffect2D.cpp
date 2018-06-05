//�x�c���l
#include"CEffect2D.h"
#include <fstream> 
#include "../../../../Define/Define.h"
#include "../../../Camera/CCamera.h"
#include "../../../Convenient/CConvenient.h"
#include "../../../Graphic/CLoadTexManager.h"
/*�傫�������p*/
#define SIZE_UP_DIVIDE 5.0f //�T�C�Y�����p
/*�@������*/
#define VEC_NORMAL 1.0f,1.0f,0.0f
#include<stdio.h>


CEffect2D::CEffect2D() : mAnimaCount(0), mAnimaSize(0), mTimeCount(0), 
mAnimaFrameNum(0), mAnimaFrameMax(0), mAnimaFlag(false), mpWidthLeft(0),mpWidthRight(0){
	CTask::eName = CTask::E_BILLBOARD;
}

CEffect2D::~CEffect2D(){
	/*�z�񂪂���ꍇ�폜*/
	P_ARRAY_DELETE(mpWidthLeft); 
	P_ARRAY_DELETE(mpWidthRight);
}

/*�A�j���[�V�����ݒ�*/
void CEffect2D::SetAnima(int size, float width){
	/*�z�񂪂���ꍇ�폜*/
	P_ARRAY_DELETE(mpWidthLeft); 
	P_ARRAY_DELETE(mpWidthRight);
	/*�̈�m��*/
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
void CEffect2D::Update(){
	/*�A�j���[�V������flag�����Ɛi�߂�*/
	if (mAnimaFlag){
		if (CConvenient::Time(&mTimeCount, mAnimaSpeed)){
			mAnimaFrameNum++;//�R�}��i�߂�
			SetFrame(mAnimaFrameNum);//�A�j���[�V�����R�}�w��
			if (mAnimaFrameMax - 1 == mAnimaFrameNum){//�ő�l�̏ꍇ
				mAnimaFrameNum = 0;//�J�E���g���[����
				mAnimaFlag = false;
			}
			mTimeCount = 0;//�J�E���g�����Z�b�g
		}
	}
	/*�r���{�[�h�ݒ�*/
	mpCamera = &MainCamera; 
	mMatrix.identity();
	mMatrix.translate(mPos);
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
	/*�t���O�����ƕ`��*/
	if (mAnimaFlag){
		/*�}�g���b�N�X�̌v�Z*/
		glPushMatrix();
		glMultMatrixf(mMatrix.f);
		/*�`��*/
		CRectangle::Render();
		glPopMatrix();
	}
}
/*�A�j���[�V�����t���O��true��*/
void CEffect2D::StartAnima(float speed, CVector3 pos){
	mAnimaSpeed = speed;
	mPos = pos;
	mAnimaFlag = true;
}
/*�A�j���[�V�����t���O��false��*/
void CEffect2D::DisableAnima(){
	mAnimaFlag = false;
}

/*�����̒l�ɖ߂�*/
void CEffect2D::Init(CTexture *tex, float x, float y, STexVer texVer){
	mpTexture = tex;
	/*�T�C�Y*/
	SetVertex(EFF_SIZE(x,y));//���_
	mSizeX = x; mSizeY = y;//�T�C�Y
	SetDiffuse(WHITE_COLOR);
	SetNormal(VEC_NORMAL);
	SetTex(mpTexture, texVer.left, texVer.top, texVer.right, texVer.bottom);
}

/*�e�N�X�`��������Ƃ��̏�����*/
void CEffect2D::Init(){
	/*�n���}�[�G�t�F�N�g����������*/
	SetVertex(EFF_SIZE(mSizeX,mSizeY));
	SetFrame(0);//�����l�ɐݒ�
}
