#include "../CGameScene.h"
#include "CTutorial.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CKey.h"
#include "../../../Camera/CCamera.h"
#include "../../../Key/CMouse.h"
#include "../../../Convenient/CConvenient.h"
#include "../../../Collision/CCollision.h"
/*テクスチャの頂点指定,簡略化*/
#define TEX_SIZE(v) v.left,v.top,v.right,v.bottom 

CTutorial* CTutorial::mpTutorial = 0;

//GetInstance
CTutorial* CTutorial::GetInstance() {
	if (mpTutorial == 0) {
		mpTutorial = new CTutorial();
	}
	return mpTutorial;
}

/*コンストラクタ*/
CTutorial::CTutorial() : mFlagUv(false), eState(ESTATE::ALL_ENE_KILL)
, mTime(0){}
/*デストラクタ*/
CTutorial::~CTutorial(){}

/*初期化*/
void CTutorial::Init() {
	mPos = CVector3(0.0f, 0.0f, 0.0f);
	eState = ESTATE::ALL_ENE_KILL;
	mTime = 0;
#define TEX_X 600//テクスチャの横幅
#define TEX_Y 37//テクスチャ行幅
#define TEX_BG_Y 70//BGのサイズY
#define SIZE_DOUB 0.6f
	/*サイズ*/
	mRect.SetVertex(RECT_SIZE(SIZE_DOUB, TEX_X, TEX_Y));
	mRect.mPosition.y = DISP_2D_Y / 2.5f;//ポジション設定
	mBG.SetVertex(RECT_SIZE(SIZE_DOUB, TEX_X, TEX_BG_Y));
	mBG.mPosition = mRect.mPosition;
	const float ajust = 10;//ポジション調整用
	mBG.mPosition.y -= TEX_Y * SIZE_DOUB - ajust;
	/*テクスチャ*/
	/*テクスチャ*/
	mTex.Load(TGA_FILE"Tutorial\\Text.tga");
	mTexBG.Load(TGA_FILE"Tutorial\\TextBG.tga");
	/*頂点数保存種類分け*/
	for (int i = 0; i < ESTATE::ARRAY; i++) {
		mVer[i] = STexVer(0.0f, TEX_Y * (i), TEX_X, TEX_Y * (i + 1));
	}
	/*UV張替え*/
	mRect.SetUv(&mTex, TEX_SIZE(mVer[eState]));
	mBG.SetUv  (&mTexBG, TEX_SIZE(STexVer(0,0, TEX_X, TEX_BG_Y)));
	/*アルファ調整*/
	mRect.SetColor(NO_A_WHITE_COLOR, 0.5f);//半透明にする
}

/*更新*/
void CTutorial::Update(){
	/*１秒たったら && はじめのみ*/
	if (CConvenient::Time(&mTime, 1.0f) && eState  == ESTATE::ALL_ENE_KILL) {
		CGameScene::mPauseFlag = true;
	}
	/*Enterを押すと画面切り替え*/
	if (CKey::once(VK_RETURN)) {
		Change();
		CGameScene::mPauseFlag = false;
	}
}
/*文字切り替え*/
void CTutorial::Change() {
	int i = eState + 1;
	eState = (ESTATE)i;//文字を進める;
	/*UV張替え*/
	mRect.SetUv(&mTex, TEX_SIZE(mVer[eState]));
}

/*描画*/
void CTutorial::Render(){
	/*チュートリアル中なら*/
	if (eState < ARRAY){
		CRectangle2::Disp2D_Start();//2D処理開始
		/*描画開始*/
		mBG.Render();
		mRect.Render();
		/*描画終了*/
		CRectangle2::Disp2D_Exit();//2D処理終了
	}
}
