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
#define MODEL_FILE_UNITY		"x\\SDUnity\\SDUnityBoxing.x"
/*アニメーションのファイル場所*/
#define F_PL_IDLING				"x\\Anima\\Idling.x"
#define F_PL_RUN				"x\\Anima\\Run.x"
#define F_PL_RUN_ATTACK			"x\\Anima\\powerRunAttack.x"
#define F_PL_ATTACK				"x\\Anima\\Attack2.x"
#define F_PL_ATTACK_JUMP		"x\\Anima\\Ani_AttackJump.x"
#define F_PL_JUMP				"x\\Anima\\Ani_Jump.x"
#define F_PL_DAMAGE				"x\\Anima\\Ani_Damage.x"

/*エネミー*/
/*スライム*/
#define MODEL_FILE_SLIME		"x\\Slime\\Slime.x"//スライム	
#define SLIME_MAX 10//スライムの数
#define SLIME_POS(i) CVector3(i * SLIME_MAX,0,i * SLIME_MAX)//スライムの数
/*アニメーションのファイル場所*/
#define F_SLI_IDLING			"x\\Slime\\Anima\\Idling.x"
#define F_SLI_RUN				"x\\Slime\\Anima\\Run.x"
#define F_SLI_ATTACK			"x\\Slime\\Anima\\Attack2.x"
#define F_SLI_JUMP				"x\\Slime\\Anima\\Ani_Jump.x"
#define F_SLI_DAMAGE			"x\\Slime\\Anima\\Ani_Damage.x"

/*lag回避用*/
#define LAG_SIZE 0.1f //0，1秒間lag回避用
/*パックの初期位置*/
#define PUCK_INIT_POS 0.0f,0.0f,-10.0f
/*静的初期化*/
CXCharPlayer *CSceneModel::mpPlayer;

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
	for (int i = 0; i < CTask::E_STATE_ARRAY; i++)
	{
		switch (i)
		{
		case CTask::E_IDLING:
			mModPlayer.AddAnimationSet(F_PL_IDLING);//待機追加_0 
			break;
		case CTask::E_RUN:
			mModPlayer.AddAnimationSet(F_PL_RUN);//走る追加
			break;
		case CTask::E_RUN_ATTACK:
			mModPlayer.AddAnimationSet(F_PL_RUN_ATTACK);//走り攻撃
			break;
		case CTask::E_ATTACK:
			mModPlayer.AddAnimationSet(F_PL_ATTACK);//攻撃追加_2 
			break;
		case CTask::E_JUMP:
			mModPlayer.AddAnimationSet(F_PL_JUMP);//ジャンプ追加
			break;
		case CTask::E_DMGM:
			mModPlayer.AddAnimationSet(F_PL_DAMAGE);//ダメージ
			break;
		}
	}

	CXCharPlayer *pl = new CXCharPlayer(); //new作成

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
	for (int i = 0; i < CTask::E_STATE_ARRAY; i++)
	{
		switch (i)
		{
		case CTask::E_IDLING:
			temp->AddAnimationSet(F_SLI_IDLING);//待機追加_0 
			break;
		case CTask::E_RUN:
			temp->AddAnimationSet(F_SLI_RUN);//走る追加
			break;
		case CTask::E_ATTACK:
			temp->AddAnimationSet(F_SLI_ATTACK);//攻撃追加_2 
			break;
		case CTask::E_JUMP:
			temp->AddAnimationSet(F_SLI_JUMP);//ジャンプ追加
			break;
		case CTask::E_DMGM:
			temp->AddAnimationSet(F_SLI_DAMAGE);//ダメージ
			break;
		}
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

	CVector3 mPosition;								//位置　

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

void CSceneModel::UpdateEffect(){
	CTaskManager::GetInstance()->AllBillboardRender();
}