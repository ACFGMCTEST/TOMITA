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
#define TITLE_LOGO_SIZE		RECT_SIZE(0.7f,TEX_TITLE_X,TEX_TITLE_Y) 
#define RECT_BUTTON_SIZE	RECT_SIZE(0.7f,TEX_BUTTON_X,TEX_BUTTON_Y)
#define STAGE_CURSOR_SIZE	RECT_SIZE(0.3f,TEX_STAGE_CURSOR_X,TEX_STAGE_CURSOR_Y)
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
#define FLASHING_NUM 0.01f,1.0f,0.7f

CHome::~CHome(){

}
CHome::CHome() :CTitle(){

	eScene = eSceneNo::E_HOME;
	/*タイトル色指定*/
	mTitleLogo.SetColor(NO_A_WHITE_COLOR,0.0f);
	/*セレクトポリゴン設定*/
	mSelectButton.SetColor(NO_A_WHITE_COLOR, 0.0f);
	mSelectButton.SetVertex(RECT_BUTTON_SIZE);
	mSelectButton.mPosition = SELECT_POS;
	/*モデルチェンジポリゴン設定*/
	mModelChangeButton.SetColor(NO_A_WHITE_COLOR, 0.0f);
	mModelChangeButton.SetVertex(RECT_BUTTON_SIZE);
	mModelChangeButton.mPosition = MODEL_CHANGE_POS;
	/*セレクトのButtonポリゴン設定*/
	mSelectCursor.SetColor(NO_A_WHITE_COLOR, 0.0f);
	mSelectCursor.SetVertex(STAGE_CURSOR_SIZE);
	mSelectCursor.mPosition = 
		CVector2(*mSelectButton.mpLeft - *mSelectCursor.mpRight + mSelectButton.mPosition.x
		,mSelectButton.mPosition.y);

	/*セレクトテクスチャ設定*/
	mTexSelectButton.Load(TEX_SELECT_FILE);
	mSelectButton.SetUv(&mTexSelectButton, 0, 0, TEX_BUTTON_X, TEX_BUTTON_Y);
	/*セレクトテクスチャ設定*/
	mTexModelChangeButton.Load(TEX_MODEL_CHANGE_FILE);
	mModelChangeButton.SetUv(&mTexModelChangeButton, 0, 0,TEX_BUTTON_X, TEX_BUTTON_Y);	
	/*セレクトテクスチャ設定*/
	mTexStageCursor.Load(TEX_STAGE_CURSOR_FILE);
	mSelectCursor.SetUv(&mTexStageCursor, 0, 0, TEX_STAGE_CURSOR_X, TEX_STAGE_CURSOR_Y);

}
/*選択初期化*/
void CHome::SelectInit() {
	/*モデルチェンジ初期化*/
	mModelChangeButton.SetColor(NO_A_WHITE_COLOR, 1.0f);//色戻す
	mModelChangeButton.SetVertex(RECT_BUTTON_SIZE);//サイズ戻す
	mModelChangeButton.mPosition = MODEL_CHANGE_POS;//ポジション戻す

	mSelectButton.SetColor(NO_A_WHITE_COLOR, 1.0f);//カラー戻す
	mSelectButton.SetVertex(RECT_BUTTON_SIZE);//サイズ戻す
	mSelectButton.mPosition = SELECT_POS;//ポジション戻す
}
/*選択処理*/
void CHome::Select(){

	/*セレクトを選んだ場合*/
	if (eScene == E_HOME) {
		if (mSelectCursor.mPosition.y == mSelectButton.mPosition.y) {
			/*演出*/
			mSelectButton.RectScalingLeftPos(SCALLING_NUM);//拡大
			mSelectButton.FlashingColor(FLASHING_NUM);//色点滅
		}
		else 
			if (mSelectCursor.mPosition.y == mModelChangeButton.mPosition.y) {
				/*演出処理*/
				mModelChangeButton.RectScalingLeftPos(SCALLING_NUM);//拡大
				mModelChangeButton.FlashingColor(FLASHING_NUM);//色点滅
			}
	}

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
/*決定された場合(キー編)*/
void CHome::SelectDecisionKey() {
	/*キーバージョン*/
	/*選択したか判断 モデルチェンジの場合*/
	if (CKey::once(VK_RETURN)) {
		if (mSelectCursor.mPosition.y == mModelChangeButton.mPosition.y) {
			eScene = E_MODEL_CHANGE;
			return;
		}
		else /*選択したか判断 ステージセレクトの場合*/
			if (mSelectCursor.mPosition.y == mSelectButton.mPosition.y) {
				eScene = E_STAGE_SELECT;
				return;
			}
	}
}
/*決定された場合(マウス編)*/
void CHome::SelectDecisionMouse() {
	/*マウスバージョン*/
	if (CCollision2D::Collision2D(mModelChangeButton, mCursor)) {
		mSelectCursor.mPosition.y = mModelChangeButton.mPosition.y;
		mModelChangeButton.RectScalingLeftPos(SCALLING_NUM);//拡大
		if (CMouse::GetInstance()->mOneLeftFlag) {
			eScene = E_MODEL_CHANGE;
		}
		return;
	}
	/*選択したか判断 ステージセレクトの場合*/
	if (CCollision2D::Collision2D(mSelectButton, mCursor) ) {
		mSelectCursor.mPosition.y = mSelectButton.mPosition.y;
		mSelectButton.RectScalingLeftPos(SCALLING_NUM);//拡大

		if (CMouse::GetInstance()->mOneLeftFlag) {
			eScene = E_STAGE_SELECT;//セレクトに
		}

		return;
	}
}
/*決定された場合*/
void CHome::SelectDecision(){
	/*選択したときの関数*/
	Select();
	SelectDecisionKey();
	SelectDecisionMouse();
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
void CHome::Update() {
	/*BGのScroll処理*/
	CTitle::Scroll();
	
	/*決定されてたか判断*/
	SelectDecision();


	/*フェード処理*/
	/*フラグが立つとフェイドアウトしていく*/

	if (eScene == E_MODEL_CHANGE)mModelChangeButton.FadeOut(FADE_SPEED, 0.0f);
	if (eScene == E_STAGE_SELECT) mSelectButton.FadeOut(FADE_SPEED, 0.0f);
	if(eScene != E_HOME)mSelectCursor.FadeOut(FADE_SPEED, 0.0f);

	/*演出初回フェードで登場*/
	if (eScene == E_HOME && mSelectButton.mTriangle1.a != 1) {
		AllFade();
	}
};
/*初めのフェード処理*/
void CHome::AllFade() {
	mTitleLogo.Fade(FADE_SPEED, 1.0f);
	mSelectButton.Fade(FADE_SPEED, 1.0f);
	mModelChangeButton.Fade(FADE_SPEED, 1.0f);
	mSelectCursor.Fade(FADE_SPEED, 1.0f);
}
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