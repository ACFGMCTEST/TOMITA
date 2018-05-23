#include "CTutorial.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CKey.h"
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
	
}

/*更新*/
void CTutorial::Update(){

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
