#include"CHome.h"
#include "../Define\Define.h"
#include <fstream> 
#include <stdio.h>
#include "../GameMain\Key\CKey.h"
#include "../../Key/CMouse.h"
#include "../../Collision/CCollision2D.h"
//テクスチャサイズ
#define TEX_TITLE_X			410
#define TEX_TITLE_Y			100

//ポリゴンサイズ
#define TITLE_LOGO_SIZE		BUTTON_SIZE(0.7f,TEX_TITLE_X,TEX_TITLE_Y) 
#define RECT_BUTTON_SIZE	BUTTON_SIZE(0.7f,TEX_BUTTON_X,TEX_BUTTON_Y)
#define STAGE_CURSOR_SIZE	BUTTON_SIZE(0.3f,TEX_STAGE_CURSOR_X,TEX_STAGE_CURSOR_Y)
/*ポリゴンのポジション*/
#define TITLE_POS			BUTTON_POS(0,0.2f)
#define SELECT_POS			BUTTON_POS(0.06f,-0.2f)
#define MODEL_CHANGE_POS	BUTTON_POS(0.06f,-0.4f)
/*テクスチャ場所*/
#define TEX_TITLE_FILE			TGA_FILE"Title\\TitleLogo.tga"
#define TEX_SELECT_FILE			TGA_FILE"Home\\StageSelect.tga"
#define TEX_MODEL_CHANGE_FILE	TGA_FILE"Home\\ModelChange.tga"
/*演出の数値 拡大縮小関数*/
#define SCALLING_NUM 1.2f,2.0f
/*演出の数値 色の点滅用*/
#define FLASHING_NUM 0.005f,1.0f,0.7f

CHome::~CHome(){

}
CHome::CHome() :CTitle(){
	/*BGのScroll引継ぎ*/
	CTitle::BgScrollInit();
	/*タイトル色指定*/
	mTitleLogo.SetColor(WHITE_COLOR);
	/*セレクトポリゴン設定*/
	mSelectButton.SetColor(NO_A_GRAY_COLOR, 0.0f);
	mSelectButton.SetVertex(RECT_BUTTON_SIZE);
	mSelectButton.mPosition = SELECT_POS;
	/*モデルチェンジポリゴン設定*/
	mModelChangeButton.SetColor(NO_A_GRAY_COLOR, 0.0f);
	mModelChangeButton.SetVertex(RECT_BUTTON_SIZE);
	mModelChangeButton.mPosition = MODEL_CHANGE_POS;
	/*セレクトのButtonポリゴン設定*/
	mSelectCursor.SetColor(NO_A_GRAY_COLOR, 0.0f);
	mSelectCursor.SetVertex(STAGE_CURSOR_SIZE);
	mSelectCursor.mPosition = CVector2(*mSelectButton.mpLeft - *mSelectCursor.mpRight + mSelectButton.mPosition.x
		,mSelectButton.mPosition.y);

	/*セレクトテクスチャ設定*/
	mTexSelectButton.load(TEX_SELECT_FILE);
	mSelectButton.SetUv(&mTexSelectButton, 0, 0, TEX_BUTTON_X, TEX_BUTTON_Y);
	/*セレクトテクスチャ設定*/
	mTexModelChangeButton.load(TEX_MODEL_CHANGE_FILE);
	mModelChangeButton.SetUv(&mTexModelChangeButton, 0, 0,TEX_BUTTON_X, TEX_BUTTON_Y);	
	/*セレクトテクスチャ設定*/
	mTexStageCursor.load(TEX_STAGE_CURSOR_FILE);
	mSelectCursor.SetUv(&mTexStageCursor, 0, 0, TEX_STAGE_CURSOR_X, TEX_STAGE_CURSOR_Y);

}


