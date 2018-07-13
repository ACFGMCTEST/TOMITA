#include "CHpBar.h"
#include <cmath>
/*
初期化処理
*/

void CHpBar::Init(CCamera *pCamera,float max, float value, float widht, float height, 
	CVector3 *pos,CVector3 *rot,CVector3 ajust){
	mMax = max;
	mValue = value;
	mHeight = height;
	mWidth = widht;
	widht /= 2;
	height /= 2;
	//座標の設定を行う
	mGauge.SetVertex(pCamera,SVer(-widht, height, widht, -height), pos, rot,ajust);
	mFrame.SetVertex(pCamera, SVer(-widht, height, widht, -height), pos, rot,ajust);
}

void CHpBar::Init(CCamera *pCamera, float max, float value, float widht, float height,
	CVector3 *pos,CVector3 ajust) {
	mMax = max;
	mValue = value;
	mHeight = height;
	mWidth = widht;
	widht /= 2;
	height /= 2;
	//座標の設定を行う
	mGauge.SetVertex(pCamera, SVer(-widht, height, widht, -height), pos, ajust);
	mFrame.SetVertex(pCamera, SVer(-widht, height, widht, -height), pos, ajust);
}

void CHpBar::SetTex(CTexture *frameName, CTexture *gaugeName, int left, int top, int right, int bottom){
	mGauge.SetUv(gaugeName, left, top, right, bottom);//ゲージテクスチャ設定
	mFrame.SetUv(frameName, left, top, right, bottom);//フレームテクスチャ設定
}

void CHpBar::Update(){
	//Hpの割合を計算
	float per = (float)mValue / mMax;


	////バーの長さを計算します
	//per = mWidth * per;
	////バーの右の座標を計算します
	//mGauge.mVertex[2].x = -mWidth / 2 + per;
	//mGauge.mVertex[3].x = -mWidth / 2 + per;

	//バーの長さを計算します
	per = -(mWidth / 2) + (mWidth * per);
	//バーの右の座標を計算します
	mGauge.mVertex[2].x =  per;
	mGauge.mVertex[3].x =  per;

	if (mValue <= 0) {
		mGauge.mVertex[2].x = 0;
		mGauge.mVertex[3].x = 0;
	}
	//カメラに向かせる
	mGauge.Update();
	mFrame.BeforePosUpdate();
}

/*描画*/
void CHpBar::Render(){

	if (mValue > 0){ mGauge.Render(); }
	mFrame.Render();

}