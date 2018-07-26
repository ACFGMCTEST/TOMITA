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
int  CSceneModel::mEnemyCount = 0;

//簡易リスポーン位置を決める
#define RESP(pObj,name)pObj->mPosition =  pObj->mPosition * \
		CMap::GetInstance()->Matrix(name);

/*コンストラクタ*/
CSceneModel::CSceneModel(){


}

CSceneModel *CSceneModel::mpSceneModel = 0;
//GetInstance
CSceneModel* CSceneModel::GetInstance() {
	if (mpSceneModel == 0) {
		mpSceneModel = new CSceneModel();
	}
	return mpSceneModel;
}

/*デストラクタ*/
CSceneModel::~CSceneModel(){
	

}

/*プレイヤー追加処理*/
void CSceneModel::PlayerAdd(){
	/*プレイヤーが扱うエフェクト*/
	mModEffect3D.TexDirectory(MODEL_FILE"Effect\\");
	mModEffect3D.Load(MODEL_FILE"Effect\\Effect.x");
	mModEffect3D.AddAnimationSet(MODEL_FILE"Effect\\EffectAnima.x");

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
	mModPlayer.AddAnimationSet(F_PL_SPECIAL);//スペシャル技


	CPlayer *pl = new CPlayer(); //new作成

	pl->Init(&mModPlayer);
	pl->mPosition.y = POS_Y;
	CTaskManager::GetInstance()->Add(pl);//タスクに追加
	mpPlayer = pl; //操作用
}

/*エネミー追加処理(スライム)*/
void CSceneModel::SlimeInit(){
	/*プレイヤー*/
	mModSlime.TexDirectory(MODEL_FILE"Slime\\");
	mModSlime.Load(MODEL_FILE_SLIME);


	/*アニメーション追加処理*/
	mModSlime.AddAnimationSet(F_SLI_IDLING);
	mModSlime.AddAnimationSet(F_SLI_RUN);
	mModSlime.AddAnimationSet(F_SLI_DAMAGE);
	mModSlime.AddAnimationSet(F_SLI_ATTACK);

}

/*リスポーン指定してAdd*/
CSlime *CSceneModel::SlimeAdd(char *name,CVector3 ajustPos) {
	mEnemyCount++;
	CSlime *sl;
	/*インスタンス作成*/
	sl= new CSlime();
	sl->Init(&mModSlime);
	/*pos指定*/
	RESP(sl, name);//リスポーン場所指定　
	sl->mPosition += ajustPos;
	CTaskManager::GetInstance()->Add(sl);//タスクに追加
	return sl;
}

/*キングエネミー*/
void CSceneModel::KingSlimeAdd() {
	CKingSlime *sl = new CKingSlime();
	sl->Init(&mModKingSlime);
	sl->mPosition = sl->mPosition *   CMap::GetInstance()->Matrix("Armature_KingEnemy");
	CTaskManager::GetInstance()->Add(sl);//タスクに追加
}
/*初期化処理*/
void CSceneModel::KingSlimeInit() {
	mModKingSlime.TexDirectory(MODEL_FILE"Slime\\King\\");
	mModKingSlime.Load(KING_MODEL_FILE_SLIME);

	/*アニメーション追加処理*/
	mModKingSlime.AddAnimationSet(F_SLI_KING_IDLING);
	mModKingSlime.AddAnimationSet(F_SLI_KING_RUN);
	mModKingSlime.AddAnimationSet(F_SLI_KING_DAMAGE);
	mModKingSlime.AddAnimationSet(F_SLI_KING_ATTACK);

}

void CSceneModel::Init() {
	mEnemyCount = 0;
	
	/*プレイヤー初期化*/
	PlayerAdd();
	/*エネミー*/
	SlimeInit();
	for (int i = 0; i < SLIME_MAX0; i++) {
		/*位置が被らないようにする*/
		const CVector3 pos = CVector3(5.0f * i, 0.0f, 5.0f * i);
		SlimeAdd(ENEMY_RESP_0,pos);//スライム
	}
	KingSlimeInit();//スライム

}



