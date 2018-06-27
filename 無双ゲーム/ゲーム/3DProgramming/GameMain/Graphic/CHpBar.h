#ifndef CHPBAR_H
#define CHPBAR_H
#include "CBillBoard.h"
#include "../Task/CTask.h"
class CHpBar : public CTask{
public:
	CBillBoard mFrame;//フレーム
	CBillBoard mGauge;//ゲージ
	float mMax; //最大ＨＰ
	float mValue; //現在ＨＰ
	float mWidth, mHeight; //幅と高さ
	/*コンストラクタ*/
	CHpBar(){ CTask::eName = CTask::E_BILLBOARD; }
	/*設定*/
	void Init(float max, float value, float widht, float height, CVector3 *pos,CVector3 ajust);
	/*テクスチャ設定*/
	void SetTex(CTexture *frameName, CTexture *gaugeName, int left, int top, int right, int bottom);
	void Update();
	void Render();
};

#endif