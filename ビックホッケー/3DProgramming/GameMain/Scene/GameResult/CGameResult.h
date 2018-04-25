//高橋弘樹
#ifndef CGAMERESULT_HPP
#define CGAMERESULT_HPP
#include"../../../Base/CBase.h"
#include "../../Graphic/CRectangle2.h"
#include"../CScene.h"
#include "../ItemScene/CItem.h"

#define DIGIT 3 //桁数
#define TIPS  4
#define NUM_SIZE -40,40,40,-40

#define PRIZE0 10 * 2
#define PRIZE1 20 * 2
#define PRIZE2 30 * 2
#define PRIZE3 40 * 2


//Result画面
//クエストで入手した金額の計算を行い加算する
//クエストの金額ｘ点数の差分
//0-5の場合５倍　２－５の場合３倍

class CGameResult :public CScene{


public:

	CItem mItem;

	CRectangle2 mBG;                    //バックグラウンドの略 （背景)
	CRectangle2 mResult;	            //リザルト
	CRectangle2 mQuestName;	            //クエスト名ロゴ
	CRectangle2 mBaseMoney    [DIGIT];  //元となる金額
	CRectangle2 mMagnification[DIGIT];  //報酬にかかる倍率
	CRectangle2 mTotalMoney   [DIGIT];  //元金と倍率を計算した結果。最終的に手に入る金額を表示する
	CRectangle2 mPocketMoney  [DIGIT];  //所持金の表示
	CRectangle2 mTips         [TIPS];

	CRectangle2 mCursor;//カーソル


	CTexture	*mpTexture;
	CTexture	*mpMenu;
	CTexture	*mpNumber;

	int difit1;
	int difit2;
	int difit3;

	static int mPrize;

	float mNumCount;

	int mQuestMoney; //クエスト固有の報酬

	int mDifference; //相手とのスコアの差分を保存して倍率として扱う
	
	int  mTotal; //元金と倍率を計算した結果

	float mPocketMoneySave;

	float mAlpha = 0.0f;

	static bool mFlagResult;//フラグが立つと更新処理

	enum EPrize{
		E_Quest0,
		E_Quest1,
		E_Quest2,
		E_Quest3,
	};



	/*状態選択*/
	enum EStatus
	{
		E_GAMESTART,
		E_GAMEEXIT
	};
	EStatus eStatus;

	~CGameResult();
	CGameResult();
	
	void Number(int score, CRectangle2 &odifit, CRectangle2 &twdifit, CRectangle2 &thdifit);
	void Init();
	void Update();
	void Render();

};
#endif
