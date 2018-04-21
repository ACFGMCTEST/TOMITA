//富田健斗
#include"CEffect2D.h"
#include <fstream> 
#include "../../../../Define/Define.h"
#include "../../../Camera/CCamera.h"
#include "../../../Convenient/CConvenient.h"
#include "../../../Graphic/CLoadTexManager.h"
/*アニメーション変わるスピード*/
#define ANIMA_SPEED 0.07f
/*大きさ調整用*/
#define SIZE_UP_DIVIDE 5.0f //サイズ調整用
/*法線向き*/
#define VEC_NORMAL 1.0f,1.0f,0.0f
#include<stdio.h>



CEffect2D::CEffect2D() : mAnimaCount(0), mAnimaSize(0), mTimeCount(0), 
mAnimaFrameNum(0), mAnimaFrameMax(0), mAnimaFlag(false), mpWidthLeft(0), mpWidthRight(0) {}

CEffect2D::~CEffect2D(){
	P_ARRAY_DELETE(mpWidthLeft)
	P_ARRAY_DELETE(mpWidthRight);
}

/*アニメーション設定*/
void CEffect2D::SetAnima(int size, float width){
	mAnimaFrameMax = size; //Frame最大数記録 
	mpWidthLeft = new float[size]; //サイズ保存
	mpWidthRight = new float[size]; //サイズ保存
	for (int i = 1; i <= size; i++){
		mpWidthLeft[i - 1] = i * width - width;
		mpWidthRight[i - 1] = width * i;
	}
	SetFrame(0);//初期値に設定

}
/*サイズ指定*/
void CEffect2D::SetVertex(CVector3 v0, CVector3 v1, CVector3 v2, CVector3 v3){
	ver[E_LT] = v0;
	ver[E_LB] = v1;
	ver[E_RB] = v2;
	ver[E_RT] = v3;
	CRectangle::SetVertex(ver[E_LT], ver[E_LB], ver[E_RB], ver[E_RT]);
}
/*現在のフレーム数指定*/
void CEffect2D::SetFrame(int i){
	SetUv(mpTexture, mpWidthLeft[i], mTexTop, mpWidthRight[i], mTexBottom);
}
/*テクスチャ設定*/
void CEffect2D::SetTex(CTexture *name,float left,float top,float right,float bottom){
	mTexLeft = left;
	mTexTop = top;
	mTexRight = right;
	mTexBottom = bottom;
	mpTexture = name;
	SetUv(mpTexture, left, top, right, bottom);
}
/*更新処理*/
void CEffect2D::Update(CVector3 pos){
	/*アニメーションのflagが立つと進める*/
	if (mAnimaFlag){
		if (CConvenient::Time(&mTimeCount, ANIMA_SPEED)){
			mAnimaFrameNum++;//コマを進める
			SetFrame(mAnimaFrameNum);//アニメーションコマ指定
			if (mAnimaFrameMax - 1 == mAnimaFrameNum){//最大値の場合
				mAnimaFrameNum = 0;//カウントをゼロに
			}
			mTimeCount = 0;//カウントをリセット
		}
	}
	/*ビルボード設定*/
	mpCamera = &MainCamera; 
	mMatrix.identity();
	mMatrix.translate(pos);
	mMatrix = mMatrix * mpCamera->mCameraInverse;

}
/*サイズアップ*/
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
	/*マトリックスの計算*/
	glPushMatrix();
	glMultMatrixf(mMatrix.f);
	/*描画*/
	CRectangle::Render();
	glPopMatrix();

}
/*アニメーションフラグをtrueに*/
void CEffect2D::EnableAnima(){
	mAnimaFlag = true;
}
/*アニメーションフラグをfalseに*/
void CEffect2D::DisableAnima(){
	mAnimaFlag = false;
}

/*初期の値に戻す*/
void CEffect2D::Init(CEffect2D::E_STATUS eStatus){
	switch (eStatus)
	{
		/*ハンマー*/
	case CEffect2D::E_HAMMER:
		/*ハンマーエフェクト初期化処理*/
		SetVertex(HAMMER_EFFECT_SIZE);
		SetDiffuse(WHITE_COLOR);
		SetNormal(VEC_NORMAL);
		SetTex(CLoadTexManager::GetInstance()->mpHammer, TEX_HAMMER_EFFECT_SIZE);
		SetAnima(TEX_HAMMER_EFFECT_ANI_SIZE, TEX_HAMMER_EFFECT_WIDTH);
		break;
		/*ゴール*/
	case CEffect2D::E_SPARK:

		/*ゴールエフェクト初期化処理*/
		SetVertex(SPARK_EFFECT_SIZE);
		SetDiffuse(WHITE_COLOR);
		SetNormal(VEC_NORMAL);
		SetTex(CLoadTexManager::GetInstance()->mpSpark, TEX_SPARK_EFFECT_SIZE);
		SetAnima(TEX_SPARK_EFFECT_ANI_SIZE, TEX_SPARK_EFFECT_WIDTH);
		break;
	}


}
/*テクスチャがあるときの初期化*/
void CEffect2D::NoTexInit(){
	/*ハンマーエフェクト初期化処理*/
	SetVertex(HAMMER_EFFECT_SIZE);
	SetFrame(0);//初期値に設定
}
