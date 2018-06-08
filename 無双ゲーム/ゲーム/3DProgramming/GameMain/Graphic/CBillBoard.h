#ifndef CBILLBOARD
#define CBILLBOARD

#include "../Vector/CVector3.h"
#include "../Matrix/CMatrix44.h"
#include "CTexture.h"
#include "../Camera/CCamera.h"

class CBillBoard {
public:


	//四角形の頂点4つ
	CVector3 mVertex[4];
	//位置
	CVector3 *mpPosition;
	//合成行列
	CMatrix44 mMatrix;
	//テクスチャ
	CTexture *mpTexture;	
	float mUv[4][2];//テクスチャマッピング
	/*サイズ設定*/
	void SetVertex(float left, float top, float right, float bottom, CVector3 *pos);
	void SetVertex(float left, float top, float right, float bottom);
	/*テクスチャ設定*/
	void SetUv(CTexture *t, int left, int top, int right, int bottom);
	/*コンストラクタ*/
	CBillBoard();

	void Update();
	void BeforePosUpdate();
	void Render();

};

#endif
