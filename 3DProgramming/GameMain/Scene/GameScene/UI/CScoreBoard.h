//高橋弘樹
#ifndef CSCOREBOARD_HPP
#define CSCOREBOARD_HPP
#include "../../../Graphic/CRectangle2.h"
#include "../../GameClearScene/CGameClear.h"
#include "../../GameOverScene/CGameOver.h"
#include "../../CountDown/CCountDown.h"
#include "../../GameResult/CGameResult.h"
#include "../Tutorial/CTutorial.h"

#define BGM_GAGE 9
#define SE_GAGE 9

class CScoreBoard{
private:
	static CScoreBoard *mSceneManager;

	CTutorial mTutorial;

public:
	bool mFlagSceneChage;//シーンチェンジするフラグ
	static bool mFlagSkill0;//スキル発動中かどうか　バフ系
	static CScoreBoard *GetInstance(); //GetInstance



	~CScoreBoard();
	CScoreBoard();
	CRectangle2 mPlayer;				//PLscore0

	CRectangle2 mEnemy;					//PLscore1

	CRectangle2 mHyphen;				//SCORE拡大表示時のHyphen

	CRectangle2 mVs;					//VSマーク

	CRectangle2 mSkillEffect;			//スキルエフェクト

	CGameResult mGameResult;
	CGameClear mGameClear;
	CGameOver mGameOver;
	CCountDown mCountDown;

	CTexture   *mpNumber;				//スコア

	static int mPlayerScore;
	static int mEnemyScore;
	static bool mGameEnd;//ゲームを終了フラグ

	static bool mcFirstAction;

	const float mcGageLimit = 200.0f;	//スキルゲージのリミット
	const float mcAlphaMax = 1.0f;		//色設定　αのマックス値
	const float mcAlphaMin = 0.0f;

	const float mcLightingBoxSize = 100.0f;	//デフォルトライティングサイズ
	float mLightingSize = mcLightingBoxSize;


	const float mcDefaultNumX = 20.0f;
	const float mcDefaultNumY = 17.5f;

	float mNumRectX;						//
	float mNumRectY;

	float mSkillCollarR=1.0f;
	float mSkillCollarG=1.0f;
	float mSkillCollarB=1.0f;
	bool  mSkillCollarUnder=false;

	const int   mcNumSizeLimit = 5;
	int   mFlash;						//ナンバーの点滅用
	int   mColorChange;

	int   mGoalManager;

	const float mcLoopSpeed = 0.3f;//グラデーションのループスピード

	enum Goal
	{
		E_NORMAL,
		E_PLAYER,
		E_ENEMY,

	};
	bool  mInit;
	bool  mNumMin;

	//プレイヤースコア
	CRectangle2 mPlScore1;	//一桁目
	CRectangle2 mPlScore2;	//二桁目
	CRectangle2 mPlScore3;	//三桁目

	//エネミ―スコア
	CRectangle2 mEnScore1;	//一桁目
	CRectangle2 mEnScore2;	//二桁目
	CRectangle2 mEnScore3;	//三桁目




	CRectangle2 mBackButton;	    //戻るボタン


	CRectangle2 mSkillGauge;//スキルゲージ

	CRectangle2 mSkillGaugeBack;//スキルゲージの裏の目隠し

	CRectangle2 mSkillGaugeEffect;//スキルゲージエフェクト

	CRectangle2 mGaugeFrame;//スキルゲージフレーム

	CRectangle2 mFrameLighting;//フレームライト



	CTexture	*mpTextureSkillEffect1;
	CTexture	*mpTextureP_Name;
	CTexture	*mpTextureE_Name;
	CTexture	*mpTexturevs;
	CTexture	*mpGauge;
	CTexture	*mpMenu;
	CTexture    *mpFrame;
	CTexture    *mpLighting;
	CTexture    *mpHyphen;


	float mAlpha;
	float alpha2;

	int status;

	int rectnum;	//四角形の数
	int rectx;		//四角形のｘ座標
	int recty;		//四角形のｙ座標

	int difit1;
	int difit2;
	int difit3;

	static float skillgage;	//スキルのゲージ

	float effectalpha; //スキルエフェクトのα制御


	void NumberUpdate(CRectangle2 &WinScore, CRectangle2 &LoseScore, CVector2 WinPos,CVector2 LosePos);

	void Number(int Score, CRectangle2 &odifit, CRectangle2 &twdifit, CRectangle2 &thdifit);//スコア用の数字表示の関数

	void TutoUpdate();

	void Init();
	void Update();
	void Render();

	/*当たり判定
	ゴール判定　自分
	*/
	void GoalPlayer();
	/*当たり判定
	ゴール判定　相手
	*/
	void GoalEnemy();
};
#endif
