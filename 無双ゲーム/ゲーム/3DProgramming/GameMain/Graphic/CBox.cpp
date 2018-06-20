#include "CBox.h"
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

#define BOX_NORMAL_Z1	0.5f,0.5f,0.0f
#define BOX_NORMAL_Z2	0.5f,0.5f,0.0f

/*
 SetVertex
 頂点座標を設定する
 x1 < x2 X軸の下限と上限
 y1 < y2 Y軸の下限と上限
 z1 < z2 Z軸の下限と上限
*/
///*全てのレンダー用*/

/* シェーダー使いたい時に使う
myVer =　 代入したいもの
i = 配列番号
Ver = 代入する頂点番号
Normal = 代入する法線番号
*/
void SetMyVertex(CBoxVertex *myVer,int *i,CVector3 Ver ,CVector3 Normal){

	//頂点配列に設定し、法線を設定する
	myVer[*i].mPosition = Ver;
	myVer[*i++].mNormal = Normal;

}

void CBox::SetVertex(float size) {
	//頂点インデックスを使わず、全ての面データを作成
	CBoxVertex *myVertex;
	//頂点数分頂点配列作成
	myVertex = new CBoxVertex[BOX_VER_SIZE];
	int VerNum = 0;
	
	CVector3 v0, v1, v2, v3;




	//右
	v0 = CVector3(-size, size, -size);
	v1 = CVector3(-size, -size, -size);
	v2 = CVector3(-size, -size, size);
	v3 = CVector3(-size, size, size);
	mRect[E_x1].SetVertex(v0, v1, v2, v3);
	mRect[E_x1].SetNormal(BOX_NORMAL_X1);

	//左
	v0 = CVector3(size, size, size);
	v1 = CVector3(size, -size, size);
	v2 = CVector3(size, -size, -size);
	v3 = CVector3(size, size, -size);
	mRect[E_x2].SetVertex(v0, v1, v2, v3);
	mRect[E_x2].SetNormal(BOX_NORMAL_X2);

	//下
	v0 = CVector3(size, -size, -size);
	v1 = CVector3(size, -size, size);
	v2 = CVector3(-size, -size,size);
	v3 = CVector3(-size, -size, -size);
	mRect[E_y1].SetVertex(v0, v1, v2, v3);
	mRect[E_y1].SetNormal(BOX_NORMAL_Y1);
	

	//上
	v0 = CVector3(-size, size, -size);
	v1 = CVector3(-size, size, size);
	v2 = CVector3(size, size,  size);
	v3 = CVector3(size, size,  -size);
	mRect[E_y2].SetVertex(v0, v1, v2, v3);
	mRect[E_y2].SetNormal(BOX_NORMAL_Y2);
	

	//後ろ
	v0 = CVector3(size,  size, -size);
	v1 = CVector3(size,  -size, -size);
	v2 = CVector3(-size, -size, -size);
	v3 = CVector3(-size, size, -size);
	mRect[E_z1].SetVertex(v0, v1, v2, v3);
	mRect[E_z1].SetNormal(BOX_NORMAL_Z1);

	//前
	v0 = CVector3(-size, size,  size);
	v1 = CVector3(-size, -size, size);
	v2 = CVector3(size,  -size, size);
	v3 = CVector3(size,  size,  size);
	mRect[E_z2].SetVertex(v0, v1, v2, v3);
	mRect[E_z2].SetNormal(BOX_NORMAL_Z2);
}

/*すべてのUVを同じに*/
void CBox::AllUV(CTexture *t, int left, int top, int right, int bottom){
	mRect[E_z1].SetUv(t, left, top, right, bottom);
	mRect[E_z2].SetUv(t, left, top, right, bottom);

	mRect[E_x2].SetUv(t, left, top, right, bottom);
	mRect[E_x1].SetUv(t, left, top, right, bottom);


	mRect[E_y2].SetUv(t, left, top, right, bottom);
	mRect[E_y1].SetUv(t, left, top, right, bottom);

}


/*テクスチャ設定*/
void CBox::SetTex(E_TexBox eTexState){
	switch (eTexState)
	{
#define SIZE(i) 256 * i//ｓｕｋａｉボックス縦横比
#define REVERSE(left,top,right,bottom) left,bottom,right,top
	case E_TexBox::E_SKY_BOX:
		mRect[E_y1].SetUv(CLoadTexManager::GetInstance()->mpSkyBox, SIZE(2), SIZE(0), SIZE(1), SIZE(1));
		mRect[E_y2].SetUv(CLoadTexManager::GetInstance()->mpSkyBox, SIZE(1), SIZE(2), SIZE(2), SIZE(3));

		mRect[E_x1].SetUv(CLoadTexManager::GetInstance()->mpSkyBox, REVERSE( 0 , SIZE(1), SIZE(1), SIZE(2)));
		mRect[E_z2].SetUv(CLoadTexManager::GetInstance()->mpSkyBox, REVERSE(SIZE(1), SIZE(1), SIZE(2), SIZE(2)));

		mRect[E_x2].SetUv(CLoadTexManager::GetInstance()->mpSkyBox, REVERSE(SIZE(2), SIZE(1), SIZE(3), SIZE(2)));
		mRect[E_z1].SetUv(CLoadTexManager::GetInstance()->mpSkyBox, REVERSE(SIZE(3), SIZE(1), SIZE(4), SIZE(2)));
		
		SetColor(WHITE_COLOR);
		break;
	}
}

void CBox::Render() {
	glPushMatrix();	//現在のモデルビュー行列の退避
	//行列の作成
	C3DBase::UpdateMatrix();
	////回転


	//行列で回転移動させる
	glMultMatrixf(C3DBase::mMatrix.f);
	//三角ポリゴンを描画する
	for (int i = 0; i < BOX_FACE_NUM; i++) {
		/*マトリックをボックスに合わせる*/
		mRect[i].mMatrix = mMatrix;
		mRect[i].Render();
	}
	glPopMatrix();	//モデルビュー行列を退避した値に戻す
}

void CBox::Render2() {
	glPushMatrix();	//現在のモデルビュー行列の退避
	//行列の作成
	C3DBase::UpdateMatrix();
	//行列で回転移動させる
	glMultMatrixf(mMatrix.f);
	//三角ポリゴンを描画する
	for (int i = 0; i < 4; i++) {
		mRect[i].Render();
	}
	glPopMatrix();	//モデルビュー行列を退避した値に戻す
}

void CBox::RenderTop() {
	glPushMatrix();	//現在のモデルビュー行列の退避
	//行列の作成
	C3DBase::UpdateMatrix();
	//行列で回転移動させる
	glMultMatrixf(mMatrix.f);
	//三角ポリゴンを描画する
	mRect[E_y2].Render();
	glPopMatrix();	//モデルビュー行列を退避した値に戻す
}


/*テクスチャ横スクロール関数*/
void CBox::TexSideScroll(float speed){
	for (int i = 0; i < BOX_FACE_NUM; i++)
	{
		mRect[i].TexSideScroll(speed);
	}
}


/*テクスチャ縦スクロール関数*/
void CBox::TexVerticalScroll(float speed){
	for (int i = 0; i < BOX_FACE_NUM; i++)
	{
		mRect[i].TexVerticalScroll(speed);
	}
}
