#ifndef CBOX_H
#define CBOX_H
#include "CShader.h"
#include "CRectangle.h"
#include "CTexture.h"
#include "../../3DBase/C3DBase.h"
#include "../Vector/CVector2.h"
#include "../../Define/Define.h"

/*面の数*/
#define BOX_FACE_NUM 6
/*ボックスの座標を入れる シェーダー用*/
class CBoxVertex{
public:
	CVector3 mPosition;
	CVector3 mNormal;
	float mColor[4];
	CVector2 mTextureCoords;

	CBoxVertex(){}
};


class CBox :public C3DBase{
private:
	CTexture *mpTextrue;//テクスチャ

public:
	float mDiffuse[4];//カラー設定
	float *mColorRGBA[4];//カラー設定

	CRectangle mRect[6];	//面が6個分
	GLuint	mMyVertexBuffer;
	
	/*大きさ記憶用*/
	float mSize;
	/*頂点場所*/
	enum E_VER{
		E_x1, E_x2, E_z1, E_z2, E_y1, E_y2
	};

	//頂点データの設定 1のほうをマイナスで外側　1のほうをプラスで内側
	void SetVertex(float size);
	enum E_TexBox 
	{
		E_SKY_BOX,
	};
	E_TexBox eTexState;
	//テクスチャの設定
	void SetTex(E_TexBox eTexState);

	//色指定
	void SetColor(float r,float g,float b,float a){
		for (int i = 0; i < 6; i++){
			mRect[i].SetDiffuse(r, g, b, a);
		}
	}

	//すべてのUVを同じに
	void AllUV(CTexture *texture, int left, int top, int right, int bottom);
	/*フェードイン*/
	void Fade(float speed,float a){
		for (int i = 0; i < 6; i++){
			mRect[i].Fade(speed, a);

		}
	}
	/*フェードアウト*/
	void FadeOut(float speed, float a){
		for (int i = 0; i < 6; i++){
			mRect[i].FadeOut(speed, a);
		}
	}

	//描画処理
	void Render();
	/*上がないバージョン*/
	void Render2();
	/*頭のみ*/
	void RenderTop();

	/*コンストラクタ*/
	CBox() :mSize(0.0f){
		for (int i = 0; i < 6; i++) mRect[i].SetDiffuse(1.0f, 1.0f, 0.0f, 1.0f);

	}
	

	/*テクスチャ横スクロール関数*/
	void TexSideScroll(float speed);
	/*テクスチャ縦スクロール関数*/
	void TexVerticalScroll(float speed);

};

#endif