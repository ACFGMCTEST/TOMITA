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
	CVector3 mPosition;
	//合成行列
	CMatrix44 mMatrix;
	//カメラのポインタ
	CCamera *mpCamera;
	//テクスチャ
	CTexture *mpTexture;	

	void SetVertex(float left, float right, float bottom, float top);
	void Update();
	void Render();

};

#endif
