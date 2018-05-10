//高橋弘樹
#include"COption.h"
#include"../../Key/CKey.h"
#include"../../Key/CMouse.h"
#include <fstream> 
#include<stdio.h>

#define DISP_2D_Y 768 //縦幅

#define BACK_GROUND     -400.0f, 300.0f, 400.0f, -300.0f
///////////////////////////////////////
//BGM
#define BGM_BOX	-300.0f, 220.0f,    0.0f, 30.0f
#define BGM_MIN	-20.0f,  40.0f, 20.0f,   -40.0f
#define BGM_MAX -20.0f,  40.0f, 20.0f,   -40.0f
///////////////////////////////////////
//SE
#define SE_BOX	-300.0f, 20.0f,	  0.0f,   -170.0f
#define SE_MIN	-20.0f,  40.0f, 20.0f,   -40.0f
#define SE_MAX	-20.0f,  40.0f, 20.0f,   -40.0f
///////////////////////////////////////
//その他
#define GAGE_ICON	      -20.0f,  40.0f, 20.0f,   -40.0f
#define BACK_BUTTON		-320.0f, -180.0f, -220.0f, -240.0f

#define FIRST_X	100			//アイコンの初期ｘ値
#define FIRST_Y	180		//アイコンの初期ｙ値
#define RECT_WIDE 3

#define ITEM_MENU	  TGA_FILE"itembutton.tga"
#define BACK	  TGA_FILE"backbutton.tga"


/*texフェイル*/
#define CURSOR_CG 0,0,150,120


COption::COption() :rectnum(0){
	rectx = FIRST_X;
	recty = FIRST_Y;
}

COption::~COption(){
	if (mpTexture) {
		//テクスチャを使っていればインスタンス削除
		delete mpTexture;
		mpTexture = 0;
	}
	if (mpMenu) {
		//テクスチャを使っていればインスタンス削除
		delete mpMenu;
		mpMenu = 0;
	}
}

void COption::Init(){

	alpha = 0.0f;
	alpha2 = 0.0f;




	//背景の呼び出し
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load(TGA_FILE"testback_.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*gluOrtho2D(-320.0f, 320.0f, -340.0f, 340.0f);*/
	mBackGround.SetVertex(BACK_GROUND); //ここで大きさ変更
	mBackGround.SetColor(RED_COLOR);
	mBackGround.SetUv(mpTexture, 0, 0, 1024, 768);

//////////////////////////////////////////////////////////////////////////////////
	//BGM
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"start_menu_.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mBgmBox.SetVertex(BGM_BOX);
	mBgmBox.SetColor(GREEN_COLOR);
	mBgmBox.SetUv(mpMenu, 0, 0, 250, 46);
	//mSelectOutfit.position();

	//SE
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"start_menu_.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mSeBox.SetVertex(SE_BOX);
	mSeBox.SetColor(YELLOW_COLOR);
	mSeBox.SetUv(mpMenu, 0, 46, 250, 89);


/////////////////////////////////////////////////////////////////////////////////////////
	//BGM_MAX
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"start_menu_.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mBgmMax.SetVertex(BGM_MAX);
	mBgmMax.SetColor(NOTHING_COLOR);
	mBgmMax.SetUv(mpMenu, 0, 46, 250, 89);

	//BGM_MIN
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"start_menu_.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mBgmMin.SetVertex(BGM_MIN);
	mBgmMin.SetColor(NOTHING_COLOR);
	mBgmMin.SetUv(mpMenu, 0, 46, 250, 89);

///////////////////////////////////////////////////////////////////////////////////////

	//SE_MAX
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"start_menu_.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mSeMax.SetVertex(SE_MAX);
	mSeMax.SetColor(NOTHING_COLOR);
	mSeMax.SetUv(mpMenu, 0, 46, 250, 89);

	//SE_MIN
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"start_menu_.tga");	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mSeMin.SetVertex(SE_MIN);
	mSeMin.SetColor(NOTHING_COLOR);
	mSeMin.SetUv(mpMenu, 0, 46, 250, 89);



///////////////////////////////////////////////////////////////////////////////////////////



	////戻るボタンの呼び出し
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(BACK);	//テクスチャファイル読み込み
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-320.0f, 320.0f, -240.0f, 240.0f);
	mBackButton.SetVertex(BACK_RECT);
	mBackButton.SetColor(1.0f, 1.0f, 0.0f, 0.5f);
	mBackButton.SetUv(mpMenu, TEST_CG);



