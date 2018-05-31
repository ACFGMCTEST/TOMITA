//冨田健斗
#ifndef CEffect2D_HPP
#define CEffect2D_HPP
#include  "../../../Task/CTask.h"
#include "../../../Graphic/CRectangle.h"
#define TIP_ARRAY 11

/*エフェクトサイズ*/
#define EFF_SIZE(x,y)CVector3(-x,y,0.0f),\
	CVector3(-x, -y, 0.0f), \
	CVector3(x, -y, 0.0f), \
	CVector3(x, y, 0.0f)
/*ハンマーエフェクトサイズ*/
#define HAMMER_EFFECT_SIZE	CVector3 (-0.1f, 0.1f,0.0f),\
	CVector3(-0.1f, -0.1f, 0.0f), \
	CVector3(0.1f, -0.1f, 0.0f), \
	CVector3(0.1f, 0.1f, 0.0f)
#define HAMMER_EFFECT_POS CVector3(0.0f, 0.8f, 0.0f)
#define HAMMER_SIZE_UP 0.002f //サイズアップするスピード

/*エフェクトのポジション*/
#define SPARK_EFFECT_POS CVector3(0.0f, 1.0f, 0.0f)

/*テクスチャのエフェクトサイズ*/
#define TEX_HAMMER_EFFECT_SIZE 0,0,960,192
#define TEX_HAMMER_EFFECT_WIDTH 192 //幅
#define TEX_HAMMER_EFFECT_ANI_SIZE 5
/*ゴール*/
#define TEX_SPARK_EFFECT_SIZE 0,0,1125,225
#define TEX_SPARK_EFFECT_WIDTH 225 //幅
#define TEX_SPARK_EFFECT_ANI_SIZE 5

class CEffect2D : public CRectangle ,public CTask{
private:
	CTexture mTex;/*テクスチャ*/
	float mAnimaCount;//現在の枚数
	float mAnimaSize;//何枚あるか
	float mAnimaFrameNum; //現在のナンバー数
	float mTimeCount;//カウント用
	float mAnimaFrameMax; //アニメーションの最大Frame数配列数なので注意
	float *mpWidthLeft, *mpWidthRight;//幅
	float mTexLeft, mTexTop, mTexRight, mTexBottom; //縦横
	float mAnimaSpeed;//再生スピード
	bool mAnimaFlag;//アニメーションをスタートするか決める

	enum E_VER{
		E_LT,//左上
		E_LB,//左下
		E_RB,//右下
		E_RT, //右上
		E_ARRAY
	};
	CVector3 ver[E_ARRAY];//頂点数
public:
	~CEffect2D();
	CEffect2D();
	/*サイズ指定*/
	void SetVertex(CVector3 v0, CVector3 v1, CVector3 v2, CVector3 v3);
	/*アニメーション枚数と間隔指定*/
	void SetAnima(int size,float width);
	/*現在のフレーム数指定*/
	void SetFrame(int i);
	/*サイズアップ*/
	void SizeUp(float up);
	/*テクスチャ貼り付け*/
	void SetTex(CTexture *name, float left, float top, float right, float bottom);
	/*更新処理*/
	void Update();
	/*描画処理*/
	void Render();
	/*アニメーションフラグをtrueに,引数で再生スピードとポジションを決める*/
	void StartAnima(float speed ,CVector3 pos);
	/*アニメーションフラグをfalseに*/
	void DisableAnima();

	/*初期設定*/
	void CEffect2D::Init(char *name, float x, float y, STexVer texVer);
	/*テクスチャがあるときの初期化*/
	void NoTexInit();



};
#endif
