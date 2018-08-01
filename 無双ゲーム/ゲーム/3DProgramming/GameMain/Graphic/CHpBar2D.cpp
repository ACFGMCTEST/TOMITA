#include "CHpBar2D.h"
#include <cmath>
/*
初期化処理
*/

void CHpBar2D::Init(float max, float value, float widht, float height, CVector2 pos){
	mMax = max;
	mValue = value;
	mHeight = height;
	mWidth = widht;
	widht /= 2;
	height /= 2;
	//座標の設定を行う
	mGauge.SetVertex(-widht, height, widht, -height);
	mGauge.mPosition = pos;
	mFrame.SetVertex(-widht, height, widht, -height);
	mFrame.mPosition = pos;
}
void CHpBar2D::Init(float max, float value, float left, float top, float right, float bottom){
	mMax = max;
	mValue = value;
	mHeight = abs(top) + abs(bottom);
	mWidth  = abs(left)  + abs(right);
	//座標の設定を行う
	mGauge.SetVertex(left, top, right, bottom);
	mFrame.SetVertex(left, top, right, bottom);
}
//エフェクトを有効にする
void CHpBar2D::EnableEffect() {
	mpGaugeEffect = new CRectangle2();
	mpGaugeEffect->SetVertex
	(-mWidth/2, mHeight / 2, mWidth / 2, -mHeight / 2);
	mpGaugeEffect->mpPos = &mGauge.mPosition;
}

void CHpBar2D::SetTex(CTexture *frameName, CTexture *gaugeName, STexVer ver){
	mGauge.SetUv(gaugeName, ver.left, ver.top, ver.right, ver.bottom);//ゲージテクスチャ設定
	mFrame.SetUv(frameName, ver.left, ver.top, ver.right, ver.bottom);//フレームテクスチャ設定
}
/*テクスチャエフェクト設定*/
void CHpBar2D::SetTex(
	CTexture *frameName,
	CTexture *gaugeName,
	CTexture *gaugeMax,
	STexVer ver) {
	mGauge.SetUv(gaugeName, ver.left, ver.top, ver.right, ver.bottom);//ゲージテクスチャ設定
	mFrame.SetUv(frameName, ver.left, ver.top, ver.right, ver.bottom);//フレームテクスチャ設定
	//エフェクトがある場合
	if (mpGaugeEffect) {
		mpGaugeEffect->SetUv(gaugeMax, ver.left, ver.top, ver.right, ver.bottom);
	}
}

void CHpBar2D::Update(){
	mGauge.mPosition = mPos;
	mFrame.mPosition = mPos;
	//Hpの割合を計算
	float per = (float)mValue / mMax;
	

	//バーの長さを計算します
	per = -(mWidth / 2)  +  mWidth * per;

	//バーの右の座標を計算します
	mGauge.SetVertex(-mWidth/2,mHeight/2, per,-mHeight / 2);
	if (mValue <= 0){
		mGauge.SetVertex(0, mHeight / 2,0, -mHeight / 2);
	}
	//エフェクトがある場合 
	if (mpGaugeEffect && mValue >= mMax) {
#define SPEED 0.025f
#define UP 1.0f//色の上限
#define DOWN 0.0f//色の下限
		mpGaugeEffect->FlashingColor(SPEED,UP,DOWN);
	}
}

/*描画*/
void CHpBar2D::Render(){
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//色は置き換えてマッピング

	CRectangle2::Disp2D_Start();
	if (mValue > 0) { mGauge.Render(); }
	mFrame.Render();
	if (mpGaugeEffect && mValue >= mMax)mpGaugeEffect->Render();

	CRectangle2::Disp2D_Exit();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//色は置き換えてマッピング
}