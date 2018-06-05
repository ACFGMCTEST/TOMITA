#include <Windows.h>
#include "CSceneModel.h"
#include "../../../Task/CTaskManager.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CKey.h"
#include "../../../Collision/CCollisionManager.h"
#include "../Map/CMap.h"
#include "../../../Collision/CCollision2D.h"
#include "../../../Key/CMouse.h"
#include "../../../Convenient/CConvenient.h"
#include "../CharaDate/Enemy/Slime/CSlime.h"
#include "../CGameScene.h"



#define Char_HP_SIZE 600.0f,600.0f,0.8f,0.1f //キャラのHP
/*キャラクターのポジション*/
#define PLAYER_POS i*2,0.0f,0.0f//プレイヤーのポジション
#define ENEMY_POS  i*3.0f,0.0f,10.0f//エネミーのポジション

/*角度*/
#define ANGLE_360 360
#define ANGLE_90  90
#define ANGLE_50  50
#define ANGLE_5   5.0f
#define ANGLE_180 180.0f
/*サイズ*/
#define COL_INIT_MOUSE_SIZE -DISP_X/2, DISP_Y/2, DISP_X/2, -DISP_Y/2

/*モデルのファイル場所*/

/*プレイヤー*/
#define MODEL_FILE_UNITY		MODEL_FILE"SDUnity\\SDUnityBoxing.x"
/*アニメーションのファイル場所*/
#define F_PL_IDLING				MODEL_FILE"SDUnity\\Anima\\Idling.x"
#define F_PL_RUN				MODEL_FILE"SDUnity\\Anima\\Run.x"
#define F_PL_RUN_ATTACK			MODEL_FILE"SDUnity\\Anima\\powerRunAttack.x"
#define F_PL_ATTACK				MODEL_FILE"SDUnity\\Anima\\Attack2.x"
#define F_PL_JUMP				MODEL_FILE"SDUnity\\Anima\\Ani_Jump.x"
#define F_PL_DAMAGE				MODEL_FILE"SDUnity\\Anima\\Damage.x"

/*エネミー*/
/*スライム*/
#define MODEL_FILE_SLIME		MODEL_FILE"Slime\\Slime.x"//スライム	
#define SLIME_MAX 5//スライムの数
#define SLIME_POS(i) CVector3(i * SLIME_MAX + 10,0,i * SLIME_MAX + 10)//スライムの数
/*アニメーションのファイル場所*/
#define F_SLI_IDLING			MODEL_FILE"Slime\\Anima\\Idling.x"
#define F_SLI_RUN				MODEL_FILE"Slime\\Anima\\Run.x"
#define F_SLI_DAMAGE			MODEL_FILE"Slime\\Anima\\Damage.x"
#define F_SLI_ATTACK			MODEL_FILE"Slime\\Anima\\Attack.x"

/*lag回避用*/
#define LAG_SIZE 0.1f //0，1秒間lag回避用
/*パックの初期位置*/
#define PUCK_INIT_POS 0.0f,0.0f,-10.0f
/*静的初期化*/
CPlayer *CSceneModel::mpPlayer;

/*すべてのモデルキャラ削除*/
void CSceneModel::ModelAllKill(){
	CTaskManager::GetInstance()->AllKill();
}

/*コンストラクタ*/
CSceneModel::CSceneModel() :mMouseInitCount(0.0f),mLagTime(0.0f){


}

/*デストラクタ*/
CSceneModel::~CSceneModel(){
	

}

/*プレイヤー追加処理*/
void CSceneModel::PlayerAdd(){
	/*プレイヤー*/
	mModPlayer.Load(MODEL_FILE_UNITY);
	/*アニメーション追加処理*/
	for (int i = 0; i < CPlayer::E_STATE_ARRAY; i++)
	{
		switch (i)
		{
		case CPlayer::E_IDLING:
			mModPlayer.AddAnimationSet(F_PL_IDLING);//待機追加_0 
			break;
		case CPlayer::E_RUN:
			mModPlayer.AddAnimationSet(F_PL_RUN);//走る追加
			break;
		case CPlayer::E_RUN_ATTACK:
			mModPlayer.AddAnimationSet(F_PL_RUN_ATTACK);//走り攻撃
			break;
		case CPlayer::E_ATTACK:
			mModPlayer.AddAnimationSet(F_PL_ATTACK);//攻撃追加_2 
			break;
		case CPlayer::E_JUMP:
			mModPlayer.AddAnimationSet(F_PL_JUMP);//ジャンプ追加
			break;
		case CPlayer::E_DAMAGE:
			mModPlayer.AddAnimationSet(F_PL_DAMAGE);//ダメージ
			break;
		}
	}

	CPlayer *pl = new CPlayer(); //new作成

	pl->Init(&mModPlayer);
	CTaskManager::GetInstance()->Add(pl);//タスクに追加
	mpPlayer = pl; //操作用
}

/*エネミー追加処理(スライム)*/
void CSceneModel::SlimeAdd(){
	/*コピー用*/
	CModelX *temp = &mModSlime;
	/*プレイヤー*/
	temp->Load(MODEL_FILE_SLIME);
	/*アニメーション追加処理*/
	for (int i = 0; i < CSlime::E_STATE_ARRAY; i++)
	{
		CSlime::E_STATE state = (CSlime::E_STATE)i;
		switch (state)
		{
		case CSlime::E_IDLING:
			temp->AddAnimationSet(F_SLI_IDLING);
			break;
		case CSlime::E_RUN:
			temp->AddAnimationSet(F_SLI_RUN);
			break;
		case CSlime::E_DAMAGE:
			temp->AddAnimationSet(F_SLI_DAMAGE);
			break;
		case CSlime::E_ATTACK:
			temp->AddAnimationSet(F_SLI_ATTACK);
			break;
		};
	}

	CSlime *sl[SLIME_MAX];
	for (int i = 0; i < SLIME_MAX; i++)
	{
		/*インスタンス作成*/
		sl[i] = new CSlime();
		sl[i]->Init(temp);
		sl[i]->mPosition = SLIME_POS(i);
		CTaskManager::GetInstance()->Add(sl[i]);//タスクに追加
	}
}

void CSceneModel::Init() {
	mMouseInitCount = 0.0f;							//マウスが初期位置に戻るまでの時間
	mLagTime = 0.0f;								//lagによるバグ回避時間

	
	/*プレイヤー初期化*/
	PlayerAdd();
	/*エネミー*/
	SlimeAdd();//スライム


}

void CSceneModel::Update() {
	/*lag回避*/
	if (!CConvenient::Time(&mLagTime, LAG_SIZE)){
		CMouse::GetInstance()->mLeftFlag = false;
	}

	CTaskManager::GetInstance()->AllUpdate();
}

void CSceneModel::Render() {
	CTaskManager::GetInstance()->AllRender();
}
