#include "CHpBar.h"
#include <cmath>
/*
初期化処理
*/

void CHpBar::Init(float max, float value, float widht, float height, CVector3 *pos){
	mMax = max;
	mValue = value;
	mHeight = height;
	mWidth = widht;
	widht /= 2;
	height /= 2;
	//座標の設定を行う
	mGauge.SetVertex(-widht, widht, -height, height, pos);
	mFrame.SetVertex(-widht, widht, -height, height, pos);
}
void CHpBar::Init(float max, float value, float left, float right, float bottom, float top, CVector3 *pos){
	mMax = max;
	mValue = value;
	mHeight = abs(left) + abs(right);
	mWidth  = abs(top) + abs(bottom);
	//座標の設定を行う
	mGauge.SetVertex(left, right, bottom, top, pos);
	mFrame.SetVertex(left, right, bottom, top, pos);
}
void CHpBar::SetTex(CTexture *frameName, CTexture *gaugeName, int left, int top, int right, int bottom){
	mGauge.SetUv(gaugeName, left, top, right, bottom);//ゲージテクスチャ設定
	mFrame.SetUv(frameName, left, top, right, bottom);//フレームテクスチャ設定
}

void CHpBar::Update(){
	//Hpの割合を計算
	float per = (float)mValue / mMax;


	//バーの長さを計算します
	per = mWidth * per;
	//バーの右の座標を計算します
	mGauge.mVertex[2].x = -mWidth / 2 + per;
	mGauge.mVertex[3].x = -mWidth / 2 + per;
	if (mValue <= 0){
		mGauge.mVertex[2].x = 0;
		mGauge.mVertex[3].x = 0;
	}
	//カメラに向かせる
	mGauge.Update();
	mFrame.Update();
}

/*描画*/
void CHpBar::Render(){
	if (mValue > 0){ mGauge.Render(); }
	mFrame.Render();
}