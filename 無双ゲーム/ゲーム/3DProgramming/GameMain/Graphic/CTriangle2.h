/*
三角形クラス
担当者　 冨田健斗
*/
#ifndef TRIANLE_HPP
#define TRIANLE_HPP
#include "glut.h"	//OpenGLユーティリティのインクルード
#include "../Vector/CVector2.h"	//2次元ベクトルのヘッダをインクルードする

/* 三角形クラス */
class CTriangle2 {
public:
	//頂点１から３までの変数を作成
	float x1;	//頂点１のX座標
	float y1;	//頂点１のY座標
	float x2;	//頂点２のX座標
	float y2;	//頂点２のY座標
	float x3;	//頂点３のX座標
	float y3;	//頂点３のY座標

	float r, g, b, a;	//r:赤 g:緑 b:青 a:アルファ（透明度）
	CVector2 v1, v2, v3;
	int degree;
	

	/* デフォルトコンストラクタ
	x1 ～ y3までに0.0fを代入する
	*/
	CTriangle2() :degree(0), r(1.0f), g(1.0f), b(1.0f), a(1.0f){
		x1 = y1 = x2 = y2 = x3 = y3 = 0.0f;
	}

	/* 頂点１～３のX座標、Y座標の値を初期設定し、描画色を赤にする
	CTriangle(float ix1, float iy1, float ix2, float iy2, float ix3, float iy3)
	[in] ix1 頂点１のX座標
	[in] iy1 頂点１のY座標
	[in] ix2 頂点２のX座標
	[in] iy2 頂点２のY座標
	[in] ix3 頂点３のX座標
	[in] iy3 頂点３のY座標
	*/
	CTriangle2(float ix1, float iy1, float ix2, float iy2, float ix3, float iy3)
		:CTriangle2(ix1, iy1, ix2, iy2, ix3, iy3, 1.0f, 1.0f, 1.0f, 1.0f){
		degree = 0;
		//		x1 = ix1; y1 = iy1; x2 = ix2; y2 = iy2; x3 = ix3; y3 = iy3;
	}

	/* 頂点１～３のX座標、Y座標と描画色の値を初期設定する
	CTriangle(float ix1, float iy1, float ix2, float iy2, float ix3, float iy3 float ir, float ig, float ib, float ia)
	[in] ix1 頂点１のX座標
	[in] iy1 頂点１のY座標
	[in] ix2 頂点２のX座標
	[in] iy2 頂点２のY座標
	[in] ix3 頂点３のX座標
	[in] iy3 頂点３のY座標
	[in] ir 赤の値（0.0f～1.0f）
	[in] ig 緑の値（0.0f～1.0f）
	[in] ib 青の値（0.0f～1.0f）
	[in] ia 透明度の値（0.0f：透明～1.0f：不透明）
	*/
	CTriangle2(float ix1, float iy1, float ix2, float iy2, float ix3, float iy3, float ir, float ig, float ib, float ia)
		: x1(ix1), y1(iy1), x2(ix2), y2(iy2), x3(ix3), y3(iy3), r(ir), g(ig), b(ib), a(ia) {
		degree = 0;
	}

	/* render関数
	三角形を描画する
	*/
	void Render() {
		//描画色を設定
		glColor4f(r, g, b, a);
		//三角形の描画
		glBegin(GL_TRIANGLES);	//三角形の頂点指定開始
		glVertex2f(x1, y1);	//頂点１の指定
		glVertex2f(x2, y2);	//頂点２の指定
		glVertex2f(x3, y3);	//頂点３の指定
		glEnd();	//頂点指定終了
	}

	/* 指定された位置に描画する
	render(CVector2 pos)
	[in] pos	位置
	*/
	void Render(CVector2 pos);
	/* 
	指定された位置にテクスチャ付きで描画する
	render(CVector2 pos, float uv[])
	[in] pos	位置
	[in] uv[]	テクスチャマッピングデータ（配列）
	*/
	void Render(CVector2 pos, float uv[]);


	void Render(CVector2 pos, float degree);
	void Render(CVector2 pos, float degree, float uv[]);

};

#endif