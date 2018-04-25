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


/*サイズマクロ*/
#define BUTTON_SIZE(Double,x,y) -Double*x,Double*y,Double*x,-Double*y //背景のサイズ ロゴの調整用
#define BG_SIZE -DISP_X,DISP_Y,DISP_X,-DISP_Y //背景のサイズ
#define CURSOR_SIZE -10.0f,10.0f,10.0f,-10.0f//カーソルのサイズ
/*ポジション移動*/
#define BUTTON_POS(x,y) CVector2(DISP_X*x,DISP_Y*y)

/*長方形クラス*/
class  CRectangle2 {
private:
	
	bool mFlagSaveTex;//テクスチャがセーブされたか判断

	int mTexScrollSideInit;//初期の場所保存

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
	
	/*初期頂点設定されたか*/
	bool mFlagVerInit;
	/*初期値頂点場所*/
	float mSaveRight;
	float mSaveTop;
	float mSaveLeft;
	float mSaveBottom;

public:
	/*テクスチャの縦横保管*/
	enum  E_TEXVER
	{
		E_TOP,
		E_BOTTOM,
		E_LEFT,
		E_RIGHT,
		E_ARRAY
	};
	float mSaveInitTexVer[E_ARRAY];//テクスチャのサイズ保存 初めの値
	float mSaveTexVer[E_ARRAY];//テクスチャのサイズ保存 現在の値

	CTriangle2	mTriangle1;	//三角形クラスの三角形１
	CTriangle2	mTriangle2;	//三角形クラスの三角形２

	CVector2	mPosition;	//基準位置
	CVector2	*mpPos;		//アドレスが入った場合はこっちを優先

	CTexture	*mpTexture;
	float		uv[2][6];

	int mDegree;//回転変数
	bool mFlagDeg;//回転判断

	/*頂点*/
	float *mpLeft;
	float *mpRight;
	float *mpTop;
	float *mpBottom;
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
	void SetUv(CTexture *t, float left, float top, float right, float bottom);
	/*テクスチャある場合*/
	void Uv(float left, float top, float right, float bottom);
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

	/*色の関数　アップ*/
	void ColorUp(float speed);
	/*色の関数　ダウン*/
	void ColorDown(float speed);
	/*色の点数関数
	speed = 速さ
	upLimit = カラーアップの上限
	downLimit = カラーダウンの上限
	*/
	void FlashingColor(float speed,float upLimit,float downLimit);
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
	double　拡大縮小の値
	time いつまでに処理するかの時間
	*/
	void RectScaling(float Double, float time);
	/*拡大縮小関数 頭が動かないバージョン
	double　拡大縮小の値
	time いつまでに処理するかの時間
	*/
	void RectScalingLeftPos(float Double, float time);
	
	/*回転させるよう*/
	void CRectangle2::SetUvRot();
	/*2D処理を開始する処理*/
	static void Disp2D_Start();
	/*2D処理を終了する処理*/
	static void Disp2D_Exit();

	/*テクスチャ横スクロール関数
	speed = Scrollの速さ
	InitSide =  Scroll開始の横幅
	*/
	void TexSideScroll(float speed,int InitSide);
	/*テクスチャ縦スクロール関数*/
	void TexVerticalScroll(float speed);

};

#endif