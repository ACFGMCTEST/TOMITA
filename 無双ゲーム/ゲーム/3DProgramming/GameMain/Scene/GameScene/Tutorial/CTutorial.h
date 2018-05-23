#ifndef TUTORIAL_HPP
#define TUTORIAL_HPP

#include "../../../Graphic/CRectangle2.h"
#define ARRAY_OPERA 2//説明の数

class CTutorial{
private:
	/*ポリゴン*/
	CRectangle2 mOperation[ARRAY_OPERA];//操作説明文字
	/*テクスチャ*/

	/*テクスチャの配列番号*/
	enum E_TEX{
		E_TEX_WALK,//歩く　
		E_TEX_ATTTACK,//攻撃
		E_TEX_JUMP,//ジャンプ
		E_TEX_SPECIAL,//必殺技
	};
	CTexture mTex;//テクスチャロード

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