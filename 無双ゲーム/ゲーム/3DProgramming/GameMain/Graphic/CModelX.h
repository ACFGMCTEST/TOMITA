#ifndef CMODELX_H	//インクルードガード
#define CMODELX_H

#include "glew.h"
#include "glut.h"
#include <string>

#define MODEL_FILE "sample.blend.x"	//入力ファイル名
//#define MODEL_FILE "ラグナ.x"	//入力ファイル名
//#define MODEL_FILE "x\\00_Mesh1P.x"	//入力ファイル名

//領域解放をマクロ化
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
#define SAFE_DELETE(a) { if(a) delete a; a = 0;}
//配列のサイズ取得をマクロ化
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#include <vector>	//vectorクラスのインクルード（動的配列）
//#include "CMatrix44.h"	//マトリクスクラスのインクルード
//#include "CTexture.h"	//テクスチャのインクルード
//#include "CVector2.h"
//#include "CShader.h"

#include "../Matrix/CMatrix44.h"
#include "../Graphic/CTexture.h"
#include "../Vector/CVector2.h"
#include "CShader.h"

class CMyVertex {
public:
	CVector3 mPosition;
	CVector3 mNormal;
	CVector2 mTextureCoords;
	float mBoneWeight[4];
	float mBoneIndex[4];

	CMyVertex() {
		for (int i = 0; i < 4; i++) {
			mBoneIndex[i] = 0;
			mBoneWeight[i] = 0.0f;
		}
		mBoneWeight[0] = 1.0f;
	}
};

class CModelX;	// CModelXクラスの宣言

/*
CAnimationKey
アニメーションキークラス
*/
class CAnimationKey {
public:
	//時間
	float mTime;
	//行列
	CMatrix44 mMatrix;
};

/*
CAnimation
アニメーションクラス
*/
class CAnimation {
public:
	char *mpFrameName;	//フレーム名
	int mFrameIndex;	//フレーム番号

	int mKeyNum;	//キー数（時間数）
	CAnimationKey *mpKey;	//キーの配列

	CAnimation(CModelX *model);

	~CAnimation() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}
};

/*
CAnimationSet
アニメーションセット
*/
class CAnimationSet {
public:
	//アニメーション名
	char *mpName;
	//アニメーション
	std::vector<CAnimation*> mAnimation;

	//14S
	float mTime;	//現在時間
	float mWeight;	//重み
	float mMaxTime;	//最大時間
	//14E

	CAnimationSet(CModelX *model);

	~CAnimationSet() {
		SAFE_DELETE_ARRAY(mpName);
		//アニメーション要素の削除
		for (int i = 0; i < mAnimation.size(); i++) {
			delete mAnimation[i];
		}
	}
};

/*
CSkinWeights
スキンウェイトクラス
*/
class CSkinWeights {
public:
	char *mpFrameName;	//フレーム名
	int mFrameIndex;	//フレーム番号
	int mIndexNum;	//頂点番号数
	int *mpIndex;	//頂点番号配列
	float *mpWeight;	//頂点ウェイト配列
	CMatrix44 mOffset;	//オフセットマトリックス

	CSkinWeights(CModelX *model);

	~CSkinWeights() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}
};
/*
CMaterial
マテリアルクラス
*/
class CMaterial {
public:
	char *mpName;	//マテリアル名
	float mDiffuse[4];
	float mColorRGBA[4];
	float mPower;
	float mSpecular[3];
	float mEmissive[3];
	//テクスチャファイル名
	char *mpTextureFilename;
	//18
	//テクスチャID
	GLuint mTextureId;

	CMaterial(CModelX *model);

	~CMaterial() {
		SAFE_DELETE_ARRAY(mpName);
		SAFE_DELETE_ARRAY(mpTextureFilename);
	}
	//マテリアルを適用する
	void SetMaterial();
	//18
	//マテリアルを無効にする
	void UnSetMaterial();

	//Add Shader
	void SetShader(CShader *shader);
};