///////////////////////////////////////////////////////////////////////////////////////////
	int rectcnt = BGM_GAGE;

	for (int i = 0; i < BGM_GAGE; i++){
		printf("%d\n", i);

		rectcnt--;
		//BGMゲージ
		mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
		mpMenu->load("not_image");	//テクスチャファイル読み込み
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		mBgmGage[i].SetVertex(GAGE_ICON);
		mBgmGage[i].SetColor (PINK_COLOR);
		mBgmGage[i].position = CVector2(rectx, recty);
		mBgmGage[i].SetUv    (mpMenu, TEST_CG);


		//SEゲージ
		mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
		mpMenu->load("not_image");	//テクスチャファイル読み込み
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		mSeGage[i].SetVertex(GAGE_ICON);
		mSeGage[i].SetColor (WHITE_COLOR);
		mSeGage[i].position = CVector2(rectx,-100);
		mSeGage[i].SetUv    (mpMenu, TEST_CG);

		rectx += 50.0f;
		if (rectcnt == 0){ rectx = FIRST_X;  rectcnt = RECT_WIDE; };

	}

	


	/*カーソル四角作成*/
	mpTexCursor = new CTexture();
	mpTexCursor->load(TGA_FILE"cursor.tga");
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);
	mCursor.SetUv(mpTexCursor, CURSOR_CG);

	status = 0;//デフォルトで0

}




void COption::Update(){


	mBackButton.SetColor(WHITE_COLOR);		   //黒色

	mCursor.position = CMouse::mPos;

	//メニュー画面での選択。２項目しかないからstatus移動もここでやる

	if (CKey::once(UP_KEY)){
		//cursorchange.play();
		//mCursor.SetVertex(-180.0f, -90.0f, -140.0f, -130.0f);
		/*	status = 0;*/
	}

	if (CKey::once(DOWN_KEY)){
		/*	cursorchange.play();
		mCursor.SetVertex(-180.0f, -170.0f, -140.0f, -210.0f);*/
		/*status = 1;*/
	}

	//促す
	if (CKey::push(ENTER_KEY))
	{
		//作成しますか？とはい　いいえを表示する

		/*mHelp.Render();
		mYes.Render();
		mNo.Render();*/



	}

	switch (status)
	{
	case 0:
		//mGameStart.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		//mGameExit.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		if (CKey::push(ENTER_KEY))
		{
			//SE再生
			//returnkey.play();

			//BGMをストップする
			//Itembgm.stop();

			//CSceneManager::GetInstance()->ChangeScene(SceneNo::GAME_MAIN);	//ゲーム画面に移行します。

		}
		break;
	case 1:
		//mGameStart.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		//mGameExit.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

		if (CKey::push(ENTER_KEY))
		{
			//SEの再生
			/*	returnkey.play();*/

			exit(0);	//ゲームを終了します。

		}

		break;
	}


};

/*
描画処理のみを行う。
*/
void COption::Render() {
	CRectangle2::Disp2D_Start();//描画開始
	mBackGround.Render();
	mBgmBox.Render();
	mSeBox.Render();

	mBgmMin.Render();
	mBgmMax.Render();

	mSeMin.Render();
	mSeMax.Render();


	for (int i = 0; i <= BGM_GAGE; i++) {

		mBgmGage[i].Render();
	};
	for (int i = 0; i <= SE_GAGE; i++) {

		mSeGage[i].Render();
	};

	mBackButton.Render();

	mCursor.Render();
	CRectangle2::Disp2D_Exit();//描画終了




	/*mSelectOutfitDetails.	Render();*/
	//odifit.Render();
	//thdifit.Render();
	//twdifit.Render();




}