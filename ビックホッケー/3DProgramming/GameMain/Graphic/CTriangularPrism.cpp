#include "CTriangularPrism.h"
#include "../Vector/CVector3.h"
#include "../../Light/CLight.h"
#include "../Graphic/CLoadTexManager.h"
#include "../Scene/GameScene/Map/CMap.h"
/*ボックスの頂点数を決める　面数 * 四角形頂点数*/
#define BOX_VER_SIZE	6 * 4

/*法線のベクトル*/
#define BOX_NORMAL_X1	-0.0f,0.5f,0.5f
#define BOX_NORMAL_X2	0.0f,0.5f,0.5f

#define BOX_NORMAL_Y1	0.0f,-1.0f,0.0f
#define BOX_NORMAL_Y2	0.0f,1.0f,0.0f

#define BOX_NORMAL_Z1	0.5f,0.5f,-0.0f
#define BOX_NORMAL_Z2	0.5f,0.5f,0.0f
/*法線ベクトル*/
#define NORMAL_SLANTING 0.5f,1.0f,-0.0f//斜め
#define NORMAL_BACK		0.5f,0.5f,-0.0f//後ろ
#define NORMAL_BOTTOM	0.0f,1.0f,0.0f//した
#define NORMAL_RIGHT	-0.0f,0.5f,0.5f
#define NORMAL_LEFT		0.0f,0.5f,0.5f

/*テクスチャサイズ*/
#define TEX_SPEED_UP_SIZE		0,0,100,100
#define TEX_SPEED_DOWN_SIZE		0,0,100,100
#define TEX_NET_SIZE			0,0,200*CMap::mMapX,200
#define TEX_WALL_SIZE			0,0,300,300
/*
 SetVertex
 頂点座標を設定する
 x1 < x2 X軸の下限と上限
 y1 < y2 Y軸の下限と上限
 z1 < z2 Z軸の下限と上限
*/
///*全てのレンダー用*/
void CTriangularPrism::SetVertex(float x1, float x2, float y1, float y2, float z1, float z2) {

	CVector3 v0, v1, v2, v3;

	//下
	v0 = CVector3(x1, y1, z1);
	v1 = CVector3(x1, y1, z2);
	v2 = CVector3(x2, y1, z2);
	v3 = CVector3(x2, y1, z1);
	mRect[E_BOTTOM].SetVertex(v0, v1, v2, v3);
	mRect[E_BOTTOM].SetNormal(NORMAL_BOTTOM);

	//後ろ
	v0.x = x1; v0.y = y2; v0.z = z1;//左上後ろ
	v1.x = x1; v1.y = y1; v1.z = z1;//左下後ろ
	v2.x = x1; v2.y = y1; v2.z = z2;//左下前
	v3.x = x1; v3.y = y2; v3.z = z2;//左上前
	mRect[E_BACK].SetVertex(v0, v1, v2, v3);
	mRect[E_BACK].SetNormal(NORMAL_BACK);

	//斜め
	v0.x = x1; v0.y = y2; v0.z = z1;//左上後
	v1.x = x2; v1.y = y1; v1.z = z1;//右下後
	v2.x = x2; v2.y = y1; v2.z = z2;//右下前
	v3.x = x1; v3.y = y2; v3.z = z2;//右上前
	mRect[E_SLANTING].SetVertex(v0,v3,v2,v1);
	mRect[E_SLANTING].SetNormal(NORMAL_SLANTING);



	/*右*/
	v0 = CVector3(x1, y2, z1);
	v1 = CVector3(x1, y1, z1);
	v2 = CVector3(x2, y1, z1);
	mTriangle[E_TRIANGLE_FACE::E_RIGHT].SetVertex(v0, v2, v1);
	mTriangle[E_TRIANGLE_FACE::E_RIGHT].SetNormal(NORMAL_RIGHT);


	/*左*/
	v0 = CVector3(x1, y2, z2);//左上前
	v1 = CVector3(x1, y1, z2);//左下前
	v2 = CVector3(x2, y1, z2);//右下前
	mTriangle[E_TRIANGLE_FACE::E_LEFT].SetVertex(v0, v1, v2);
	mTriangle[E_TRIANGLE_FACE::E_LEFT].SetNormal(NORMAL_LEFT);
}

/*すべてのUVを同じに*/
void CTriangularPrism::AllUV(CTexture *t, int left, int top, int right, int bottom){
	mRect[E_BACK].SetUv(t, left, top, right, bottom);
	mRect[E_SLANTING].SetUv(t, left, top, right, bottom);
	mRect[E_BOTTOM].SetUv(t, left, top, right, bottom);

}

/*テクスチャ設定*/
void CTriangularPrism::SetTex(E_TexBox eTexState){

}


//色指定
void CTriangularPrism::SetColor(float r, float g, float b, float a){
	/*四角形*/
	for (int i = 0; i < E_RECT_FACE::E_RECT_ARRAY; i++) {
		mRect[i].SetDiffuse(r, g, b, a);
	}
	/*三角形*/
	for (int i = 0; i < E_TRIANGLE_FACE::E_TRI_ARRAY; i++)
	{
		mTriangle[i].SetDiffuse(r, g, b, a);
	}
}

void CTriangularPrism::Render() {
	glPushMatrix();	//現在のモデルビュー行列の退避
	//行列の作成
	CBase::UpdateMatrix();
	//行列で回転移動させる
	glMultMatrixf(mMatrix.f);
	//ポリゴンを描画する
	for (int i = 0; i < E_RECT_FACE::E_RECT_ARRAY; i++) {
		/*マトリックをボックスに合わせる*/
		mRect[i].mMatrix = mMatrix;
		mRect[i].Render();
	}
	for (int i = 0; i < E_TRIANGLE_FACE::E_TRI_ARRAY; i++)
	{
		mTriangle[i].mMatrix = mMatrix;
		mTriangle[i].Render();
	}
	glPopMatrix();	//モデルビュー行列を退避した値に戻す
}



/*大きさを変える関数
float Double は　倍率を入れる
*/
void CTriangularPrism::SizeDouble(float Double){


}


/*テクスチャ横スクロール関数*/
void CTriangularPrism::TexSideScroll(float speed){

}


/*テクスチャ縦スクロール関数*/
void CTriangularPrism::TexVerticalScroll(float speed){
	
}
