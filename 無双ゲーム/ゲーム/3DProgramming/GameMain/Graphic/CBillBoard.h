#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "../Vector/CVector3.h"
#include "../Matrix/CMatrix44.h"
#include "CTexture.h"
#include "../Camera/CCamera.h"
#include "../Task/CTask.h"

/*頂点*/
struct SVer
{
	float left;
	float top;
	float right; 
	float bottom;

	/*細かく設定*/
	SVer(float x1, float y2, float  x2, float y1) :
		left(x1),top(y2),right(x2),bottom(y1){}
	/*すべて設定*/
	SVer(float all) :
		left(-all), top(all), right(all), bottom(-all){}
	/*縦横設定*/
	SVer(float x,float y) :
		left(x), top(y), right(x), bottom(y) {} 
};

class CBillBoard : public CTask {
private:
	CCamera *mpCamera;//ビルボード用
	float mDif[4];//色設定 rgbaの順番
	CVector3 mNormal;//法線
public:


	//四角形の頂点4つ
	CVector3 mVertex[4];
	//位置 ポインタで合わせるもの
	CVector3 *mpPosition;
	CVector3 *mpRotation;//回転値
	//調整用ポジション ポインタで合わせるため調整用
	CVector3 mAjustPos;

	//合成行列
	CMatrix44 mMatrix;
	//テクスチャ
	CTexture *mpTexture;	
	float mUv[4][2];//テクスチャマッピング
	/*サイズ設定*/
	void SetVertex(CCamera *pCamera, SVer ver, CVector3 *pos, CVector3 *rot, CVector3 ajust);
	void SetVertex(SVer ver);
	void SetVertex(CCamera *pCamera,SVer ver, CVector3 *pos,CVector3 ajust);
	void SetVertex(CCamera *pCamera, float left, float top, float right, float bottom);
	/*テクスチャ設定*/
	void SetUv(CTexture *t, int left, int top, int right, int bottom);
	/*コンストラクタ*/
	CBillBoard();

	/*色設定*/
	void SetColor(float r, float g, float b, float a) {
		mDif[0] = r;
		mDif[1] = g;
		mDif[2] = b;
		mDif[3] = a;
	}
	void Update();
	void BeforePosUpdate();
	void Render();
	void MiniMapRender();


};

#endif
