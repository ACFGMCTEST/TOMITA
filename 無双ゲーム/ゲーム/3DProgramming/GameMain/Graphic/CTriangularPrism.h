#ifndef TRIANGULAR_PRISM_H
#define TRIANGULAR_PRISM_H

#include "CShader.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CTexture.h"
#include "../../3DBase/C3DBase.h"
#include "../Vector/CVector2.h"
#include "../../Define/Define.h"

/*面の数*/
#define BOX_FACE_NUM 6

class CTriangularPrism :public C3DBase{
private:
	CTexture *mpTextrue;//テクスチャ

public:
	enum E_COLOR{
		E_RED,//赤
		E_GREEN,//緑
		E_BLUE,//青
		E_ALPHA,//透明度
		E_ARRAY,//配列数
	};
	float mDiffuse[E_ARRAY];//カラー設定
	/*四角形_面の方向*/
	enum E_RECT_FACE{
		E_BACK,//後ろ
		E_BOTTOM,//下
		E_SLANTING,//ななめ
		E_RECT_ARRAY,//配列数
	};
	/*面*/
	CRectangle mRect[E_RECT_FACE::E_RECT_ARRAY];	//面が3個分
	/*三角形_面の方向*/
	enum E_TRIANGLE_FACE{
		E_LEFT,//左
		E_RIGHT,//右
		E_TRI_ARRAY,//配列数
	};
	CTriangle mTriangle[E_TRIANGLE_FACE::E_TRI_ARRAY];//面が二つ分


	//頂点データの設定 1のほうをマイナスで外側　1のほうをプラスで内側
	void SetVertex(float x1, float x2, float y1, float y2, float z1, float z2);
	enum E_TexBox 
	{
		E_SLOPE,			//坂
	};
	E_TexBox eTexState;
	//テクスチャの設定
	void SetTex(E_TexBox eTexState);

	//色指定
	void SetColor(float r, float g, float b, float a);

	//すべてのUVを同じに
	void AllUV(CTexture *texture, int left, int top, int right, int bottom);


	//描画処理
	void Render();

	/*大きさを変える関数
	float Double は　倍率を入れる
	*/
	void SizeDouble(float Double);

	/*テクスチャ横スクロール関数*/
	void TexSideScroll(float speed);
	/*テクスチャ縦スクロール関数*/
	void TexVerticalScroll(float speed);

};

#endif