//CMeshクラスの定義
class CMesh {
public:
	int mVertexNum;		//頂点数
	CVector3 *mpVertex;	//頂点データ
	int mFaceNum;		//面数
	int *mpVertexIndex;	//面を構成する頂点番号
	int mNormalNum;		//法線数
	CVector3 *mpNormal;	//法線データ
	int mMaterialNum;	//マテリアル数
	int mMaterialIndexNum;	//マテリアル番号数（面数）
	int *mpMaterialIndex;	//マテリアル番号

	//マテリアルデータ
	std::vector<CMaterial*> mMaterial;
	std::vector<int> mMaterialVertexCount;
	//スキンウェイト
	std::vector<CSkinWeights*> mSkinWeights;
	//16
	CVector3 *mpAnimateVertex;	//アニメーション用頂点
	CVector3 *mpAnimateNormal;	//アニメーション用法線
	//19
	//テクスチャ座標データ
	CVector2 *mpTextureCoords;
	//Add Shader
	GLuint	  mMyVertexBuffer;
	int       mMyVertexNum;
	//	CMatrix44 mTransformMatrix[155];

	float mRed, mGreen, mBlue, mAlpha; //rgba色情報

	//コンストラクタ
	CMesh()
		: mVertexNum(0)
		, mpVertex(0)
		, mFaceNum(0)
		, mpVertexIndex(0)
		, mNormalNum(0)
		, mpNormal(0)
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(0)
		//16
		, mpAnimateVertex(0)
		, mpAnimateNormal(0)
		//19
		, mpTextureCoords(0)
		, mMyVertexNum(0)
		, mMyVertexBuffer(0)
		, mRed(0.0f), mGreen(0.0f), mBlue(0.0f), mAlpha(0.0f)
	{}
	//デストラクタ
	~CMesh() {
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		//16
		SAFE_DELETE_ARRAY(mpAnimateVertex);
		SAFE_DELETE_ARRAY(mpAnimateNormal);
		//19
		SAFE_DELETE_ARRAY(mpTextureCoords);
		//スキンウェイトの削除
		for (int i = 0; i < mSkinWeights.size(); i++) {
			delete mSkinWeights[i];
		}
		glDeleteBuffers(1, &mMyVertexBuffer);
	}
	//読み込み処理
	void Init(CModelX *model);
	//描画
	void Render();
	void Render(CModelX *model, CMatrix44 transformMatrix[], int transformMatrixSize);
	//16
	//頂点にアニメーション適用
	void AnimateVertex(CModelX *model);
	void CreateVertexBuffer();
};


//CModelXFrameクラスの定義
class CModelXFrame {
public:
	std::vector<CModelXFrame*> mChild;	//子フレームの配列
	CMatrix44 mTransformMatrix;	//変換行列
	CMatrix44 mCombinedMatrix;	//合成行列
	char* mpName;	//フレーム名前
	int mIndex;		//フレーム番号

	CMesh mMesh;	//Meshデータ

	//コンストラクタ
	CModelXFrame()
		: mpName(0)
		, mIndex(0) {}

	CModelXFrame(CModelX* model);
	//デストラクタ
	~CModelXFrame() {
		//子フレームを全て解放する
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++) {
			delete *itr;
		}
		//名前のエリアを解放する
		SAFE_DELETE_ARRAY(mpName);
	}
	//描画
	void Render();
	//アニメーションないバージョン
	void NoaAnimaRender();

	//合成行列の作成
	void Animate(CMatrix44* parent);
};

/*
CModelX
Xファイル形式の3Dモデルデータをプログラムで認識する
*/
class CModelX {
public:
	char* mpPointer;	//読み込み位置
	char mToken[1024];	//取り出した単語の領域
	std::string mTexDirectory;//読み込みファイル場所
	bool mAnimaFlag;//フラグアニメーション
	/*色セット*/
	void SetColor(float r, float g, float b, float a);
	/*色があるか判断*/
	bool ColorFlag();
	/*色のフェード点滅*/
	void Flashing(){};

	std::vector<CModelXFrame*> mFrame;	//フレームの配列
	std::vector<CAnimationSet*> mAnimationSet;	//アニメーションセットの配列
	std::vector<std::string> mAnimaName;//アニメーションの名前
	//24
	int mAnimationIndex;	//現在のアニメーション番号

