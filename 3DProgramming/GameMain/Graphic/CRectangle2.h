/*
四角形のベースクラス()
担当者 冨田健斗
*/
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "CTriangle2.h"	//三角形クラスのヘッダをインクルードする
#include "../Vector/CVector2.h"	//2次元ベクトルのヘッダをインクルードする
#include "CTexture.h"
#include "../../Define/Define.h"


/*長方形クラス*/
class  CRectangle2 {
private:
	/*色が最大値以上だと戻す
	limit = 最大値
	*num = 変更する数
	*/
	void LimitEqual(float *num,float Limit);

	/*Flashing関数で使う*/
	enum COLOR{
		UP, DOWN
	};

	COLOR eState = UP;
	/*拡大縮小関数の連続で使う*/
	enum E_Scalling{
		E_One, E_BIG, E_SMALL, //単発の時
		E_BIGREPEAT, E_SMALLREPEAT,//連続の時
		E_BIGONE, E_SMALLONE,//１回だけの時
		E_BIGONE_OUT, E_SMALLONE_OUT,//１回だけ終了の時
	};
	E_Scalling eScalling = E_One;
	float m_BigX, m_BigY;//大きいほう記憶
	float m_SmallX, m_SmallY;//小さいほう記憶
	float m_ChangeSaveX, m_ChangeSaveY;//値が変わった判断用


public:
	CTriangle2	triangle1;	//三角形クラスの三角形１
	CTriangle2	triangle2;	//三角形クラスの三角形２

	CVector2	position;	//基準位置

	CTexture	*ptexture;
	float		uv[2][6];
	int degree;
	bool deg_enabled;
	float *mRLeft;
	float *mRRight;
	float *mRTop;
	float *mRBottom;
	/* 頂点１～３のX座標、Y座標と描画色の値を初期設定する
	CRectangle(float left, float top, float right, float bottom, float r, float g, float b, float a)
	[in] left	左端の値
	[in] top	上部の値
	[in] right	右端の値
	[in] bottom	下部の値
	[in] ir 赤の値（0.0f～1.0f）
	[in] ig 緑の値（0.0f～1.0f）
	[in] ib 青の値（0.0f～1.0f）
	[in] ia 透明度の値（0.0f：透明～1.0f：不透明）
	*/
	CRectangle2(float left, float top, float right, float bottom, float r, float g, float b, float a);

	CRectangle2(float left, float top, float right, float bottom, float r, float g, float b, float a, CVector2 pos);
	CRectangle2();

	//描画する
	void Render();

	/*
	left	画像の左上端を原点(0,0)とし、貼り付けたい領域の左の座標値
	top		画像の左上端を原点(0,0)とし、貼り付けたい領域の上の座標値
	right	画像の左上端を原点(0,0)とし、貼り付けたい領域の右の座標値
	bottom	画像の左上端を原点(0,0)とし、貼り付けたい領域の下の座標値
	*/
	void SetUv(CTexture *t, int left, int top, int right, int bottom);
	/* setVertex
	left:左のx座標
	top:上のy座標
	right:右のx座標
	bottom:下のy座標
	四角形の各頂点の座標を設定する
	*/
	void SetVertex(float left, float top, float right, float bottom);
	/* setColor
	r:赤(0.0～1.0)
	g:緑(0.0～1.0)
	b:青(0.0～1.0)
	a:アルファ(0.0透明～1.0不透明)
	四角形の色を設定する
	*/
	void SetColor(float r, float g, float b, float a);
	/*
	フェード関数 speed = フェードの速さ
	a = ALPHA
	*/
	void Fade(float speed, float a);
	/*
	フェード関数 speed = フェードの速さ
	a = ALPHA
	*/
	void FadeOut(float speed, float a);

	/*色の点滅関数*/
	void ColorUp(float speed);
	void ColorDown(float speed);
	void FlashingColor(float speed);
	/*Gradationループ関数で使うもの*/
	/*カラーが変更する*/
	enum E_COLOR_CHANGE{
		E_GREEN_YELLOW,	//緑から黄
		E_YELLOW_RED,	//黄から赤
		E_RED_PURPLE,	//赤から紫
		E_PURPLE_BLUE,	//紫から青
		E_BLUE_CYAN,	//青から青緑
		E_CYAN_GREEN,	//青緑から緑
	};
	E_COLOR_CHANGE eColorChange;
	/*グラデーション準備関数
	どこからスタートするか決める
	*/
	void SetGradationLoop(E_COLOR_CHANGE state);
	/*グラデーションのループ関数
	色相環にループする関数
	speed = 速さ
	*/
	void GradationLoop(float speed);
	/*拡大縮小関数
	state 大きくする小さくする決める
	ｘ,ｙ　拡大縮小の値　プラス方向指定
	time いつまでに処理するかの時間
	*/
	void RectScaling(float x, float y, float time);

	/*連続バージョン
	ｘ,ｙ　拡大縮小の値　プラス方向指定
	flag　falseは１回連続させる trueはずっと連続する
	*/
	void RectScaling(float x, float y, float time, bool flag);

	/*回転させるよう*/
	void CRectangle2::SetUvRot() {

		float saveUv0[2] = { uv[0][0], uv[0][1] };
		uv[0][0] = uv[3][0];
		uv[0][1] = uv[3][1];

		float saveUv2[2] = { uv[2][2], uv[2][1] };
		uv[2][0] = uv[1][0];
		uv[2][1] = uv[1][1];

		uv[1][0] = saveUv0[0];
		uv[1][1] = saveUv0[1];

		uv[3][0] = saveUv2[0];
		uv[3][1] = saveUv2[1];
	}
	/*2D処理を開始する処理*/
	static void Disp2D_Start(){
		/*描画準備*/
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(-DISP_2D_X,DISP_2D_X,-DISP_2D_Y,DISP_2D_Y);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	}
	/*2D処理を終了する処理*/
	static void Disp2D_Exit(){
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glDisable(GL_BLEND);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
	}
};

#endif