#ifndef CBOX_H
#define CBOX_H
#include "CShader.h"
#include "CRectangle.h"
#include "CTexture.h"
#include "../../Base/CBase.h"
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


class CBox :public CBase{
private:
	CTexture *mpTextrue;//テクスチャ

public:
	float mDiffuse[4];//カラー設定
	float *mColorRGBA[4];//カラー設定

	CRectangle mRect[6];	//面が6個分
	GLuint	mMyVertexBuffer;
	///*オールレンダー用*/
	//static CMatrix44 *mAllBoxTransformMatrixSize;
	//static int mAllBoxSize;
	//static GLuint mAllBoxMyVertexBuffer;
	//static CAllBoxVertex mAllBox;
	//CShader mShader;
	/*大きさ記憶用*/
	float mSizeX1;
	float mSizeX2;
	float mSizeY1;
	float mSizeY2;
	float mSizeZ1;
	float mSizeZ2;

	/*頂点場所*/
	enum E_VER{
		E_x1, E_x2, E_z1, E_z2, E_y1, E_y2
	};

	//頂点データの設定 1のほうをマイナスで外側　1のほうをプラスで内側
	void SetVertex(float x1, float x2, float y1, float y2, float z1, float z2);
	enum E_TexBox 
	{
		E_SPEED_UP,			//高速床
		E_SPEED_DOWN,		//減速床
		E_TRAMPOLINE,		//トランポリン
		E_BOX,				//ボックス
		E_NET,				//網
		E_WALL,				//壁
		E_SLOPE,			//坂
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
	CBox() :mSizeX1(0.0f), mSizeX2(0.0f), mSizeY1(0.0f), mSizeY2(0.0f), mSizeZ1(0.0f), mSizeZ2(0.0f){
		for (int i = 0; i < 6; i++) mRect[i].SetDiffuse(1.0f, 1.0f, 0.0f, 1.0f);

	}


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