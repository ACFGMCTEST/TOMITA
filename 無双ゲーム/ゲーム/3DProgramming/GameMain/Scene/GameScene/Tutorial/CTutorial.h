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
	E_TEX_RULE,			//0番ルール
	E_TEX_MOVE,			//1番移動説明
	E_TEX_CAMERA_KEY,	//2番カメラキー説明
	E_TEX_CAMERA_MOUSE,	//3番カメラマウス説明
	E_TEX_ATTACK_PUSH,	//4番攻撃説明
	E_TEX_ATACK_LONG,	//5番攻撃ため説明
	E_TEX_PAUZE,		//6番ポーズ説明
	};
	CTexture mTex;//テクスチャロード

	bool mFlagUv;//アップデートで張り替えるために使う

public:
	/*状態シーン 現在表示するUI*/
	enum E_TUTORIAL_STATE{
		E_RULE, //ルール説明
		E_WALK,//歩き説明
		E_CAMERA,//カメラの説明
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