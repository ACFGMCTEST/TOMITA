//高橋弘樹
#ifndef CQuest_HPP
#define CQuest_HPP
#include "../../../Base/CBase.h"
#include"../../Graphic/CRectangle2.h"
#include"../CScene.h"

#define BOARD 3

class CQuest :public CScene{
public:
	CRectangle2 mBG;		//（背景）

	CRectangle2 mQuestName00;	    //クエスト名
	CRectangle2 mQuestName01;
	CRectangle2 mQuestName02;
	CRectangle2 mShadow[BOARD];


	CRectangle2 mCursor;//カーソル

	CRectangle2 mBackButton;	    //戻るボタン

	CTexture	*mpTextureBG;
	CTexture	*mpTextureQUEST_NAME0;
	CTexture	*mpMenuQUEST_NAME1;
	CTexture	*mpMenuQUEST_NAME2;
	CTexture	*mpMenuBACK;
	CTexture	*mpTexCursor;

	/*クエストの状態*/
	enum E_CHOICE{
		E_QUEST00,
		E_QUEST01,
		E_QUEST02,
		E_QUEST03
	};
	static E_CHOICE eChoice;

	float alpha;
	float alpha2;

	int status;

	~CQuest();
	CQuest(){
		mpTextureBG = 0;
		mpTextureQUEST_NAME0 = 0;
		mpMenuQUEST_NAME1 = 0;
		mpMenuQUEST_NAME2 = 0;
		mpMenuBACK = 0;
		mpTexCursor = 0;
	};
	void Init();
	void Update();
	void Render();

};
#endif
