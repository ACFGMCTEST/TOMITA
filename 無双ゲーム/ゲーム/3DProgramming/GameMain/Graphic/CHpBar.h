#ifndef CHPBAR_H
#define CHPBAR_H
#include "CBillBoard.h"

class CHpBar{
public:
	CBillBoard mFrame;//フレーム
	CBillBoard mGauge;//ゲージ

	float mMax; //最大ＨＰ
	float mValue; //現在ＨＰ
	float mWidth, mHeight; //幅と高さ
	void Init(float max, float value, float widht, float height, CVector3 *pos);
	void Init(float max, float value, float left, float right, float bottom, float top, CVector3 *pos);
	/*テクスチャ設定*/
	void SetTex(CTexture *frameName, CTexture *gaugeName, int left, int top, int right, int bottom);
	void Update();
	void Render();
};

#endif