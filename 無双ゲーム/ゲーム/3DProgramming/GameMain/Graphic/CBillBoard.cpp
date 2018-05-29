#include "CBillBoard.h"
#include "glut.h"
#include "../Camera/CCamera.h"
//カメラのポインタ
CCamera *CBillBoard::mpCamera = 0;
/*コンストラクタ*/
CBillBoard::CBillBoard():mpTexture(0){}

/*サイズ設定*/
void CBillBoard::SetVertex(float left, float right, float bottom, float top,CVector3 *pos) {
	mVertex[0].x = left;
	mVertex[0].y = top;
	mVertex[0].z = 0.0f;
	mVertex[1].x = left;
	mVertex[1].y = bottom;
	mVertex[1].z = 0.0f;
	mVertex[2].x = right;
	mVertex[2].y = bottom;
	mVertex[2].z = 0.0f;
	mVertex[3].x = right;
	mVertex[3].y = top;
	mVertex[3].z = 0.0f;
	mpPosition = pos;
}
/*テクスチャ設定*/
void CBillBoard::SetUv(CTexture *t, int left, int top, int right, int bottom) {
	mpTexture = t;
	mUv[0][0] = (float)left / mpTexture->header.width;
	mUv[0][1] = (float)(mpTexture->header.height - top) / mpTexture->header.height;
	mUv[1][0] = (float)left / mpTexture->header.width;
	mUv[1][1] = (float)(mpTexture->header.height - bottom) / mpTexture->header.height;
	mUv[2][0] = (float)right / mpTexture->header.width;
	mUv[2][1] = (float)(mpTexture->header.height - bottom) / mpTexture->header.height;
	mUv[3][0] = (float)right / mpTexture->header.width;
	mUv[3][1] = (float)(mpTexture->header.height - top) / mpTexture->header.height;
}
/*更新処理*/
void CBillBoard::Update() {
	mMatrix.identity();
	mMatrix.translate(*mpPosition);
	mMatrix = mMatrix * mpCamera->mCameraInverse;
}
/*描画*/
void CBillBoard::Render() {
	if (mpTexture){
		//テクスチャを有効にする
		glEnable(GL_TEXTURE_2D);
		//アルファブレンドを有効にする
		glEnable(GL_BLEND);
		//ブレンド方法を指定
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//テクスチャを指定
		glBindTexture(GL_TEXTURE_2D, mpTexture->id);
		float dif[4] = { 1.0f, 1.0f, 1.0f, 1.0f };//カラー設定
		glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
		glPushMatrix();
		glMultMatrixf(mMatrix.f);
		glBegin(GL_QUADS);

		glTexCoord2fv(mUv[0]); glVertex3f(mVertex[0].x, mVertex[0].y, mVertex[0].z);
		glTexCoord2fv(mUv[1]); glVertex3f(mVertex[1].x, mVertex[1].y, mVertex[1].z);
		glTexCoord2fv(mUv[2]); glVertex3f(mVertex[2].x, mVertex[2].y, mVertex[2].z);
		glTexCoord2fv(mUv[3]); glVertex3f(mVertex[3].x, mVertex[3].y, mVertex[3].z);
		glEnd();
		glPopMatrix();

		//テクスチャを解放
		glBindTexture(GL_TEXTURE_2D, 0);
		//アルファブレンドを無効
		glDisable(GL_BLEND);
		//テクスチャを無効
		glDisable(GL_TEXTURE_2D);
	}
	else{
		glPushMatrix();
		glMultMatrixf(mMatrix.f);
		glBegin(GL_QUADS);
		glVertex3f(mVertex[0].x, mVertex[0].y, mVertex[0].z);
		glVertex3f(mVertex[1].x, mVertex[1].y, mVertex[1].z);
		glVertex3f(mVertex[2].x, mVertex[2].y, mVertex[2].z);
		glVertex3f(mVertex[3].x, mVertex[3].y, mVertex[3].z);
		glEnd();
		glPopMatrix();
	}

}

