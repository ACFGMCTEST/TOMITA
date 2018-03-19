//高橋弘樹
#include "CShopCreating.h"
#include"../../Key/CKey.h"
#include "../../../Define/Define.h"
#include "../../Key/CMouse.h"

#define WEAPON_NAME "weaponname.tga"
#define ARMOR_NAME "armorname.tga"


int CShopCreating::status = E_WEAPON;

CShopCreating::~CShopCreating(){
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



void CShopCreating::Init(){

	alpha = 0.0f;
	alpha2 = 0.0f;

	printf("こんにちは\n");
	printf("%d\n", status);

	switch (status)
	{
	case E_WEAPON:
		printf("Weaponです");
		//武器名前の呼び出し
		mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
		mpMenu->load(WEAPON_NAME);	//テクスチャファイル読み込み


		mWeaponName00.SetVertex(-200.0f, 200.0f, 20.0f, 130.0f);
		mWeaponName00.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		mWeaponName00.SetUv(mpMenu, TEST_CG);

		//武器名前の呼び出し
		mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
		mpMenu->load(WEAPON_NAME);	//テクスチャファイル読み込み


		mWeaponName01.SetVertex(-200.0f, 110.0f, 20.0f, 40.0f);
		mWeaponName01.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		mWeaponName01.SetUv(mpMenu, TEST_CG);

		////武器名前の呼び出し
		mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
		mpMenu->load(WEAPON_NAME);	//テクスチャファイル読み込み


		mWeaponName02.SetVertex(-200.0f, 20.0f, 20.0f, -50.0f);
		mWeaponName02.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		mWeaponName02.SetUv(mpMenu, TEST_CG);


		////武器名前の呼び出し
		mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
		mpMenu->load(WEAPON_NAME);	//テクスチャファイル読み込み


		mWeaponName03.SetVertex(-200.0f, -70.0f, 20.0f, -140.0f);
		mWeaponName03.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		mWeaponName03.SetUv(mpMenu, TEST_CG);

		////吹き出しの呼び出し
		mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
		mpMenu->load(WEAPON_NAME);	//テクスチャファイル読み込み

		mWeaponDetails.SetVertex(50.0f, 220.0f, 310.0f, -220.0f);
		mWeaponDetails.SetColor(1.0f, 1.0f, 1.0f, 0.0f);
		mWeaponDetails.SetUv(mpMenu, TEST_CG);

		break;

   case E_ARMOR:
		printf("Armorです");
		//武器名前の呼び出し
		mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
		mpMenu->load(ARMOR_NAME);	//テクスチャファイル読み込み


		mWeaponName00.SetVertex(-200.0f, 200.0f, 20.0f, 130.0f);
		mWeaponName00.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		mWeaponName00.SetUv(mpMenu, TEST_CG);

		//武器名前の呼び出し
		mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
		mpMenu->load(ARMOR_NAME);	//テクスチャファイル読み込み


		mWeaponName01.SetVertex(-200.0f, 110.0f, 20.0f, 40.0f);
		mWeaponName01.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		mWeaponName01.SetUv(mpMenu, TEST_CG);

		////武器名前の呼び出し
		mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
		mpMenu->load(ARMOR_NAME);	//テクスチャファイル読み込み


		mWeaponName02.SetVertex(-200.0f, 20.0f, 20.0f, -50.0f);
		mWeaponName02.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		mWeaponName02.SetUv(mpMenu, TEST_CG);


		////武器名前の呼び出し
		mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
		mpMenu->load(ARMOR_NAME);	//テクスチャファイル読み込み


		mWeaponName03.SetVertex(-200.0f, -70.0f, 20.0f, -140.0f);
		mWeaponName03.SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		mWeaponName03.SetUv(mpMenu, TEST_CG);

		////吹き出しの呼び出し
		mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
		mpMenu->load(ARMOR_NAME);	//テクスチャファイル読み込み

		mWeaponDetails.SetVertex(50.0f, 220.0f, 310.0f, -220.0f);
		mWeaponDetails.SetColor(1.0f, 1.0f, 1.0f, 0.0f);
		mWeaponDetails.SetUv(mpMenu, TEST_CG);

		break;
	}


	//背景の呼び出し
	mpTexture = new CTexture();	//テクスチャクラスのインスタンス作成
	mpTexture->load("testback_.tga");	//テクスチャファイル読み込み

	mBackGround.SetVertex(BG_SIZE); //ここで大きさ変更
	mBackGround.SetColor(1.0f, 1.0f, 1.0f, 0.0f);
	mBackGround.SetUv(mpTexture, 0, 0, 1024, 768);



	////戻るボタンの呼び出し
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"backbutton.tga");	//テクスチャファイル読み込み


	mBackButton.SetVertex(BACK_RECT);
	mBackButton.SetColor(1.0f, 1.0f, 0.0f, 0.5f);
	mBackButton.SetUv(mpMenu, TEST_CG);




	////作成しますか？の呼び出し
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成


	mHelp.SetVertex(-120.0f, 160.0f, 120.0f, 60.0f);
	mHelp.SetColor(0.7f, 0.7f, 1.0f, 0.8f);
	mHelp.SetUv(mpMenu, 0, 46, 250, 89);


	////はいボタンの呼び出し
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"start_menu_.tga");	//テクスチャファイル読み込み
	

	mYes.SetVertex(-280.0f, -20.0f, -30.0f, -140.0f);
	mYes.SetColor(0.7f, 0.7f, 1.0f, 0.8f);
	mYes.SetUv(mpMenu, 0, 46, 250, 89);


	////いいえボタンの呼び出し
	mpMenu = new CTexture();	//テクスチャクラスのインスタンス作成
	mpMenu->load(TGA_FILE"start_menu_.tga");	//テクスチャファイル読み込み


	mNo.SetVertex(30.0f, -20.0f, 280.0f, -140.0f);
	mNo.SetColor(0.7f, 0.7f, 1.0f, 0.8f);
	mNo.SetUv(mpMenu, 0, 46, 250, 89);




	/*カーソル四角作成*/
	mCursor.SetVertex(CURSOR_SIZE);
	mCursor.SetColor(WHITE_COLOR);


	status = 0;//デフォルトで0
}




void CShopCreating::Update(){

	mBackGround.SetColor(1.0f, 0.0f, 0.0f, 1.0f); //赤色
	mBackButton.SetColor(WHITE_COLOR); //黒色
	mWeaponName00.SetColor(WHITE_COLOR); //緑色
	mWeaponName01.SetColor(WHITE_COLOR); //青色
	mWeaponName02.SetColor(WHITE_COLOR); //白色
	mWeaponName03.SetColor(WHITE_COLOR); //灰色
	mWeaponDetails.SetColor(WHITE_COLOR); //黄色

	mCursor.position = CMouse::GetInstance()->mPos;

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

		mHelp.Render();
		mYes.Render();
		mNo.Render();



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
			//ShopCreatingbgm.stop();

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
void CShopCreating::Render() {
	CRectangle2::Disp2D_Start();//描画開始
	mBackGround.Render();
	mWeaponName00.Render();
	mWeaponName01.Render();
	mWeaponName02.Render();
	mWeaponName03.Render();
	mBackButton.Render();
	mWeaponDetails.Render();
	mCursor.Render();
	CRectangle2::Disp2D_Exit();//描画終了
	//odifit.Render();
	//thdifit.Render();
	//twdifit.Render();




}