#ifndef CHPBAR_2D_H
#define CHPBAR_2D_H
#include "CRectangle2.h"
#include "../Task/CTask.h"

class CHpBar2D : public CTask{
public:
	CRectangle2 mFrame;//フレーム
	CRectangle2 mGauge;//ゲージ
	CRectangle2 *mpGaugeEffect;//ゲージマックスの時にエフェクトをつける
	CVector2 mPos;
	float mMax; //最大ＨＰ
	float mValue; //現在ＨＰ
	float mWidth, mHeight; //幅と高さ
	/*コンストラクタ*/
	CHpBar2D() : mpGaugeEffect(nullptr){ CTask::eName = CTask::E_2D; }
	~CHpBar2D() { P_DELETE(mpGaugeEffect); }
	/*設定*/
	void Init(float max, float value, float widht, float height, CVector2 pos);
	void Init(float max, float value, float left, float top, float right, float bottom);
	void EnableEffect();//エフェクトを有効にする
	/*テクスチャ設定*/
	void SetTex(CTexture *frameName, CTexture *gaugeName, STexVer ver);
	/*テクスチャエフェクト設定*/
	void SetTex(
		CTexture *frameName,
		CTexture *gaugeName,
		CTexture *gaugeMax,
		STexVer ver);

	void Update();
	void Render();
};

#endif