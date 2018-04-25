#include "CRectangle2.h"
#include "../Define/Define.h"
#include "../Convenient/CConvenient.h"
#include <cassert>

/*単体のCOLORが1.0fよりいかないようにする*/
#define LIMIT_COLOR 1.0f

CRectangle2::CRectangle2(float left, float top, float right, float bottom, float r, float g, float b, float a)
:	//三角形クラスのコンストラクタを呼ぶ
mTriangle1(left, top, left, bottom, right, bottom, r, g, b, a),
mTriangle2(left, top, right, bottom, right, top, r, g, b, a), mpTexture(0), mDegree(0)
{}



CRectangle2::CRectangle2(float left, float top, float right, float bottom, float r, float g, float b, float a, CVector2 pos)
:	//三角形クラスのコンストラクタを呼ぶ
mTriangle1(left, top, left, bottom, right, bottom, r, g, b, a),
mTriangle2(left, top, right, bottom, right, top, r, g, b, a), mPosition(pos), mpTexture(0), mDegree(0)
{};


CRectangle2::CRectangle2() :mpTexture(0), mFlagDeg(false), mDegree(0), mpPos(nullptr), mFlagVerInit(false),
 mPosition(0.0f, 0.0f), mFlagSaveTex(false),mTexScrollSideInit(0){}



//描画する
void CRectangle2::Render() {
	/*ポジションに値がアドレスが入った場合*/
	if (mpPos){
		mPosition = *mpPos;
	}

	if (mDegree != 0 || mFlagDeg){ //回る四角かどうか
		if (mpTexture != 0){ //テクスチャがあるかどうか
			//テクスチャを有効にする
			glEnable(GL_TEXTURE_2D);
			//アルファブレンドを有効にする
			glEnable(GL_BLEND);
			//ブレンド方法を指定
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//テクスチャを指定
			glBindTexture(GL_TEXTURE_2D, mpTexture->id);
			//三角形1の描画
			mTriangle1.Render(mPosition, mDegree, uv[0]);
			//三角形2の描画
			mTriangle2.Render(mPosition, mDegree, uv[1]);
			//テクスチャを解放
			glBindTexture(GL_TEXTURE_2D, 0);
			//アルファブレンドを無効
			glDisable(GL_BLEND);
			//テクスチャを無効
			glDisable(GL_TEXTURE_2D);
		}
		else{
			mTriangle1.Render(mPosition, mDegree);
			mTriangle2.Render(mPosition, mDegree);
			mFlagDeg = true;
		}
	}
	else if (mpTexture == 0) {
		mTriangle1.Render(mPosition);	//三角形１を描画する
		mTriangle2.Render(mPosition);	//三角形２を描画する
	}
	else {
		//テクスチャを有効にする
		glEnable(GL_TEXTURE_2D);
		//アルファブレンドを有効にする
		glEnable(GL_BLEND);
		//ブレンド方法を指定
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//テクスチャを指定
		glBindTexture(GL_TEXTURE_2D, mpTexture->id);
		//三角形1の描画
		mTriangle1.Render(mPosition, uv[0]);
		//三角形2の描画
		mTriangle2.Render(mPosition, uv[1]);
		//テクスチャを解放
		glBindTexture(GL_TEXTURE_2D, 0);
		//アルファブレンドを無効
		glDisable(GL_BLEND);
		//テクスチャを無効
		glDisable(GL_TEXTURE_2D);
	}
}

//更新処理の宣言
void Update();
/*
left	画像の左上端を原点(0,0)とし、貼り付けたい領域の左の座標値
top		画像の左上端を原点(0,0)とし、貼り付けたい領域の上の座標値
right	画像の左上端を原点(0,0)とし、貼り付けたい領域の右の座標値
bottom	画像の左上端を原点(0,0)とし、貼り付けたい領域の下の座標値
*/