/*選択処理*/
void CHome::Select(){

	/*セレクトを選んだ場合*/
	if (mSelectCursor.mPosition.y == mSelectButton.mPosition.y){
		/*演出*/
		mSelectButton.RectScalingLeftPos(SCALLING_NUM);//拡大
		mSelectButton.FlashingColor(FLASHING_NUM);//色点滅
	}
	else{
		/*セレクト初期化*/
		mSelectButton.SetColor(NO_A_GRAY_COLOR, 1.0f);//カラー戻す
		mSelectButton.SetVertex(RECT_BUTTON_SIZE);//サイズ戻す
		mSelectButton.mPosition = SELECT_POS;//ポジション戻す
	}

	/*モデルチェンジを選んだ場合*/
	if (mSelectCursor.mPosition.y == mModelChangeButton.mPosition.y){
		/*演出処理*/
		mModelChangeButton.RectScalingLeftPos(SCALLING_NUM);//拡大
		mModelChangeButton.FlashingColor(FLASHING_NUM);//色点滅
	}
	else{
		/*モデルチェンジ初期化*/
		mModelChangeButton.SetColor(NO_A_GRAY_COLOR, 1.0f);//色戻す
		mModelChangeButton.SetVertex(RECT_BUTTON_SIZE);//サイズ戻す
		mModelChangeButton.mPosition = MODEL_CHANGE_POS;//ポジション戻す
	}

	/*色点滅*/
	mSelectCursor.FlashingColor(FLASHING_NUM);

	/*Cursorの移動処理*/
	/*モデルチェンジ選んだ時*/
	if (CKey::once(DOWN_KEY)){
		mSelectCursor.mPosition.y = mModelChangeButton.mPosition.y;
	}
	/*ステージセレクト選んだ時*/
	if (CKey::once(UP_KEY)){
		mSelectCursor.mPosition.y = mSelectButton.mPosition.y;
	
	}

}

/*決定された場合*/
void CHome::SelectDecision(){
	/*マウスバージョン*/
	if (CCollision2D::Collision2D(mModelChangeButton, mCursor) && CMouse::GetInstance()->mOneLeftFlag){
		mFlagFadeOut = true;
		mSelectCursor.mPosition.y = mModelChangeButton.mPosition.y;
		mModelChangeButton.RectScalingLeftPos(SCALLING_NUM);//拡大
		eScene = E_MODEL_CHANGE;
		return;
	}
	/*選択したか判断 ステージセレクトの場合*/
	if (CCollision2D::Collision2D(mSelectButton, mCursor) && CMouse::GetInstance()->mOneLeftFlag ){
		mFlagFadeOut = true;
		mSelectCursor.mPosition.y = mSelectButton.mPosition.y;
		mSelectButton.RectScalingLeftPos(SCALLING_NUM);//拡大
		eScene = E_STAGE_SELECT;//セレクトに

		return;
	}
	/*キーバージョン*/
	/*選択したか判断 モデルチェンジの場合*/
	if (CKey::once(VK_RETURN) && mSelectCursor.mPosition.y == mModelChangeButton.mPosition.y){
		mFlagFadeOut = true;
		eScene = E_MODEL_CHANGE;
		return;
	}
	/*選択したか判断 ステージセレクトの場合*/
	if (CKey::once(VK_RETURN) && mSelectCursor.mPosition.y == mSelectButton.mPosition.y){
		mFlagFadeOut = true;
		eScene = E_STAGE_SELECT;
		return;
	}


}
/*シーン遷移 判断*/
bool CHome::SceneFlag(){
	/*フェードアウトが完了したら*/
	if (mModelChangeButton.mTriangle1.a == 0 || 
		mSelectButton.mTriangle1.a == 0){
		return true;
	}
	return false;
	
}

/*更新処理*/
void CHome::Update(){
	/*BGのScroll処理*/
	CTitle::Scroll();
	/*選択したときの関数*/
	Select();
	/*決定されてたか判断*/
	SelectDecision();


	/*フェード処理*/
	/*フラグが立つとフェイドアウトしていく*/
	if (mFlagFadeOut){
		mSelectButton.FadeOut(FADE_SPEED, 0.0f);
		if (eScene == E_MODEL_CHANGE)mModelChangeButton.FadeOut(FADE_SPEED, 0.0f);
		if (eScene == E_STAGE_SELECT)mSelectCursor.FadeOut(FADE_SPEED, 0.0f);
	}
	/*演出初回フェードで登場*/
	else if (mSelectButton.mTriangle1.a != 1){
		mSelectButton.Fade(FADE_SPEED, 1.0f);
		mModelChangeButton.Fade(FADE_SPEED, 1.0f);
		mSelectCursor.Fade(FADE_SPEED, 1.0f);

	}
};

/*
描画処理のみを行う。
*/
void CHome::Render() {
	CRectangle2::Disp2D_Start();//描画はじめ


	mBG.Render();	
	mTitleLogo.Render();
	mSelectButton.Render();
	mModelChangeButton.Render();
	mSelectCursor.Render();
	mCursor.Render();


	
	CRectangle2::Disp2D_Exit();//描画終わり
}