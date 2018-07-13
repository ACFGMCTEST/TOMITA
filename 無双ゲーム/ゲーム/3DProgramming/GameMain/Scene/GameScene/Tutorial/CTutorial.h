#ifndef TUTORIAL_HPP
#define TUTORIAL_HPP

#include "../../../Graphic/CRectangle2.h"
#define ARRAY_OPERA 2//説明の数
class CTutorial{
private:
	static CTutorial *mpTutorial;
	CVector3 mPos;//はじめのポジション
	CTutorial();

	/*表示するテキスト並び順*/
	enum ESTATE {
		ALL_ENE_KILL,	//すべての敵を倒せ
		MOVE,		//移動とカメラ説明
		BLOW_OFF,	//吹き飛ばした時の説明
		ATTACK_AVOID,	//攻撃と回避説明
		HIGH_HILL_SLI,	//高台スライム倒す誘導
		JUMP,		//ジャンプ説明
		PUSH_OFF,	//高台から突き落とした時の説明
		KING_KILL,	//親玉倒す
		SPECIAL_ATTACK,	//必殺技説明
		ARRAY
	};
	ESTATE eState;//Tutorialの現在の状態
	/*ポリゴン*/
	CRectangle2 mRect;//操作説明文字
	CRectangle2 mBG;//文字背景BG
	/*テクスチャ*/
	CTexture mTex;
	CTexture mTexBG;
	/*テクスチャの種類わけ*/
	STexVer mVer[ARRAY];
	/*タイム*/
	float mTime;
	bool mFlagUv;//アップデートで張り替えるために使う
public:
	static CTutorial *GetInstance();

	~CTutorial();

	void Init();
	/*文字切り替え*/
	void Change();
	void Update();
	void Render();
};

#endif