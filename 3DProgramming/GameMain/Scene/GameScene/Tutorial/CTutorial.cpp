#include "CTutorial.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CKey.h"
#include "../UI/CScoreBoard.h"
#include "../../../Camera/CCamera.h"
#include "../../../Key/CMouse.h"
/*サイズ*/
#define PERCENT_OPERA 1.2f
#define SIZE_OPERA			-200*PERCENT_OPERA,\
							20*PERCENT_OPERA,\
							200*PERCENT_OPERA,\
							-20*PERCENT_OPERA
/*読み込み*/
#define TEX_NAME			TGA_FILE"tutorial/operation.tga"

/*テクスチャサイズ*/
#define TEX_SIZE		0,0,400,280//すべての大きさ 上幅感覚４０です
#define TEX_SIZE(i)		0,i*40,400,40*(i+1)//i個でテクスチャ分け

/*位置*/
#define FAST_POS			CVector2(0.0f,-100)	

#define POS(i)			CVector2(0.0f*(i+1),-100*(i+1))	

/*コンストラクタ*/
CTutorial::CTutorial() : mFlagUv(false), eTutoState(E_RULE){}
/*デストラクタ*/
CTutorial::~CTutorial(){}
/*初期化*/
void CTutorial::Init(){
	/*テクスチャ読み込み*/
	mTex.load(TEX_NAME);

	for (int i = 0; i < ARRAY_OPERA; i++){
		/*四角形サイズ設定*/
		mOperation[i].SetVertex(SIZE_OPERA);
		/*貼り付け*/
		mOperation[i].SetUv(&mTex, TEX_SIZE(E_TEX_RULE));
	}

}

/*更新*/
void CTutorial::Update(){

	for (int i = 0; i < ARRAY_OPERA; i++){
		mOperation[i].position = FAST_POS;
	}

	/*チューリアル状態遷移*/
	switch (eTutoState)
	{
	case CTutorial::E_RULE:

		/*エンター切り替え*/
		if (CKey::once(VK_RETURN) || CMouse::GetInstance()->mOneLeftFlag){
			eTutoState = E_PUCK;
			MainCamera.StateChange(CCamera::E_STATE::E_PACK);
		}

		break;
	case E_PUCK:

		/*エンター切り替え*/
		if (CKey::once(VK_RETURN) || CMouse::GetInstance()->mOneLeftFlag){
			eTutoState = E_GOAL;
			MainCamera.StateChange(CCamera::E_STATE::E_GOAL);
		}

		break;
	case E_GOAL:
		/*エンター切り替え*/
		if (CKey::once(VK_RETURN) || CMouse::GetInstance()->mOneLeftFlag){
			eTutoState = E_WALK;
			MainCamera.StateChange(CCamera::E_STATE::E_CHARA);
		}
		break;
	case CTutorial::E_WALK:
		/*テクスチャ張替え*/
		if (!mFlagUv){
			mOperation[0].SetUv(&mTex, TEX_SIZE(E_TEX_MOVE));
			mOperation[1].SetUv(&mTex, TEX_SIZE(E_TEX_MOVE));
			mFlagUv = true;
		}
		/*エンター切り替え*/
		if (CKey::once(VK_RETURN) || CMouse::GetInstance()->mOneLeftFlag){
			eTutoState = E_CAMERA;
			mFlagUv = false;
		}
		break;
	case E_CAMERA:
		/*ポジション変える*/
		for (int i = 0; i < ARRAY_OPERA; i++){
			mOperation[i].position = POS(i);
		}
		/*テクスチャ張替え*/
		if (!mFlagUv){
			mOperation[0].SetUv(&mTex, TEX_SIZE(E_TEX_CAMERA_KEY));
			mOperation[1].SetUv(&mTex, TEX_SIZE(E_TEX_CAMERA_MOUSE));
			mFlagUv = true;
		}
		/*エンター切り替え*/
		if (CKey::once(VK_RETURN) || CMouse::GetInstance()->mOneLeftFlag){
			eTutoState = E_ATTACK;
			mFlagUv = false;
		}
		break;

	case CTutorial::E_ATTACK:
		/*ポジション変える*/
		for (int i = 0; i < ARRAY_OPERA; i++){
			mOperation[i].position = POS(i);
		}
		/*テクスチャ張替え*/
		if (!mFlagUv){
			mOperation[0].SetUv(&mTex, TEX_SIZE(E_TEX_ATTACK_PUSH));
			mOperation[1].SetUv(&mTex, TEX_SIZE(E_TEX_ATACK_LONG));
			mFlagUv = true;
		}
		/*エンター切り替え*/
		if (CKey::once(VK_RETURN) || CMouse::GetInstance()->mOneLeftFlag){
			eTutoState = E_PAUZE;
			mFlagUv = false;
		}
		break;
	case CTutorial::E_PAUZE:
		/*テクスチャ張替え*/
		if (!mFlagUv){
			mOperation[0].SetUv(&mTex, TEX_SIZE(E_TEX_PAUZE));
			mOperation[1].SetUv(&mTex, TEX_SIZE(E_TEX_PAUZE));
			mFlagUv = true;
		}
		/*エンター切り替え*/
		if (CKey::once(VK_RETURN) || CMouse::GetInstance()->mOneLeftFlag){
			eTutoState = E_ARRAY;
			mFlagUv = false;
		}
		break;
	case CTutorial::E_ARRAY:
		break;
	}
}

/*描画*/
void CTutorial::Render(){
	/*チュートリアル中なら*/
	if (eTutoState != E_ARRAY){
		CRectangle2::Disp2D_Start();//2D処理開始
		/*描画開始*/
		for (int i = 0; i < ARRAY_OPERA; i++){
			mOperation[i].Render();

		}
		/*描画終了*/
		CRectangle2::Disp2D_Exit();//2D処理終了
	}
}