	//17
	std::vector<CMaterial*> mMaterial;	//マテリアルの配列
	//18
	std::vector<CTexture*> mTexture;	//テクスチャの配列

	CShader mShader;

	std::vector<CMesh*> mMesh;	//Mesh配列

	CModelX()
		: mpPointer(0), mAnimationIndex(0), mAnimaFlag(false),mTexDirectory("")
	{}
	~CModelX() {
		if (mFrame.size() > 0)
			delete mFrame[0];
		for (int i = 0; i < mAnimationSet.size(); i++) {
			delete mAnimationSet[i];
		}
		//17
		//マテリアルの解放
		for (int i = 0; i < mMaterial.size(); i++) {
			delete mMaterial[i];
		}
		//18
		//テクスチャの解放
		for (int i = 0; i < mTexture.size(); i++) {
			delete mTexture[i];
		}
	}
	//ファイル場所指定
	void TexDirectory(char *fileName) {mTexDirectory = fileName;}
	//ファイル読み込み
	void Load(char* file);
	//ファイル読み込み
	void NoAnimaLoad(char* file);
	//単語の取り出し
	void GetToken();
	//ノードの読み飛ばし
	void SkipNode();
	//浮動小数点データの取得
	float GetFloatToken();
	//整数データの取得
	int GetIntToken();
	//描画
	void Render();
	CModelXFrame* FindFrame(char* name);

	//フレームの変換行列更新
	void AnimateFrame();
	//16
	//スキンウェイトのフレーム番号設定
	void SetSkinWeightFrameIndex();
	//頂点にアニメーションを適用
	void AnimateVertex();
	//17
	//マテリアルの検索
	CMaterial* FindMaterial(char* name);
	//18
	//テクスチャの検索
	CTexture* FindTexture(char* name);
	//20
	//アニメーションセットの追加
	void AddAnimationSet(char* filename);

	void CreateVertexBuffer();

};
/*
メッシュ毎の
スキンメッシュ行列配列のクラス
*/
class CMeshSkinMatrix {
public:
	CMatrix44 *mpSkinnedMatrix;	//行列の配列
	int mSize;	//行列の要素数
	CMeshSkinMatrix()
		: mpSkinnedMatrix(0)
		, mSize(0)
	{}
	~CMeshSkinMatrix() {
		SAFE_DELETE_ARRAY(mpSkinnedMatrix);
	}
};
#include "../Task/CTask.h"

/*
スキンメッシュ用
アニメーション制御クラス
*/
class CModelXS : public CTask{
public:
	CModelX *mpModel;	//Xモデルデータへのポインタ
	CMatrix44 *mpCombinedMatrix;	//ボーンの合成行列
	CMeshSkinMatrix *mpMeshSkinMatrix;	//メッシュ毎のスキンメッシュ行列

	bool mAnimaFlag;//アニメーションをするか判断
	int mAnimationIndex;	//アニメーション番号
	bool mAnimationLoopFlg;	//true:繰り返す
	bool mRenderFlag;//描画のフラグ
	float mAnimationFrameSize;//アニメーションの再生フレーム数
	float mAnimationTime;	//現在のアニメーション時間

	CModelXS()
		: mpModel(0)
		, mpCombinedMatrix(0)
		, mpMeshSkinMatrix(0)
		, mRenderFlag(true)
		, mAnimaFlag(false)
	{}

	~CModelXS() {
		SAFE_DELETE_ARRAY(mpCombinedMatrix);
		SAFE_DELETE_ARRAY(mpMeshSkinMatrix);
	}

	//初期化処理
	void Init(CModelX *model);
	//アニメーションの変更
	//void ChangeAnimation(int index, bool loop, float framesize);
	//アニメーションの変更
	void ChangeAnimation(char *fileName, bool loop, float framesize);
	//使いまわしようアニメーションの変更
	void ChangeAnimation(char *fileName, char *fileSecondName, bool loop, float framesize);
	//更新処理
	void Update(CMatrix44 &m);
	void UpdateSkinMatrix(CMatrix44 &matrix);

	//MATRIXのみ更新
	void MatrixUpdate(CMatrix44 &m);

	//描画処理
	void Render();

	

};

#endif