void CRectangle2::SetUv(CTexture *t, float left, float top, float right, float bottom) {
	mpTexture = t;
	uv[0][0] = uv[1][0] = (float)left / mpTexture->header.width;
	uv[0][1] = uv[1][1] = (float)(mpTexture->header.height - top) / mpTexture->header.height;
	uv[0][2] = (float)left / mpTexture->header.width;
	uv[0][3] = (float)(mpTexture->header.height - bottom) / mpTexture->header.height;
	uv[0][4] = uv[1][2] = (float)right / mpTexture->header.width;
	uv[0][5] = uv[1][3] = (float)(mpTexture->header.height - bottom) / mpTexture->header.height;
	uv[1][4] = (float)right / mpTexture->header.width;
	uv[1][5] = (float)(mpTexture->header.height - top) / mpTexture->header.height;

	/*テクスチャの値保存*/
	if (!mFlagSaveTex){
		mSaveInitTexVer[E_TOP] = top;
		mSaveInitTexVer[E_BOTTOM] = bottom;
		mSaveInitTexVer[E_LEFT] = left;
		mSaveInitTexVer[E_RIGHT] = right;
		mFlagSaveTex = true;
	}
	mSaveTexVer[E_TOP] = top;
	mSaveTexVer[E_BOTTOM] = bottom;
	mSaveTexVer[E_LEFT] = left;
	mSaveTexVer[E_RIGHT] = right;
}
/*テクスチャある場合*/
void CRectangle2::Uv(float left, float top, float right, float bottom){
	/*テクスチャがない場合エラー*/
	assert(mpTexture);
	SetUv(mpTexture, left, top, right, bottom);	
}


void CRectangle2::SetVertex(float left, float top, float right, float bottom) {

	mTriangle1.x1 = left; mTriangle1.y1 = top;
	mTriangle1.x2 = left; mTriangle1.y2 = bottom;
	mTriangle1.x3 = right; mTriangle1.y3 = bottom;
	mTriangle2.x1 = left; mTriangle2.y1 = top;
	mTriangle2.x2 = right; mTriangle2.y2 = bottom;
	mTriangle2.x3 = right; mTriangle2.y3 = top;
	mTriangle1.v1 = CVector2(left, top); mTriangle1.v2 = CVector2(left, bottom); mTriangle1.v3 = CVector2(right, bottom);
	mTriangle2.v1 = CVector2(left, top); mTriangle2.v2 = CVector2(right, bottom); mTriangle2.v3 = CVector2(right, top);
	mpLeft = &mTriangle1.x1;
	mpRight = &mTriangle1.x3;
	mpBottom = &mTriangle1.y3;
	mpTop = &mTriangle2.y1;

	/*初期頂点入れる*/
	if (!mFlagVerInit){
		mSaveLeft = left;
		mSaveTop = top;
		mSaveRight = right;
		mSaveBottom = bottom;
		mFlagVerInit = true;
	}

}

void CRectangle2::SetColor(float r, float g, float b, float a) {
	/*1番目*/
	CConvenient::LimitEqual(&mTriangle1.r, r, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&mTriangle1.g, g, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&mTriangle1.b, b, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&mTriangle1.a, a, LIMIT_COLOR, 0.0f);
	/*2番目*/
	CConvenient::LimitEqual(&mTriangle2.r, r, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&mTriangle2.g, g, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&mTriangle2.b, b, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&mTriangle2.a, a, LIMIT_COLOR, 0.0f);
}

/*フェード関数*/
#define SET_C3 mTriangle1.r,mTriangle1.g,mTriangle1.b //元の四角形rgb


void CRectangle2::Fade(float speed, float a){
	float mFade4 = mTriangle1.a + speed;		//フェード関数で使う
	mFade4 += speed;
	if (mFade4 >= a){
		mFade4 = a;
	}
	SetColor(SET_C3, mFade4);
}

/*フェード関数*/
void CRectangle2::FadeOut(float speed, float a){
	float mFade4 = mTriangle1.a - speed;		//フェード関数で使う
	mFade4 -= speed;
	if (mFade4 <= a){
		mFade4 = a;
	}
	SetColor(SET_C3, mFade4);
}
#define FLASHING_DOWN__C4(s) \
	mTriangle1.r - s, \
	mTriangle1.g - s, \
	mTriangle1.b - s, \
	mTriangle1.a - s //元の四角形rgba

#define FLASHING_UP__C4(s) \
	mTriangle1.r + s, \
	mTriangle1.g + s, \
	mTriangle1.b + s, \
	mTriangle1.a + s //元の四角形rgba

