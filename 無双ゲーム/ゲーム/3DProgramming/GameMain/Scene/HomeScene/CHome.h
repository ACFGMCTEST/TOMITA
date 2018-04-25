#ifndef HOME_HPP
#define HOME_HPP
#include "../TitleScene/CTitle.h"
#include "../GameMain\Graphic\CRectangle2.h"
#include "../GameMain\Scene\CScene.h"


/*ホーム画面のクラス*/
class CHome :public CTitle{
private:
	/*ポリゴン*/
	CRectangle2 mSelectButton;
	CRectangle2 mModelChangeButton;
	CRectangle2 mSelectCursor;
	/*テクスチャ*/
	CTexture	mTexSelectButton;
	CTexture	mTexModelChangeButton;
	CTexture	mTexStageCursor;

	/*シーン判断用*/
	bool mFlagScene;

	/*選択した時の関数*/
	void Select();
	/*決定された場合*/
	void SelectDecision();


	
public:

	/*シーン遷移 判断 マネージャーで呼び出す*/
	bool SceneFlag();
	eSceneNo eScene;//シーン以降変数

	CHome();
	~CHome();
	void Update();
	void Render();

};
#endif
