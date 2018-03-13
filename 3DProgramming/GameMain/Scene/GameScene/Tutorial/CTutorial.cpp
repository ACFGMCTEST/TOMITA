#include "CTutorial.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CKey.h"
#include "../UI/CScoreBoard.h"

/*サイズ*/
#define SIZE_FRAME			-150,50,150,-50
#define SIZE_OPERA			-150,50,150,-50
/*読み込み*/
#define TEX_NAME_FRAME					TGA_FILE"tutorial/frame.tga"
#define TEX_NAME_OPE_RULE				TGA_FILE"tutorial/rule.tga"
#define TEX_NAME_OPE_WALK				TGA_FILE"tutorial/walk.tga"
#define TEX_NAME_OPE_CAMERA_KEY			TGA_FILE"tutorial/cameraKey.tga"
#define TEX_NAME_OPE_CAMERA_MOUSE		TGA_FILE"tutorial/cameraMouse.tga"
#define TEX_NAME_OPE_PAUSE				TGA_FILE"tutorial/pause.tga"
#define TEX_NAME_OPE_SPECIAL			TGA_FILE"tutorial/special.tga"
/*テクスチャサイズ*/
#define TEX_SIZE_FRAME		0,0,400,100	
#define TEX_SIZE_OPERA		0,0,400,100	
#define TEX_SIZE_WALK		0,0,400,100	
#define TEX_SIZE_MOUSE		0,0,400,100	
#define TEX_SIZE_KEY		0,0,400,100	

/*位置*/
#define FAST_POS			CVector2(0.0f,100)	
/*コンストラクタ*/
CTutorial::CTutorial() : mFlagUv(false), eTutoState(E_RULE){}
/*デストラクタ*/
CTutorial::~CTutorial(){}
/*初期化*/
void CTutorial::Init(){
	
	/*テクスチャ読み込み*/
	mTexFrame.load(TEX_NAME_FRAME);//枠ロード
	mTexOperation.load(TEX_NAME_OPE_RULE);//RULEロード
	mTexWalk.load(TEX_NAME_OPE_WALK);//
	mTexCameraKey.load(TEX_NAME_OPE_CAMERA_KEY);
	mTexCameraMouse.load(TEX_NAME_OPE_CAMERA_MOUSE);

	for (int i = 0; i < ARRAY_OPERA; i++){
		/*四角形サイズ設定*/
		mOperation[i].SetVertex(SIZE_OPERA);
		/*貼り付け*/
		mOperation[i].SetUv(&mTexOperation, TEX_SIZE_OPERA);
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
		if (CKey::once(VK_RETURN)){
			eTutoState = E_WALK;
		}

		break;
	case CTutorial::E_WALK:
		/*テクスチャ張替え*/
		if (!mFlagUv){
			mOperation[0].SetUv(&mTexWalk, TEX_SIZE_FRAME);
			mOperation[1].SetUv(&mTexWalk, TEX_SIZE_FRAME);
			mFlagUv = true;
		}
		/*エンター切り替え*/
		if (CKey::once(VK_RETURN)){
			eTutoState = E_ATTACK;
			mFlagUv = false;
		}
		break;
	case CTutorial::E_ATTACK:
		/*テクスチャ張替え*/
		if (!mFlagUv){
			mOperation[0].SetUv(&mTexCameraKey, TEX_SIZE_FRAME);
			mOperation[1].SetUv(&mTexCameraKey, TEX_SIZE_FRAME);
			mFlagUv = true;
		}
		/*エンター切り替え*/
		if (CKey::once(VK_RETURN)){
			eTutoState = E_PAUZE;
			mFlagUv = false;
		}
		break;
	case CTutorial::E_PAUZE:
		/*テクスチャ張替え*/
		if (!mFlagUv){
			mOperation[0].SetUv(&mTexCameraMouse, TEX_SIZE_FRAME);
			mOperation[1].SetUv(&mTexCameraMouse, TEX_SIZE_FRAME);
			mFlagUv = true;
		}
		/*エンター切り替え*/
		if (CKey::once(VK_RETURN)){
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
	CRectangle2::Disp2D_Start();//2D処理開始
	/*描画開始*/
	for (int i = 0; i < ARRAY_OPERA; i++){
		mOperation[i].Render();
		
	}
	/*描画終了*/
	CRectangle2::Disp2D_Exit();//2D処理終了
}