//色DOWN
void CRectangle2::ColorDown(float speed){
	if (mTriangle1.r > 0.0f){
		SetColor(FLASHING_DOWN__C4(speed));
	}
	if (mTriangle1.r <= 0){
		SetColor(0.0f, 0.0f, 0.0f, mTriangle1.a);
	}
}
/*色UP*/
void CRectangle2::ColorUp(float speed){
	if (mTriangle1.r < 1.0f){
		SetColor(FLASHING_UP__C4(speed));
	}
	if (mTriangle1.r <= 0){
		SetColor(1.0f, 1.0f, 1.0f, mTriangle1.a);
	}
}
/*色の点滅*/
void CRectangle2::FlashingColor(float speed,float upLimit,float downLimit){
	switch (eState)
	{
	case UP:
		SetColor(FLASHING_UP__C4(speed));
		if (mTriangle1.r >= upLimit){
			eState = DOWN;
		}
		break;
	case DOWN:
		SetColor(FLASHING_DOWN__C4(speed));
		if (mTriangle1.r <=  downLimit){
			eState = UP;
		}
		break;
	}

}

/*Gradation準備関数*/
void CRectangle2::SetGradationLoop(CRectangle2::E_COLOR_CHANGE state){
	eColorChange = state;
	/*色を規定値に設定*/
	switch (state)
	{
	case CRectangle2::E_GREEN_YELLOW:
		SetColor(GREEN_COLOR);
		break;
	case CRectangle2::E_YELLOW_RED:
		SetColor(YELLOW_COLOR);
		break;
	case CRectangle2::E_RED_PURPLE:
		SetColor(RED_COLOR);
		break;
	case CRectangle2::E_PURPLE_BLUE:
		SetColor(PURPLE_COLOR);
		break;
	case CRectangle2::E_BLUE_CYAN:
		SetColor(BLUE_COLOR);
		break;
	case CRectangle2::E_CYAN_GREEN:
		SetColor(CYAN_COLOR);
		break;
	default:
		break;
	}


}

/*グラデーション関数*/
void CRectangle2::GradationLoop(float speed){
	float red, green, blue, alpha;//保存用カラー
	/*カラー変更していく*/
	red = mTriangle1.r;
	green = mTriangle1.g;
	blue = mTriangle1.b;
	alpha = mTriangle1.a;
	/*色変更*/
	switch (eColorChange)
	{
		/*緑から黄*/
	case CRectangle2::E_GREEN_YELLOW:
		red += speed;
		/*赤が最大なら,現在黄*/
		if (red >= LIMIT_COLOR){
			eColorChange = E_YELLOW_RED;
		}
		break;
		/*黄から赤*/
	case CRectangle2::E_YELLOW_RED:
		green -= speed;
		/*緑が最小なら,現在赤*/
		if (green <= 0.0f){
			eColorChange = E_RED_PURPLE;
		}
		break;
		/*赤から紫*/
	case CRectangle2::E_RED_PURPLE:
		blue += speed;
		/*赤が最大なら,現在紫*/
		if (blue >= LIMIT_COLOR){
			eColorChange = E_PURPLE_BLUE;
		}
		break;
		/*紫から青*/
	case CRectangle2::E_PURPLE_BLUE:
		red -= speed;
		/*赤が最小なら,現在青*/
		if (red <= 0.0f){
			eColorChange = E_BLUE_CYAN;
		}
		break;
		/*青から青緑*/
	case CRectangle2::E_BLUE_CYAN:
		green += speed;
		/*緑が最大なら,現在青緑*/
		if (green >= LIMIT_COLOR){
			eColorChange = E_CYAN_GREEN;
		}
		break;
		/*青緑から緑*/
	case CRectangle2::E_CYAN_GREEN:
		blue -= speed;
		/*が最小なら,現在緑*/
		if (blue <= 0.0f){
			eColorChange = E_GREEN_YELLOW;
		}
		break;
	default:
		break;
	}
	/*カラー*/
	SetColor(red,green,blue,alpha);
}

