#include "CHpBar.h"

/*
初期化処理
*/

void CHpBar::Init(float max, float value, float widht, float height){
	mMax = max;
	mValue = value;
	mHeight = height;
	mWidth = widht;
	widht /= 2;
	height /= 2;
	//座標の設定を行う
	SetVertex(-widht, widht, -height, height);
}

void CHpBar::Update(){
//Hpの割合を計算
	float per = (float)mValue / mMax;
	if (per < 0.0f){
		per = 0.0f;
	}
	//バーの長さを計算します
	per = mWidth * per;
	//バーの右の座標を計算します
	mVertex[2].x = -mWidth / 2 + per;
	mVertex[3].x = -mWidth / 2 + per;
	//カメラに向かせる
	CBillBoard::Update();
}