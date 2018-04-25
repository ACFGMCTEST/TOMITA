#include "CRectangle2.h"
#include "../Define/Define.h"
#include "../Convenient/CConvenient.h"

/*単体のCOLORが1.0fよりいかないようにする*/
#define LIMIT_COLOR 1.0f

CRectangle2::CRectangle2(float left, float top, float right, float bottom, float r, float g, float b, float a)
:	//三角形クラスのコンストラクタを呼ぶ
triangle1(left, top, left, bottom, right, bottom, r, g, b, a),
triangle2(left, top, right, bottom, right, top, r, g, b, a), ptexture(0), degree(0)
{}



CRectangle2::CRectangle2(float left, float top, float right, float bottom, float r, float g, float b, float a, CVector2 pos)
:	//三角形クラスのコンストラクタを呼ぶ
triangle1(left, top, left, bottom, right, bottom, r, g, b, a),
triangle2(left, top, right, bottom, right, top, r, g, b, a), position(pos), ptexture(0), degree(0)
{};


CRectangle2::CRectangle2() :ptexture(0), deg_enabled(false), degree(0), 
m_BigX(0.0f), m_BigY(0.0f), m_SmallX(0.0f), m_SmallY(0.0f), position(0.0f, 0.0f){}



//描画する
void CRectangle2::Render() {


	if (degree != 0 || deg_enabled){ //回る四角かどうか
		if (ptexture != 0){ //テクスチャがあるかどうか
			//テクスチャを有効にする
			glEnable(GL_TEXTURE_2D);
			//アルファブレンドを有効にする
			glEnable(GL_BLEND);
			//ブレンド方法を指定
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//テクスチャを指定
			glBindTexture(GL_TEXTURE_2D, ptexture->id);
			//三角形1の描画
			triangle1.Render(position, degree, uv[0]);
			//三角形2の描画
			triangle2.Render(position, degree, uv[1]);
			//テクスチャを解放
			glBindTexture(GL_TEXTURE_2D, 0);
			//アルファブレンドを無効
			glDisable(GL_BLEND);
			//テクスチャを無効
			glDisable(GL_TEXTURE_2D);
		}
		else{
			triangle1.Render(position, degree);
			triangle2.Render(position, degree);
			deg_enabled = true;
		}
	}
	else if (ptexture == 0) {
		triangle1.Render(position);	//三角形１を描画する
		triangle2.Render(position);	//三角形２を描画する
	}
	else {
		//テクスチャを有効にする
		glEnable(GL_TEXTURE_2D);
		//アルファブレンドを有効にする
		glEnable(GL_BLEND);
		//ブレンド方法を指定
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//テクスチャを指定
		glBindTexture(GL_TEXTURE_2D, ptexture->id);
		//三角形1の描画
		triangle1.Render(position, uv[0]);
		//三角形2の描画
		triangle2.Render(position, uv[1]);
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

void CRectangle2::SetUv(CTexture *t, int left, int top, int right, int bottom) {
	ptexture = t;
	uv[0][0] = uv[1][0] = (float)left / ptexture->header.width;
	uv[0][1] = uv[1][1] = (float)(ptexture->header.height - top) / ptexture->header.height;
	uv[0][2] = (float)left / ptexture->header.width;
	uv[0][3] = (float)(ptexture->header.height - bottom) / ptexture->header.height;
	uv[0][4] = uv[1][2] = (float)right / ptexture->header.width;
	uv[0][5] = uv[1][3] = (float)(ptexture->header.height - bottom) / ptexture->header.height;
	uv[1][4] = (float)right / ptexture->header.width;
	uv[1][5] = (float)(ptexture->header.height - top) / ptexture->header.height;
}
void CRectangle2::Uv(int left, int top, int right, int bottom) {
	/*テクスチャがある場合*/
	if (ptexture){
		SetUv(ptexture, left, top, right, bottom);
	}
	else{
		printf("テクスチャが張られていません.SetUv()で貼ってください\n");
	}

}

void CRectangle2::SetVertex(float left, float top, float right, float bottom) {

	triangle1.x1 = left; triangle1.y1 = top;
	triangle1.x2 = left; triangle1.y2 = bottom;
	triangle1.x3 = right; triangle1.y3 = bottom;
	triangle2.x1 = left; triangle2.y1 = top;
	triangle2.x2 = right; triangle2.y2 = bottom;
	triangle2.x3 = right; triangle2.y3 = top;
	triangle1.v1 = CVector2(left, top); triangle1.v2 = CVector2(left, bottom); triangle1.v3 = CVector2(right, bottom);
	triangle2.v1 = CVector2(left, top); triangle2.v2 = CVector2(right, bottom); triangle2.v3 = CVector2(right, top);
	mRLeft = &triangle1.x1;
	mRRight = &triangle1.x3;
	mRBottom = &triangle1.y3;
	mRTop = &triangle2.y1;

}

void CRectangle2::SetColor(float r, float g, float b, float a) {
	/*1番目*/
	CConvenient::LimitEqual(&triangle1.r, r, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&triangle1.g, g, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&triangle1.b, b, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&triangle1.a, a, LIMIT_COLOR, 0.0f);
	/*2番目*/
	CConvenient::LimitEqual(&triangle2.r, r, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&triangle2.g, g, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&triangle2.b, b, LIMIT_COLOR, 0.0f);
	CConvenient::LimitEqual(&triangle2.a, a, LIMIT_COLOR, 0.0f);
}

/*フェード関数*/
#define SET_C3 triangle1.r,triangle1.g,triangle1.b //元の四角形rgb


void CRectangle2::Fade(float speed, float a){
	float mFade4 = triangle1.a + speed;		//フェード関数で使う
	mFade4 += speed;
	if (mFade4 >= a){
		mFade4 = a;
	}
	SetColor(SET_C3, mFade4);
}

/*フェード関数*/
void CRectangle2::FadeOut(float speed, float a){
	float mFade4 = triangle1.a - speed;		//フェード関数で使う
	mFade4 -= speed;
	if (mFade4 <= a){
		mFade4 = a;
	}
	SetColor(SET_C3, mFade4);
}
#define FLASHING_DOWN__C4 \
	triangle1.r - speed, \
	triangle1.g - speed, \
	triangle1.b - speed, \
	triangle1.a - speed //元の四角形rgba

#define FLASHING_UP__C4 \
	triangle1.r + speed, \
	triangle1.g + speed, \
	triangle1.b + speed, \
	triangle1.a + speed //元の四角形rgba

//色DOWN
void CRectangle2::ColorDown(float speed){
	if (triangle1.r > 0.0f){
		SetColor(FLASHING_DOWN__C4);
	}
	if (triangle1.r <= 0){
		SetColor(0.0f, 0.0f, 0.0f, triangle1.a);
	}
}
/*色UP*/
void CRectangle2::ColorUp(float speed){
	if (triangle1.r < 1.0f){
		SetColor(FLASHING_UP__C4);
	}
	if (triangle1.r <= 0){
		SetColor(1.0f, 1.0f, 1.0f, triangle1.a);
	}
}
/*色の点滅*/
void CRectangle2::FlashingColor(float speed){
	switch (eState)
	{
	case UP:
		SetColor(FLASHING_UP__C4);
		if (triangle1.r >= 1.0f){
			eState = DOWN;
		}
		break;
	case DOWN:
		SetColor(FLASHING_DOWN__C4);
		if (triangle1.r <= 0){
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
	red = triangle1.r;
	green = triangle1.g;
	blue = triangle1.b;
	alpha = triangle1.a;
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
void CRectangle2::RectScaling(float x, float y, float time){
	float speedx, speedy;
	speedx = time / FPS;
	speedy = time / FPS;
	switch (eScalling)
	{
		/*拡大か縮小判断*/
	case CRectangle2::E_One:
		if (*mRRight <= x){
			/*大きさの記憶*/
			m_BigX = x;
			m_BigY = y;
			m_SmallX = *mRRight;
			m_SmallY = *mRTop;
			/*切り替え処理*/
			eScalling = CRectangle2::E_BIG;
		}
		else{
			/*大きさ記憶*/
			m_BigX = *mRRight;
			m_BigY = *mRTop;
			m_SmallX = x;
			m_SmallY = y;
			/*切り替え処理*/
			eScalling = CRectangle2::E_SMALL;
		}
		m_ChangeSaveX = x;
		m_ChangeSaveY = y;
		break;
		/*大きくなる処理*/
	case CRectangle2::E_BIG:
	case CRectangle2::E_BIGREPEAT:
	case CRectangle2::E_BIGONE:
	case CRectangle2::E_BIGONE_OUT:
		/*X拡大*/
		if (*mRRight < m_BigX){
			SetVertex(*mRLeft - speedx, *mRTop, *mRRight + speedx, *mRBottom);
		}
		else{
			SetVertex(-m_BigX, *mRTop, m_BigX, *mRBottom);

		}
		/*Ｙ拡大*/
		if (*mRTop < m_BigY){
			SetVertex(*mRLeft, *mRTop + speedy, *mRRight, *mRBottom - speedy);
		}
		else{
			SetVertex(*mRLeft, m_BigY, *mRRight, -m_BigY);
		}
		/*もし値が変わったら*/
		if (eScalling == E_BIG && x != m_ChangeSaveX ||
			eScalling == E_BIG &&y != m_ChangeSaveY){
			eScalling = CRectangle2::E_One;
		}

		break;
		/*小さくなる処理*/
	case CRectangle2::E_SMALL:
	case CRectangle2::E_SMALLREPEAT:
	case CRectangle2::E_SMALLONE:
	case CRectangle2::E_SMALLONE_OUT:

		/*X縮小*/

		if (*mRRight > m_SmallX){
			SetVertex(*mRLeft + speedx, *mRTop, *mRRight - speedx, *mRBottom);
		}
		else{
			SetVertex(-m_SmallX, *mRTop, m_SmallX, *mRBottom);

		}
		/*Ｙ縮小*/
		if (*mRTop > m_SmallY){
			SetVertex(*mRLeft, *mRTop - speedy, *mRRight, *mRBottom + speedy);
		}
		else{
			SetVertex(*mRLeft, m_SmallY, *mRRight, -m_SmallY);
		}
		/*もし値が変わったら*/
		if (eScalling == E_SMALL && x != m_ChangeSaveX ||
			eScalling == E_SMALL && y != m_ChangeSaveY){
			eScalling = CRectangle2::E_One;
		}

		break;
	};

}
/*連続バージョン*/
void CRectangle2::RectScaling(float x, float y, float time, bool flag){

	switch (flag)
	{
		/*連続させる*/
	case true:
		switch (eScalling)
		{
		case CRectangle2::E_One:
			if (*mRRight <= x){
				/*大きさの記憶*/
				m_BigX = x;
				m_BigY = y;
				m_SmallX = *mRRight;
				m_SmallY = *mRTop;
				/*切り替え処理*/
				eScalling = CRectangle2::E_BIGREPEAT;
			}
			else{
				/*大きさ記憶*/
				m_BigX = *mRRight;
				m_BigY = *mRTop;
				m_SmallX = x;
				m_SmallY = y;
				/*切り替え処理*/
				eScalling = CRectangle2::E_SMALLREPEAT;
			}
			break;
		case CRectangle2::E_BIGREPEAT:
			/*拡大縮小*/
			RectScaling(m_BigX, m_BigY, time);
			if (*mRRight >= m_BigX && *mRTop >= m_BigY){ //限界まで大きくなると
				eScalling = CRectangle2::E_SMALL;
			}
			break;
		case CRectangle2::E_SMALLREPEAT:
			/*拡大縮小*/
			RectScaling(m_SmallX, m_SmallY, time);
			if (*mRRight <= m_SmallX && *mRTop <= m_SmallY){ //限界まで小さくなると
				eScalling = CRectangle2::E_BIG;
			}
			break;
		};
		break;
		/*一回だけ連続させる*/
	case false:
		switch (eScalling)
		{
		case CRectangle2::E_One:
			if (*mRRight <= x){
				/*大きさの記憶*/
				m_BigX = x;
				m_BigY = y;
				m_SmallX = *mRRight;
				m_SmallY = *mRTop;
				/*切り替え処理*/
				eScalling = CRectangle2::E_BIGONE;
			}
			else{
				/*大きさ記憶*/
				m_BigX = *mRRight;
				m_BigY = *mRTop;
				m_SmallX = x;
				m_SmallY = y;
				/*切り替え処理*/
				eScalling = CRectangle2::E_SMALLONE;
			}
			break;
		case CRectangle2::E_BIGONE:
			/*拡大縮小*/
			RectScaling(m_BigX, m_BigX, time);
			if (*mRRight >= m_BigX && *mRTop >= m_BigY){ //限界まで大きくなると
				eScalling = CRectangle2::E_SMALLONE_OUT;
			}
			break;
		case CRectangle2::E_SMALLONE:
			/*拡大縮小*/
			RectScaling(m_SmallX, m_SmallY, time);
			if (*mRRight <= m_SmallX && *mRTop <= m_SmallY){ //限界まで小さくなると
				eScalling = CRectangle2::E_BIGONE_OUT;
			}
		case CRectangle2::E_BIGONE_OUT:
			/*拡大縮小*/
			RectScaling(m_BigX, m_BigX, time);
			if (*mRRight >= m_BigX && *mRTop >= m_BigY){ //限界まで大きくなると
				break;
			}
			break;
		case CRectangle2::E_SMALLONE_OUT:
			/*拡大縮小*/
			RectScaling(m_SmallX, m_SmallY, time);
			if (*mRRight <= m_SmallX && *mRTop <= m_SmallY){ //限界まで小さくなると
				break;
			}
			break;
		};
		break;
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