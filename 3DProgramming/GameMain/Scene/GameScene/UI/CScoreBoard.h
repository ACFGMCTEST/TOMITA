//�����O��
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
	bool mFlagSceneChage;//�V�[���`�F���W����t���O
	static bool mFlagSkill0;//�X�L�����������ǂ����@�o�t�n
	static CScoreBoard *GetInstance(); //GetInstance



	~CScoreBoard();
	CScoreBoard();
	CRectangle2 mPlayer;				//PLscore0

	CRectangle2 mEnemy;					//PLscore1

	CRectangle2 mHyphen;				//SCORE�g��\������Hyphen

	CRectangle2 mVs;					//VS�}�[�N

	CRectangle2 mSkillEffect;			//�X�L���G�t�F�N�g

	CGameResult mGameResult;
	CGameClear mGameClear;
	CGameOver mGameOver;
	CCountDown mCountDown;

	CTexture   *mpNumber;				//�X�R�A

	static int mPlayerScore;
	static int mEnemyScore;
	static bool mGameEnd;//�Q�[�����I���t���O

	static bool mcFirstAction;

	const float mcGageLimit = 200.0f;	//�X�L���Q�[�W�̃��~�b�g
	const float mcAlphaMax = 1.0f;		//�F�ݒ�@���̃}�b�N�X�l
	const float mcAlphaMin = 0.0f;

	const float mcLightingBoxSize = 100.0f;	//�f�t�H���g���C�e�B���O�T�C�Y
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
	int   mFlash;						//�i���o�[�̓_�ŗp
	int   mColorChange;

	int   mGoalManager;

	const float mcLoopSpeed = 0.3f;//�O���f�[�V�����̃��[�v�X�s�[�h

	enum Goal
	{
		E_NORMAL,
		E_PLAYER,
		E_ENEMY,

	};
	bool  mInit;
	bool  mNumMin;

	//�v���C���[�X�R�A
	CRectangle2 mPlScore1;	//�ꌅ��
	CRectangle2 mPlScore2;	//�񌅖�
	CRectangle2 mPlScore3;	//�O����

	//�G�l�~�\�X�R�A
	CRectangle2 mEnScore1;	//�ꌅ��
	CRectangle2 mEnScore2;	//�񌅖�
	CRectangle2 mEnScore3;	//�O����




	CRectangle2 mBackButton;	    //�߂�{�^��


	CRectangle2 mSkillGauge;//�X�L���Q�[�W

	CRectangle2 mSkillGaugeBack;//�X�L���Q�[�W�̗��̖ډB��

	CRectangle2 mSkillGaugeEffect;//�X�L���Q�[�W�G�t�F�N�g

	CRectangle2 mGaugeFrame;//�X�L���Q�[�W�t���[��

	CRectangle2 mFrameLighting;//�t���[�����C�g



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

	int rectnum;	//�l�p�`�̐�
	int rectx;		//�l�p�`�̂����W
	int recty;		//�l�p�`�̂����W

	int difit1;
	int difit2;
	int difit3;

	static float skillgage;	//�X�L���̃Q�[�W

	float effectalpha; //�X�L���G�t�F�N�g�̃�����


	void NumberUpdate(CRectangle2 &WinScore, CRectangle2 &LoseScore, CVector2 WinPos,CVector2 LosePos);

	void Number(int Score, CRectangle2 &odifit, CRectangle2 &twdifit, CRectangle2 &thdifit);//�X�R�A�p�̐����\���̊֐�

	void TutoUpdate();

	void Init();
	void Update();
	void Render();

	/*�����蔻��
	�S�[������@����
	*/
	void GoalPlayer();
	/*�����蔻��
	�S�[������@����
	*/
	void GoalEnemy();
};
#endif
