#include <math.h>
#include"CTitle.h"
#include "../../../Define/Define.h"
#include "../../Convenient/CConvenient.h"
#include "../../Collision/CCollision2D.h"
#include "../../Key/CMouse.h"
#include"../../Key/CKey.h"
//テクスチャサイズ
#define TEX_TITLE_X		410
#define TEX_TITLE_Y		100
#define TEX_PUSH_X		210
#define TEX_PUSH_Y		30

//ポリゴンサイズ
#define TITLELOGO_SIZE	BUTTON_SIZE(0.8f,TEX_TITLE_X,TEX_TITLE_Y) 
#define PUSH_KEY_SIZE	BUTTON_SIZE(1,TEX_PUSH_X,TEX_PUSH_Y) 
#define CURSOR_SIZE		BUTTON_SIZE(0.1f,TEX_CURSOR_X,TEX_CURSOR_Y)
/*ポリゴンのポジション*/
#define TITLE_POS		BUTTON_POS(0,0.2f)
#define PUSH_KEY_POS	BUTTON_POS(0,-0.2f)



/*テクスチャ場所*/
#define TEX_TITLE_FILE		TGA_FILE"Title\\TitleLogo.tga"
#define TEX_PUSH_KEY_FILE	TGA_FILE"Title\\PushKey.tga"


/*BGのScroll引継ぎ変数*/
float CTitle::mScrollLeft = 0;
float CTitle::mScrollRight = 0;

CTitle::~CTitle(){
}

CTitle::CTitle() :mFlagFadeOut(false){

	/*タイトルポリゴン設定*/
	mTitleLogo.SetColor(NO_A_WHITE_COLOR,0.0f); //タイトルロゴのカラーを決める
	mTitleLogo.SetVertex(TITLELOGO_SIZE);//タイトルサイズ決める
	mTitleLogo.mPosition = TITLE_POS;//ポジション決める
	/*押してくださいポリゴン設定*/
	mPushKey.SetColor(NO_A_WHITE_COLOR, 0.0f); //タイトルロゴのカラーを決める
	mPushKey.SetVertex(PUSH_KEY_SIZE);//タイトルサイズ決める
	mPushKey.mPosition = PUSH_KEY_POS;//ポジション決める
	/*背景ポリゴン設定*/
	mBG.SetColor(WHITE_COLOR); //タイトルロゴのカラーを決める
	mBG.SetVertex(BG_SIZE);
	/*CURSORポリゴン設定*/
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.mpPos = &CMouse::GetInstance()->mPos;

	/*タイトルテクスチャ設定*/
	mTexTitleLogo.load(TEX_TITLE_FILE);	//テクスチャファイル読み込み
	mTitleLogo.SetUv(&mTexTitleLogo, 0, 0, TEX_TITLE_X, TEX_TITLE_Y);//TGA上の座標
	/*押してくださいテクスチャ設定*/
	mTexPushKey.load(TEX_PUSH_KEY_FILE);	//テクスチャファイル読み込み
	mPushKey.SetUv(&mTexPushKey,0,0,TEX_PUSH_X,TEX_PUSH_Y);//TGA上の座標
	/*背景テクスチャ設定*/
	mTexBG.load(TEX_BG_FILE);	//テクスチャファイル読み込み
	mBG.SetUv(&mTexBG, 0,0,TEX_BG_X,TEX_BG_Y);//TGA上の座標
	/*カーソル*/
	mTexCursor.load(TEX_CURSOR_FILE);
	mCursor.SetUv(&mTexCursor, 0, 0, TEX_CURSOR_X, TEX_CURSOR_Y);
}

/*BGのScroll処理*/
void CTitle::Scroll(){
	/*背景スクロール処理*/
	mBG.TexSideScroll(SCROLL_SPEED, TEX_BG_SCROLL);
	/*Scroll情報記憶*/
	mScrollLeft = mBG.mSaveTexVer[CRectangle2::E_TEXVER::E_LEFT];
	mScrollRight = mBG.mSaveTexVer[CRectangle2::E_TEXVER::E_RIGHT];

}
/*更新処理*/
void CTitle::Update(){
	Scroll();
	/*当たり判定の処理 ボタンをクリックしたとき,またはエンターを押したとき*/
	if (CCollision2D::Collision2D(mPushKey, mCursor) && CMouse::GetInstance()->mOneLeftFlag ||
		CKey::once(VK_RETURN)){
		mFlagFadeOut = true;
	}
	/*フラグが立つとフェイドアウトしていく*/
	if (mFlagFadeOut){
		mPushKey.FadeOut(FADE_SPEED, 0.0f);
	}
	/*演出初回フェードで登場*/
	else if(mTitleLogo.mTriangle1.a != 1){
		mTitleLogo.Fade(FADE_SPEED,ALPHA_MAX);
		mPushKey.Fade(FADE_SPEED, ALPHA_MAX);
	}


};
/*シーン遷移するときに使う*/
bool CTitle::SceneFlag(){
	/*フェードアウトが終了したら*/
	if (mPushKey.mTriangle1.a == 0.0f){
		return true;
	}
	return false;
}
/*BGのSCROLL引継ぎInit*/
void CTitle::BgScrollInit(){
	mBG.Uv(mScrollLeft, 0, mScrollRight, mBG.mSaveTexVer[CRectangle2::E_TEXVER::E_BOTTOM]);
}

/*描画*/
void CTitle::Render() {
	CRectangle2::Disp2D_Start();//描画はじめ
	mBG.Render();
	mTitleLogo.Render();
	mPushKey.Render();
	mCursor.Render();
	CRectangle2::Disp2D_Exit();;//描画終了


}