/*拡大縮小関数*/
void CRectangle2::RectScaling(float Double, float time){
	/*両店が入ってない場合エラー*/
	assert(mFlagVerInit);

	float speedx, speedy;
	/*大きくなるスピード*/
	speedx = *mpRight * 1 / FPS * time;
	speedy = *mpTop * 1 / FPS  * time;

	if (*mpRight + speedx > mSaveRight * Double && mSaveRight * Double > *mpRight - speedx){ return; }

	/*大きい場合*/
	if (*mpRight + speedx > mSaveRight * Double){
		/*小さくする*/
		SetVertex
			(
			*mpLeft   + speedx,
			*mpTop    - speedy,
			*mpRight  - speedx,
			*mpBottom + speedy
			);

	}
	/*小さい場合*/
	else{
		/*大きくする*/
		SetVertex
			(
			*mpLeft - speedx,
			*mpTop + speedy,
			*mpRight + speedx,
			*mpBottom - speedy
			);
	}
	

}

/*拡大縮小関数 頭が動かないバージョン
double　拡大縮小の値
time いつまでに処理するかの時間
*/
void CRectangle2::RectScalingLeftPos(float Double, float time){
	/*両店が入ってない場合エラー*/
	assert(mFlagVerInit);

	float speedx, speedy;
	/*大きくなるスピード*/
	speedx = *mpRight * 1 / FPS * time;
	speedy = *mpTop * 1 / FPS  * time;

	if (*mpRight + speedx > mSaveRight * Double && mSaveRight * Double > *mpRight - speedx){ return; }

	/*大きい場合*/
	if (*mpRight + speedx > mSaveRight * Double){
		/*小さくする*/
		SetVertex
			(
			*mpLeft + speedx,
			*mpTop - speedy,
			*mpRight - speedx,
			*mpBottom + speedy
			);
		mPosition.x -= speedx ;
	}
	/*小さい場合*/
	else{
		/*大きくする*/
		SetVertex
			(
			*mpLeft - speedx,
			*mpTop + speedy,
			*mpRight + speedx,
			*mpBottom - speedy
			);
		mPosition.x += speedx ;
	}

}

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
void CRectangle2::Disp2D_Start(){
	/*描画準備*/
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-DISP_2D_X, DISP_2D_X, -DISP_2D_Y, DISP_2D_Y);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}
/*2D処理を終了する処理*/
void CRectangle2::Disp2D_Exit(){
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
}

/*テクスチャ横スクロール関数*/
void CRectangle2::TexSideScroll(float speed,int InitSide){
	float left, top, right, bottom;
	/*保存*/
	left = mSaveTexVer[E_LEFT];
	top = mSaveTexVer[E_TOP];
	bottom = mSaveTexVer[E_BOTTOM];
	/*初めはScroll場所の位置を決める*/
	if (mTexScrollSideInit == 0){
		mTexScrollSideInit = InitSide;
		right = mTexScrollSideInit;
	}else{
		right = mSaveTexVer[E_RIGHT];
	}

	/*計算*/
	CConvenient::LoopPlus(&left, speed, mSaveInitTexVer[E_RIGHT], mSaveInitTexVer[E_LEFT]);
	CConvenient::LoopPlus(&right, speed, mSaveInitTexVer[E_RIGHT] + mTexScrollSideInit,
		mSaveInitTexVer[E_LEFT] + mTexScrollSideInit);
	SetUv(mpTexture, left, top, right, bottom);

}


/*テクスチャ縦スクロール関数*/
void CRectangle2::TexVerticalScroll(float speed){
	float left, top, right, bottom;
	/*保存*/
	left = mSaveTexVer[E_LEFT];
	top = mSaveTexVer[E_TOP];
	right = mSaveTexVer[E_RIGHT];
	bottom = mSaveTexVer[E_BOTTOM];
	/*計算*/
	CConvenient::LoopPlus(&top, speed, mSaveInitTexVer[E_TOP], mSaveInitTexVer[E_BOTTOM]);
	CConvenient::LoopPlus(&bottom, speed, mSaveInitTexVer[E_TOP], mSaveInitTexVer[E_BOTTOM]);
	SetUv(mpTexture, left, top, right, bottom);

}