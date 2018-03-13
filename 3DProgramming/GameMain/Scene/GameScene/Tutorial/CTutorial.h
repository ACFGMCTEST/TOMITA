#ifndef TUTORIAL_HPP
#define TUTORIAL_HPP

#include "../../../Graphic/CRectangle2.h"
#define ARRAY_OPERA 2//説明の数

class CTutorial{
private:
	/*ポリゴン*/
	CRectangle2 mOperation[ARRAY_OPERA];//操作説明文字
	/*テクスチャ*/
	CTexture mTexFrame;//枠のテクスチャ
	CTexture mTexOperation;//操作説明文字のテクスチャ
	CTexture mTexWalk;//歩き説明
	CTexture mTexCameraKey;//カメラ説明(矢印)
	CTexture mTexCameraMouse;//カメラ説明(矢印)
	bool mFlagUv;//アップデートで張り替えるために使う

public:
	/*状態シーン 現在表示するUI*/
	enum E_TUTORIAL_STATE{
		E_RULE, //ルール説明
		E_WALK,//歩き説明
		E_ATTACK,//操作説明
		E_PAUZE,//ポーズ説明
		E_ARRAY,//enumの数
	};
	E_TUTORIAL_STATE eTutoState;//Tutorialの現在の状態

	CTutorial();
	~CTutorial();

	void Init();
	void Update();
	void Render();

};

#endif