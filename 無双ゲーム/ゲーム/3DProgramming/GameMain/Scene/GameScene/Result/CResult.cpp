#include "../CGameScene.h"
#include "CResult.h"
#include "../../../Convenient/CConvenient.h"
/*サイズ*/
#define BG_SIZE -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y
#define LOGO_POS CVector2(0.0f,100.0f) //ポジション

CResult* CResult::mResult = 0;
//GetInstance
CResult* CResult::GetInstance() {
	if (mResult == 0) {
		mResult = new CResult();
	}
	return mResult;
}

CResult::~CResult(){

}
/*テクスチャのサイズ*/
#define TEX_SIZE_X 340
#define TEX_SIZE_Y 50
void CResult::Init(){
	mRenderFlag = false;
	mCount = 0.0f;
	//ロゴテクスチャ
	mTexLogo.Load(TGA_FILE"Result\\Result.tga");
	
	//背景の呼び出し
	mBG.SetVertex(BG_SIZE); //ここで大きさ変更	
	mBG.SetColor(0.0f, 0.0f, 0.0f, 0.0f);//色をブラックにする
	mBG.SetUv(&mTexBG, TEST_CG);



	//クリアロゴの呼び出し
	mLogo.SetVertex(RECT_SIZE(1.0f, TEX_SIZE_X, TEX_SIZE_Y)); //ここで大きさ変更
	mLogo.SetColor(NO_A_WHITE_COLOR, 0.0f);
	mLogo.SetUv(&mTexLogo, 0.0f, TEX_SIZE_Y, TEX_SIZE_X, TEX_SIZE_Y * 2);//テクスチャ　over時
	mLogo.mPosition = LOGO_POS;

}

//Clearしたとき呼ぶ
void CResult::Clear() {
	mBG.SetColor(NO_A_WHITE_COLOR, 0.0f);
	mLogo.SetUv(&mTexLogo, 0.0f, 0.0f, TEX_SIZE_X, TEX_SIZE_Y);
	mRenderFlag = true;
}
//死亡したとき呼ぶ
void CResult::Over() {
	mBG.SetColor(0.0f, 0.0f, 0.0f, 0.0f);
	mRenderFlag = true;
}

#define FADE_SPEED 0.01f
#define FADE_BG_SPEED 0.005f
#define FADE_TIME 4.0f //フェードが始まる時間
void CResult::Update(){
	/*描画する状態なら*/
	if (mRenderFlag) {
		/*時間がたっていない場合*/
		if (!CConvenient::Time(&mCount, FADE_TIME)) {
			mLogo.Fade(FADE_SPEED, 1.0f);
		}
		else {
			mBG.Fade(FADE_BG_SPEED, 1.0f);
			mLogo.FadeOut(FADE_BG_SPEED, 0.0f);
			if(mLogo.mTriangle1.a == 0.0f)CGameScene::eState = CGameScene::E_END;
		}
	}

};

/*
描画処理のみを行う。
*/
void CResult::Render() {
	if (mRenderFlag) {
		
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//色は置き換えてマッピング

		CRectangle2::Disp2D_Start();//2D処理開始

		/*この場所に描画処理を入れる*/
		mBG.Render();
		mLogo.Render();
		/*描画終了*/

		CRectangle2::Disp2D_Exit();//2D処理終了

	}
}