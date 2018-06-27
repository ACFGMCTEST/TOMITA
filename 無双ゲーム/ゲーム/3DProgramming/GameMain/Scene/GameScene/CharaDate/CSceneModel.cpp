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

/*キャラクター*/
#include "../CharaDate/Enemy/Slime/CSlime.h"
#include "../CharaDate/Enemy/Slime/King/CKingSlime.h"

#include "../CGameScene.h"



#define Char_HP_SIZE 600.0f,600.0f,0.8f,0.1f //キャラのHP
/*キャラクターのポジション*/
#define POS_Y 10

/*角度*/
#define ANGLE_360 360
#define ANGLE_90  90
#define ANGLE_50  50
#define ANGLE_5   5.0f
#define ANGLE_180 180.0f
/*サイズ*/
#define COL_INIT_MOUSE_SIZE -DISP_X/2, DISP_Y/2, DISP_X/2, -DISP_Y/2

/*lag回避用*/
#define LAG_SIZE 0.1f //0，1秒間lag回避用
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
	mModPlayer.TexDirectory(MODEL_FILE"SDUnity\\");
	mModPlayer.Load(MODEL_FILE_UNITY);

	mModPlayer.AddAnimationSet(F_PL_IDLING);//待機追加_0 
	mModPlayer.AddAnimationSet(F_PL_RUN);//走る追加
	mModPlayer.AddAnimationSet(F_PL_ATTACK);//攻撃追加_2 
	mModPlayer.AddAnimationSet(F_PL_RUN_ATTACK);//走り攻撃
	mModPlayer.AddAnimationSet(F_PL_JUMP);//ジャンプ追加
	mModPlayer.AddAnimationSet(F_PL_DAMAGE);//ダメージ
	mModPlayer.AddAnimationSet(F_PL_DIED);//死亡
	mModPlayer.AddAnimationSet(F_PL_AVOID);//回避

	CPlayer *pl = new CPlayer(); //new作成

	pl->Init(&mModPlayer);
	pl->mPosition.y = POS_Y;
	CTaskManager::GetInstance()->Add(pl);//タスクに追加
	mpPlayer = pl; //操作用
}

/*エネミー追加処理(スライム)*/
void CSceneModel::SlimeAdd(){
	/*コピー用*/
	CModelX *temp = &mModSlime;
	/*プレイヤー*/
	temp->TexDirectory(MODEL_FILE"Slime\\");
	temp->Load(MODEL_FILE_SLIME);


	/*アニメーション追加処理*/
	temp->AddAnimationSet(F_SLI_IDLING);
	temp->AddAnimationSet(F_SLI_RUN);
	temp->AddAnimationSet(F_SLI_DAMAGE);
	temp->AddAnimationSet(F_SLI_ATTACK);


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

/*キングエネミー*/
void CSceneModel::KingSlimeAdd() {
	mModKingSlime.TexDirectory(MODEL_FILE"Slime\\King\\");
	mModKingSlime.Load(KING_MODEL_FILE_SLIME);

	/*アニメーション追加処理*/
	mModKingSlime.AddAnimationSet(F_SLI_KING_IDLING);
	mModKingSlime.AddAnimationSet(F_SLI_KING_RUN);
	mModKingSlime.AddAnimationSet(F_SLI_KING_DAMAGE);
	mModKingSlime.AddAnimationSet(F_SLI_KING_ATTACK);

	CKingSlime *sl = new CKingSlime();
	sl->Init(&mModKingSlime);
	sl->mPosition = sl->mPosition *   CMap::GetInstance()->mRespawn;
	CTaskManager::GetInstance()->Add(sl);//タスクに追加
}

void CSceneModel::Init() {
	mMouseInitCount = 0.0f;							//マウスが初期位置に戻るまでの時間
	mLagTime = 0.0f;								//lagによるバグ回避時間

	
	/*プレイヤー初期化*/
	PlayerAdd();
	/*エネミー*/
	SlimeAdd();//スライム
	KingSlimeAdd();//スライム

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
